/**
 * @file token.h
 * @brief Contains the Token class for representing a token in a regular
 *       expression.
 * @author Carlos Salguero
 * @date 2023-10-28
 * @version 1.0.0
 *
 * @copyright Copyright (c) - MIT License
 * 
 */

#pragma once

namespace Syntax
{
    /**
     * @class Token
     * @brief Class representing a token in a regular expression.
     */
    class Token
    {
    public:
        /**
         * @brief Enum class for determining the type of the token
         */
        enum class Type
        {
            PARENTHESIS_OPEN,
            PARENTHESIS_CLOSE,
            OR_OPERATOR,
            CONCATENATION_OPERATOR,
            KLEENE_STAR,
            PLUS,
            QUESTION_MARK,
            LITERAL
        };

        // Constructor
        /**
         * @brief Construct a new Token object
         *
         * @param[in] type Type of the token
         * @param[in] value Value of the token
         */
        inline Token(Type type, char value) : m_type(type), m_value(value) {}

        // Inline getters
        /**
         * @brief Get the type of the token
         *
         * @return Type Type of the token
         */
        [[nodiscard]] inline Type get_type() const { return m_type; }

        /**
         * @brief Get the value of the token
         *
         * @return char Value of the token
         */
        [[nodiscard]] inline char get_value() const { return m_value; }

    private:
        Type m_type;
        char m_value;
    };
} // namespace Syntax