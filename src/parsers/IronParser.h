
// Generated from Iron.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  IronParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, LINE_COMMENT = 2, BLOCK_COMMENT = 3, COMMA = 4, COLON = 5, 
    EQ = 6, SEMICOLON = 7, DOT = 8, STAR = 9, L_CURLY = 10, R_CURLY = 11, 
    L_PAREN = 12, R_PAREN = 13, PLUS = 14, MINUS = 15, DIV = 16, L_BRACKET = 17, 
    R_BRACKET = 18, ARROW = 19, FUNCTION = 20, LET = 21, PUBLIC = 22, IMPORT = 23, 
    RETURN = 24, TYPE_INT = 25, TYPE_CHAR = 26, TYPE_FLOAT = 27, TYPE_STRING = 28, 
    TYPE_BOOLEAN = 29, TYPE_DOUBLE = 30, REAL_NUMBER = 31, INT_NUMBER = 32, 
    BOOLEAN_VALUE = 33, STRING_LITERAL = 34, IDENTIFIER = 35, NEWLINE = 36, 
    WS = 37
  };

  enum {
    RuleProgram = 0, RuleImportStatement = 1, RuleQualifiedName = 2, RuleEntryPoint = 3, 
    RuleStatementList = 4, RuleReturnStatement = 5, RuleFunctionDeclaration = 6, 
    RuleArrowFunctionInline = 7, RuleArrowFunctionBlock = 8, RuleFunctionSignature = 9, 
    RuleFunctionReturnType = 10, RuleFunctionArgs = 11, RuleFunctionArg = 12, 
    RuleFunctionCall = 13, RuleFunctionCallArgs = 14, RuleFunctionCallArg = 15, 
    RuleVarDeclaration = 16, RuleAssignment = 17, RuleVarAssignment = 18, 
    RuleExpr = 19, RuleNumber = 20, RuleDataFormat = 21, RuleVarTypes = 22
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
  class EntryPointContext;
  class StatementListContext;
  class ReturnStatementContext;
  class FunctionDeclarationContext;
  class ArrowFunctionInlineContext;
  class ArrowFunctionBlockContext;
  class FunctionSignatureContext;
  class FunctionReturnTypeContext;
  class FunctionArgsContext;
  class FunctionArgContext;
  class FunctionCallContext;
  class FunctionCallArgsContext;
  class FunctionCallArgContext;
  class VarDeclarationContext;
  class AssignmentContext;
  class VarAssignmentContext;
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
    std::vector<FunctionDeclarationContext *> functionDeclaration();
    FunctionDeclarationContext* functionDeclaration(size_t i);
    std::vector<EntryPointContext *> entryPoint();
    EntryPointContext* entryPoint(size_t i);

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

  class  EntryPointContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *argVar = nullptr;
    EntryPointContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_PAREN();
    antlr4::tree::TerminalNode *R_PAREN();
    antlr4::tree::TerminalNode *L_CURLY();
    StatementListContext *statementList();
    antlr4::tree::TerminalNode *R_CURLY();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EntryPointContext* entryPoint();

  class  StatementListContext : public antlr4::ParserRuleContext {
  public:
    StatementListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<VarDeclarationContext *> varDeclaration();
    VarDeclarationContext* varDeclaration(size_t i);
    std::vector<FunctionCallContext *> functionCall();
    FunctionCallContext* functionCall(size_t i);
    std::vector<VarAssignmentContext *> varAssignment();
    VarAssignmentContext* varAssignment(size_t i);
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<ReturnStatementContext *> returnStatement();
    ReturnStatementContext* returnStatement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StatementListContext* statementList();

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

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArrowFunctionInlineContext* arrowFunctionInline();

  class  ArrowFunctionBlockContext : public antlr4::ParserRuleContext {
  public:
    ArrowFunctionBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionSignatureContext *functionSignature();
    antlr4::tree::TerminalNode *ARROW();
    antlr4::tree::TerminalNode *L_CURLY();
    StatementListContext *statementList();
    antlr4::tree::TerminalNode *R_CURLY();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArrowFunctionBlockContext* arrowFunctionBlock();

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
    VarTypesContext *varTypes();
    FunctionSignatureContext *functionSignature();
    AssignmentContext *assignment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionArgContext* functionArg();

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
    ArrowFunctionBlockContext *arrowFunctionBlock();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionCallArgContext* functionCallArg();

  class  VarDeclarationContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    VarDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LET();
    antlr4::tree::TerminalNode *COLON();
    VarTypesContext *varTypes();
    antlr4::tree::TerminalNode *IDENTIFIER();
    AssignmentContext *assignment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VarDeclarationContext* varDeclaration();

  class  AssignmentContext : public antlr4::ParserRuleContext {
  public:
    AssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EQ();
    ArrowFunctionInlineContext *arrowFunctionInline();
    ArrowFunctionBlockContext *arrowFunctionBlock();
    DataFormatContext *dataFormat();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssignmentContext* assignment();

  class  VarAssignmentContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *varName = nullptr;
    VarAssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *IDENTIFIER();
    ArrowFunctionInlineContext *arrowFunctionInline();
    ArrowFunctionBlockContext *arrowFunctionBlock();
    DataFormatContext *dataFormat();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VarAssignmentContext* varAssignment();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    IronParser::ExprContext *left = nullptr;
    antlr4::Token *varName = nullptr;
    antlr4::Token *mult = nullptr;
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

  bool exprSempred(ExprContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

