
// Generated from HightLavelIR.g4 by ANTLR 4.13.2


#include "HightLavelIRListener.h"

#include "HightLavelIRParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct HightLavelIRParserStaticData final {
  HightLavelIRParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  HightLavelIRParserStaticData(const HightLavelIRParserStaticData&) = delete;
  HightLavelIRParserStaticData(HightLavelIRParserStaticData&&) = delete;
  HightLavelIRParserStaticData& operator=(const HightLavelIRParserStaticData&) = delete;
  HightLavelIRParserStaticData& operator=(HightLavelIRParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag hightlavelirParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<HightLavelIRParserStaticData> hightlavelirParserStaticData = nullptr;

void hightlavelirParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (hightlavelirParserStaticData != nullptr) {
    return;
  }
#else
  assert(hightlavelirParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<HightLavelIRParserStaticData>(
    std::vector<std::string>{
      "program", "importStatement", "qualifiedName", "statementList", "functionDeclaration", 
      "functionSignature", "functionReturnType", "functionArgs", "functionArg", 
      "functionCall", "functionCallArgs", "functionCallArg", "op", "opRight", 
      "opLeft", "typeRight", "typeLeft", "cast", "math_op", "expr", "assignment", 
      "number", "dataFormat", "varTypes"
    },
    std::vector<std::string>{
      "", "':'", "','", "'='", "';'", "'.'", "'*'", "'{'", "'}'", "'('", 
      "')'", "'MULT'", "'PLUS'", "'MINUS'", "'DIV'", "'['", "']'", "'@'", 
      "'->'", "'_'", "'fn'", "'let'", "'public'", "'private'", "'import'", 
      "'return'", "'to'", "'int'", "'char'", "'float'", "'string'", "'boolean'", 
      "'double'", "'void'", "'cast'"
    },
    std::vector<std::string>{
      "", "COLON", "COMMA", "EQ", "SEMICOLON", "DOT", "STAR", "L_CURLY", 
      "R_CURLY", "L_PAREN", "R_PAREN", "MULT", "PLUS", "MINUS", "DIV", "L_BRACKET", 
      "R_BRACKET", "AT", "ARROW", "UNDERSCORE", "FUNCTION", "LET", "PUBLIC", 
      "PRIVATE", "IMPORT", "RETURN", "TO", "TYPE_INT", "TYPE_CHAR", "TYPE_FLOAT", 
      "TYPE_STRING", "TYPE_BOOLEAN", "TYPE_DOUBLE", "VOID", "CAST", "REAL_NUMBER", 
      "INT_NUMBER", "BOOLEAN_VALUE", "STRING_LITERAL", "IDENTIFIER", "NEWLINE", 
      "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,41,185,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,1,0,5,0,50,8,0,10,0,12,0,53,9,0,1,0,5,0,56,8,0,
  	10,0,12,0,59,9,0,1,0,1,0,1,1,1,1,1,1,1,1,3,1,67,8,1,1,2,1,2,1,2,5,2,72,
  	8,2,10,2,12,2,75,9,2,1,3,5,3,78,8,3,10,3,12,3,81,9,3,1,4,3,4,84,8,4,1,
  	4,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,5,3,5,95,8,5,1,5,1,5,3,5,99,8,5,1,6,1,
  	6,1,6,3,6,104,8,6,1,7,1,7,1,7,5,7,109,8,7,10,7,12,7,112,9,7,1,8,1,8,1,
  	8,1,8,3,8,118,8,8,1,9,1,9,1,9,3,9,123,8,9,1,9,1,9,1,10,1,10,1,10,5,10,
  	130,8,10,10,10,12,10,133,9,10,1,11,1,11,1,11,1,11,1,11,1,11,3,11,141,
  	8,11,1,12,1,12,3,12,145,8,12,1,13,1,13,1,14,1,14,1,15,1,15,1,16,1,16,
  	1,17,1,17,1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,18,1,19,1,19,1,19,1,19,
  	1,19,1,19,1,19,1,19,1,19,1,19,3,19,175,8,19,1,20,1,20,1,21,1,21,1,22,
  	1,22,1,23,1,23,1,23,0,0,24,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,
  	32,34,36,38,40,42,44,46,0,5,1,0,22,23,1,0,11,14,1,0,35,36,1,0,35,38,2,
  	0,20,20,27,32,179,0,51,1,0,0,0,2,62,1,0,0,0,4,68,1,0,0,0,6,79,1,0,0,0,
  	8,83,1,0,0,0,10,92,1,0,0,0,12,100,1,0,0,0,14,105,1,0,0,0,16,113,1,0,0,
  	0,18,119,1,0,0,0,20,126,1,0,0,0,22,134,1,0,0,0,24,144,1,0,0,0,26,146,
  	1,0,0,0,28,148,1,0,0,0,30,150,1,0,0,0,32,152,1,0,0,0,34,154,1,0,0,0,36,
  	159,1,0,0,0,38,164,1,0,0,0,40,176,1,0,0,0,42,178,1,0,0,0,44,180,1,0,0,
  	0,46,182,1,0,0,0,48,50,3,2,1,0,49,48,1,0,0,0,50,53,1,0,0,0,51,49,1,0,
  	0,0,51,52,1,0,0,0,52,57,1,0,0,0,53,51,1,0,0,0,54,56,3,8,4,0,55,54,1,0,
  	0,0,56,59,1,0,0,0,57,55,1,0,0,0,57,58,1,0,0,0,58,60,1,0,0,0,59,57,1,0,
  	0,0,60,61,5,0,0,1,61,1,1,0,0,0,62,63,5,24,0,0,63,66,3,4,2,0,64,65,5,5,
  	0,0,65,67,5,6,0,0,66,64,1,0,0,0,66,67,1,0,0,0,67,3,1,0,0,0,68,73,5,39,
  	0,0,69,70,5,5,0,0,70,72,5,39,0,0,71,69,1,0,0,0,72,75,1,0,0,0,73,71,1,
  	0,0,0,73,74,1,0,0,0,74,5,1,0,0,0,75,73,1,0,0,0,76,78,3,38,19,0,77,76,
  	1,0,0,0,78,81,1,0,0,0,79,77,1,0,0,0,79,80,1,0,0,0,80,7,1,0,0,0,81,79,
  	1,0,0,0,82,84,7,0,0,0,83,82,1,0,0,0,83,84,1,0,0,0,84,85,1,0,0,0,85,86,
  	5,20,0,0,86,87,5,39,0,0,87,88,3,10,5,0,88,89,5,7,0,0,89,90,3,6,3,0,90,
  	91,5,8,0,0,91,9,1,0,0,0,92,94,5,9,0,0,93,95,3,14,7,0,94,93,1,0,0,0,94,
  	95,1,0,0,0,95,96,1,0,0,0,96,98,5,10,0,0,97,99,3,12,6,0,98,97,1,0,0,0,
  	98,99,1,0,0,0,99,11,1,0,0,0,100,103,5,1,0,0,101,104,3,46,23,0,102,104,
  	5,33,0,0,103,101,1,0,0,0,103,102,1,0,0,0,104,13,1,0,0,0,105,110,3,16,
  	8,0,106,107,5,2,0,0,107,109,3,16,8,0,108,106,1,0,0,0,109,112,1,0,0,0,
  	110,108,1,0,0,0,110,111,1,0,0,0,111,15,1,0,0,0,112,110,1,0,0,0,113,114,
  	5,39,0,0,114,117,5,1,0,0,115,118,3,46,23,0,116,118,3,10,5,0,117,115,1,
  	0,0,0,117,116,1,0,0,0,118,17,1,0,0,0,119,120,5,39,0,0,120,122,5,9,0,0,
  	121,123,3,20,10,0,122,121,1,0,0,0,122,123,1,0,0,0,123,124,1,0,0,0,124,
  	125,5,10,0,0,125,19,1,0,0,0,126,131,3,22,11,0,127,128,5,2,0,0,128,130,
  	3,22,11,0,129,127,1,0,0,0,130,133,1,0,0,0,131,129,1,0,0,0,131,132,1,0,
  	0,0,132,21,1,0,0,0,133,131,1,0,0,0,134,135,5,39,0,0,135,140,5,1,0,0,136,
  	141,3,44,22,0,137,138,3,18,9,0,138,139,5,39,0,0,139,141,1,0,0,0,140,136,
  	1,0,0,0,140,137,1,0,0,0,141,23,1,0,0,0,142,145,5,39,0,0,143,145,3,42,
  	21,0,144,142,1,0,0,0,144,143,1,0,0,0,145,25,1,0,0,0,146,147,3,24,12,0,
  	147,27,1,0,0,0,148,149,3,24,12,0,149,29,1,0,0,0,150,151,3,46,23,0,151,
  	31,1,0,0,0,152,153,3,46,23,0,153,33,1,0,0,0,154,155,5,39,0,0,155,156,
  	3,32,16,0,156,157,5,26,0,0,157,158,3,30,15,0,158,35,1,0,0,0,159,160,7,
  	1,0,0,160,161,3,28,14,0,161,162,5,2,0,0,162,163,3,26,13,0,163,37,1,0,
  	0,0,164,165,5,21,0,0,165,166,5,39,0,0,166,167,5,1,0,0,167,168,3,46,23,
  	0,168,174,5,3,0,0,169,175,3,36,18,0,170,175,3,18,9,0,171,175,3,34,17,
  	0,172,175,3,42,21,0,173,175,3,40,20,0,174,169,1,0,0,0,174,170,1,0,0,0,
  	174,171,1,0,0,0,174,172,1,0,0,0,174,173,1,0,0,0,175,39,1,0,0,0,176,177,
  	5,39,0,0,177,41,1,0,0,0,178,179,7,2,0,0,179,43,1,0,0,0,180,181,7,3,0,
  	0,181,45,1,0,0,0,182,183,7,4,0,0,183,47,1,0,0,0,16,51,57,66,73,79,83,
  	94,98,103,110,117,122,131,140,144,174
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  hightlavelirParserStaticData = std::move(staticData);
}

}

HightLavelIRParser::HightLavelIRParser(TokenStream *input) : HightLavelIRParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

HightLavelIRParser::HightLavelIRParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  HightLavelIRParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *hightlavelirParserStaticData->atn, hightlavelirParserStaticData->decisionToDFA, hightlavelirParserStaticData->sharedContextCache, options);
}

HightLavelIRParser::~HightLavelIRParser() {
  delete _interpreter;
}

const atn::ATN& HightLavelIRParser::getATN() const {
  return *hightlavelirParserStaticData->atn;
}

std::string HightLavelIRParser::getGrammarFileName() const {
  return "HightLavelIR.g4";
}

const std::vector<std::string>& HightLavelIRParser::getRuleNames() const {
  return hightlavelirParserStaticData->ruleNames;
}

const dfa::Vocabulary& HightLavelIRParser::getVocabulary() const {
  return hightlavelirParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView HightLavelIRParser::getSerializedATN() const {
  return hightlavelirParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

HightLavelIRParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HightLavelIRParser::ProgramContext::EOF() {
  return getToken(HightLavelIRParser::EOF, 0);
}

std::vector<HightLavelIRParser::ImportStatementContext *> HightLavelIRParser::ProgramContext::importStatement() {
  return getRuleContexts<HightLavelIRParser::ImportStatementContext>();
}

HightLavelIRParser::ImportStatementContext* HightLavelIRParser::ProgramContext::importStatement(size_t i) {
  return getRuleContext<HightLavelIRParser::ImportStatementContext>(i);
}

std::vector<HightLavelIRParser::FunctionDeclarationContext *> HightLavelIRParser::ProgramContext::functionDeclaration() {
  return getRuleContexts<HightLavelIRParser::FunctionDeclarationContext>();
}

HightLavelIRParser::FunctionDeclarationContext* HightLavelIRParser::ProgramContext::functionDeclaration(size_t i) {
  return getRuleContext<HightLavelIRParser::FunctionDeclarationContext>(i);
}


size_t HightLavelIRParser::ProgramContext::getRuleIndex() const {
  return HightLavelIRParser::RuleProgram;
}

void HightLavelIRParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void HightLavelIRParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}

HightLavelIRParser::ProgramContext* HightLavelIRParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, HightLavelIRParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(51);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HightLavelIRParser::IMPORT) {
      setState(48);
      importStatement();
      setState(53);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(57);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 13631488) != 0)) {
      setState(54);
      functionDeclaration();
      setState(59);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(60);
    match(HightLavelIRParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportStatementContext ------------------------------------------------------------------

HightLavelIRParser::ImportStatementContext::ImportStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HightLavelIRParser::ImportStatementContext::IMPORT() {
  return getToken(HightLavelIRParser::IMPORT, 0);
}

HightLavelIRParser::QualifiedNameContext* HightLavelIRParser::ImportStatementContext::qualifiedName() {
  return getRuleContext<HightLavelIRParser::QualifiedNameContext>(0);
}

tree::TerminalNode* HightLavelIRParser::ImportStatementContext::DOT() {
  return getToken(HightLavelIRParser::DOT, 0);
}

tree::TerminalNode* HightLavelIRParser::ImportStatementContext::STAR() {
  return getToken(HightLavelIRParser::STAR, 0);
}


size_t HightLavelIRParser::ImportStatementContext::getRuleIndex() const {
  return HightLavelIRParser::RuleImportStatement;
}

void HightLavelIRParser::ImportStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportStatement(this);
}

void HightLavelIRParser::ImportStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportStatement(this);
}

HightLavelIRParser::ImportStatementContext* HightLavelIRParser::importStatement() {
  ImportStatementContext *_localctx = _tracker.createInstance<ImportStatementContext>(_ctx, getState());
  enterRule(_localctx, 2, HightLavelIRParser::RuleImportStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(62);
    match(HightLavelIRParser::IMPORT);
    setState(63);
    qualifiedName();
    setState(66);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HightLavelIRParser::DOT) {
      setState(64);
      match(HightLavelIRParser::DOT);
      setState(65);
      match(HightLavelIRParser::STAR);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QualifiedNameContext ------------------------------------------------------------------

HightLavelIRParser::QualifiedNameContext::QualifiedNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> HightLavelIRParser::QualifiedNameContext::IDENTIFIER() {
  return getTokens(HightLavelIRParser::IDENTIFIER);
}

tree::TerminalNode* HightLavelIRParser::QualifiedNameContext::IDENTIFIER(size_t i) {
  return getToken(HightLavelIRParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> HightLavelIRParser::QualifiedNameContext::DOT() {
  return getTokens(HightLavelIRParser::DOT);
}

tree::TerminalNode* HightLavelIRParser::QualifiedNameContext::DOT(size_t i) {
  return getToken(HightLavelIRParser::DOT, i);
}


size_t HightLavelIRParser::QualifiedNameContext::getRuleIndex() const {
  return HightLavelIRParser::RuleQualifiedName;
}

void HightLavelIRParser::QualifiedNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterQualifiedName(this);
}

void HightLavelIRParser::QualifiedNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitQualifiedName(this);
}

HightLavelIRParser::QualifiedNameContext* HightLavelIRParser::qualifiedName() {
  QualifiedNameContext *_localctx = _tracker.createInstance<QualifiedNameContext>(_ctx, getState());
  enterRule(_localctx, 4, HightLavelIRParser::RuleQualifiedName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(68);
    match(HightLavelIRParser::IDENTIFIER);
    setState(73);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(69);
        match(HightLavelIRParser::DOT);
        setState(70);
        match(HightLavelIRParser::IDENTIFIER); 
      }
      setState(75);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementListContext ------------------------------------------------------------------

HightLavelIRParser::StatementListContext::StatementListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HightLavelIRParser::ExprContext *> HightLavelIRParser::StatementListContext::expr() {
  return getRuleContexts<HightLavelIRParser::ExprContext>();
}

HightLavelIRParser::ExprContext* HightLavelIRParser::StatementListContext::expr(size_t i) {
  return getRuleContext<HightLavelIRParser::ExprContext>(i);
}


size_t HightLavelIRParser::StatementListContext::getRuleIndex() const {
  return HightLavelIRParser::RuleStatementList;
}

void HightLavelIRParser::StatementListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatementList(this);
}

void HightLavelIRParser::StatementListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatementList(this);
}

HightLavelIRParser::StatementListContext* HightLavelIRParser::statementList() {
  StatementListContext *_localctx = _tracker.createInstance<StatementListContext>(_ctx, getState());
  enterRule(_localctx, 6, HightLavelIRParser::RuleStatementList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(79);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HightLavelIRParser::LET) {
      setState(76);
      expr();
      setState(81);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDeclarationContext ------------------------------------------------------------------

HightLavelIRParser::FunctionDeclarationContext::FunctionDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HightLavelIRParser::FunctionDeclarationContext::FUNCTION() {
  return getToken(HightLavelIRParser::FUNCTION, 0);
}

HightLavelIRParser::FunctionSignatureContext* HightLavelIRParser::FunctionDeclarationContext::functionSignature() {
  return getRuleContext<HightLavelIRParser::FunctionSignatureContext>(0);
}

tree::TerminalNode* HightLavelIRParser::FunctionDeclarationContext::L_CURLY() {
  return getToken(HightLavelIRParser::L_CURLY, 0);
}

HightLavelIRParser::StatementListContext* HightLavelIRParser::FunctionDeclarationContext::statementList() {
  return getRuleContext<HightLavelIRParser::StatementListContext>(0);
}

tree::TerminalNode* HightLavelIRParser::FunctionDeclarationContext::R_CURLY() {
  return getToken(HightLavelIRParser::R_CURLY, 0);
}

tree::TerminalNode* HightLavelIRParser::FunctionDeclarationContext::IDENTIFIER() {
  return getToken(HightLavelIRParser::IDENTIFIER, 0);
}

tree::TerminalNode* HightLavelIRParser::FunctionDeclarationContext::PRIVATE() {
  return getToken(HightLavelIRParser::PRIVATE, 0);
}

tree::TerminalNode* HightLavelIRParser::FunctionDeclarationContext::PUBLIC() {
  return getToken(HightLavelIRParser::PUBLIC, 0);
}


size_t HightLavelIRParser::FunctionDeclarationContext::getRuleIndex() const {
  return HightLavelIRParser::RuleFunctionDeclaration;
}

void HightLavelIRParser::FunctionDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDeclaration(this);
}

void HightLavelIRParser::FunctionDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDeclaration(this);
}

HightLavelIRParser::FunctionDeclarationContext* HightLavelIRParser::functionDeclaration() {
  FunctionDeclarationContext *_localctx = _tracker.createInstance<FunctionDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 8, HightLavelIRParser::RuleFunctionDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(83);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HightLavelIRParser::PUBLIC

    || _la == HightLavelIRParser::PRIVATE) {
      setState(82);
      _la = _input->LA(1);
      if (!(_la == HightLavelIRParser::PUBLIC

      || _la == HightLavelIRParser::PRIVATE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(85);
    match(HightLavelIRParser::FUNCTION);
    setState(86);
    antlrcpp::downCast<FunctionDeclarationContext *>(_localctx)->functionName = match(HightLavelIRParser::IDENTIFIER);
    setState(87);
    functionSignature();
    setState(88);
    match(HightLavelIRParser::L_CURLY);
    setState(89);
    statementList();
    setState(90);
    match(HightLavelIRParser::R_CURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionSignatureContext ------------------------------------------------------------------

HightLavelIRParser::FunctionSignatureContext::FunctionSignatureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HightLavelIRParser::FunctionSignatureContext::L_PAREN() {
  return getToken(HightLavelIRParser::L_PAREN, 0);
}

tree::TerminalNode* HightLavelIRParser::FunctionSignatureContext::R_PAREN() {
  return getToken(HightLavelIRParser::R_PAREN, 0);
}

HightLavelIRParser::FunctionArgsContext* HightLavelIRParser::FunctionSignatureContext::functionArgs() {
  return getRuleContext<HightLavelIRParser::FunctionArgsContext>(0);
}

HightLavelIRParser::FunctionReturnTypeContext* HightLavelIRParser::FunctionSignatureContext::functionReturnType() {
  return getRuleContext<HightLavelIRParser::FunctionReturnTypeContext>(0);
}


size_t HightLavelIRParser::FunctionSignatureContext::getRuleIndex() const {
  return HightLavelIRParser::RuleFunctionSignature;
}

void HightLavelIRParser::FunctionSignatureContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionSignature(this);
}

void HightLavelIRParser::FunctionSignatureContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionSignature(this);
}

HightLavelIRParser::FunctionSignatureContext* HightLavelIRParser::functionSignature() {
  FunctionSignatureContext *_localctx = _tracker.createInstance<FunctionSignatureContext>(_ctx, getState());
  enterRule(_localctx, 10, HightLavelIRParser::RuleFunctionSignature);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(92);
    match(HightLavelIRParser::L_PAREN);
    setState(94);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HightLavelIRParser::IDENTIFIER) {
      setState(93);
      functionArgs();
    }
    setState(96);
    match(HightLavelIRParser::R_PAREN);
    setState(98);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HightLavelIRParser::COLON) {
      setState(97);
      functionReturnType();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionReturnTypeContext ------------------------------------------------------------------

HightLavelIRParser::FunctionReturnTypeContext::FunctionReturnTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HightLavelIRParser::FunctionReturnTypeContext::COLON() {
  return getToken(HightLavelIRParser::COLON, 0);
}

HightLavelIRParser::VarTypesContext* HightLavelIRParser::FunctionReturnTypeContext::varTypes() {
  return getRuleContext<HightLavelIRParser::VarTypesContext>(0);
}

tree::TerminalNode* HightLavelIRParser::FunctionReturnTypeContext::VOID() {
  return getToken(HightLavelIRParser::VOID, 0);
}


size_t HightLavelIRParser::FunctionReturnTypeContext::getRuleIndex() const {
  return HightLavelIRParser::RuleFunctionReturnType;
}

void HightLavelIRParser::FunctionReturnTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionReturnType(this);
}

void HightLavelIRParser::FunctionReturnTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionReturnType(this);
}

HightLavelIRParser::FunctionReturnTypeContext* HightLavelIRParser::functionReturnType() {
  FunctionReturnTypeContext *_localctx = _tracker.createInstance<FunctionReturnTypeContext>(_ctx, getState());
  enterRule(_localctx, 12, HightLavelIRParser::RuleFunctionReturnType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(100);
    match(HightLavelIRParser::COLON);
    setState(103);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HightLavelIRParser::FUNCTION:
      case HightLavelIRParser::TYPE_INT:
      case HightLavelIRParser::TYPE_CHAR:
      case HightLavelIRParser::TYPE_FLOAT:
      case HightLavelIRParser::TYPE_STRING:
      case HightLavelIRParser::TYPE_BOOLEAN:
      case HightLavelIRParser::TYPE_DOUBLE: {
        setState(101);
        varTypes();
        break;
      }

      case HightLavelIRParser::VOID: {
        setState(102);
        match(HightLavelIRParser::VOID);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionArgsContext ------------------------------------------------------------------

HightLavelIRParser::FunctionArgsContext::FunctionArgsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HightLavelIRParser::FunctionArgContext *> HightLavelIRParser::FunctionArgsContext::functionArg() {
  return getRuleContexts<HightLavelIRParser::FunctionArgContext>();
}

HightLavelIRParser::FunctionArgContext* HightLavelIRParser::FunctionArgsContext::functionArg(size_t i) {
  return getRuleContext<HightLavelIRParser::FunctionArgContext>(i);
}

std::vector<tree::TerminalNode *> HightLavelIRParser::FunctionArgsContext::COMMA() {
  return getTokens(HightLavelIRParser::COMMA);
}

tree::TerminalNode* HightLavelIRParser::FunctionArgsContext::COMMA(size_t i) {
  return getToken(HightLavelIRParser::COMMA, i);
}


size_t HightLavelIRParser::FunctionArgsContext::getRuleIndex() const {
  return HightLavelIRParser::RuleFunctionArgs;
}

void HightLavelIRParser::FunctionArgsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionArgs(this);
}

void HightLavelIRParser::FunctionArgsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionArgs(this);
}

HightLavelIRParser::FunctionArgsContext* HightLavelIRParser::functionArgs() {
  FunctionArgsContext *_localctx = _tracker.createInstance<FunctionArgsContext>(_ctx, getState());
  enterRule(_localctx, 14, HightLavelIRParser::RuleFunctionArgs);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(105);
    functionArg();
    setState(110);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HightLavelIRParser::COMMA) {
      setState(106);
      match(HightLavelIRParser::COMMA);
      setState(107);
      functionArg();
      setState(112);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionArgContext ------------------------------------------------------------------

HightLavelIRParser::FunctionArgContext::FunctionArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HightLavelIRParser::FunctionArgContext::COLON() {
  return getToken(HightLavelIRParser::COLON, 0);
}

tree::TerminalNode* HightLavelIRParser::FunctionArgContext::IDENTIFIER() {
  return getToken(HightLavelIRParser::IDENTIFIER, 0);
}

HightLavelIRParser::VarTypesContext* HightLavelIRParser::FunctionArgContext::varTypes() {
  return getRuleContext<HightLavelIRParser::VarTypesContext>(0);
}

HightLavelIRParser::FunctionSignatureContext* HightLavelIRParser::FunctionArgContext::functionSignature() {
  return getRuleContext<HightLavelIRParser::FunctionSignatureContext>(0);
}


size_t HightLavelIRParser::FunctionArgContext::getRuleIndex() const {
  return HightLavelIRParser::RuleFunctionArg;
}

void HightLavelIRParser::FunctionArgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionArg(this);
}

void HightLavelIRParser::FunctionArgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionArg(this);
}

HightLavelIRParser::FunctionArgContext* HightLavelIRParser::functionArg() {
  FunctionArgContext *_localctx = _tracker.createInstance<FunctionArgContext>(_ctx, getState());
  enterRule(_localctx, 16, HightLavelIRParser::RuleFunctionArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(113);
    antlrcpp::downCast<FunctionArgContext *>(_localctx)->varName = match(HightLavelIRParser::IDENTIFIER);
    setState(114);
    match(HightLavelIRParser::COLON);
    setState(117);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HightLavelIRParser::FUNCTION:
      case HightLavelIRParser::TYPE_INT:
      case HightLavelIRParser::TYPE_CHAR:
      case HightLavelIRParser::TYPE_FLOAT:
      case HightLavelIRParser::TYPE_STRING:
      case HightLavelIRParser::TYPE_BOOLEAN:
      case HightLavelIRParser::TYPE_DOUBLE: {
        setState(115);
        varTypes();
        break;
      }

      case HightLavelIRParser::L_PAREN: {
        setState(116);
        functionSignature();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallContext ------------------------------------------------------------------

HightLavelIRParser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HightLavelIRParser::FunctionCallContext::L_PAREN() {
  return getToken(HightLavelIRParser::L_PAREN, 0);
}

tree::TerminalNode* HightLavelIRParser::FunctionCallContext::R_PAREN() {
  return getToken(HightLavelIRParser::R_PAREN, 0);
}

tree::TerminalNode* HightLavelIRParser::FunctionCallContext::IDENTIFIER() {
  return getToken(HightLavelIRParser::IDENTIFIER, 0);
}

HightLavelIRParser::FunctionCallArgsContext* HightLavelIRParser::FunctionCallContext::functionCallArgs() {
  return getRuleContext<HightLavelIRParser::FunctionCallArgsContext>(0);
}


size_t HightLavelIRParser::FunctionCallContext::getRuleIndex() const {
  return HightLavelIRParser::RuleFunctionCall;
}

void HightLavelIRParser::FunctionCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCall(this);
}

void HightLavelIRParser::FunctionCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCall(this);
}

HightLavelIRParser::FunctionCallContext* HightLavelIRParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 18, HightLavelIRParser::RuleFunctionCall);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(119);
    antlrcpp::downCast<FunctionCallContext *>(_localctx)->functionName = match(HightLavelIRParser::IDENTIFIER);
    setState(120);
    match(HightLavelIRParser::L_PAREN);
    setState(122);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HightLavelIRParser::IDENTIFIER) {
      setState(121);
      functionCallArgs();
    }
    setState(124);
    match(HightLavelIRParser::R_PAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallArgsContext ------------------------------------------------------------------

HightLavelIRParser::FunctionCallArgsContext::FunctionCallArgsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HightLavelIRParser::FunctionCallArgContext *> HightLavelIRParser::FunctionCallArgsContext::functionCallArg() {
  return getRuleContexts<HightLavelIRParser::FunctionCallArgContext>();
}

HightLavelIRParser::FunctionCallArgContext* HightLavelIRParser::FunctionCallArgsContext::functionCallArg(size_t i) {
  return getRuleContext<HightLavelIRParser::FunctionCallArgContext>(i);
}

std::vector<tree::TerminalNode *> HightLavelIRParser::FunctionCallArgsContext::COMMA() {
  return getTokens(HightLavelIRParser::COMMA);
}

tree::TerminalNode* HightLavelIRParser::FunctionCallArgsContext::COMMA(size_t i) {
  return getToken(HightLavelIRParser::COMMA, i);
}


size_t HightLavelIRParser::FunctionCallArgsContext::getRuleIndex() const {
  return HightLavelIRParser::RuleFunctionCallArgs;
}

void HightLavelIRParser::FunctionCallArgsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCallArgs(this);
}

void HightLavelIRParser::FunctionCallArgsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCallArgs(this);
}

HightLavelIRParser::FunctionCallArgsContext* HightLavelIRParser::functionCallArgs() {
  FunctionCallArgsContext *_localctx = _tracker.createInstance<FunctionCallArgsContext>(_ctx, getState());
  enterRule(_localctx, 20, HightLavelIRParser::RuleFunctionCallArgs);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(126);
    functionCallArg();
    setState(131);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HightLavelIRParser::COMMA) {
      setState(127);
      match(HightLavelIRParser::COMMA);
      setState(128);
      functionCallArg();
      setState(133);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallArgContext ------------------------------------------------------------------

HightLavelIRParser::FunctionCallArgContext::FunctionCallArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HightLavelIRParser::FunctionCallArgContext::COLON() {
  return getToken(HightLavelIRParser::COLON, 0);
}

std::vector<tree::TerminalNode *> HightLavelIRParser::FunctionCallArgContext::IDENTIFIER() {
  return getTokens(HightLavelIRParser::IDENTIFIER);
}

tree::TerminalNode* HightLavelIRParser::FunctionCallArgContext::IDENTIFIER(size_t i) {
  return getToken(HightLavelIRParser::IDENTIFIER, i);
}

HightLavelIRParser::DataFormatContext* HightLavelIRParser::FunctionCallArgContext::dataFormat() {
  return getRuleContext<HightLavelIRParser::DataFormatContext>(0);
}

HightLavelIRParser::FunctionCallContext* HightLavelIRParser::FunctionCallArgContext::functionCall() {
  return getRuleContext<HightLavelIRParser::FunctionCallContext>(0);
}


size_t HightLavelIRParser::FunctionCallArgContext::getRuleIndex() const {
  return HightLavelIRParser::RuleFunctionCallArg;
}

void HightLavelIRParser::FunctionCallArgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCallArg(this);
}

void HightLavelIRParser::FunctionCallArgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCallArg(this);
}

HightLavelIRParser::FunctionCallArgContext* HightLavelIRParser::functionCallArg() {
  FunctionCallArgContext *_localctx = _tracker.createInstance<FunctionCallArgContext>(_ctx, getState());
  enterRule(_localctx, 22, HightLavelIRParser::RuleFunctionCallArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(134);
    antlrcpp::downCast<FunctionCallArgContext *>(_localctx)->varName = match(HightLavelIRParser::IDENTIFIER);
    setState(135);
    match(HightLavelIRParser::COLON);
    setState(140);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HightLavelIRParser::REAL_NUMBER:
      case HightLavelIRParser::INT_NUMBER:
      case HightLavelIRParser::BOOLEAN_VALUE:
      case HightLavelIRParser::STRING_LITERAL: {
        setState(136);
        dataFormat();
        break;
      }

      case HightLavelIRParser::IDENTIFIER: {
        setState(137);
        functionCall();
        setState(138);
        antlrcpp::downCast<FunctionCallArgContext *>(_localctx)->anotherVarName = match(HightLavelIRParser::IDENTIFIER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OpContext ------------------------------------------------------------------

HightLavelIRParser::OpContext::OpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HightLavelIRParser::NumberContext* HightLavelIRParser::OpContext::number() {
  return getRuleContext<HightLavelIRParser::NumberContext>(0);
}

tree::TerminalNode* HightLavelIRParser::OpContext::IDENTIFIER() {
  return getToken(HightLavelIRParser::IDENTIFIER, 0);
}


size_t HightLavelIRParser::OpContext::getRuleIndex() const {
  return HightLavelIRParser::RuleOp;
}

void HightLavelIRParser::OpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOp(this);
}

void HightLavelIRParser::OpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOp(this);
}

HightLavelIRParser::OpContext* HightLavelIRParser::op() {
  OpContext *_localctx = _tracker.createInstance<OpContext>(_ctx, getState());
  enterRule(_localctx, 24, HightLavelIRParser::RuleOp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(144);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HightLavelIRParser::IDENTIFIER: {
        setState(142);
        antlrcpp::downCast<OpContext *>(_localctx)->varName = match(HightLavelIRParser::IDENTIFIER);
        break;
      }

      case HightLavelIRParser::REAL_NUMBER:
      case HightLavelIRParser::INT_NUMBER: {
        setState(143);
        number();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OpRightContext ------------------------------------------------------------------

HightLavelIRParser::OpRightContext::OpRightContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HightLavelIRParser::OpContext* HightLavelIRParser::OpRightContext::op() {
  return getRuleContext<HightLavelIRParser::OpContext>(0);
}


size_t HightLavelIRParser::OpRightContext::getRuleIndex() const {
  return HightLavelIRParser::RuleOpRight;
}

void HightLavelIRParser::OpRightContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOpRight(this);
}

void HightLavelIRParser::OpRightContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOpRight(this);
}

HightLavelIRParser::OpRightContext* HightLavelIRParser::opRight() {
  OpRightContext *_localctx = _tracker.createInstance<OpRightContext>(_ctx, getState());
  enterRule(_localctx, 26, HightLavelIRParser::RuleOpRight);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(146);
    op();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OpLeftContext ------------------------------------------------------------------

HightLavelIRParser::OpLeftContext::OpLeftContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HightLavelIRParser::OpContext* HightLavelIRParser::OpLeftContext::op() {
  return getRuleContext<HightLavelIRParser::OpContext>(0);
}


size_t HightLavelIRParser::OpLeftContext::getRuleIndex() const {
  return HightLavelIRParser::RuleOpLeft;
}

void HightLavelIRParser::OpLeftContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOpLeft(this);
}

void HightLavelIRParser::OpLeftContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOpLeft(this);
}

HightLavelIRParser::OpLeftContext* HightLavelIRParser::opLeft() {
  OpLeftContext *_localctx = _tracker.createInstance<OpLeftContext>(_ctx, getState());
  enterRule(_localctx, 28, HightLavelIRParser::RuleOpLeft);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(148);
    op();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeRightContext ------------------------------------------------------------------

HightLavelIRParser::TypeRightContext::TypeRightContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HightLavelIRParser::VarTypesContext* HightLavelIRParser::TypeRightContext::varTypes() {
  return getRuleContext<HightLavelIRParser::VarTypesContext>(0);
}


size_t HightLavelIRParser::TypeRightContext::getRuleIndex() const {
  return HightLavelIRParser::RuleTypeRight;
}

void HightLavelIRParser::TypeRightContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeRight(this);
}

void HightLavelIRParser::TypeRightContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeRight(this);
}

HightLavelIRParser::TypeRightContext* HightLavelIRParser::typeRight() {
  TypeRightContext *_localctx = _tracker.createInstance<TypeRightContext>(_ctx, getState());
  enterRule(_localctx, 30, HightLavelIRParser::RuleTypeRight);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(150);
    varTypes();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeLeftContext ------------------------------------------------------------------

HightLavelIRParser::TypeLeftContext::TypeLeftContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HightLavelIRParser::VarTypesContext* HightLavelIRParser::TypeLeftContext::varTypes() {
  return getRuleContext<HightLavelIRParser::VarTypesContext>(0);
}


size_t HightLavelIRParser::TypeLeftContext::getRuleIndex() const {
  return HightLavelIRParser::RuleTypeLeft;
}

void HightLavelIRParser::TypeLeftContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeLeft(this);
}

void HightLavelIRParser::TypeLeftContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeLeft(this);
}

HightLavelIRParser::TypeLeftContext* HightLavelIRParser::typeLeft() {
  TypeLeftContext *_localctx = _tracker.createInstance<TypeLeftContext>(_ctx, getState());
  enterRule(_localctx, 32, HightLavelIRParser::RuleTypeLeft);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(152);
    varTypes();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CastContext ------------------------------------------------------------------

HightLavelIRParser::CastContext::CastContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HightLavelIRParser::TypeLeftContext* HightLavelIRParser::CastContext::typeLeft() {
  return getRuleContext<HightLavelIRParser::TypeLeftContext>(0);
}

tree::TerminalNode* HightLavelIRParser::CastContext::TO() {
  return getToken(HightLavelIRParser::TO, 0);
}

HightLavelIRParser::TypeRightContext* HightLavelIRParser::CastContext::typeRight() {
  return getRuleContext<HightLavelIRParser::TypeRightContext>(0);
}

tree::TerminalNode* HightLavelIRParser::CastContext::IDENTIFIER() {
  return getToken(HightLavelIRParser::IDENTIFIER, 0);
}


size_t HightLavelIRParser::CastContext::getRuleIndex() const {
  return HightLavelIRParser::RuleCast;
}

void HightLavelIRParser::CastContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCast(this);
}

void HightLavelIRParser::CastContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCast(this);
}

HightLavelIRParser::CastContext* HightLavelIRParser::cast() {
  CastContext *_localctx = _tracker.createInstance<CastContext>(_ctx, getState());
  enterRule(_localctx, 34, HightLavelIRParser::RuleCast);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(154);
    antlrcpp::downCast<CastContext *>(_localctx)->anotherVarName = match(HightLavelIRParser::IDENTIFIER);
    setState(155);
    typeLeft();
    setState(156);
    match(HightLavelIRParser::TO);
    setState(157);
    typeRight();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Math_opContext ------------------------------------------------------------------

HightLavelIRParser::Math_opContext::Math_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HightLavelIRParser::OpLeftContext* HightLavelIRParser::Math_opContext::opLeft() {
  return getRuleContext<HightLavelIRParser::OpLeftContext>(0);
}

tree::TerminalNode* HightLavelIRParser::Math_opContext::COMMA() {
  return getToken(HightLavelIRParser::COMMA, 0);
}

HightLavelIRParser::OpRightContext* HightLavelIRParser::Math_opContext::opRight() {
  return getRuleContext<HightLavelIRParser::OpRightContext>(0);
}

tree::TerminalNode* HightLavelIRParser::Math_opContext::MULT() {
  return getToken(HightLavelIRParser::MULT, 0);
}

tree::TerminalNode* HightLavelIRParser::Math_opContext::DIV() {
  return getToken(HightLavelIRParser::DIV, 0);
}

tree::TerminalNode* HightLavelIRParser::Math_opContext::PLUS() {
  return getToken(HightLavelIRParser::PLUS, 0);
}

tree::TerminalNode* HightLavelIRParser::Math_opContext::MINUS() {
  return getToken(HightLavelIRParser::MINUS, 0);
}


size_t HightLavelIRParser::Math_opContext::getRuleIndex() const {
  return HightLavelIRParser::RuleMath_op;
}

void HightLavelIRParser::Math_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMath_op(this);
}

void HightLavelIRParser::Math_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMath_op(this);
}

HightLavelIRParser::Math_opContext* HightLavelIRParser::math_op() {
  Math_opContext *_localctx = _tracker.createInstance<Math_opContext>(_ctx, getState());
  enterRule(_localctx, 36, HightLavelIRParser::RuleMath_op);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(159);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 30720) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(160);
    opLeft();
    setState(161);
    match(HightLavelIRParser::COMMA);
    setState(162);
    opRight();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

HightLavelIRParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HightLavelIRParser::ExprContext::LET() {
  return getToken(HightLavelIRParser::LET, 0);
}

tree::TerminalNode* HightLavelIRParser::ExprContext::COLON() {
  return getToken(HightLavelIRParser::COLON, 0);
}

HightLavelIRParser::VarTypesContext* HightLavelIRParser::ExprContext::varTypes() {
  return getRuleContext<HightLavelIRParser::VarTypesContext>(0);
}

tree::TerminalNode* HightLavelIRParser::ExprContext::EQ() {
  return getToken(HightLavelIRParser::EQ, 0);
}

tree::TerminalNode* HightLavelIRParser::ExprContext::IDENTIFIER() {
  return getToken(HightLavelIRParser::IDENTIFIER, 0);
}

HightLavelIRParser::Math_opContext* HightLavelIRParser::ExprContext::math_op() {
  return getRuleContext<HightLavelIRParser::Math_opContext>(0);
}

HightLavelIRParser::FunctionCallContext* HightLavelIRParser::ExprContext::functionCall() {
  return getRuleContext<HightLavelIRParser::FunctionCallContext>(0);
}

HightLavelIRParser::CastContext* HightLavelIRParser::ExprContext::cast() {
  return getRuleContext<HightLavelIRParser::CastContext>(0);
}

HightLavelIRParser::NumberContext* HightLavelIRParser::ExprContext::number() {
  return getRuleContext<HightLavelIRParser::NumberContext>(0);
}

HightLavelIRParser::AssignmentContext* HightLavelIRParser::ExprContext::assignment() {
  return getRuleContext<HightLavelIRParser::AssignmentContext>(0);
}


size_t HightLavelIRParser::ExprContext::getRuleIndex() const {
  return HightLavelIRParser::RuleExpr;
}

void HightLavelIRParser::ExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr(this);
}

void HightLavelIRParser::ExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr(this);
}

HightLavelIRParser::ExprContext* HightLavelIRParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 38, HightLavelIRParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(164);
    match(HightLavelIRParser::LET);
    setState(165);
    antlrcpp::downCast<ExprContext *>(_localctx)->varName = match(HightLavelIRParser::IDENTIFIER);
    setState(166);
    match(HightLavelIRParser::COLON);
    setState(167);
    varTypes();
    setState(168);
    match(HightLavelIRParser::EQ);
    setState(174);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      setState(169);
      math_op();
      break;
    }

    case 2: {
      setState(170);
      functionCall();
      break;
    }

    case 3: {
      setState(171);
      cast();
      break;
    }

    case 4: {
      setState(172);
      number();
      break;
    }

    case 5: {
      setState(173);
      assignment();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

HightLavelIRParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HightLavelIRParser::AssignmentContext::IDENTIFIER() {
  return getToken(HightLavelIRParser::IDENTIFIER, 0);
}


size_t HightLavelIRParser::AssignmentContext::getRuleIndex() const {
  return HightLavelIRParser::RuleAssignment;
}

void HightLavelIRParser::AssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignment(this);
}

void HightLavelIRParser::AssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignment(this);
}

HightLavelIRParser::AssignmentContext* HightLavelIRParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 40, HightLavelIRParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(176);
    antlrcpp::downCast<AssignmentContext *>(_localctx)->anotherVarName = match(HightLavelIRParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

HightLavelIRParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HightLavelIRParser::NumberContext::REAL_NUMBER() {
  return getToken(HightLavelIRParser::REAL_NUMBER, 0);
}

tree::TerminalNode* HightLavelIRParser::NumberContext::INT_NUMBER() {
  return getToken(HightLavelIRParser::INT_NUMBER, 0);
}


size_t HightLavelIRParser::NumberContext::getRuleIndex() const {
  return HightLavelIRParser::RuleNumber;
}

void HightLavelIRParser::NumberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumber(this);
}

void HightLavelIRParser::NumberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumber(this);
}

HightLavelIRParser::NumberContext* HightLavelIRParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 42, HightLavelIRParser::RuleNumber);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(178);
    _la = _input->LA(1);
    if (!(_la == HightLavelIRParser::REAL_NUMBER

    || _la == HightLavelIRParser::INT_NUMBER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DataFormatContext ------------------------------------------------------------------

HightLavelIRParser::DataFormatContext::DataFormatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HightLavelIRParser::DataFormatContext::REAL_NUMBER() {
  return getToken(HightLavelIRParser::REAL_NUMBER, 0);
}

tree::TerminalNode* HightLavelIRParser::DataFormatContext::INT_NUMBER() {
  return getToken(HightLavelIRParser::INT_NUMBER, 0);
}

tree::TerminalNode* HightLavelIRParser::DataFormatContext::BOOLEAN_VALUE() {
  return getToken(HightLavelIRParser::BOOLEAN_VALUE, 0);
}

tree::TerminalNode* HightLavelIRParser::DataFormatContext::STRING_LITERAL() {
  return getToken(HightLavelIRParser::STRING_LITERAL, 0);
}


size_t HightLavelIRParser::DataFormatContext::getRuleIndex() const {
  return HightLavelIRParser::RuleDataFormat;
}

void HightLavelIRParser::DataFormatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDataFormat(this);
}

void HightLavelIRParser::DataFormatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDataFormat(this);
}

HightLavelIRParser::DataFormatContext* HightLavelIRParser::dataFormat() {
  DataFormatContext *_localctx = _tracker.createInstance<DataFormatContext>(_ctx, getState());
  enterRule(_localctx, 44, HightLavelIRParser::RuleDataFormat);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(180);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 515396075520) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarTypesContext ------------------------------------------------------------------

HightLavelIRParser::VarTypesContext::VarTypesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HightLavelIRParser::VarTypesContext::TYPE_BOOLEAN() {
  return getToken(HightLavelIRParser::TYPE_BOOLEAN, 0);
}

tree::TerminalNode* HightLavelIRParser::VarTypesContext::TYPE_CHAR() {
  return getToken(HightLavelIRParser::TYPE_CHAR, 0);
}

tree::TerminalNode* HightLavelIRParser::VarTypesContext::TYPE_DOUBLE() {
  return getToken(HightLavelIRParser::TYPE_DOUBLE, 0);
}

tree::TerminalNode* HightLavelIRParser::VarTypesContext::TYPE_FLOAT() {
  return getToken(HightLavelIRParser::TYPE_FLOAT, 0);
}

tree::TerminalNode* HightLavelIRParser::VarTypesContext::TYPE_INT() {
  return getToken(HightLavelIRParser::TYPE_INT, 0);
}

tree::TerminalNode* HightLavelIRParser::VarTypesContext::TYPE_STRING() {
  return getToken(HightLavelIRParser::TYPE_STRING, 0);
}

tree::TerminalNode* HightLavelIRParser::VarTypesContext::FUNCTION() {
  return getToken(HightLavelIRParser::FUNCTION, 0);
}


size_t HightLavelIRParser::VarTypesContext::getRuleIndex() const {
  return HightLavelIRParser::RuleVarTypes;
}

void HightLavelIRParser::VarTypesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarTypes(this);
}

void HightLavelIRParser::VarTypesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarTypes(this);
}

HightLavelIRParser::VarTypesContext* HightLavelIRParser::varTypes() {
  VarTypesContext *_localctx = _tracker.createInstance<VarTypesContext>(_ctx, getState());
  enterRule(_localctx, 46, HightLavelIRParser::RuleVarTypes);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(182);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8456765440) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void HightLavelIRParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  hightlavelirParserInitialize();
#else
  ::antlr4::internal::call_once(hightlavelirParserOnceFlag, hightlavelirParserInitialize);
#endif
}
