#pragma once

#include <memory>
#include "../token/token.h"

namespace lex
{
  /**
   * @class TokenObserver
   * @brief Interface for classes that want to observe tokens as they are
   *
   */
  class TokenObserver
  {
  public:
    virtual ~TokenObserver() = default;
    virtual void on_token(std::shared_ptr<Token> token) = 0;
  };
}