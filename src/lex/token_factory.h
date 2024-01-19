#pragma once

#include <memory>
#include <vector>
#include "observers/token_observer.h"

namespace lex
{
  class TokenFactory
  {
  public:
    TokenFactory() = default;

    /**
     * @brief Register an observer to be notified when a token is created
     *
     * @param[in] observer Observer to be notified
     */
    void register_observer(const std::shared_ptr<TokenObserver> &observer)
    {
      m_observers.emplace_back(observer);
    }

    /**
     * @brief Create a token object
     *
     * @param[in] type     Type of the token
     * @param[in] value    Value of the token
     * @param[in] position Position of the token in the regex
     * @return std::shared_ptr<Token>
     */
    std::shared_ptr<Token> create_token(TokenType type,
                                        const std::string &value,
                                        std::size_t position)
    {
      auto token = std::make_shared<RegexToken>(type, value,
                                                position);

      notify_observers(token);
      return token;
    }

  private:
    std::vector<std::shared_ptr<TokenObserver>> m_observers;

    // Helper functions
    void notify_observers(const std::shared_ptr<Token> &token)
    {
      for (const auto &observer : m_observers)
        observer->on_token(token);
    }
  };
} // namespace lex