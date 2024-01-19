#include <iostream>

// Project Files
#include "utils/logger.h"
#include "lexer/lexer.h"

int main()
{
  std::string input = "a|b";
  lexer::Lexer lexer(input);

  std::vector<std::shared_ptr<lex::Token>> tokens = lexer.tokenize();

  for (auto token : tokens)
  {
    std::cout << token->to_string() << std::endl;
  }

  
}