#pragma once

#include "token_observer.h"
#include "../../../src/utils/logger.h"

namespace lex
{
  /**
   * @class TokenLogger
   * @brief The TokenLogger class is responsible for logging tokens
   *
   */
  class TokenLogger : public TokenObserver
  {
  public:
    TokenLogger()
        : logger(logger::Logger::get_logger())
    {
    }

    void on_token(std::shared_ptr<Token> token) override
    {
      if (logger)
        logger->debug("TokenLogger: {}", token->to_string());

      else
        throw std::runtime_error("TokenLogger: logger is null");
    }

  private:
    // logger
    std::shared_ptr<spdlog::logger> logger;
  };
} // namespace lex