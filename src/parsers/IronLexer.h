
// Generated from Iron.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  IronLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, LINE_COMMENT = 4, BLOCK_COMMENT = 5, COMMA = 6, 
    COLON = 7, EQ = 8, SEMICOLON = 9, DOT = 10, STAR = 11, L_CURLY = 12, 
    R_CURLY = 13, L_PAREN = 14, R_PAREN = 15, PLUS = 16, MINUS = 17, DIV = 18, 
    L_BRACKET = 19, R_BRACKET = 20, ARROW = 21, AND = 22, OR = 23, NOT = 24, 
    EQEQ = 25, NEQ = 26, LT = 27, LTE = 28, GT = 29, GTE = 30, IF = 31, 
    FUNCTION = 32, LET = 33, ELSE = 34, PUBLIC = 35, IMPORT = 36, RETURN = 37, 
    TYPE_INT = 38, TYPE_CHAR = 39, TYPE_FLOAT = 40, TYPE_STRING = 41, TYPE_BOOLEAN = 42, 
    TYPE_DOUBLE = 43, TYPE_VOID = 44, REAL_NUMBER = 45, INT_NUMBER = 46, 
    BOOLEAN_VALUE = 47, STRING_LITERAL = 48, IDENTIFIER = 49, NEWLINE = 50, 
    WS = 51
  };

  explicit IronLexer(antlr4::CharStream *input);

  ~IronLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

