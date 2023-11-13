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

using namespace AbstractSyntaxTree;

/**
 * @class NodeTest
 * @brief Test fixture for the Node class.
 */
class NodeTest : public ::testing::Test
{
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(NodeTest, LiteralNodeMatch)
{
    LiteralNode node("a");

    ASSERT_TRUE(node.match("a"));
    ASSERT_FALSE(node.match("b"));
}

TEST_F(NodeTest, DotNodeMatch)
{
    DotNode node;

    ASSERT_TRUE(node.match("a"));
    ASSERT_TRUE(node.match("b"));
    ASSERT_TRUE(node.match("c"));
    ASSERT_FALSE(node.match(""));

    ASSERT_TRUE(node.match("aa"));
}

TEST_F(NodeTest, StartNodeMatch)
{
    auto child = std::make_unique<LiteralNode>("a");
    StartNode node(std::move(child));

    ASSERT_TRUE(node.match("aaa"));
    ASSERT_FALSE(node.match("baa"));
}

TEST_F(NodeTest, PlusNodeMatch)
{
    auto child = std::make_unique<LiteralNode>("a");
    PlusNode node(std::move(child));

    ASSERT_TRUE(node.match("a"));
    ASSERT_TRUE(node.match("aaa"));
    ASSERT_FALSE(node.match("b"));
}

TEST_F(NodeTest, QUestionNodeMatch)
{
    auto child = std::make_unique<LiteralNode>("a");
    QuestionNode node(std::move(child));

    ASSERT_TRUE(node.match("a"));
    ASSERT_TRUE(node.match("b"));
    ASSERT_FALSE(node.match("c"));
}

TEST_F(NodeTest, AlternationNodeMAtch)
{
    auto left = std::make_unique<LiteralNode>("a");
    auto right = std::make_unique<LiteralNode>("b");
    AlternationNode node(std::move(left), std::move(right));

    ASSERT_TRUE(node.match("a"));
    ASSERT_TRUE(node.match("b"));
    ASSERT_FALSE(node.match("c"));
}

TEST_F(NodeTest, StarNodeMatch)
{
    auto child = std::make_unique<LiteralNode>("a");
    StarNode node(std::move(child));

    ASSERT_TRUE(node.match("a"));
    ASSERT_TRUE(node.match("aaa"));
    ASSERT_FALSE(node.match("b"));
}

TEST_F(NodeTest, GroupMatch)
{
    auto child = std::make_unique<LiteralNode>("a");
    GroupNode node(std::move(child));

    ASSERT_TRUE(node.match("a"));
    ASSERT_FALSE(node.match("b"));
}

TEST_F(NodeTest, EndNodeMatch)
{
    EndNode node;

    ASSERT_TRUE(node.match(""));
    ASSERT_FALSE(node.match("a"));
}

TEST_F(NodeTest, CharacterSetNodeMatch)
{
    CharacterSetNode node("abc");

    ASSERT_TRUE(node.match("a"));
    ASSERT_TRUE(node.match("b"));
    ASSERT_TRUE(node.match("c"));
    ASSERT_FALSE(node.match("d"));
}

TEST_F(NodeTest, EscapeNodeMatch)
{
    EscapeNode node('a');

    ASSERT_TRUE(node.match("a"));
    ASSERT_FALSE(node.match("b"));
}

TEST_F(NodeTest, NegatedCharacterSetNodeMatch)
{
    NegatedCharacterSetNode node("abc");

    ASSERT_FALSE(node.match("a"));
    ASSERT_FALSE(node.match("b"));
    ASSERT_FALSE(node.match("c"));
    ASSERT_TRUE(node.match("d"));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}