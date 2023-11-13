// C++ Standard Library
#include <stack>

// Logger
#include <spdlog/spdlog.h>

// Project Files
#include "../../include/AST/ast.h"

namespace Syntax
{
    // Constructor
    /**
     * @brief Construct a new AbstractSyntaxTree:: AbstractSyntaxTree object
     *
     * @param[in] regex Regular expression to parse
     */
    AbstractSyntaxTree::AbstractSyntaxTree(const std::string &regex)
        : m_regex(regex)
    {
        spdlog::info("Initializing AST with regex: {}", regex);
        m_root = parse_regex(regex);
    }

    // Methods (Public)
    /**
     * @brief Matches the given string with the regex
     *
     * @param[in] input String to be matched
     * @return True if the input string could be matched
     * @return False if the input string could not be matched
     */
    bool AbstractSyntaxTree::match(const std::string &input) const
    {
        if (!m_root)
        {
            spdlog::error(
                "AST Root is null. Regex not properly initialized");
            return false;
        }

        return m_root->match(input);
    }

    // Methods (Private)
    /**
     * @brief Parses a regular expression into an AST composed of various node
     * types.
     *
     * @details This function interprets the regex pattern and constructs a
     * corresponding tree structure where each node represents a distinct
     * construct in the regex (e.g. a literal character, a character set, etc.)
     * The AST can be used to match stirngs against the regex pattern.
     *
     * @details Supported constructs include:
     *          - Literal characters
     *          - Character classes (e.g., [a-z], [A-Z], [0-9])
     *          - Predefined character classes (e.g., \d, \w, \s)
     *          - Quantifiers (e.g., *, +, ?, {n}, {n,}, {n,m})
     *          - Alternation (e.g., a|b)
     *          - Grouping Parentheses (e.g., (a|b))
     *          - Anchors (e.g., ^, $)
     *          - Escape characters (e.g., \\)
     *          - Dot (.) to match any character
     *
     * @param[in] regex The regular expression string to be parsed into an AST
     * @return A std::unique_ptr to the root node of the constructed AST. If the
     *         the regex is invalid or empty, the function returns nullptr.
     */
    std::unique_ptr<RegexNode> AbstractSyntaxTree::parse_regex(
        const std::string &regex)
    {
        spdlog::info("Parsing regex: {}", regex);

        if (regex.empty())
        {
            spdlog::warn("Parsing empty regex");
            return nullptr;
        }

        std::stack<std::unique_ptr<RegexNode>> node_stack;
        bool in_char_set = false;
        std::string char_set;

        for (std::size_t i{}; i < regex.size(); ++i)
        {
            char character = regex[i];

            if (in_char_set)
            {
                if (character == ']')
                {
                    in_char_set = false;
                    node_stack.emplace(
                        std::make_unique<CharacterSetNode>(char_set));

                    char_set.clear();
                }

                else
                {
                    char_set += character;
                }

                continue;
            }

            switch (character)
            {
            case '.':
                node_stack.emplace(std::make_unique<DotNode>());
                break;

            case '*':
                if (node_stack.empty())
                    throw std::runtime_error(
                        "Invalid regex syntax: '*' without preceding node");

                node_stack.emplace(std::make_unique<StarNode>(
                    std::move(node_stack.top())));

                node_stack.pop();
                break;

            case '+':
                if (node_stack.empty())
                    throw std::runtime_error(
                        "Invalid regex syntax: '+' without preceding node");

                node_stack.emplace(std::make_unique<PlusNode>(
                    std::move(node_stack.top())));

                node_stack.pop();
                break;

            case '?':
                if (node_stack.empty())
                    throw std::runtime_error(
                        "Invalid regex syntax: '?' without preceding node");

                node_stack.emplace(std::make_unique<QuestionNode>(
                    std::move(node_stack.top())));

                node_stack.pop();
                break;

            case '|':
                if (node_stack.size() < 2)
                    throw std::runtime_error(
                        "Invalid regex syntax: '|' without preceding nodes");

                {
                    auto right = std::move(node_stack.top());
                    node_stack.pop();

                    auto left = std::move(node_stack.top());
                    node_stack.pop();

                    node_stack.emplace(std::make_unique<AlternationNode>(
                        std::move(left), std::move(right)));
                }

                break;

            case '[':
            {
                std::size_t end = regex.find(']', i);
                if (end == std::string::npos)
                    throw std::runtime_error(
                        "Invalid regex syntax: '[' without closing ']'");

                std::string set = regex.substr(i + 1, end - i - 1);
                node_stack.emplace(std::make_unique<CharacterSetNode>(
                    set));

                i = end;
                break;
            }

            case '\\':
            {
                if (i + 1 >= regex.size())
                    throw std::runtime_error("Invalid regex syntax: '\\' at end of regex");

                char escaped = regex[++i];
                node_stack.emplace(std::make_unique<EscapeNode>(
                    escaped));

                break;
            }

            case '(':
            {
                std::size_t end = regex.find(')', i);
                if (end == std::string::npos)
                    throw std::runtime_error(
                        "Invalid regex syntax: '(' without closing ')'");

                std::string sub_regex = regex.substr(i + 1, end - i - 1);
                auto sub_node = parse_regex(sub_regex);

                node_stack.emplace(std::make_unique<GroupNode>(
                    std::move(sub_node)));

                i = end;
                break;
            }

            case ')':
                throw std::runtime_error(
                    "Invalid regex syntax: ')' without opening '('");

                break;

            case '^':
                node_stack.emplace(std::make_unique<StartNode>());
                break;

            case '$':
                node_stack.emplace(std::make_unique<EndNode>());
                break;

            default:
                node_stack.emplace(std::make_unique<LiteralNode>(character));

                break;
            }
        }

        if (in_char_set)
            throw std::runtime_error(
                "Invalid regex syntax: '[' without closing ']'");

        if (!node_stack.empty())
            return std::move(node_stack.top());

        return nullptr;
    }
}; // namespace Syntax