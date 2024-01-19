#pragma once

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

/**
 * @namespace logger
 * @brief Defines the logger class for the project
 *
 */
namespace logger
{
  class Logger
  {
  public:
    /**
     * @brief Get the logger object
     * @details Creates two loggers, one for console and one for stderr
     *
     * @return std::shared_ptr<spdlog::logger>& The logger
     */
    static std::shared_ptr<spdlog::logger> &get_logger()
    {
      static Logger logger;
      return logger.s_logger;
    }

  private:
    static std::shared_ptr<spdlog::logger> s_logger;
    Logger()
    {
      auto logger = spdlog::stdout_color_mt("console");

      const std::string pattern =
          "[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [thread %t] %v";

      logger->set_pattern(pattern);
      logger->set_level(spdlog::level::trace);

      s_logger = logger;
    }
  };

  std::shared_ptr<spdlog::logger> Logger::s_logger = nullptr;

} // namespace logger