#ifdef UNIT_TEST
#include <gtest/gtest.h>
#endif // UNIT_TEST

#include "../src/lexer/lexer.h"

#ifdef UNIT_TEST
TEST(LexerTest, TokenizeEmptyInput)
{
  lexer::Lexer lexer("");

  auto tokens = lexer.tokenize();
  ASSERT_EQ(tokens.size(), 0);
}

TEST(LexerTest, TokenizeSingleCharacter)
{
  lexer::Lexer lexer("a");

  auto tokens = lexer.tokenize();
  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0]->get_type(), lex::TokenType::LITERAL);
  ASSERT_EQ(tokens[0]->get_value(), "a");
}

#endif // UNIT_TEST