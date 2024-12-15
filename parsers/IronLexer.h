
// Generated from Iron.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  IronLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, COLON = 2, EQ = 3, SEMICOLON = 4, DOT = 5, STAR = 6, L_CURLY = 7, 
    R_CURLY = 8, L_BRACKET = 9, R_BRACKET = 10, L_PAREN = 11, R_PAREN = 12, 
    FUNCTION = 13, LET = 14, PUBLIC = 15, IMPORT = 16, TYPE_INT = 17, TYPE_CHAR = 18, 
    TYPE_FLOAT = 19, TYPE_STRING = 20, TYPE_BOOLEAN = 21, TYPE_DOUBLE = 22, 
    REAL_NUMBER = 23, INT_NUMBER = 24, BOOLEAN_VALUE = 25, STRING_LITERAL = 26, 
    IDENTIFIER = 27, NEWLINE = 28, WS = 29
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

