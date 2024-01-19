#include <iostream>

// Project Files
#include "utils/logger.h"
#include "lexer/lexer.h"
#include "lex/observers/token_logger.h"

int main()
{
  std::string pattern = R"(\s*([+\-*/()]|\d+)\s*)";
  lexer::Lexer lexer(pattern);

  std::shared_ptr<lex::TokenLogger> token_logger =
      std::make_shared<lex::TokenLogger>();

  lexer.register_observer(token_logger);
  std::vector<std::shared_ptr<lex::Token>> tokens = lexer.tokenize();
}
