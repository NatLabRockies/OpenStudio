
// Generated from modelica.g4 by ANTLR 4.13.2

#pragma once

#include "antlr4-runtime.h"
#include "modelicaParser.h"

/**
 * This class defines an abstract visitor for a parse tree
 * produced by modelicaParser.
 */
class modelicaVisitor : public antlr4::tree::AbstractParseTreeVisitor
{
 public:
  /**
   * Visit parse trees produced by modelicaParser.
   */
  virtual std::any visitStored_definition(modelicaParser::Stored_definitionContext* context) = 0;

  virtual std::any visitWithin_statement(modelicaParser::Within_statementContext* context) = 0;

  virtual std::any visitClass_definition(modelicaParser::Class_definitionContext* context) = 0;

  virtual std::any visitClass_specifier(modelicaParser::Class_specifierContext* context) = 0;

  virtual std::any visitClass_prefixes(modelicaParser::Class_prefixesContext* context) = 0;

  virtual std::any visitLong_class_specifier(modelicaParser::Long_class_specifierContext* context) = 0;

  virtual std::any visitShort_class_specifier(modelicaParser::Short_class_specifierContext* context) = 0;

  virtual std::any visitDer_class_specifier(modelicaParser::Der_class_specifierContext* context) = 0;

  virtual std::any visitBase_prefix(modelicaParser::Base_prefixContext* context) = 0;

  virtual std::any visitEnum_list(modelicaParser::Enum_listContext* context) = 0;

  virtual std::any visitEnumeration_literal(modelicaParser::Enumeration_literalContext* context) = 0;

  virtual std::any visitComposition(modelicaParser::CompositionContext* context) = 0;

  virtual std::any visitLanguage_specification(modelicaParser::Language_specificationContext* context) = 0;

  virtual std::any visitExternal_function_call(modelicaParser::External_function_callContext* context) = 0;

  virtual std::any visitElement_list(modelicaParser::Element_listContext* context) = 0;

  virtual std::any visitElement(modelicaParser::ElementContext* context) = 0;

  virtual std::any visitImport_clause(modelicaParser::Import_clauseContext* context) = 0;

  virtual std::any visitImport_list(modelicaParser::Import_listContext* context) = 0;

  virtual std::any visitExtends_clause(modelicaParser::Extends_clauseContext* context) = 0;

  virtual std::any visitConstraining_clause(modelicaParser::Constraining_clauseContext* context) = 0;

  virtual std::any visitComponent_clause(modelicaParser::Component_clauseContext* context) = 0;

  virtual std::any visitType_prefix(modelicaParser::Type_prefixContext* context) = 0;

  virtual std::any visitType_specifier(modelicaParser::Type_specifierContext* context) = 0;

  virtual std::any visitComponent_list(modelicaParser::Component_listContext* context) = 0;

  virtual std::any visitComponent_declaration(modelicaParser::Component_declarationContext* context) = 0;

  virtual std::any visitCondition_attribute(modelicaParser::Condition_attributeContext* context) = 0;

  virtual std::any visitDeclaration(modelicaParser::DeclarationContext* context) = 0;

  virtual std::any visitModification(modelicaParser::ModificationContext* context) = 0;

  virtual std::any visitClass_modification(modelicaParser::Class_modificationContext* context) = 0;

  virtual std::any visitArgument_list(modelicaParser::Argument_listContext* context) = 0;

  virtual std::any visitArgument(modelicaParser::ArgumentContext* context) = 0;

  virtual std::any visitElement_modification_or_replaceable(modelicaParser::Element_modification_or_replaceableContext* context) = 0;

  virtual std::any visitElement_modification(modelicaParser::Element_modificationContext* context) = 0;

  virtual std::any visitElement_redeclaration(modelicaParser::Element_redeclarationContext* context) = 0;

  virtual std::any visitElement_replaceable(modelicaParser::Element_replaceableContext* context) = 0;

  virtual std::any visitComponent_clause1(modelicaParser::Component_clause1Context* context) = 0;

  virtual std::any visitComponent_declaration1(modelicaParser::Component_declaration1Context* context) = 0;

  virtual std::any visitShort_class_definition(modelicaParser::Short_class_definitionContext* context) = 0;

  virtual std::any visitEquation_section(modelicaParser::Equation_sectionContext* context) = 0;

  virtual std::any visitAlgorithm_section(modelicaParser::Algorithm_sectionContext* context) = 0;

  virtual std::any visitEquation(modelicaParser::EquationContext* context) = 0;

  virtual std::any visitStatement(modelicaParser::StatementContext* context) = 0;

  virtual std::any visitIf_equation(modelicaParser::If_equationContext* context) = 0;

  virtual std::any visitIf_statement(modelicaParser::If_statementContext* context) = 0;

  virtual std::any visitFor_equation(modelicaParser::For_equationContext* context) = 0;

  virtual std::any visitFor_statement(modelicaParser::For_statementContext* context) = 0;

  virtual std::any visitFor_indices(modelicaParser::For_indicesContext* context) = 0;

  virtual std::any visitFor_index(modelicaParser::For_indexContext* context) = 0;

  virtual std::any visitWhile_statement(modelicaParser::While_statementContext* context) = 0;

  virtual std::any visitWhen_equation(modelicaParser::When_equationContext* context) = 0;

  virtual std::any visitWhen_statement(modelicaParser::When_statementContext* context) = 0;

  virtual std::any visitConnect_clause(modelicaParser::Connect_clauseContext* context) = 0;

  virtual std::any visitExpression(modelicaParser::ExpressionContext* context) = 0;

  virtual std::any visitSimple_expression(modelicaParser::Simple_expressionContext* context) = 0;

  virtual std::any visitLogical_expression(modelicaParser::Logical_expressionContext* context) = 0;

  virtual std::any visitLogical_term(modelicaParser::Logical_termContext* context) = 0;

  virtual std::any visitLogical_factor(modelicaParser::Logical_factorContext* context) = 0;

  virtual std::any visitRelation(modelicaParser::RelationContext* context) = 0;

  virtual std::any visitRel_op(modelicaParser::Rel_opContext* context) = 0;

  virtual std::any visitArithmetic_expression(modelicaParser::Arithmetic_expressionContext* context) = 0;

  virtual std::any visitAdd_op(modelicaParser::Add_opContext* context) = 0;

  virtual std::any visitTerm(modelicaParser::TermContext* context) = 0;

  virtual std::any visitMul_op(modelicaParser::Mul_opContext* context) = 0;

  virtual std::any visitFactor(modelicaParser::FactorContext* context) = 0;

  virtual std::any visitPrimary(modelicaParser::PrimaryContext* context) = 0;

  virtual std::any visitName(modelicaParser::NameContext* context) = 0;

  virtual std::any visitComponent_reference(modelicaParser::Component_referenceContext* context) = 0;

  virtual std::any visitFunction_call_args(modelicaParser::Function_call_argsContext* context) = 0;

  virtual std::any visitFunction_arguments(modelicaParser::Function_argumentsContext* context) = 0;

  virtual std::any visitNamed_arguments(modelicaParser::Named_argumentsContext* context) = 0;

  virtual std::any visitNamed_argument(modelicaParser::Named_argumentContext* context) = 0;

  virtual std::any visitFunction_argument(modelicaParser::Function_argumentContext* context) = 0;

  virtual std::any visitOutput_expression_list(modelicaParser::Output_expression_listContext* context) = 0;

  virtual std::any visitExpression_list(modelicaParser::Expression_listContext* context) = 0;

  virtual std::any visitArray_subscripts(modelicaParser::Array_subscriptsContext* context) = 0;

  virtual std::any visitSubscript(modelicaParser::SubscriptContext* context) = 0;

  virtual std::any visitComment(modelicaParser::CommentContext* context) = 0;

  virtual std::any visitString_comment(modelicaParser::String_commentContext* context) = 0;

  virtual std::any visitModel_annotation(modelicaParser::Model_annotationContext* context) = 0;

  virtual std::any visitAnnotation(modelicaParser::AnnotationContext* context) = 0;
};
