
// Generated from HightLavelIR.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "HightLavelIRListener.h"


/**
 * This class provides an empty implementation of HightLavelIRListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  HightLavelIRBaseListener : public HightLavelIRListener {
public:

  virtual void enterProgram(HightLavelIRParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(HightLavelIRParser::ProgramContext * /*ctx*/) override { }

  virtual void enterImportStatement(HightLavelIRParser::ImportStatementContext * /*ctx*/) override { }
  virtual void exitImportStatement(HightLavelIRParser::ImportStatementContext * /*ctx*/) override { }

  virtual void enterQualifiedName(HightLavelIRParser::QualifiedNameContext * /*ctx*/) override { }
  virtual void exitQualifiedName(HightLavelIRParser::QualifiedNameContext * /*ctx*/) override { }

  virtual void enterStatementList(HightLavelIRParser::StatementListContext * /*ctx*/) override { }
  virtual void exitStatementList(HightLavelIRParser::StatementListContext * /*ctx*/) override { }

  virtual void enterFunctionDeclaration(HightLavelIRParser::FunctionDeclarationContext * /*ctx*/) override { }
  virtual void exitFunctionDeclaration(HightLavelIRParser::FunctionDeclarationContext * /*ctx*/) override { }

  virtual void enterFunctionSignature(HightLavelIRParser::FunctionSignatureContext * /*ctx*/) override { }
  virtual void exitFunctionSignature(HightLavelIRParser::FunctionSignatureContext * /*ctx*/) override { }

  virtual void enterFunctionReturnType(HightLavelIRParser::FunctionReturnTypeContext * /*ctx*/) override { }
  virtual void exitFunctionReturnType(HightLavelIRParser::FunctionReturnTypeContext * /*ctx*/) override { }

  virtual void enterFunctionArgs(HightLavelIRParser::FunctionArgsContext * /*ctx*/) override { }
  virtual void exitFunctionArgs(HightLavelIRParser::FunctionArgsContext * /*ctx*/) override { }

  virtual void enterFunctionArg(HightLavelIRParser::FunctionArgContext * /*ctx*/) override { }
  virtual void exitFunctionArg(HightLavelIRParser::FunctionArgContext * /*ctx*/) override { }

  virtual void enterFunctionCall(HightLavelIRParser::FunctionCallContext * /*ctx*/) override { }
  virtual void exitFunctionCall(HightLavelIRParser::FunctionCallContext * /*ctx*/) override { }

  virtual void enterFunctionCallArgs(HightLavelIRParser::FunctionCallArgsContext * /*ctx*/) override { }
  virtual void exitFunctionCallArgs(HightLavelIRParser::FunctionCallArgsContext * /*ctx*/) override { }

  virtual void enterFunctionCallArg(HightLavelIRParser::FunctionCallArgContext * /*ctx*/) override { }
  virtual void exitFunctionCallArg(HightLavelIRParser::FunctionCallArgContext * /*ctx*/) override { }

  virtual void enterOp(HightLavelIRParser::OpContext * /*ctx*/) override { }
  virtual void exitOp(HightLavelIRParser::OpContext * /*ctx*/) override { }

  virtual void enterOpRight(HightLavelIRParser::OpRightContext * /*ctx*/) override { }
  virtual void exitOpRight(HightLavelIRParser::OpRightContext * /*ctx*/) override { }

  virtual void enterOpLeft(HightLavelIRParser::OpLeftContext * /*ctx*/) override { }
  virtual void exitOpLeft(HightLavelIRParser::OpLeftContext * /*ctx*/) override { }

  virtual void enterTypeRight(HightLavelIRParser::TypeRightContext * /*ctx*/) override { }
  virtual void exitTypeRight(HightLavelIRParser::TypeRightContext * /*ctx*/) override { }

  virtual void enterTypeLeft(HightLavelIRParser::TypeLeftContext * /*ctx*/) override { }
  virtual void exitTypeLeft(HightLavelIRParser::TypeLeftContext * /*ctx*/) override { }

  virtual void enterCast(HightLavelIRParser::CastContext * /*ctx*/) override { }
  virtual void exitCast(HightLavelIRParser::CastContext * /*ctx*/) override { }

  virtual void enterMath_op(HightLavelIRParser::Math_opContext * /*ctx*/) override { }
  virtual void exitMath_op(HightLavelIRParser::Math_opContext * /*ctx*/) override { }

  virtual void enterExpr(HightLavelIRParser::ExprContext * /*ctx*/) override { }
  virtual void exitExpr(HightLavelIRParser::ExprContext * /*ctx*/) override { }

  virtual void enterNumber(HightLavelIRParser::NumberContext * /*ctx*/) override { }
  virtual void exitNumber(HightLavelIRParser::NumberContext * /*ctx*/) override { }

  virtual void enterDataFormat(HightLavelIRParser::DataFormatContext * /*ctx*/) override { }
  virtual void exitDataFormat(HightLavelIRParser::DataFormatContext * /*ctx*/) override { }

  virtual void enterVarTypes(HightLavelIRParser::VarTypesContext * /*ctx*/) override { }
  virtual void exitVarTypes(HightLavelIRParser::VarTypesContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

