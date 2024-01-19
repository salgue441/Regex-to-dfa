#include <iostream>

// Project Files
#include "utils/logger.h"
#include "lex/token_factory.h"
#include "lex/observers/token_logger.h"

int main()
{
  lex::TokenFactory token_factory;
  auto observer = std::make_shared<lex::TokenLogger>();

  token_factory.register_observer(observer);
  auto token = token_factory.create_token(lex::TokenType::LITERAL,
                                          "a", 0);

  auto token2 = token_factory.create_token(lex::TokenType::LITERAL,
                                           "*", 1);
}