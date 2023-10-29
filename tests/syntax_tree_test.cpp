#include <gtest/gtest.h>
#include "../include/syntax_tree/syntax_tree.h"

using namespace Syntax;

/**
 * @brief Test fixture for the SyntaxTree class
 */
class SyntaxTreeTest : public ::testing::Test
{
protected:
    SyntaxTree tree;

public:
    SyntaxTreeTest() = default;

    virtual void SetUp();
    virtual void TearDown();
};

/**
 * @brief Set up the test fixture
 *
 * @property tree SyntaxTree object to test
 * @note This method is called before each test is run
 */
void SyntaxTreeTest::SetUp()
{
}

/**
 * @brief Tear down the test fixture
 *
 * @property tree SyntaxTree object to test
 * @note This method is called after each test is run
 */
void SyntaxTreeTest::TearDown()
{
}

/**
 * @brief Construct a new test f object
 *
 * @property tree SyntaxTree object to test
 * @note This method is called before each test is run
 */
TEST_F(SyntaxTreeTest, TestBuild3)
{
    std::string regex = "a|b|c";
    tree.build(regex);

    auto root = tree.get_root();
    ASSERT_EQ(root->get_token().get_type(), Token::Type::OR_OPERATOR);

    auto left = root->get_left();
    ASSERT_EQ(left->get_token().get_type(), Token::Type::OR_OPERATOR);

    auto left_left = left->get_left();
    ASSERT_EQ(left_left->get_token().get_type(), Token::Type::LITERAL);

    auto left_right = left->get_right();
    ASSERT_EQ(left_right->get_token().get_type(), Token::Type::LITERAL);

    auto right = root->get_right();
    ASSERT_EQ(right->get_token().get_type(), Token::Type::LITERAL);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}