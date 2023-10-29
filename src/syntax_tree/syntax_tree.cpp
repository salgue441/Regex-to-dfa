/**
 * @file syntax_tree.cpp
 * @brief Contains the implementation of the SyntaxTree class for building
 *       a syntax tree from a regular expression.
 * @author Carlos Salguero
 * @date 2023-10-28
 * @version 0.1
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <regex>
#include "../../include/syntax_tree/syntax_tree.h"

namespace Syntax
{
    // Methods
    /**
     * @brief Builds the syntax tree from the regular expression
     * This method uses the Shunting-yard algorithm to build the syntax tree.
     *
     * @param[in] regex Regular expression to build the syntax tree from
     * @note This method is based on the following article:
     * https://en.wikipedia.org/wiki/Shunting-yard_algorithm
     *
     * @note Time complexity: O(n)
     * @note Space complexity: O(n)
     */
    void SyntaxTree::build(const std::string &regex)
    {
        auto tokens = tokenize(regex);

        for (auto token : tokens)
        {
            switch (token.get_type())
            {
            case Token::Type::LITERAL:
                m_operands.push(std::make_shared<Node>(token));
                break;

            case Token::Type::PARENTHESIS_OPEN:
                m_operators.push(token.get_type());
                break;

            case Token::Type::PARENTHESIS_CLOSE:
                while (!m_operators.empty() &&
                       m_operators.top() != Token::Type::PARENTHESIS_OPEN)
                {
                    process_operator(m_operators.top());
                    m_operators.pop();
                }

                if (!m_operators.empty())
                    m_operators.pop();

                break;

            default:
                while (!m_operators.empty() &&
                       precedence(token.get_type()) <=
                           precedence(m_operators.top()))
                {
                    process_operator(m_operators.top());
                    m_operators.pop();
                }

                m_operators.push(token.get_type());
                break;
            }
        }

        while (!m_operators.empty())
        {
            process_operator(m_operators.top());
            m_operators.pop();
        }

        if (!m_operands.empty())
        {
            m_root = m_operands.top();
            m_operands.pop();
        }
    }

    // Private methods
    /**
     * @brief Determines the precedence of the given operator
     * @details This method is used by the build method.
     *
     * @param[in] op Operator to determine the precedence of
     * @return int Precedence of the given operator
     *
     * @note Time complexity: O(1)
     * @note Space complexity: O(1)
     */
    int SyntaxTree::precedence(Token::Type op) const
    {
        switch (op)
        {
        case Token::Type::LITERAL:
            return 3;

        case Token::Type::KLEENE_STAR:
        case Token::Type::PLUS:
        case Token::Type::QUESTION_MARK:
            return 2;

        case Token::Type::CONCATENATION_OPERATOR:
            return 1;

        case Token::Type::OR_OPERATOR:
            return 0;

        default:
            return -1;
        }
    }

    /**
     * @brief Processes a given operator and adds it to the syntax tree.
     * @details This method is used by the build method.
     *
     * @param[in] op Operator to process
     *
     * @note Time complexity: O(1)
     * @note Space complexity: O(1)
     */
    void SyntaxTree::process_operator(Token::Type op)
    {
        auto new_node = std::make_shared<Node>(Token(op, 0));

        if (op == Token::Type::LITERAL && m_operands.size() >= 2)
        {
            new_node->set_right(m_operands.top());
            m_operands.pop();

            new_node->set_left(m_operands.top());
            m_operands.pop();
        }

        else if (m_operands.size() >= 1)
        {
            new_node->set_right(m_operands.top());
            m_operands.pop();
        }

        m_operands.push(new_node);
    }

    /**
     * @brief Tokenizes the given regular expression
     * @details This method is used by the build method.
     *
     * @param[in] regex Regular expression to tokenize
     * @return std::vector<Token> Vector of tokens
     *
     * @note Time complexity: O(n)
     * @note Space complexity: O(n)
     */
    std::vector<Token> SyntaxTree::tokenize(const std::string &regex) const
    {
        std::vector<Token::Type> tokens;

        for (char character : regex)
        {
            switch (character)
            {
            case '(':
                tokens.emplace_back(Token::Type::PARENTHESIS_OPEN);
                break;

            case ')':
                tokens.emplace_back(Token::Type::PARENTHESIS_CLOSE);
                break;

            case '|':
                tokens.emplace_back(Token::Type::OR_OPERATOR);
                break;

            case '.':
                tokens.emplace_back(Token::Type::CONCATENATION_OPERATOR);
                break;

            case '*':
                tokens.emplace_back(Token::Type::KLEENE_STAR);
                break;

            case '+':
                tokens.emplace_back(Token::Type::PLUS);
                break;

            case '?':
                tokens.emplace_back(Token::Type::QUESTION_MARK);
                break;

            default:
                tokens.emplace_back(Token::Type::LITERAL);
                break;
            }
        }

        std::vector<Token> result;

        for (size_t i = 0; i < tokens.size(); i++)
        {
            if (tokens[i] == Token::Type::LITERAL)
            {
                if (i + 1 < tokens.size() &&
                    tokens[i + 1] == Token::Type::LITERAL)
                {
                    result.emplace_back(Token::Type::LITERAL,
                                        regex[i]);

                    result.emplace_back(
                        Token::Type::CONCATENATION_OPERATOR, '.');
                }

                else
                    result.emplace_back(Token::Type::LITERAL,
                                        regex[i]);
            }
            else
                result.emplace_back(tokens[i], 0);
        }

        return result;
    }

} // namespace Syntax