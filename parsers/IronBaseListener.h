
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

  virtual void enterBody(IronParser::BodyContext * /*ctx*/) override { }
  virtual void exitBody(IronParser::BodyContext * /*ctx*/) override { }

  virtual void enterFunctionDeclaration(IronParser::FunctionDeclarationContext * /*ctx*/) override { }
  virtual void exitFunctionDeclaration(IronParser::FunctionDeclarationContext * /*ctx*/) override { }

  virtual void enterStatement(IronParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(IronParser::StatementContext * /*ctx*/) override { }

  virtual void enterVarDeclaration(IronParser::VarDeclarationContext * /*ctx*/) override { }
  virtual void exitVarDeclaration(IronParser::VarDeclarationContext * /*ctx*/) override { }

  virtual void enterDataFormat(IronParser::DataFormatContext * /*ctx*/) override { }
  virtual void exitDataFormat(IronParser::DataFormatContext * /*ctx*/) override { }

  virtual void enterVarTypes(IronParser::VarTypesContext * /*ctx*/) override { }
  virtual void exitVarTypes(IronParser::VarTypesContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

