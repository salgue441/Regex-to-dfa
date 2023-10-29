#pragma once

#include <memory>
#include <stack>
#include <string>
#include <vector>

#include "../node/node.h"

namespace Syntax
{
    /**
     * @brief Syntax tree class for the parser
     */
    class SyntaxTree
    {
    public:
        // Constructor
        /**
         * @brief Construct a new Syntax Tree object
         * @details This constructor is only used for testing purposes
         */
        inline SyntaxTree() : m_root(nullptr) {}

        /**
         * @brief Construct a new Syntax Tree object
         *
         * @param[in] root Root node of the syntax tree
         */
        inline SyntaxTree(std::shared_ptr<Node> root) : m_root(root) {}

        // Inline getters
        /**
         * @brief Get the root node of the syntax tree
         *
         * @return std::shared_ptr<Node> Root node of the syntax tree
         */
        [[nodiscard]] inline std::shared_ptr<Node> get_root() const
        {
            return m_root;
        }

        // Methods
        /**
         * @brief Builds the syntax tree from the given regular expression
         *
         * @param[in] regex Regular expression to build the syntax tree from
         */
        void build(const std::string &regex);

    private:
        std::shared_ptr<Node> m_root;
        std::stack<std::shared_ptr<Node>> m_operands;
        std::stack<Token::Type> m_operators;

        // Methods
        /**
         * @brief Determines the precedence of the given operator
         *
         * @param[in] op Operator to determine the precedence of
         * @return int Precedence of the given operator
         */
        int precedence(Token::Type op) const;

        /**
         * @brief Processes a given operator and adds it to the syntax tree
         *
         * @param[in] op Operator to process
         */
        void process_operator(Token::Type op);

        /**
         * @brief Tokenizes the given regular expression
         *
         * @param[in] regex Regular expression to tokenize
         * @return std::vector<Token> Vector of tokens
         */
        std::vector<Token> tokenize(const std::string &regex) const;
    };
} // namespace Synax