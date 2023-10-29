#pragma once

namespace Syntax
{
    /**
     * @brief Token class for the parser
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