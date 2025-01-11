
// Generated from Iron.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  IronLexer : public antlr4::Lexer {
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

