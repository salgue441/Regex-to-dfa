#include <gtest/gtest.h>
#include "../include/AST/ast.h"

using namespace Syntax;

class RegexASTTree : public ::testing::Test
{
protected:
};

TEST_F(RegexASTTree, SimpleLiteralRegex)
{
    std::string regex = "a";
    AbstractSyntaxTree ast(regex);

    EXPECT_TRUE(ast.match("a"));
    EXPECT_FALSE(ast.match("b"));
}
