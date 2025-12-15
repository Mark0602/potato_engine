#include "potato-render.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

static bool load_binary_file(const char* filename, std::vector<uint8_t>& out_data)
{
    // Hardcode the assets path for now
    std::string assetsPath = "assets/shaders/";

    std::string fullPath = assetsPath + filename;

    std::cout << "[load_binary_file] Loading: " << fullPath << "\n";
    std::ifstream file(fullPath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "[pipeline] Failed to open shader file: " << fullPath << "\n";
        return false;
    }

    std::streamsize size = file.tellg();
    if (size <= 0) {
        std::cerr << "[pipeline] Shader file is empty: " << fullPath << "\n";
        file.close();
        return false;
    }

    out_data.resize(static_cast<size_t>(size));
    file.seekg(0, std::ios::beg);

    if (!file.read(reinterpret_cast<char*>(out_data.data()), size)) {
        std::cerr << "[pipeline] Failed to read shader file: " << fullPath << "\n";
        file.close();
        return false;
    }

    file.close();
    std::cout << "[load_binary_file] Successfully loaded " << filename << " (" << size << " bytes)\n";
    return true;
}

potato_render::potato_render(SDL_Window* window, SDL_GPUDevice* device, SDL_Renderer* renderer)
    : renderer(renderer)
    , window(window)
    , device(device)
    , default_color_pipeline(nullptr)
{
    std::cout << "[potato_render] constructor: window=" << (void*)window << " device=" << (void*)device << " renderer=" << (void*)renderer << "\n";

    if (!this->device || !this->window) {
        std::cerr << "[potato_render] invalid device/window\n";
        return;
    }

    std::cout << "[potato_render] calling init_default_pipeline()..." << std::endl;
    if (!init_default_pipeline()) {
        std::cerr << "[potato_render] WARNING: default pipeline init failed\n";
    } else {
        std::cout << "[potato_render] init_default_pipeline() succeeded" << std::endl;
    }
}

potato_render::~potato_render() {
    destroy_pipelines();
    vertex_buffers.clear();
}

void potato_render::render() {
    if (!device || !window) {
        std::cerr << "[render] device or window is null\n";
        return;
    }

    SDL_GPUCommandBuffer* cmdbuf = SDL_AcquireGPUCommandBuffer(this->device);
    if (cmdbuf == nullptr) {
        std::cerr << "[render] Failed to acquire command buffer\n";
        return;
    }

    SDL_GPUTexture* swapchain_texture;
    uint32_t w, h; 
    if (!SDL_WaitAndAcquireGPUSwapchainTexture(cmdbuf, this->window, &swapchain_texture, &w, &h)) {
        std::cerr << "[render] Failed to acquire swapchain texture: " << SDL_GetError() << "\n";
        SDL_SubmitGPUCommandBuffer(cmdbuf);
        return;
    }

    if (swapchain_texture == nullptr) {
        std::cerr << "[render] Swapchain texture is null\n";
        SDL_SubmitGPUCommandBuffer(cmdbuf);
        return;
    }

    //std::cout << "[render] Command buffer: " << cmdbuf << std::endl;
    //std::cout << "[render] Render pass texture: " << swapchain_texture << std::endl;

    // Update vertex buffers BEFORE starting render pass
    for (const auto& item : vertex_buffers) {
        if (item) {
            item->update_gpu_buffer(cmdbuf);
        }
    }

    SDL_GPUColorTargetInfo color_target = {};
    color_target.texture      = swapchain_texture;
    color_target.clear_color  = {0.0f, 0.0f, 0.0f, 1.0f};
    color_target.load_op      = SDL_GPU_LOADOP_CLEAR;
    color_target.store_op     = SDL_GPU_STOREOP_STORE;

    SDL_GPURenderPass* render_pass = SDL_BeginGPURenderPass(
        cmdbuf,
        &color_target,
        1,
        nullptr
    );

    if (!render_pass) {
        std::cerr << "[render] Failed to begin render pass: " << SDL_GetError() << "\n";
        SDL_SubmitGPUCommandBuffer(cmdbuf);
        return;
    }

    if (default_color_pipeline) {
        SDL_BindGPUGraphicsPipeline(render_pass, default_color_pipeline);

        for (const auto& item : vertex_buffers) {
            if (!item) continue;

            SDL_GPUBuffer* gpu_buffer = item->get_gpu_buffer();
            if (!gpu_buffer) continue;

            SDL_GPUBufferBinding vertex_binding{};
            vertex_binding.buffer = gpu_buffer;
            vertex_binding.offset = 0;

            SDL_BindGPUVertexBuffers(
                render_pass,
                0,                  // first_slot
                &vertex_binding,
                1                   // num_bindings
            );

            SDL_DrawGPUPrimitives(
                render_pass,
                3,
                0,
                static_cast<Uint32>(item->get_vertex_count()),
                1
            );
        }
    }

    SDL_EndGPURenderPass(render_pass);
    SDL_SubmitGPUCommandBuffer(cmdbuf);

    // Present the swapchain
    //SDL_GPU_Present(device, window);

    // Clear the vertex buffers list for next frame
    vertex_buffers.clear();
}

bool potato_render::init_default_pipeline()
{
    std::cout << "[pipeline] init_default_pipeline() start" << std::endl;
    if (!device) {
        std::cerr << "[pipeline] device is not initialized\n";
        return false;
    }

    std::cout << "[pipeline] loading shader binaries..." << std::endl;
    std::vector<uint8_t> vs_code;
    std::vector<uint8_t> ps_code;

    if (!load_binary_file("default_color_vs.spv", vs_code)) {
        std::cerr << "[pipeline] Failed to load vertex shader\n";
        return false;
    }
    std::cout << "[pipeline] Vertex shader loaded OK (" << vs_code.size() << " bytes)\n";

    if (!load_binary_file("default_color_ps.spv", ps_code)) {
        std::cerr << "[pipeline] Failed to load pixel shader\n";
        return false;
    }
    std::cout << "[pipeline] Pixel shader loaded OK (" << ps_code.size() << " bytes)\n";

    if (vs_code.empty() || ps_code.empty()) {
        std::cerr << "[pipeline] Shader code is empty (vs: " << vs_code.size() 
                  << " bytes, ps: " << ps_code.size() << " bytes)\n";
        return false;
    }

    SDL_GPUShaderCreateInfo vs_info{};
    vs_info.code                 = vs_code.data();
    vs_info.code_size            = vs_code.size();
    vs_info.entrypoint           = "main";
    vs_info.format               = SDL_GPU_SHADERFORMAT_SPIRV;
    vs_info.stage                = SDL_GPU_SHADERSTAGE_VERTEX;
    vs_info.num_samplers         = 0;
    vs_info.num_storage_buffers  = 0;
    vs_info.num_storage_textures = 0;
    vs_info.num_uniform_buffers  = 0;

    std::cout << "[pipeline] Creating VS with " << vs_info.code_size << " bytes...\n";
    SDL_GPUShader* vs = SDL_CreateGPUShader(device, &vs_info);
    if (!vs) {
        std::cerr << "[pipeline] Failed to create VS: " << SDL_GetError() << "\n";
        return false;
    }
    std::cout << "[pipeline] VS created OK\n";

    SDL_GPUShaderCreateInfo ps_info{};
    ps_info.code                 = ps_code.data();
    ps_info.code_size            = ps_code.size();
    ps_info.entrypoint           = "main";
    ps_info.format               = SDL_GPU_SHADERFORMAT_SPIRV;
    ps_info.stage                = SDL_GPU_SHADERSTAGE_VERTEX;
    ps_info.num_samplers         = 0;
    ps_info.num_storage_buffers  = 0;
    ps_info.num_storage_textures = 0;
    ps_info.num_uniform_buffers  = 0;

    std::cout << "[pipeline] Creating PS with " << ps_info.code_size << " bytes...\n";
    SDL_GPUShader* ps = SDL_CreateGPUShader(device, &ps_info);
    if (!ps) {
        std::cerr << "[pipeline] Failed to create PS: " << SDL_GetError() << "\n";
        SDL_ReleaseGPUShader(device, vs);
        return false;
    }
    std::cout << "[pipeline] PS created OK\n";

    SDL_GPUVertexAttribute attributes[2]{};

    attributes[0].location    = 0;
    attributes[0].buffer_slot = 0;
    attributes[0].format      = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2;
    attributes[0].offset      = 0;

    attributes[1].location    = 1;
    attributes[1].buffer_slot = 0;
    attributes[1].format      = SDL_GPU_VERTEXELEMENTFORMAT_UBYTE4_NORM;
    attributes[1].offset      = sizeof(float) * 4;

    std::cout << "[pipeline] Vertex attributes set up (position + color)\n";

    SDL_GPUVertexBufferDescription vb_desc{};
    vb_desc.slot               = 0;
    vb_desc.input_rate         = SDL_GPU_VERTEXINPUTRATE_VERTEX;
    vb_desc.instance_step_rate = 0;
    vb_desc.pitch              = sizeof(vertex);
    std::cout << "[pipeline] Vertex buffer description set up\n";

    SDL_GPUVertexInputState vertex_input{};
    vertex_input.vertex_buffer_descriptions = &vb_desc;
    vertex_input.num_vertex_buffers         = 1;
    vertex_input.vertex_attributes          = attributes;
    vertex_input.num_vertex_attributes      = 2;
    std::cout << "[pipeline] Vertex input state set up (2 attributes)\n";

    SDL_GPUGraphicsPipelineTargetInfo target_info{};
    SDL_GPUColorTargetDescription color_target{};

    // Use a standard format instead of swapchain format (swapchain format is only known during acquire)
    color_target.format = SDL_GPU_TEXTUREFORMAT_B8G8R8A8_UNORM;
    color_target.blend_state.enable_blend = false;
    std::cout << "[pipeline] Color target description set up (format: SDL_GPU_TEXTUREFORMAT_B8G8R8A8_UNORM)\n";

    target_info.num_color_targets          = 1;
    target_info.color_target_descriptions  = &color_target;
    std::cout << "[pipeline] Target info set up\n";

    SDL_GPUDepthStencilState depth_state{};
    depth_state.enable_depth_test  = false;
    depth_state.enable_depth_write = false;
    std::cout << "[pipeline] Depth stencil state set up\n";

    SDL_GPURasterizerState rast_state{};
    rast_state.fill_mode  = SDL_GPU_FILLMODE_FILL;
    rast_state.cull_mode  = SDL_GPU_CULLMODE_NONE;
    rast_state.front_face = SDL_GPU_FRONTFACE_COUNTER_CLOCKWISE;
    std::cout << "[pipeline] Rasterizer state set up\n";

    SDL_GPUMultisampleState msaa_state{};
    msaa_state.sample_count = (SDL_GPUSampleCount)1;
    std::cout << "[pipeline] Multisample state set up\n";

    SDL_GPUGraphicsPipelineCreateInfo info{};
    info.vertex_shader       = vs;
    info.fragment_shader     = ps;
    info.vertex_input_state  = vertex_input;
    info.primitive_type      = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
    info.rasterizer_state    = rast_state;
    info.multisample_state   = msaa_state;
    info.depth_stencil_state = depth_state;
    info.target_info         = target_info;
    info.props               = 0;
    std::cout << "[pipeline] Graphics pipeline create info set up\n";

    std::cout << "[pipeline] Creating graphics pipeline...\n";
    SDL_GPUGraphicsPipeline* p = SDL_CreateGPUGraphicsPipeline(device, &info);

    if (!p) {
        std::cerr << "[pipeline] Failed to create graphics pipeline: " << SDL_GetError() << "\n";
        SDL_ReleaseGPUShader(device, vs);
        SDL_ReleaseGPUShader(device, ps);
        return false;
    }

    SDL_ReleaseGPUShader(device, vs);
    SDL_ReleaseGPUShader(device, ps);

    default_color_pipeline = p;
    std::cout << "[pipeline] DefaultColor pipeline created OK\n";
    return true;
}

void potato_render::destroy_pipelines() {
    if (default_color_pipeline && device) {
        SDL_ReleaseGPUGraphicsPipeline(device, default_color_pipeline);
        default_color_pipeline = nullptr;
    }
}