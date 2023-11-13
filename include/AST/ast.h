#ifndef AST_H
#define AST_H

// C++ Standard Library
#include <memory>
#include <string>
#include <vector>

// Project Files
#include "../node/node.h"

namespace Syntax
{
    /**
     * @class AbstractSyntaxTree
     * @brief Creates the AST for regular expression syntax
     *
     */
    class AbstractSyntaxTree
    {
    public:
        // Constructor
        explicit AbstractSyntaxTree(const std::string &regex);

        // Methods
        bool match(const std::string &input) const;
        std::string to_string() const;

    private:
        std::string m_regex;
        std::unique_ptr<RegexNode> m_root;

        // Methods
        std::unique_ptr<RegexNode> parse_regex(const std::string &regex);
    };
}

#endif //! AST_H