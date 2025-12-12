
// Generated from modelica.g4 by ANTLR 4.13.2

#pragma once

#include "antlr4-runtime.h"
#include "modelicaParser.h"

/**
 * This interface defines an abstract listener for a parse tree produced by modelicaParser.
 */
class modelicaListener : public antlr4::tree::ParseTreeListener
{
 public:
  virtual void enterStored_definition(modelicaParser::Stored_definitionContext* ctx) = 0;
  virtual void exitStored_definition(modelicaParser::Stored_definitionContext* ctx) = 0;

  virtual void enterWithin_statement(modelicaParser::Within_statementContext* ctx) = 0;
  virtual void exitWithin_statement(modelicaParser::Within_statementContext* ctx) = 0;

  virtual void enterClass_definition(modelicaParser::Class_definitionContext* ctx) = 0;
  virtual void exitClass_definition(modelicaParser::Class_definitionContext* ctx) = 0;

  virtual void enterClass_specifier(modelicaParser::Class_specifierContext* ctx) = 0;
  virtual void exitClass_specifier(modelicaParser::Class_specifierContext* ctx) = 0;

  virtual void enterClass_prefixes(modelicaParser::Class_prefixesContext* ctx) = 0;
  virtual void exitClass_prefixes(modelicaParser::Class_prefixesContext* ctx) = 0;

  virtual void enterLong_class_specifier(modelicaParser::Long_class_specifierContext* ctx) = 0;
  virtual void exitLong_class_specifier(modelicaParser::Long_class_specifierContext* ctx) = 0;

  virtual void enterShort_class_specifier(modelicaParser::Short_class_specifierContext* ctx) = 0;
  virtual void exitShort_class_specifier(modelicaParser::Short_class_specifierContext* ctx) = 0;

  virtual void enterDer_class_specifier(modelicaParser::Der_class_specifierContext* ctx) = 0;
  virtual void exitDer_class_specifier(modelicaParser::Der_class_specifierContext* ctx) = 0;

  virtual void enterBase_prefix(modelicaParser::Base_prefixContext* ctx) = 0;
  virtual void exitBase_prefix(modelicaParser::Base_prefixContext* ctx) = 0;

  virtual void enterEnum_list(modelicaParser::Enum_listContext* ctx) = 0;
  virtual void exitEnum_list(modelicaParser::Enum_listContext* ctx) = 0;

  virtual void enterEnumeration_literal(modelicaParser::Enumeration_literalContext* ctx) = 0;
  virtual void exitEnumeration_literal(modelicaParser::Enumeration_literalContext* ctx) = 0;

  virtual void enterComposition(modelicaParser::CompositionContext* ctx) = 0;
  virtual void exitComposition(modelicaParser::CompositionContext* ctx) = 0;

  virtual void enterLanguage_specification(modelicaParser::Language_specificationContext* ctx) = 0;
  virtual void exitLanguage_specification(modelicaParser::Language_specificationContext* ctx) = 0;

  virtual void enterExternal_function_call(modelicaParser::External_function_callContext* ctx) = 0;
  virtual void exitExternal_function_call(modelicaParser::External_function_callContext* ctx) = 0;

  virtual void enterElement_list(modelicaParser::Element_listContext* ctx) = 0;
  virtual void exitElement_list(modelicaParser::Element_listContext* ctx) = 0;

  virtual void enterElement(modelicaParser::ElementContext* ctx) = 0;
  virtual void exitElement(modelicaParser::ElementContext* ctx) = 0;

  virtual void enterImport_clause(modelicaParser::Import_clauseContext* ctx) = 0;
  virtual void exitImport_clause(modelicaParser::Import_clauseContext* ctx) = 0;

  virtual void enterImport_list(modelicaParser::Import_listContext* ctx) = 0;
  virtual void exitImport_list(modelicaParser::Import_listContext* ctx) = 0;

  virtual void enterExtends_clause(modelicaParser::Extends_clauseContext* ctx) = 0;
  virtual void exitExtends_clause(modelicaParser::Extends_clauseContext* ctx) = 0;

  virtual void enterConstraining_clause(modelicaParser::Constraining_clauseContext* ctx) = 0;
  virtual void exitConstraining_clause(modelicaParser::Constraining_clauseContext* ctx) = 0;

  virtual void enterComponent_clause(modelicaParser::Component_clauseContext* ctx) = 0;
  virtual void exitComponent_clause(modelicaParser::Component_clauseContext* ctx) = 0;

  virtual void enterType_prefix(modelicaParser::Type_prefixContext* ctx) = 0;
  virtual void exitType_prefix(modelicaParser::Type_prefixContext* ctx) = 0;

  virtual void enterType_specifier(modelicaParser::Type_specifierContext* ctx) = 0;
  virtual void exitType_specifier(modelicaParser::Type_specifierContext* ctx) = 0;

  virtual void enterComponent_list(modelicaParser::Component_listContext* ctx) = 0;
  virtual void exitComponent_list(modelicaParser::Component_listContext* ctx) = 0;

  virtual void enterComponent_declaration(modelicaParser::Component_declarationContext* ctx) = 0;
  virtual void exitComponent_declaration(modelicaParser::Component_declarationContext* ctx) = 0;

  virtual void enterCondition_attribute(modelicaParser::Condition_attributeContext* ctx) = 0;
  virtual void exitCondition_attribute(modelicaParser::Condition_attributeContext* ctx) = 0;

  virtual void enterDeclaration(modelicaParser::DeclarationContext* ctx) = 0;
  virtual void exitDeclaration(modelicaParser::DeclarationContext* ctx) = 0;

  virtual void enterModification(modelicaParser::ModificationContext* ctx) = 0;
  virtual void exitModification(modelicaParser::ModificationContext* ctx) = 0;

  virtual void enterClass_modification(modelicaParser::Class_modificationContext* ctx) = 0;
  virtual void exitClass_modification(modelicaParser::Class_modificationContext* ctx) = 0;

  virtual void enterArgument_list(modelicaParser::Argument_listContext* ctx) = 0;
  virtual void exitArgument_list(modelicaParser::Argument_listContext* ctx) = 0;

  virtual void enterArgument(modelicaParser::ArgumentContext* ctx) = 0;
  virtual void exitArgument(modelicaParser::ArgumentContext* ctx) = 0;

  virtual void enterElement_modification_or_replaceable(modelicaParser::Element_modification_or_replaceableContext* ctx) = 0;
  virtual void exitElement_modification_or_replaceable(modelicaParser::Element_modification_or_replaceableContext* ctx) = 0;

  virtual void enterElement_modification(modelicaParser::Element_modificationContext* ctx) = 0;
  virtual void exitElement_modification(modelicaParser::Element_modificationContext* ctx) = 0;

  virtual void enterElement_redeclaration(modelicaParser::Element_redeclarationContext* ctx) = 0;
  virtual void exitElement_redeclaration(modelicaParser::Element_redeclarationContext* ctx) = 0;

  virtual void enterElement_replaceable(modelicaParser::Element_replaceableContext* ctx) = 0;
  virtual void exitElement_replaceable(modelicaParser::Element_replaceableContext* ctx) = 0;

  virtual void enterComponent_clause1(modelicaParser::Component_clause1Context* ctx) = 0;
  virtual void exitComponent_clause1(modelicaParser::Component_clause1Context* ctx) = 0;

  virtual void enterComponent_declaration1(modelicaParser::Component_declaration1Context* ctx) = 0;
  virtual void exitComponent_declaration1(modelicaParser::Component_declaration1Context* ctx) = 0;

  virtual void enterShort_class_definition(modelicaParser::Short_class_definitionContext* ctx) = 0;
  virtual void exitShort_class_definition(modelicaParser::Short_class_definitionContext* ctx) = 0;

  virtual void enterEquation_section(modelicaParser::Equation_sectionContext* ctx) = 0;
  virtual void exitEquation_section(modelicaParser::Equation_sectionContext* ctx) = 0;

  virtual void enterAlgorithm_section(modelicaParser::Algorithm_sectionContext* ctx) = 0;
  virtual void exitAlgorithm_section(modelicaParser::Algorithm_sectionContext* ctx) = 0;

  virtual void enterEquation(modelicaParser::EquationContext* ctx) = 0;
  virtual void exitEquation(modelicaParser::EquationContext* ctx) = 0;

  virtual void enterStatement(modelicaParser::StatementContext* ctx) = 0;
  virtual void exitStatement(modelicaParser::StatementContext* ctx) = 0;

  virtual void enterIf_equation(modelicaParser::If_equationContext* ctx) = 0;
  virtual void exitIf_equation(modelicaParser::If_equationContext* ctx) = 0;

  virtual void enterIf_statement(modelicaParser::If_statementContext* ctx) = 0;
  virtual void exitIf_statement(modelicaParser::If_statementContext* ctx) = 0;

  virtual void enterFor_equation(modelicaParser::For_equationContext* ctx) = 0;
  virtual void exitFor_equation(modelicaParser::For_equationContext* ctx) = 0;

  virtual void enterFor_statement(modelicaParser::For_statementContext* ctx) = 0;
  virtual void exitFor_statement(modelicaParser::For_statementContext* ctx) = 0;

  virtual void enterFor_indices(modelicaParser::For_indicesContext* ctx) = 0;
  virtual void exitFor_indices(modelicaParser::For_indicesContext* ctx) = 0;

  virtual void enterFor_index(modelicaParser::For_indexContext* ctx) = 0;
  virtual void exitFor_index(modelicaParser::For_indexContext* ctx) = 0;

  virtual void enterWhile_statement(modelicaParser::While_statementContext* ctx) = 0;
  virtual void exitWhile_statement(modelicaParser::While_statementContext* ctx) = 0;

  virtual void enterWhen_equation(modelicaParser::When_equationContext* ctx) = 0;
  virtual void exitWhen_equation(modelicaParser::When_equationContext* ctx) = 0;

  virtual void enterWhen_statement(modelicaParser::When_statementContext* ctx) = 0;
  virtual void exitWhen_statement(modelicaParser::When_statementContext* ctx) = 0;

  virtual void enterConnect_clause(modelicaParser::Connect_clauseContext* ctx) = 0;
  virtual void exitConnect_clause(modelicaParser::Connect_clauseContext* ctx) = 0;

  virtual void enterExpression(modelicaParser::ExpressionContext* ctx) = 0;
  virtual void exitExpression(modelicaParser::ExpressionContext* ctx) = 0;

  virtual void enterSimple_expression(modelicaParser::Simple_expressionContext* ctx) = 0;
  virtual void exitSimple_expression(modelicaParser::Simple_expressionContext* ctx) = 0;

  virtual void enterLogical_expression(modelicaParser::Logical_expressionContext* ctx) = 0;
  virtual void exitLogical_expression(modelicaParser::Logical_expressionContext* ctx) = 0;

  virtual void enterLogical_term(modelicaParser::Logical_termContext* ctx) = 0;
  virtual void exitLogical_term(modelicaParser::Logical_termContext* ctx) = 0;

  virtual void enterLogical_factor(modelicaParser::Logical_factorContext* ctx) = 0;
  virtual void exitLogical_factor(modelicaParser::Logical_factorContext* ctx) = 0;

  virtual void enterRelation(modelicaParser::RelationContext* ctx) = 0;
  virtual void exitRelation(modelicaParser::RelationContext* ctx) = 0;

  virtual void enterRel_op(modelicaParser::Rel_opContext* ctx) = 0;
  virtual void exitRel_op(modelicaParser::Rel_opContext* ctx) = 0;

  virtual void enterArithmetic_expression(modelicaParser::Arithmetic_expressionContext* ctx) = 0;
  virtual void exitArithmetic_expression(modelicaParser::Arithmetic_expressionContext* ctx) = 0;

  virtual void enterAdd_op(modelicaParser::Add_opContext* ctx) = 0;
  virtual void exitAdd_op(modelicaParser::Add_opContext* ctx) = 0;

  virtual void enterTerm(modelicaParser::TermContext* ctx) = 0;
  virtual void exitTerm(modelicaParser::TermContext* ctx) = 0;

  virtual void enterMul_op(modelicaParser::Mul_opContext* ctx) = 0;
  virtual void exitMul_op(modelicaParser::Mul_opContext* ctx) = 0;

  virtual void enterFactor(modelicaParser::FactorContext* ctx) = 0;
  virtual void exitFactor(modelicaParser::FactorContext* ctx) = 0;

  virtual void enterPrimary(modelicaParser::PrimaryContext* ctx) = 0;
  virtual void exitPrimary(modelicaParser::PrimaryContext* ctx) = 0;

  virtual void enterName(modelicaParser::NameContext* ctx) = 0;
  virtual void exitName(modelicaParser::NameContext* ctx) = 0;

  virtual void enterComponent_reference(modelicaParser::Component_referenceContext* ctx) = 0;
  virtual void exitComponent_reference(modelicaParser::Component_referenceContext* ctx) = 0;

  virtual void enterFunction_call_args(modelicaParser::Function_call_argsContext* ctx) = 0;
  virtual void exitFunction_call_args(modelicaParser::Function_call_argsContext* ctx) = 0;

  virtual void enterFunction_arguments(modelicaParser::Function_argumentsContext* ctx) = 0;
  virtual void exitFunction_arguments(modelicaParser::Function_argumentsContext* ctx) = 0;

  virtual void enterNamed_arguments(modelicaParser::Named_argumentsContext* ctx) = 0;
  virtual void exitNamed_arguments(modelicaParser::Named_argumentsContext* ctx) = 0;

  virtual void enterNamed_argument(modelicaParser::Named_argumentContext* ctx) = 0;
  virtual void exitNamed_argument(modelicaParser::Named_argumentContext* ctx) = 0;

  virtual void enterFunction_argument(modelicaParser::Function_argumentContext* ctx) = 0;
  virtual void exitFunction_argument(modelicaParser::Function_argumentContext* ctx) = 0;

  virtual void enterOutput_expression_list(modelicaParser::Output_expression_listContext* ctx) = 0;
  virtual void exitOutput_expression_list(modelicaParser::Output_expression_listContext* ctx) = 0;

  virtual void enterExpression_list(modelicaParser::Expression_listContext* ctx) = 0;
  virtual void exitExpression_list(modelicaParser::Expression_listContext* ctx) = 0;

  virtual void enterArray_subscripts(modelicaParser::Array_subscriptsContext* ctx) = 0;
  virtual void exitArray_subscripts(modelicaParser::Array_subscriptsContext* ctx) = 0;

  virtual void enterSubscript(modelicaParser::SubscriptContext* ctx) = 0;
  virtual void exitSubscript(modelicaParser::SubscriptContext* ctx) = 0;

  virtual void enterComment(modelicaParser::CommentContext* ctx) = 0;
  virtual void exitComment(modelicaParser::CommentContext* ctx) = 0;

  virtual void enterString_comment(modelicaParser::String_commentContext* ctx) = 0;
  virtual void exitString_comment(modelicaParser::String_commentContext* ctx) = 0;

  virtual void enterModel_annotation(modelicaParser::Model_annotationContext* ctx) = 0;
  virtual void exitModel_annotation(modelicaParser::Model_annotationContext* ctx) = 0;

  virtual void enterAnnotation(modelicaParser::AnnotationContext* ctx) = 0;
  virtual void exitAnnotation(modelicaParser::AnnotationContext* ctx) = 0;
};
