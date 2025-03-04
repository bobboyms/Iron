
// Generated from Iron.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  IronLexer : public antlr4::Lexer {
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

