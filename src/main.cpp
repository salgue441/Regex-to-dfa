#include <iostream>

#include "lexer/lexer.h"

int main(int argc, char const **argv)
{
  try
  {
    std::string input = "a|b";
    lexer::Lexer lexer(input);

    std::vector<lexer::Token> tokens = lexer.analyze();

    for (const auto &token : tokens)
      std::cout << "Type: " << static_cast<int>(token.m_type)
                << " Value: '" << token.m_value << "'\n";
  }
  catch (const std::exception &e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
}