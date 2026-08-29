#ifndef DEBUG_H
#define DEBUG_H

#include <fstream>
#include <string>
#include <mutex>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <cstdio>

/**
 * @brief Severity levels for log messages.
 *
 * Messages below the Logger's configured minimum level are silently dropped.
 */
enum class Log_Level {
    DEBUG,    ///< Verbose diagnostics, useful during development.
    INFO,     ///< General operational messages.
    WARNING,  ///< Unexpected situation, but the app can continue.
    ERROR,    ///< Recoverable error.
    CRITICAL  ///< Fatal error; the application may not be able to continue.
};

/**
 * @brief Thread-safe file and console logger.
 *
 * Call `init()` before logging, and `finalize_log()` + `close()` on shutdown.
 *
 * Example:
 * ```cpp
 * Engine::logger->log(Log_Level::INFO, "Game", "Level loaded.");
 * Engine::logger->log(Log_Level::WARNING, "Physics", "Collision solver too slow!");
 * ```
 */
class Logger {
public:
    Logger();

    /**
     * @brief Opens the log file and starts the timer.
     * @param filepath Path to the log file. Default: `"logs/latest.log"`.
     */
    void init(const std::string& filepath = "logs/latest.log");

    /// Flushes and closes the log file.
    void close();

    /**
     * @brief Writes a message to the log (file + stdout).
     * @param level    Severity level of the message.
     * @param category Short label identifying the system (e.g. `"Render"`, `"Input"`).
     * @param message  The log message text.
     */
    void log(Log_Level level, const std::string& category, const std::string& message);

    /**
     * @brief Sets the minimum level to log. Messages below this are ignored.
     * @param level The new minimum Log_Level.
     */
    void set_min_level(Log_Level level);

    /// @return `true` if the log file is open and ready.
    bool is_initialized() const;

    /// @return The current minimum log level.
    Log_Level get_min_level() const;

    /**
     * @brief Flushes and renames the log file to a timestamped filename.
     * Call this on clean shutdown so the log is not overwritten next run.
     */
    void finalize_log();

    /**
     * @brief Enables or disables per-frame index prefixes in log lines.
     * @param state `true` to enable frame indexing.
     */
    void frame_indexing(bool state);

    /// Increments the internal frame counter by 1.
    void increment_frame_index();

    /**
     * @brief Manually sets the frame counter.
     * @param index The frame index value to set.
     */
    void set_frame_index(long index);

    /**
     * @brief Enables or disables flood logging (DEBUG messages every frame).
     * Disable this in release builds to avoid log spam.
     * @param state `true` to enable.
     */
    void flood_logging(bool state) { m_flood_logging = state; }

    /// @return `true` if flood (per-frame debug) logging is enabled.
    bool is_flood_logging() const { return m_flood_logging; }

    /**
     * @brief Retrieves the entire contents of the log file as a string.
     * @return The log file contents, or an empty string if the file is not open
     * @attention THIS FUNCTION IS AN EDITOR FUNCTION.
     */
    std::string get_logged_message();

private:
    using Clock = std::chrono::steady_clock;

    std::string format_line(Log_Level level, const std::string& category, const std::string& message);
    std::string get_elapsed_time_string();

    static const char* level_to_string(Log_Level level);

private:
    std::ofstream m_file;
    mutable std::mutex m_mutex;

    Clock::time_point m_startTime;

    Log_Level m_minLevel;
    bool m_frameIndexer;
    long m_frameIndex;
    bool m_flood_logging;

    std::string m_logFilePath;
};

#endif