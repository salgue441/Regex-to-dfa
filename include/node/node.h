#ifndef NODE_H
#define NODE_H

#include <memory>
#include "../token/token.h"

namespace Syntax
{
    /**
     * @brief Node class for the syntax tree
     */
    class Node
    {
    public:
        // Constructor
        /**
         * @brief Construct a new Node object
         *
         * @param[in] token Token of the node
         */
        inline Node(Token token) : m_token(token),
                                   m_left(nullptr), m_right(nullptr) {}

        // Inline getters
        /**
         * @brief Get the left child of the node
         *
         * @return std::shared_ptr<Node> Left child of the node
         */
        [[nodiscard]] inline std::shared_ptr<Node> get_left() const
        {
            return m_left;
        }

        /**
         * @brief Get the right child of the node
         *
         * @return std::shared_ptr<Node> Right child of the node
         */
        [[nodiscard]] inline std::shared_ptr<Node> get_right() const
        {
            return m_right;
        }

        /**
         * @brief Get the token of the node
         *
         * @return Token Token of the node
         */
        [[nodiscard]] inline Token get_token() const { return m_token; }

    private:
        std::shared_ptr<Node> m_left;
        std::shared_ptr<Node> m_right;
        Token m_token;
    };
} // namespace Syntax

#endif //! NODE_H