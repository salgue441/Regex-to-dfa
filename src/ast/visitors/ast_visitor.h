// ast_visitor.h
#pragma once

namespace ast
{
  // Forward declaration
  class LiteralNode;
  class MetacharacterNode;
  class CharacterClassNode;
  class GroupingNode;
  class QuantifierNode;
  class AnchorNode;
  class EscapeSequenceNode;
  class WildcardNode;
  class AlternationNode;
  class BoundaryNode;
  class ModifierNode;
  class InvalidNode;
  class EndOfInputNode;

  /**
   * @class AstVisitor
   * @brief The AstVisitor class is the base class for all AST visitors.
   *
   */
  class AstVisitor
  {
  public:
    virtual ~AstVisitor() = default;

    virtual void visit_literal_node(const LiteralNode &node) = 0;
    virtual void visit_metacharacter_node(
        const MetacharacterNode &node) = 0;

    virtual void visit_character_class_node(
        const CharacterClassNode &node) = 0;

    virtual void visit_grouping_node(const GroupingNode &node) = 0;
    virtual void visit_quantifier_node(const QuantifierNode &node) = 0;
    virtual void visit_anchor_node(const AnchorNode &node) = 0;
    virtual void visit_escape_sequence_node(
        const EscapeSequenceNode &node) = 0;

    virtual void visit_wildcard_node(const WildcardNode &node) = 0;
    virtual void visit_alternation_node(const AlternationNode &node) = 0;
    virtual void visit_boundary_node(const BoundaryNode &node) = 0;
    virtual void visit_modifier_node(const ModifierNode &node) = 0;
    virtual void visit_invalid_node(const InvalidNode &node) = 0;
    virtual void visit_end_of_input_node(const EndOfInputNode &node) = 0;
  };

} // namespace ast
