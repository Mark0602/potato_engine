#include "debug.h"

#include <filesystem>

Logger::Logger()
    : m_startTime(Clock::now())
    , m_minLevel(Log_Level::DEBUG)
    , m_frameIndexer(false)
    , m_frameIndex(0)
    , m_flood_logging(false)
    , m_logFilePath("")
{}

void Logger::init(const std::string& filepath) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_logFilePath = filepath;
    m_startTime = Clock::now();

    const std::filesystem::path log_path(filepath);
    if (log_path.has_parent_path()) {
        std::error_code error;
        std::filesystem::create_directories(log_path.parent_path(), error);
        if (error) {
            std::cerr << "Logger error: failed to create directory: "
                      << log_path.parent_path().string() << '\n';
        }
    }

    if (m_file.is_open()) {
        m_file.close();
    }

    m_file.open(m_logFilePath, std::ios::out | std::ios::trunc);

    if (!m_file.is_open()) {
        std::cerr << "Logger error: failed to open log file: " << m_logFilePath << '\n';
    }
}

void Logger::close() {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_file.is_open()) {
        m_file.flush();
        m_file.close();
    }
}

void Logger::log(Log_Level level, const std::string& category, const std::string& message) {
    if (level < m_minLevel) {
        return;
    }

    std::lock_guard<std::mutex> lock(m_mutex);

    std::string line = format_line(level, category, message);

    if (level == Log_Level::CRITICAL) {
        std::cerr << line << '\n';
        if (m_file.is_open()) {
            m_file << line << '\n';
        }
        throw std::runtime_error("Critical error message: " + message);
    }
    std::cout << line << '\n';

    if (m_file.is_open()) {
        m_file << line << '\n';
    }
}

std::string Logger::get_logged_message() {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_file.is_open()) {
        return "";
    }

    m_file.flush();
    std::ifstream log_file(m_logFilePath);
    if (!log_file.is_open()) {
        return "";
    }
    std::ostringstream oss_content;
    oss_content << log_file.rdbuf();
    return oss_content.str();
}

void Logger::set_min_level(Log_Level level) {
    m_minLevel = level;
}

bool Logger::is_initialized() const {
    return m_file.is_open();
}

Log_Level Logger::get_min_level() const {
    return m_minLevel;
}

void Logger::finalize_log() {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_file.is_open()) {
        m_file.flush();
        m_file.close();
    }

    if (m_logFilePath.empty()) return;

    auto now = Clock::now();
    const std::filesystem::path source_path(m_logFilePath);
    std::ostringstream oss;
    oss << "finalized-"
        << std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count()
        << ".log";
    const std::filesystem::path destination =
        source_path.parent_path() / oss.str();

    std::error_code error;
    std::filesystem::rename(source_path, destination, error);
    if (error) {
        std::cerr << "Logger error: failed to finalize log: "
                  << error.message() << '\n';
    }
}

void Logger::frame_indexing(bool state) {
    m_frameIndexer = state;
}

void Logger::increment_frame_index() {
    ++m_frameIndex;
}

void Logger::set_frame_index(long index) {
    m_frameIndex = index;
}

std::string Logger::format_line(Log_Level level, const std::string& category, const std::string& message) {
    std::ostringstream oss;

    oss << '[' << get_elapsed_time_string() << ']';
    if (m_frameIndexer) {
        oss << "[Frame " << std::setw(6) << std::setfill('0') << m_frameIndex << "] ";
    }
    oss << " [" << level_to_string(level) << ']';
    oss << " [" << category << "] ";
    oss << message;

    return oss.str();
}

std::string Logger::get_elapsed_time_string() {
    auto now = Clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_startTime).count();

    long long milliseconds = elapsed % 1000;
    long long totalSeconds = elapsed / 1000;

    long long seconds = totalSeconds % 60;
    long long totalMinutes = totalSeconds / 60;

    long long minutes = totalMinutes % 60;
    long long hours = totalMinutes / 60;

    std::ostringstream oss;

    oss << std::setfill('0')
        << std::setw(2) << hours << ':'
        << std::setw(2) << minutes << ':'
        << std::setw(2) << seconds << '.'
        << std::setw(3) << milliseconds;

    return oss.str();
}

const char* Logger::level_to_string(Log_Level level) {
    switch (level) {
        case Log_Level::DEBUG:    return "DEBUG";
        case Log_Level::INFO:     return "INFO";
        case Log_Level::WARNING:  return "WARN";
        case Log_Level::ERROR:    return "ERROR";
        case Log_Level::CRITICAL: return "CRITICAL";
    }

    return "UNKNOWN";
}
