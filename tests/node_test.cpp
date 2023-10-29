/**
 * @file node_test.cpp
 * @brief Contains unit tests for the Node class.
 * @author Carlos Salguero
 * @date 2023-10-28
 * @version 1.0.0
 *
 * @copyright Copyright (c) - MIT License
 *
 */

#include <gtest/gtest.h>
#include "../include/node/node.h"

using namespace Syntax;

/**
 * @class NodeTest
 * @brief Test fixture for the Node class.
 */
class NodeTest : public ::testing::Test
{
protected:
    // Attributes
    std::shared_ptr<Node> m_node;

    // Methods
    /**
     * @brief Set up the test fixture
     */
    void SetUp() override
    {
        m_node = std::make_shared<Node>(Token(Token::Type::LITERAL, 'a'));
    }
};

/**
 * @brief Tests the constructor of the Node class
 */
TEST_F(NodeTest, Constructor)
{
    ASSERT_EQ(m_node->get_token().get_type(), Token::Type::LITERAL);
    ASSERT_EQ(m_node->get_token().get_value(), 'a');
    ASSERT_EQ(m_node->get_left(), nullptr);
    ASSERT_EQ(m_node->get_right(), nullptr);
}

/**
 * @brief Tests the set_left method of the Node class
 */
TEST_F(NodeTest, SetLeft)
{
    auto new_node = std::make_shared<Node>(Token(
        Token::Type::LITERAL, 'b'));

    m_node->set_left(new_node);
    ASSERT_EQ(m_node->get_left(), new_node);
}

/**
 * @brief Tests the set_right method of the Node class
 */
TEST_F(NodeTest, SetRight)
{
    auto new_node = std::make_shared<Node>(Token(
        Token::Type::LITERAL, 'b'));

    m_node->set_right(new_node);
    ASSERT_EQ(m_node->get_right(), new_node);
}

/**
 * @brief Tests the get_left method of the Node class
 */
TEST_F(NodeTest, GetLeft)
{
    auto new_node = std::make_shared<Node>(Token(
        Token::Type::LITERAL, 'b'));

    m_node->set_left(new_node);
    ASSERT_EQ(m_node->get_left(), new_node);
}

/**
 * @brief Tests the get_right method of the Node class
 */
TEST_F(NodeTest, GetRight)
{
    auto new_node = std::make_shared<Node>(Token(
        Token::Type::LITERAL, 'b'));

    m_node->set_right(new_node);
    ASSERT_EQ(m_node->get_right(), new_node);
}

/**
 * @brief Tests the get_token method of the Node class
 */
TEST_F(NodeTest, GetToken)
{
    ASSERT_EQ(m_node->get_token().get_type(), Token::Type::LITERAL);
    ASSERT_EQ(m_node->get_token().get_value(), 'a');
}

/**
 * @brief Tests the set_token method of the Node class
 */
TEST_F(NodeTest, SetToken)
{
    m_node->set_token(Token(Token::Type::LITERAL, 'b'));

    ASSERT_EQ(m_node->get_token().get_type(), Token::Type::LITERAL);
    ASSERT_EQ(m_node->get_token().get_value(), 'b');
}
