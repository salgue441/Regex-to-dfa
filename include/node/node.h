/**
 * @file node.h
 * @brief Defines the Node class.
 * @author Carlos Salguero
 * @date 2023-10-28
 * @version 1.0.0
 *
 * @copyright Copyright (c) - MIT License
 * 
 */

#ifndef NODE_H
#define NODE_H

#include <memory>
#include "../token/token.h"

namespace Syntax
{
    /**
     * @class Node
     * @brief Class representing a node in a syntax tree.
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

        // Inline setters
        /**
         * @brief Set the left child of the node
         *
         * @param[in] left Left child of the node
         */
        inline void set_left(std::shared_ptr<Node> left) { m_left = left; }

        /**
         * @brief Set the right child of the node
         *
         * @param[in] right Right child of the node
         */
        inline void set_right(std::shared_ptr<Node> right) { m_right = right; }

        /**
         * @brief Set the token of the node
         *
         * @param[in] token Token of the node
         */
        inline void set_token(Token token) { m_token = token; }

    private:
        std::shared_ptr<Node> m_left;
        std::shared_ptr<Node> m_right;
        Token m_token;
    };
} // namespace Syntax

#endif //! NODE_H