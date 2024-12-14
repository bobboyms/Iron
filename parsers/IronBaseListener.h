
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

  virtual void enterMulDiv(IronParser::MulDivContext * /*ctx*/) override { }
  virtual void exitMulDiv(IronParser::MulDivContext * /*ctx*/) override { }

  virtual void enterAddSub(IronParser::AddSubContext * /*ctx*/) override { }
  virtual void exitAddSub(IronParser::AddSubContext * /*ctx*/) override { }

  virtual void enterParens(IronParser::ParensContext * /*ctx*/) override { }
  virtual void exitParens(IronParser::ParensContext * /*ctx*/) override { }

  virtual void enterInt(IronParser::IntContext * /*ctx*/) override { }
  virtual void exitInt(IronParser::IntContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

