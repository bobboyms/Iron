
// Generated from Iron.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  IronParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, LINE_COMMENT = 6, 
    BLOCK_COMMENT = 7, COMMA = 8, COLON = 9, EQ = 10, SEMICOLON = 11, DOT = 12, 
    STAR = 13, L_CURLY = 14, R_CURLY = 15, L_PAREN = 16, R_PAREN = 17, PLUS = 18, 
    MINUS = 19, DIV = 20, L_BRACKET = 21, R_BRACKET = 22, ARROW = 23, AND = 24, 
    OR = 25, NOT = 26, EQEQ = 27, NEQ = 28, LT = 29, LTE = 30, GT = 31, 
    GTE = 32, IF = 33, FUNCTION = 34, LET = 35, MUT = 36, ELSE = 37, PUBLIC = 38, 
    IMPORT = 39, RETURN = 40, IN = 41, FOR = 42, WHILE = 43, TYPE_INT = 44, 
    TYPE_CHAR = 45, TYPE_FLOAT = 46, TYPE_STRING = 47, TYPE_BOOLEAN = 48, 
    TYPE_DOUBLE = 49, TYPE_VOID = 50, REPEAT = 51, STRUCT = 52, OPTIONS = 53, 
    CONTINUE = 54, BREAK = 55, REAL_NUMBER = 56, INT_NUMBER = 57, BOOLEAN_VALUE = 58, 
    STRING_LITERAL = 59, IDENTIFIER = 60, NEWLINE = 61, WS = 62
  };

  enum {
    RuleProgram = 0, RuleImportStatement = 1, RuleQualifiedName = 2, RuleStatementList = 3, 
    RuleBreakStatement = 4, RuleContinueStatement = 5, RuleStructStatement = 6, 
    RuleStructBody = 7, RuleOptionsStatement = 8, RuleOptionsBody = 9, RuleReturnStatement = 10, 
    RuleWhileStatement = 11, RuleRepeatStatement = 12, RuleForStatement = 13, 
    RuleIntervals = 14, RuleFormatStatement = 15, RuleFormatArguments = 16, 
    RuleFormatArgument = 17, RuleExternBlock = 18, RuleExternFunctionDeclaration = 19, 
    RuleExternFunctionArgs = 20, RuleExternFunctionArg = 21, RuleCTypes = 22, 
    RuleFunctionDeclaration = 23, RuleArrowFunctionInline = 24, RuleFunctionSignature = 25, 
    RuleFunctionReturnType = 26, RuleFunctionArgs = 27, RuleFunctionArg = 28, 
    RuleFnsignature = 29, RuleFunctionCall = 30, RuleFunctionCallArgs = 31, 
    RuleFunctionCallArg = 32, RuleVarDeclaration = 33, RuleAssignment = 34, 
    RuleStructInit = 35, RuleStructInitBody = 36, RuleVarAssignment = 37, 
    RuleIfBlock = 38, RuleIfStatement = 39, RuleElseStatement = 40, RuleBoolExpr = 41, 
    RuleExpr = 42, RuleNumber = 43, RuleDataFormat = 44, RuleVarTypes = 45
  };

  explicit IronParser(antlr4::TokenStream *input);

  IronParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~IronParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgramContext;
  class ImportStatementContext;
  class QualifiedNameContext;
  class StatementListContext;
  class BreakStatementContext;
  class ContinueStatementContext;
  class StructStatementContext;
  class StructBodyContext;
  class OptionsStatementContext;
  class OptionsBodyContext;
  class ReturnStatementContext;
  class WhileStatementContext;
  class RepeatStatementContext;
  class ForStatementContext;
  class IntervalsContext;
  class FormatStatementContext;
  class FormatArgumentsContext;
  class FormatArgumentContext;
  class ExternBlockContext;
  class ExternFunctionDeclarationContext;
  class ExternFunctionArgsContext;
  class ExternFunctionArgContext;
  class CTypesContext;
  class FunctionDeclarationContext;
  class ArrowFunctionInlineContext;
  class FunctionSignatureContext;
  class FunctionReturnTypeContext;
  class FunctionArgsContext;
  class FunctionArgContext;
  class FnsignatureContext;
  class FunctionCallContext;
  class FunctionCallArgsContext;
  class FunctionCallArgContext;
  class VarDeclarationContext;
  class AssignmentContext;
  class StructInitContext;
  class StructInitBodyContext;
  class VarAssignmentContext;
  class IfBlockContext;
  class IfStatementContext;
  class ElseStatementContext;
  class BoolExprContext;
  class ExprContext;
  class NumberContext;
  class DataFormatContext;
  class VarTypesContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<ImportStatementContext *> importStatement();
    ImportStatementContext* importStatement(size_t i);
    ExternBlockContext *externBlock();
    std::vector<FunctionDeclarationContext *> functionDeclaration();
    FunctionDeclarationContext* functionDeclaration(size_t i);
    std::vector<StructStatementContext *> structStatement();
    StructStatementContext* structStatement(size_t i);
    std::vector<OptionsStatementContext *> optionsStatement();
    OptionsStatementContext* optionsStatement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ProgramContext* program();

  class  ImportStatementContext : public antlr4::ParserRuleContext {
  public:
    ImportStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    QualifiedNameContext *qualifiedName();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *STAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImportStatementContext* importStatement();

  class  QualifiedNameContext : public antlr4::ParserRuleContext {
  public:
    QualifiedNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DOT();
    antlr4::tree::TerminalNode* DOT(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  QualifiedNameContext* qualifiedName();

  class  StatementListContext : public antlr4::ParserRuleContext {
  public:
    StatementListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ContinueStatementContext *> continueStatement();
    ContinueStatementContext* continueStatement(size_t i);
    std::vector<BreakStatementContext *> breakStatement();
    BreakStatementContext* breakStatement(size_t i);
    std::vector<VarDeclarationContext *> varDeclaration();
    VarDeclarationContext* varDeclaration(size_t i);
    std::vector<VarAssignmentContext *> varAssignment();
    VarAssignmentContext* varAssignment(size_t i);
    std::vector<FunctionCallContext *> functionCall();
    FunctionCallContext* functionCall(size_t i);
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<IfStatementContext *> ifStatement();
    IfStatementContext* ifStatement(size_t i);
    std::vector<WhileStatementContext *> whileStatement();
    WhileStatementContext* whileStatement(size_t i);
    std::vector<RepeatStatementContext *> repeatStatement();
    RepeatStatementContext* repeatStatement(size_t i);
    std::vector<ForStatementContext *> forStatement();
    ForStatementContext* forStatement(size_t i);
    std::vector<ReturnStatementContext *> returnStatement();
    ReturnStatementContext* returnStatement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StatementListContext* statementList();

  class  BreakStatementContext : public antlr4::ParserRuleContext {
  public:
    BreakStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BREAK();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BreakStatementContext* breakStatement();

  class  ContinueStatementContext : public antlr4::ParserRuleContext {
  public:
    ContinueStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONTINUE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ContinueStatementContext* continueStatement();

  class  StructStatementContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *structName = nullptr;
    StructStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRUCT();
    antlr4::tree::TerminalNode *L_CURLY();
    std::vector<StructBodyContext *> structBody();
    StructBodyContext* structBody(size_t i);
    antlr4::tree::TerminalNode *R_CURLY();
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StructStatementContext* structStatement();

  class  StructBodyContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    antlr4::Token *anotherType = nullptr;
    StructBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    VarTypesContext *varTypes();
    antlr4::tree::TerminalNode *MUT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StructBodyContext* structBody();

  class  OptionsStatementContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *optionName = nullptr;
    OptionsStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPTIONS();
    antlr4::tree::TerminalNode *L_CURLY();
    std::vector<OptionsBodyContext *> optionsBody();
    OptionsBodyContext* optionsBody(size_t i);
    antlr4::tree::TerminalNode *R_CURLY();
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OptionsStatementContext* optionsStatement();

  class  OptionsBodyContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *itemName = nullptr;
    OptionsBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    FunctionSignatureContext *functionSignature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OptionsBodyContext* optionsBody();

  class  ReturnStatementContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    ReturnStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RETURN();
    DataFormatContext *dataFormat();
    FunctionCallContext *functionCall();
    ExprContext *expr();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ReturnStatementContext* returnStatement();

  class  WhileStatementContext : public antlr4::ParserRuleContext {
  public:
    WhileStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WHILE();
    BoolExprContext *boolExpr();
    antlr4::tree::TerminalNode *L_CURLY();
    StatementListContext *statementList();
    antlr4::tree::TerminalNode *R_CURLY();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  WhileStatementContext* whileStatement();

  class  RepeatStatementContext : public antlr4::ParserRuleContext {
  public:
    RepeatStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *REPEAT();
    antlr4::tree::TerminalNode *L_CURLY();
    StatementListContext *statementList();
    antlr4::tree::TerminalNode *R_CURLY();
    antlr4::tree::TerminalNode *WHILE();
    BoolExprContext *boolExpr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RepeatStatementContext* repeatStatement();

  class  ForStatementContext : public antlr4::ParserRuleContext {
  public:
    ForStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *IN();
    IntervalsContext *intervals();
    antlr4::tree::TerminalNode *L_CURLY();
    StatementListContext *statementList();
    antlr4::tree::TerminalNode *R_CURLY();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ForStatementContext* forStatement();

  class  IntervalsContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *firstNumber = nullptr;
    antlr4::Token *firstVarName = nullptr;
    antlr4::Token *secondNumber = nullptr;
    antlr4::Token *secondVarName = nullptr;
    IntervalsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> INT_NUMBER();
    antlr4::tree::TerminalNode* INT_NUMBER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IntervalsContext* intervals();

  class  FormatStatementContext : public antlr4::ParserRuleContext {
  public:
    FormatStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *R_PAREN();
    FormatArgumentsContext *formatArguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FormatStatementContext* formatStatement();

  class  FormatArgumentsContext : public antlr4::ParserRuleContext {
  public:
    FormatArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FormatArgumentContext *> formatArgument();
    FormatArgumentContext* formatArgument(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FormatArgumentsContext* formatArguments();

  class  FormatArgumentContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    FormatArgumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DataFormatContext *dataFormat();
    FunctionCallContext *functionCall();
    ExprContext *expr();
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FormatArgumentContext* formatArgument();

  class  ExternBlockContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *language = nullptr;
    ExternBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_CURLY();
    antlr4::tree::TerminalNode *R_CURLY();
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<ExternFunctionDeclarationContext *> externFunctionDeclaration();
    ExternFunctionDeclarationContext* externFunctionDeclaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExternBlockContext* externBlock();

  class  ExternFunctionDeclarationContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *exterFunctionName = nullptr;
    antlr4::Token *varied = nullptr;
    ExternFunctionDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FUNCTION();
    antlr4::tree::TerminalNode *L_PAREN();
    antlr4::tree::TerminalNode *R_PAREN();
    antlr4::tree::TerminalNode *IDENTIFIER();
    ExternFunctionArgsContext *externFunctionArgs();
    antlr4::tree::TerminalNode *COMMA();
    FunctionReturnTypeContext *functionReturnType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExternFunctionDeclarationContext* externFunctionDeclaration();

  class  ExternFunctionArgsContext : public antlr4::ParserRuleContext {
  public:
    ExternFunctionArgsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExternFunctionArgContext *> externFunctionArg();
    ExternFunctionArgContext* externFunctionArg(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExternFunctionArgsContext* externFunctionArgs();

  class  ExternFunctionArgContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    antlr4::Token *ptr = nullptr;
    ExternFunctionArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    CTypesContext *cTypes();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *STAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExternFunctionArgContext* externFunctionArg();

  class  CTypesContext : public antlr4::ParserRuleContext {
  public:
    CTypesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TYPE_BOOLEAN();
    antlr4::tree::TerminalNode *TYPE_CHAR();
    antlr4::tree::TerminalNode *TYPE_DOUBLE();
    antlr4::tree::TerminalNode *TYPE_FLOAT();
    antlr4::tree::TerminalNode *TYPE_INT();
    antlr4::tree::TerminalNode *TYPE_VOID();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CTypesContext* cTypes();

  class  FunctionDeclarationContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *functionName = nullptr;
    FunctionDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FUNCTION();
    FunctionSignatureContext *functionSignature();
    antlr4::tree::TerminalNode *L_CURLY();
    StatementListContext *statementList();
    antlr4::tree::TerminalNode *R_CURLY();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *PUBLIC();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionDeclarationContext* functionDeclaration();

  class  ArrowFunctionInlineContext : public antlr4::ParserRuleContext {
  public:
    ArrowFunctionInlineContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionSignatureContext *functionSignature();
    antlr4::tree::TerminalNode *ARROW();
    ExprContext *expr();
    antlr4::tree::TerminalNode *L_CURLY();
    StatementListContext *statementList();
    antlr4::tree::TerminalNode *R_CURLY();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArrowFunctionInlineContext* arrowFunctionInline();

  class  FunctionSignatureContext : public antlr4::ParserRuleContext {
  public:
    FunctionSignatureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_PAREN();
    antlr4::tree::TerminalNode *R_PAREN();
    FunctionArgsContext *functionArgs();
    FunctionReturnTypeContext *functionReturnType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionSignatureContext* functionSignature();

  class  FunctionReturnTypeContext : public antlr4::ParserRuleContext {
  public:
    FunctionReturnTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    VarTypesContext *varTypes();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionReturnTypeContext* functionReturnType();

  class  FunctionArgsContext : public antlr4::ParserRuleContext {
  public:
    FunctionArgsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FunctionArgContext *> functionArg();
    FunctionArgContext* functionArg(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionArgsContext* functionArgs();

  class  FunctionArgContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    FunctionArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *IDENTIFIER();
    FnsignatureContext *fnsignature();
    VarTypesContext *varTypes();
    AssignmentContext *assignment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionArgContext* functionArg();

  class  FnsignatureContext : public antlr4::ParserRuleContext {
  public:
    FnsignatureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FUNCTION();
    FunctionSignatureContext *functionSignature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FnsignatureContext* fnsignature();

  class  FunctionCallContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *functionName = nullptr;
    FunctionCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_PAREN();
    antlr4::tree::TerminalNode *R_PAREN();
    antlr4::tree::TerminalNode *IDENTIFIER();
    FunctionCallArgsContext *functionCallArgs();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionCallContext* functionCall();

  class  FunctionCallArgsContext : public antlr4::ParserRuleContext {
  public:
    FunctionCallArgsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FunctionCallArgContext *> functionCallArg();
    FunctionCallArgContext* functionCallArg(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionCallArgsContext* functionCallArgs();

  class  FunctionCallArgContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    antlr4::Token *anotherVarName = nullptr;
    FunctionCallArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    DataFormatContext *dataFormat();
    FunctionCallContext *functionCall();
    ArrowFunctionInlineContext *arrowFunctionInline();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionCallArgContext* functionCallArg();

  class  VarDeclarationContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    antlr4::Token *anotherType = nullptr;
    VarDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LET();
    antlr4::tree::TerminalNode *COLON();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    VarTypesContext *varTypes();
    antlr4::tree::TerminalNode *MUT();
    AssignmentContext *assignment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VarDeclarationContext* varDeclaration();

  class  AssignmentContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    AssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EQ();
    ArrowFunctionInlineContext *arrowFunctionInline();
    DataFormatContext *dataFormat();
    StructInitContext *structInit();
    FunctionCallContext *functionCall();
    ExprContext *expr();
    BoolExprContext *boolExpr();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DOT();
    antlr4::tree::TerminalNode* DOT(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssignmentContext* assignment();

  class  StructInitContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *structName = nullptr;
    StructInitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_CURLY();
    antlr4::tree::TerminalNode *R_CURLY();
    std::vector<StructInitBodyContext *> structInitBody();
    StructInitBodyContext* structInitBody(size_t i);
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StructInitContext* structInit();

  class  StructInitBodyContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    antlr4::Token *anotherVarName = nullptr;
    StructInitBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    DataFormatContext *dataFormat();
    StructInitContext *structInit();
    FunctionCallContext *functionCall();
    ArrowFunctionInlineContext *arrowFunctionInline();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StructInitBodyContext* structInitBody();

  class  VarAssignmentContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    antlr4::Token *anotherVarName = nullptr;
    VarAssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EQ();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    ArrowFunctionInlineContext *arrowFunctionInline();
    FunctionCallContext *functionCall();
    StructInitContext *structInit();
    DataFormatContext *dataFormat();
    ExprContext *expr();
    std::vector<antlr4::tree::TerminalNode *> DOT();
    antlr4::tree::TerminalNode* DOT(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VarAssignmentContext* varAssignment();

  class  IfBlockContext : public antlr4::ParserRuleContext {
  public:
    IfBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_CURLY();
    antlr4::tree::TerminalNode *R_CURLY();
    StatementListContext *statementList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IfBlockContext* ifBlock();

  class  IfStatementContext : public antlr4::ParserRuleContext {
  public:
    IfStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *L_PAREN();
    BoolExprContext *boolExpr();
    antlr4::tree::TerminalNode *R_PAREN();
    IfBlockContext *ifBlock();
    antlr4::tree::TerminalNode *ELSE();
    ElseStatementContext *elseStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IfStatementContext* ifStatement();

  class  ElseStatementContext : public antlr4::ParserRuleContext {
  public:
    ElseStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IfStatementContext *ifStatement();
    IfBlockContext *ifBlock();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElseStatementContext* elseStatement();

  class  BoolExprContext : public antlr4::ParserRuleContext {
  public:
    IronParser::BoolExprContext *left = nullptr;
    antlr4::Token *not_ = nullptr;
    antlr4::Token *booleanValue = nullptr;
    antlr4::Token *varName = nullptr;
    antlr4::Token *op = nullptr;
    IronParser::BoolExprContext *right = nullptr;
    BoolExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_PAREN();
    std::vector<BoolExprContext *> boolExpr();
    BoolExprContext* boolExpr(size_t i);
    antlr4::tree::TerminalNode *R_PAREN();
    antlr4::tree::TerminalNode *NOT();
    antlr4::tree::TerminalNode *BOOLEAN_VALUE();
    NumberContext *number();
    antlr4::tree::TerminalNode *IDENTIFIER();
    FunctionCallContext *functionCall();
    ExprContext *expr();
    antlr4::tree::TerminalNode *EQEQ();
    antlr4::tree::TerminalNode *NEQ();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *LTE();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *GTE();
    antlr4::tree::TerminalNode *AND();
    antlr4::tree::TerminalNode *OR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BoolExprContext* boolExpr();
  BoolExprContext* boolExpr(int precedence);
  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    IronParser::ExprContext *left = nullptr;
    antlr4::Token *varName = nullptr;
    antlr4::Token *mult = nullptr;
    antlr4::Token *mod = nullptr;
    antlr4::Token *div = nullptr;
    IronParser::ExprContext *right = nullptr;
    antlr4::Token *plus = nullptr;
    antlr4::Token *minus = nullptr;
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumberContext *number();
    FunctionCallContext *functionCall();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *L_PAREN();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *R_PAREN();
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExprContext* expr();
  ExprContext* expr(int precedence);
  class  NumberContext : public antlr4::ParserRuleContext {
  public:
    NumberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *REAL_NUMBER();
    antlr4::tree::TerminalNode *INT_NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NumberContext* number();

  class  DataFormatContext : public antlr4::ParserRuleContext {
  public:
    DataFormatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *REAL_NUMBER();
    antlr4::tree::TerminalNode *INT_NUMBER();
    antlr4::tree::TerminalNode *BOOLEAN_VALUE();
    antlr4::tree::TerminalNode *STRING_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DataFormatContext* dataFormat();

  class  VarTypesContext : public antlr4::ParserRuleContext {
  public:
    VarTypesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TYPE_BOOLEAN();
    antlr4::tree::TerminalNode *TYPE_CHAR();
    antlr4::tree::TerminalNode *TYPE_DOUBLE();
    antlr4::tree::TerminalNode *TYPE_FLOAT();
    antlr4::tree::TerminalNode *TYPE_INT();
    antlr4::tree::TerminalNode *TYPE_STRING();
    antlr4::tree::TerminalNode *FUNCTION();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VarTypesContext* varTypes();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool boolExprSempred(BoolExprContext *_localctx, size_t predicateIndex);
  bool exprSempred(ExprContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

