
// Generated from Iron.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "IronListener.h"


/**
 * This class provides an empty implementation of IronListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  IronBaseListener : public IronListener {
public:

  virtual void enterProgram(IronParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(IronParser::ProgramContext * /*ctx*/) override { }

  virtual void enterImportStatement(IronParser::ImportStatementContext * /*ctx*/) override { }
  virtual void exitImportStatement(IronParser::ImportStatementContext * /*ctx*/) override { }

  virtual void enterQualifiedName(IronParser::QualifiedNameContext * /*ctx*/) override { }
  virtual void exitQualifiedName(IronParser::QualifiedNameContext * /*ctx*/) override { }

  virtual void enterEntryPoint(IronParser::EntryPointContext * /*ctx*/) override { }
  virtual void exitEntryPoint(IronParser::EntryPointContext * /*ctx*/) override { }

  virtual void enterStatementList(IronParser::StatementListContext * /*ctx*/) override { }
  virtual void exitStatementList(IronParser::StatementListContext * /*ctx*/) override { }

  virtual void enterReturn(IronParser::ReturnContext * /*ctx*/) override { }
  virtual void exitReturn(IronParser::ReturnContext * /*ctx*/) override { }

  virtual void enterFunctionDeclaration(IronParser::FunctionDeclarationContext * /*ctx*/) override { }
  virtual void exitFunctionDeclaration(IronParser::FunctionDeclarationContext * /*ctx*/) override { }

  virtual void enterArrowFunctionInline(IronParser::ArrowFunctionInlineContext * /*ctx*/) override { }
  virtual void exitArrowFunctionInline(IronParser::ArrowFunctionInlineContext * /*ctx*/) override { }

  virtual void enterArrowFunctionBlock(IronParser::ArrowFunctionBlockContext * /*ctx*/) override { }
  virtual void exitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext * /*ctx*/) override { }

  virtual void enterFunctionSignature(IronParser::FunctionSignatureContext * /*ctx*/) override { }
  virtual void exitFunctionSignature(IronParser::FunctionSignatureContext * /*ctx*/) override { }

  virtual void enterFunctionReturnType(IronParser::FunctionReturnTypeContext * /*ctx*/) override { }
  virtual void exitFunctionReturnType(IronParser::FunctionReturnTypeContext * /*ctx*/) override { }

  virtual void enterFunctionArgs(IronParser::FunctionArgsContext * /*ctx*/) override { }
  virtual void exitFunctionArgs(IronParser::FunctionArgsContext * /*ctx*/) override { }

  virtual void enterFunctionArg(IronParser::FunctionArgContext * /*ctx*/) override { }
  virtual void exitFunctionArg(IronParser::FunctionArgContext * /*ctx*/) override { }

  virtual void enterFunctionCall(IronParser::FunctionCallContext * /*ctx*/) override { }
  virtual void exitFunctionCall(IronParser::FunctionCallContext * /*ctx*/) override { }

  virtual void enterFunctionCallArgs(IronParser::FunctionCallArgsContext * /*ctx*/) override { }
  virtual void exitFunctionCallArgs(IronParser::FunctionCallArgsContext * /*ctx*/) override { }

  virtual void enterFunctionCallArg(IronParser::FunctionCallArgContext * /*ctx*/) override { }
  virtual void exitFunctionCallArg(IronParser::FunctionCallArgContext * /*ctx*/) override { }

  virtual void enterVarDeclaration(IronParser::VarDeclarationContext * /*ctx*/) override { }
  virtual void exitVarDeclaration(IronParser::VarDeclarationContext * /*ctx*/) override { }

  virtual void enterAssignment(IronParser::AssignmentContext * /*ctx*/) override { }
  virtual void exitAssignment(IronParser::AssignmentContext * /*ctx*/) override { }

  virtual void enterVarAssignment(IronParser::VarAssignmentContext * /*ctx*/) override { }
  virtual void exitVarAssignment(IronParser::VarAssignmentContext * /*ctx*/) override { }

  virtual void enterExpr(IronParser::ExprContext * /*ctx*/) override { }
  virtual void exitExpr(IronParser::ExprContext * /*ctx*/) override { }

  virtual void enterNumber(IronParser::NumberContext * /*ctx*/) override { }
  virtual void exitNumber(IronParser::NumberContext * /*ctx*/) override { }

  virtual void enterDataFormat(IronParser::DataFormatContext * /*ctx*/) override { }
  virtual void exitDataFormat(IronParser::DataFormatContext * /*ctx*/) override { }

  virtual void enterVarTypes(IronParser::VarTypesContext * /*ctx*/) override { }
  virtual void exitVarTypes(IronParser::VarTypesContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

