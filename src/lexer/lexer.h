#pragma once

#include <memory>
#include <vector>

#include "../lex/observers/token_observer.h"
#include "../lex/token_factory.h"
#include "../utils/logger.h"

namespace lexer
{
  /**
   * @class Lexer
   * @brief The lexer class is responsible for converting a regex string into a
   *        list of tokens
   *
   */
  class Lexer
  {
  public:
    // Constructors
    explicit Lexer(const std::string &input);

    // Functions
    std::vector<std::shared_ptr<lex::Token>> tokenize() const;
    void register_observer(
        std::shared_ptr<lex::TokenObserver> observer) noexcept;

  private:
    std::string m_input;
    std::vector<std::shared_ptr<lex::TokenObserver>> m_observers;
    std::shared_ptr<lex::TokenFactory> m_token_factory;
    std::shared_ptr<spdlog::logger> m_logger;

    // Helper functions
    lex::TokenType determine_type(const std::string &value) const;
    void notify_observers(std::shared_ptr<lex::Token> token) const;
  };
} // namespace lexer