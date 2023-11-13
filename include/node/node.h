/**
 * @file node.h
 * @author Carlos Salguero
 * @brief Contains the definition of the regex nodes
 * @version 0.1
 * @date 2023-10-31
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <memory>
#include <mutex>

namespace AbstractSyntaxTree
{
    /**
     * @class RegexNode
     * @brief Base class for all regex nodes
     */
    struct RegexNode
    {
        mutable std::unordered_map<std::string_view, bool> memo;
        mutable std::mutex memo_mutex;
        static const std::size_t MAX_CACHE_SIZE = 1000;

        virtual ~RegexNode() = default;

        /**
         * @brief Matches the regex node against the input string
         * @param[in] input The input string
         * @return [bool] True if the regex node matches the input string
         * @return [bool] False if the regex does not match the input string
         */
        virtual bool match(const std::string_view &input) const = 0;
    };

    /**
     * @class LiteralNode
     * @brief A regex node that matches a literal string
     */
    struct LiteralNode : public RegexNode
    {
        const char *m_literal;

        explicit LiteralNode(const char *literal);

        /**
         * @brief Matches the regex node against the input string
         * @param[in] input The input string
         * @return [bool] True if the regex node matches the input string
         * @return [bool] False if the regex does not match the input string
         */
        virtual bool match(const std::string_view &input) const override;
    };

    /**
     * @class DotNode
     * @brief A regex node that matches any character
     */
    struct DotNode : public RegexNode
    {
        /**
         * @brief Matches the regex node against the input string
         * @param[in] input The input string
         * @return [bool] True if the regex node matches the input string
         * @return [bool] False if the regex does not match the input string
         */
        virtual bool match(const std::string_view &input) const override;
    };

    /**
     * @class StartNode
     * @brief A regex node that matches the start of the input string
     */
    struct StartNode : public RegexNode
    {
        std::unique_ptr<RegexNode> m_child;

        explicit StartNode(std::unique_ptr<RegexNode> child);

        /**
         * @brief Matches the regex node against the input string
         * @param[in] input The input string
         * @return [bool] True if the regex node matches the input string
         * @return [bool] False if the regex does not match the input string
         */
        virtual bool match(const std::string_view &input) const override;
    };

    /**
     * @class PlusNode
     * @brief A regex node that matches one or more of the child node
     */
    struct PlusNode : public RegexNode
    {
        std::unique_ptr<RegexNode> m_child;

        explicit PlusNode(std::unique_ptr<RegexNode> child);

        /**
         * @brief Matches the regex node against the input string
         * @param[in] input The input string
         * @return [bool] True if the regex node matches the input string
         * @return [bool] False if the regex does not match the input string
         */
        virtual bool match(const std::string_view &input) const override;
    };

    /**
     * @class QuestionNode
     * @brief A regex node that matches zero or one of the child node
     */
    struct QuestionNode : public RegexNode
    {
        std::unique_ptr<RegexNode> m_child;

        explicit QuestionNode(std::unique_ptr<RegexNode> child);

        /**
         * @brief Matches the regex node against the input string
         * @param[in] input The input string
         * @return [bool] True if the regex node matches the input string
         * @return [bool] False if the regex does not match the input string
         */
        virtual bool match(const std::string_view &input) const override;
    };

    /**
     * @class CharClassNode
     * @brief Matches a character class
     */
    struct CharClassNode : public RegexNode
    {
        std::string m_class;

        explicit CharClassNode(const std::string &class_str);

        /**
         * @brief Matches the regex node against the input string
         * @param[in] input The input string
         * @return [bool] True if the regex node matches the input string
         * @return [bool] False if the regex does not match the input string
         */
        virtual bool match(const std::string_view &input) const override;
    };

    /**
     * @class AlternationNode
     * @brief Matches one of the child nodes
     */
    struct AlternationNode : public RegexNode
    {
        std::unique_ptr<RegexNode> m_left;
        std::unique_ptr<RegexNode> m_right;

        explicit AlternationNode(std::unique_ptr<RegexNode> left,
                                 std::unique_ptr<RegexNode> right);

        /**
         * @brief Matches the regex node against the input string
         * @param[in] input The input string
         * @return [bool] True if the regex node matches the input string
         * @return [bool] False if the regex does not match the input string
         */
        virtual bool match(const std::string_view &input) const override;
    };

    /**
     * @class StarNode
     * @brief A regex node that matches zero or more of the child node
     */
    struct StarNode : public RegexNode
    {
        std::unique_ptr<RegexNode> m_child;

        explicit StarNode(std::unique_ptr<RegexNode> child);

        /**
         * @brief Matches the regex node against the input string
         * @param[in] input The input string
         * @return [bool] True if the regex node matches the input string
         * @return [bool] False if the regex does not match the input string
         */
        virtual bool match(const std::string_view &input) const override;
    };

    /**
     * @class GroupNode
     * @brief A regex node that matches the end of the input string
     */
    struct GroupNode : public RegexNode
    {
        std::unique_ptr<RegexNode> m_child;

        explicit GroupNode(std::unique_ptr<RegexNode> child);

        /**
         * @brief Matches the regex node against the input string
         * @param[in] input The input string
         * @return [bool] True if the regex node matches the input string
         * @return [bool] False if the regex does not match the input string
         */
        virtual bool match(const std::string_view &input) const override;
    };

    /**
     * @class EndNode
     * @brief A regex node that matches the end of the input string
     */
    struct EndNode : public RegexNode
    {
        /**
         * @brief Matches the regex node against the input string
         * @param[in] input The input string
         * @return [bool] True if the regex node matches the input string
         * @return [bool] False if the regex does not match the input string
         */
        virtual bool match(const std::string_view &input) const override;
    };

    /**
     * @class CharacterSetNode
     * @brief A regex node that matches a set of characters
     */
    struct CharacterSetNode : public RegexNode
    {
        std::string m_set;

        explicit CharacterSetNode(const std::string &set);

        /**
         * @brief Matches the regex node against the input string
         * @param[in] input The input string
         * @return [bool] True if the regex node matches the input string
         * @return [bool] False if the regex does not match the input string
         */
        bool match(const std::string_view &input) const override;
    };

    /**
     * @class EscapeNode
     * @brief A regex node that matches an escaped character
     */
    struct EscapeNode : public RegexNode
    {
        char m_escape;

        explicit EscapeNode(const char &escape);

        /**
         * @brief Matches the regex node against the input string
         * @param[in] input The input string
         * @return [bool] True if the regex node matches the input string
         * @return [bool] False if the regex does not match the input string
         */
        bool match(const std::string_view &input) const override;
    };

    /**
     * @class NegatedCharacterSetNode
     * @brief Matches any character not in the set
     */
    struct NegatedCharacterSetNode : public RegexNode
    {
        std::string m_set;

        explicit NegatedCharacterSetNode(const std::string &set);

        /**
         * @brief Matches the regex node against the input string
         * @param[in] input The input string
         * @return [bool] True if the regex node does not match the input string
         * @return [bool] False if the regex matches the input string
         */
        bool match(const std::string_view &input) const override;
    };
} // namespace AbstractSyntaxTree