/**
 * @file node.cpp
 * @author Carlos Salguero
 * @brief Implementation of the regex nodes
 * @version 0.1
 * @date 2023-10-31
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdexcept>

#include "../../include/node/node.h"

namespace AbstractSyntaxTree
{

    // LiteralNode implementation
    /**
     * @brief Construct a new Literal Node:: Literal Node object
     * @param[in] literal The literal character
     */
    LiteralNode::LiteralNode(const char *literal) : m_literal(literal) {}

    /**
     * @brief Matches the regex node against the input string
     * @param[in] input The input string
     * @return [bool] True if the regex node matches the input string
     * @return [bool] False if the regex does not match the input string
     */
    bool LiteralNode::match(const std::string_view &input) const
    {
        std::lock_guard<std::mutex> lock(memo_mutex);

        if (memo.find(input) != memo.end())
            return memo.at(input);

        bool result = input.size() > 0 && input.front() == m_literal[0];

        if (memo.size() >= MAX_CACHE_SIZE)
            memo.clear();

        memo.emplace(input, result);

        return result;
    }

    // DotNode implementation
    /**
     * @brief Matches the regex node against the input string
     * @param[in] input The input string
     * @return [bool] True if the regex node matches the input string
     * @return [bool] False if the regex does not match the input string
     */
    bool DotNode::match(const std::string_view &input) const
    {
        std::lock_guard<std::mutex> lock(memo_mutex);

        if (memo.find(input) != memo.end())
            return memo.at(input);

        char front_char = input.front();
        bool result = front_char != '\0' && front_char != '\n' &&
                      front_char != '\r';

        if (memo.size() >= MAX_CACHE_SIZE)
            memo.clear();

        memo.emplace(input, front_char);

        return result;
    }

    // StartNode implementation
    /**
     * @brief Construct a new Start Node:: Start Node object
     * @param child The child node
     */
    StartNode::StartNode(std::unique_ptr<RegexNode> child)
        : m_child(std::move(child)) {}

    /**
     * @brief Matches the regex node against the input string
     * @param[in] input The input string
     * @return [bool] True if the regex node matches the input string
     * @return [bool] False if the regex does not match the input string
     */
    bool StartNode::match(const std::string_view &input) const
    {
        return m_child->match(input);
    }

    // PlusNode implementation
    /**
     * @brief Construct a new Plus Node:: Plus Node object
     * @param child The child node
     */
    PlusNode::PlusNode(std::unique_ptr<RegexNode> child)
        : m_child(std::move(child)) {}

    /**
     * @brief Matches the regex node against the input string
     * @param[in] input The input string
     * @return [bool] True if the regex node matches the input string
     * @return [bool] False if the regex does not match the input string
     */
    bool PlusNode::match(const std::string_view &input) const
    {
        std::size_t i{};

        while (i < input.size() &&
               m_child->match(input.substr(0, i + 1)))
            ++i;

        return i > 0;
    }

    // QuestionNode implementation
    /**
     * @brief Construct a new Question Node:: Question Node object
     * @param child The child node
     */
    QuestionNode::QuestionNode(std::unique_ptr<RegexNode> child)
        : m_child(std::move(child)) {}

    /**
     * @brief Matches the regex node against the input string
     * @param[in] input The input string
     * @return [bool] True if the regex node matches the input string
     * @return [bool] False if the regex does not match the input string
     */
    bool QuestionNode::match(const std::string_view &input) const
    {
        return m_child->match(input) || input.empty();
    }

    // AlternationNode implementation
    /**
     * @brief Construct a new Alternation Node:: Alternation Node object
     * @param left The left child node
     * @param right The right child node
     */
    AlternationNode::AlternationNode(std::unique_ptr<RegexNode> left,
                                     std::unique_ptr<RegexNode> right)
        : m_left(std::move(left)), m_right(std::move(right)) {}

    /**
     * @brief Matches the regex node against the input string
     * @param[in] input The input string
     * @return [bool] True if the regex node matches the input string
     * @return [bool] False if the regex does not match the input string
     */
    bool AlternationNode::match(const std::string_view &input) const
    {
        return m_left->match(input) || m_right->match(input);
    }

    // StarNode implementation
    /**
     * @brief Construct a new Star Node:: Star Node object
     * @param child The child node
     */
    StarNode::StarNode(std::unique_ptr<RegexNode> child)
        : m_child(std::move(child)) {}

    /**
     * @brief Matches the regex node against the input string
     * @param[in] input The input string
     * @return [bool] True if the regex node matches the input string
     * @return [bool] False if the regex does not match the input string
     */
    bool StarNode::match(const std::string_view &input) const
    {
        std::size_t i{};

        while (i < input.size() &&
               m_child->match(input.substr(i)))
            ++i;

        return true;
    }

    // GroupNode implementation
    /**
     * @brief Construct a new Group Node:: Group Node object
     * @param child The child node
     */
    GroupNode::GroupNode(std::unique_ptr<RegexNode> child)
        : m_child(std::move(child)) {}

    /**
     * @brief Matches the regex node against the input string
     * @param[in] input The input string
     * @return [bool] True if the regex node matches the input string
     * @return [bool] False if the regex does not match the input string
     */
    bool GroupNode::match(const std::string_view &input) const
    {
        return m_child->match(input);
    }

    // EndNode implementation
    /**
     * @brief Matches the regex node against the input string
     * @param[in] input The input string
     * @return [bool] True if the regex node matches the input string
     * @return [bool] False if the regex does not match the input string
     */
    bool EndNode::match(const std::string_view &input) const
    {
        if (input.empty())
            throw std::runtime_error("EndNode::match input is empty");

        return input.front() == '\0';
    }

    // CharacterSetNode implementation
    /**
     * @brief Construct a new Character Set Node:: Character Set Node object
     * @param[in] set The characters to match
     */
    CharacterSetNode::CharacterSetNode(const std::string &set)
        : m_set(set) {}

    /**
     * @brief Matches the regex node against the input string
     * @param[in] input The input string
     * @return [bool] True if the regex node matches the input string
     * @return [bool] False if the regex does not match the input string
     */
    bool CharacterSetNode::match(const std::string_view &input) const
    {
        std::lock_guard<std::mutex> lock(memo_mutex);

        if (memo.find(input) != memo.end())
            return memo.at(input);

        if (input.empty())
            throw std::runtime_error("CharacterSetNode::match input is empty");

        bool result = m_set.find(input.front()) != std::string::npos;

        if (memo.size() >= MAX_CACHE_SIZE)
            memo.clear();

        memo[input] = result;

        return result;
    }

    // EscapeNode implementation
    /**
     * @brief Construct a new Escape Node:: Escape Node object
     * @param[in] escape The literal character
     */
    EscapeNode::EscapeNode(const char &escape) : m_escape(escape) {}

    /**
     * @brief Matches the regex node against the input string
     * @param[in] input The input string
     * @return [bool] True if the regex node matches the input string
     * @return [bool] False if the regex does not match the input string
     */
    bool EscapeNode::match(const std::string_view &input) const
    {
        if (input.empty())
            throw std::runtime_error("EscapeNode::match input is empty");

        return input.front() == m_escape;
    }

    // NegatedCharacterSetNode implementation
    /**
     * @brief Construct a new Negated Character Set Node::
     *        Negated Character Set Node object
     * @param[in] set The characters to match
     */
    NegatedCharacterSetNode::NegatedCharacterSetNode(const std::string &set)
        : m_set(set) {}

    /**
     * @brief Matches the regex node against the input string
     * @param[in] input The input string
     * @return [bool] True if the regex node does not match the input string
     * @return [bool] False if the regex matches the input string
     */
    bool NegatedCharacterSetNode::match(const std::string_view &input) const
    {
        if (input.empty())
            throw std::runtime_error(
                "NegatedCharacterSetNode::match input is empty");

        return m_set.find(input.front()) == std::string::npos;
    }
} // namespace AbstractSyntaxTree