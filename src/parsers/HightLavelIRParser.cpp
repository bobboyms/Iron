
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
      "opLeft", "typeRight", "typeLeft", "cast", "math_op", "expr", "number", 
      "dataFormat", "varTypes"
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
  	4,1,41,181,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,1,0,5,0,48,8,0,10,0,12,0,51,9,0,1,0,5,0,54,8,0,10,0,12,0,
  	57,9,0,1,0,1,0,1,1,1,1,1,1,1,1,3,1,65,8,1,1,2,1,2,1,2,5,2,70,8,2,10,2,
  	12,2,73,9,2,1,3,5,3,76,8,3,10,3,12,3,79,9,3,1,4,3,4,82,8,4,1,4,1,4,1,
  	4,1,4,1,4,1,4,1,4,1,5,1,5,3,5,93,8,5,1,5,1,5,3,5,97,8,5,1,6,1,6,1,6,3,
  	6,102,8,6,1,7,1,7,1,7,5,7,107,8,7,10,7,12,7,110,9,7,1,8,1,8,1,8,1,8,3,
  	8,116,8,8,1,9,1,9,1,9,3,9,121,8,9,1,9,1,9,1,10,1,10,1,10,5,10,128,8,10,
  	10,10,12,10,131,9,10,1,11,1,11,1,11,1,11,1,11,1,11,3,11,139,8,11,1,12,
  	1,12,3,12,143,8,12,1,13,1,13,1,14,1,14,1,15,1,15,1,16,1,16,1,17,1,17,
  	1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,18,1,19,1,19,1,19,1,19,1,19,1,19,
  	1,19,1,19,1,19,1,19,3,19,173,8,19,1,20,1,20,1,21,1,21,1,22,1,22,1,22,
  	0,0,23,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,
  	0,5,1,0,22,23,1,0,11,14,1,0,35,36,1,0,35,38,2,0,20,20,27,32,176,0,49,
  	1,0,0,0,2,60,1,0,0,0,4,66,1,0,0,0,6,77,1,0,0,0,8,81,1,0,0,0,10,90,1,0,
  	0,0,12,98,1,0,0,0,14,103,1,0,0,0,16,111,1,0,0,0,18,117,1,0,0,0,20,124,
  	1,0,0,0,22,132,1,0,0,0,24,142,1,0,0,0,26,144,1,0,0,0,28,146,1,0,0,0,30,
  	148,1,0,0,0,32,150,1,0,0,0,34,152,1,0,0,0,36,157,1,0,0,0,38,162,1,0,0,
  	0,40,174,1,0,0,0,42,176,1,0,0,0,44,178,1,0,0,0,46,48,3,2,1,0,47,46,1,
  	0,0,0,48,51,1,0,0,0,49,47,1,0,0,0,49,50,1,0,0,0,50,55,1,0,0,0,51,49,1,
  	0,0,0,52,54,3,8,4,0,53,52,1,0,0,0,54,57,1,0,0,0,55,53,1,0,0,0,55,56,1,
  	0,0,0,56,58,1,0,0,0,57,55,1,0,0,0,58,59,5,0,0,1,59,1,1,0,0,0,60,61,5,
  	24,0,0,61,64,3,4,2,0,62,63,5,5,0,0,63,65,5,6,0,0,64,62,1,0,0,0,64,65,
  	1,0,0,0,65,3,1,0,0,0,66,71,5,39,0,0,67,68,5,5,0,0,68,70,5,39,0,0,69,67,
  	1,0,0,0,70,73,1,0,0,0,71,69,1,0,0,0,71,72,1,0,0,0,72,5,1,0,0,0,73,71,
  	1,0,0,0,74,76,3,38,19,0,75,74,1,0,0,0,76,79,1,0,0,0,77,75,1,0,0,0,77,
  	78,1,0,0,0,78,7,1,0,0,0,79,77,1,0,0,0,80,82,7,0,0,0,81,80,1,0,0,0,81,
  	82,1,0,0,0,82,83,1,0,0,0,83,84,5,20,0,0,84,85,5,39,0,0,85,86,3,10,5,0,
  	86,87,5,7,0,0,87,88,3,6,3,0,88,89,5,8,0,0,89,9,1,0,0,0,90,92,5,9,0,0,
  	91,93,3,14,7,0,92,91,1,0,0,0,92,93,1,0,0,0,93,94,1,0,0,0,94,96,5,10,0,
  	0,95,97,3,12,6,0,96,95,1,0,0,0,96,97,1,0,0,0,97,11,1,0,0,0,98,101,5,1,
  	0,0,99,102,3,44,22,0,100,102,5,33,0,0,101,99,1,0,0,0,101,100,1,0,0,0,
  	102,13,1,0,0,0,103,108,3,16,8,0,104,105,5,2,0,0,105,107,3,16,8,0,106,
  	104,1,0,0,0,107,110,1,0,0,0,108,106,1,0,0,0,108,109,1,0,0,0,109,15,1,
  	0,0,0,110,108,1,0,0,0,111,112,5,39,0,0,112,115,5,1,0,0,113,116,3,44,22,
  	0,114,116,3,10,5,0,115,113,1,0,0,0,115,114,1,0,0,0,116,17,1,0,0,0,117,
  	118,5,39,0,0,118,120,5,9,0,0,119,121,3,20,10,0,120,119,1,0,0,0,120,121,
  	1,0,0,0,121,122,1,0,0,0,122,123,5,10,0,0,123,19,1,0,0,0,124,129,3,22,
  	11,0,125,126,5,2,0,0,126,128,3,22,11,0,127,125,1,0,0,0,128,131,1,0,0,
  	0,129,127,1,0,0,0,129,130,1,0,0,0,130,21,1,0,0,0,131,129,1,0,0,0,132,
  	133,5,39,0,0,133,138,5,1,0,0,134,139,3,42,21,0,135,136,3,18,9,0,136,137,
  	5,39,0,0,137,139,1,0,0,0,138,134,1,0,0,0,138,135,1,0,0,0,139,23,1,0,0,
  	0,140,143,5,39,0,0,141,143,3,40,20,0,142,140,1,0,0,0,142,141,1,0,0,0,
  	143,25,1,0,0,0,144,145,3,24,12,0,145,27,1,0,0,0,146,147,3,24,12,0,147,
  	29,1,0,0,0,148,149,3,44,22,0,149,31,1,0,0,0,150,151,3,44,22,0,151,33,
  	1,0,0,0,152,153,5,39,0,0,153,154,3,32,16,0,154,155,5,26,0,0,155,156,3,
  	30,15,0,156,35,1,0,0,0,157,158,7,1,0,0,158,159,3,28,14,0,159,160,5,2,
  	0,0,160,161,3,26,13,0,161,37,1,0,0,0,162,163,5,21,0,0,163,164,5,39,0,
  	0,164,165,5,1,0,0,165,166,3,44,22,0,166,172,5,3,0,0,167,173,3,36,18,0,
  	168,173,3,18,9,0,169,173,3,34,17,0,170,173,3,40,20,0,171,173,5,39,0,0,
  	172,167,1,0,0,0,172,168,1,0,0,0,172,169,1,0,0,0,172,170,1,0,0,0,172,171,
  	1,0,0,0,173,39,1,0,0,0,174,175,7,2,0,0,175,41,1,0,0,0,176,177,7,3,0,0,
  	177,43,1,0,0,0,178,179,7,4,0,0,179,45,1,0,0,0,16,49,55,64,71,77,81,92,
  	96,101,108,115,120,129,138,142,172
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
    setState(49);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HightLavelIRParser::IMPORT) {
      setState(46);
      importStatement();
      setState(51);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(55);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 13631488) != 0)) {
      setState(52);
      functionDeclaration();
      setState(57);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(58);
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
    setState(60);
    match(HightLavelIRParser::IMPORT);
    setState(61);
    qualifiedName();
    setState(64);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HightLavelIRParser::DOT) {
      setState(62);
      match(HightLavelIRParser::DOT);
      setState(63);
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
    setState(66);
    match(HightLavelIRParser::IDENTIFIER);
    setState(71);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(67);
        match(HightLavelIRParser::DOT);
        setState(68);
        match(HightLavelIRParser::IDENTIFIER); 
      }
      setState(73);
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
    setState(77);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HightLavelIRParser::LET) {
      setState(74);
      expr();
      setState(79);
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
    setState(81);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HightLavelIRParser::PUBLIC

    || _la == HightLavelIRParser::PRIVATE) {
      setState(80);
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
    setState(83);
    match(HightLavelIRParser::FUNCTION);
    setState(84);
    antlrcpp::downCast<FunctionDeclarationContext *>(_localctx)->functionName = match(HightLavelIRParser::IDENTIFIER);
    setState(85);
    functionSignature();
    setState(86);
    match(HightLavelIRParser::L_CURLY);
    setState(87);
    statementList();
    setState(88);
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
    setState(90);
    match(HightLavelIRParser::L_PAREN);
    setState(92);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HightLavelIRParser::IDENTIFIER) {
      setState(91);
      functionArgs();
    }
    setState(94);
    match(HightLavelIRParser::R_PAREN);
    setState(96);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HightLavelIRParser::COLON) {
      setState(95);
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
    setState(98);
    match(HightLavelIRParser::COLON);
    setState(101);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HightLavelIRParser::FUNCTION:
      case HightLavelIRParser::TYPE_INT:
      case HightLavelIRParser::TYPE_CHAR:
      case HightLavelIRParser::TYPE_FLOAT:
      case HightLavelIRParser::TYPE_STRING:
      case HightLavelIRParser::TYPE_BOOLEAN:
      case HightLavelIRParser::TYPE_DOUBLE: {
        setState(99);
        varTypes();
        break;
      }

      case HightLavelIRParser::VOID: {
        setState(100);
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
    setState(103);
    functionArg();
    setState(108);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HightLavelIRParser::COMMA) {
      setState(104);
      match(HightLavelIRParser::COMMA);
      setState(105);
      functionArg();
      setState(110);
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
    setState(111);
    antlrcpp::downCast<FunctionArgContext *>(_localctx)->varName = match(HightLavelIRParser::IDENTIFIER);
    setState(112);
    match(HightLavelIRParser::COLON);
    setState(115);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HightLavelIRParser::FUNCTION:
      case HightLavelIRParser::TYPE_INT:
      case HightLavelIRParser::TYPE_CHAR:
      case HightLavelIRParser::TYPE_FLOAT:
      case HightLavelIRParser::TYPE_STRING:
      case HightLavelIRParser::TYPE_BOOLEAN:
      case HightLavelIRParser::TYPE_DOUBLE: {
        setState(113);
        varTypes();
        break;
      }

      case HightLavelIRParser::L_PAREN: {
        setState(114);
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
    setState(117);
    antlrcpp::downCast<FunctionCallContext *>(_localctx)->functionName = match(HightLavelIRParser::IDENTIFIER);
    setState(118);
    match(HightLavelIRParser::L_PAREN);
    setState(120);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HightLavelIRParser::IDENTIFIER) {
      setState(119);
      functionCallArgs();
    }
    setState(122);
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
    setState(124);
    functionCallArg();
    setState(129);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HightLavelIRParser::COMMA) {
      setState(125);
      match(HightLavelIRParser::COMMA);
      setState(126);
      functionCallArg();
      setState(131);
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
    setState(132);
    antlrcpp::downCast<FunctionCallArgContext *>(_localctx)->varName = match(HightLavelIRParser::IDENTIFIER);
    setState(133);
    match(HightLavelIRParser::COLON);
    setState(138);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HightLavelIRParser::REAL_NUMBER:
      case HightLavelIRParser::INT_NUMBER:
      case HightLavelIRParser::BOOLEAN_VALUE:
      case HightLavelIRParser::STRING_LITERAL: {
        setState(134);
        dataFormat();
        break;
      }

      case HightLavelIRParser::IDENTIFIER: {
        setState(135);
        functionCall();
        setState(136);
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
    setState(142);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HightLavelIRParser::IDENTIFIER: {
        setState(140);
        antlrcpp::downCast<OpContext *>(_localctx)->varName = match(HightLavelIRParser::IDENTIFIER);
        break;
      }

      case HightLavelIRParser::REAL_NUMBER:
      case HightLavelIRParser::INT_NUMBER: {
        setState(141);
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
    setState(144);
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
    setState(148);
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
    setState(152);
    antlrcpp::downCast<CastContext *>(_localctx)->anotherVarName = match(HightLavelIRParser::IDENTIFIER);
    setState(153);
    typeLeft();
    setState(154);
    match(HightLavelIRParser::TO);
    setState(155);
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
    setState(157);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 30720) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(158);
    opLeft();
    setState(159);
    match(HightLavelIRParser::COMMA);
    setState(160);
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

std::vector<tree::TerminalNode *> HightLavelIRParser::ExprContext::IDENTIFIER() {
  return getTokens(HightLavelIRParser::IDENTIFIER);
}

tree::TerminalNode* HightLavelIRParser::ExprContext::IDENTIFIER(size_t i) {
  return getToken(HightLavelIRParser::IDENTIFIER, i);
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
    setState(162);
    match(HightLavelIRParser::LET);
    setState(163);
    antlrcpp::downCast<ExprContext *>(_localctx)->varName = match(HightLavelIRParser::IDENTIFIER);
    setState(164);
    match(HightLavelIRParser::COLON);
    setState(165);
    varTypes();
    setState(166);
    match(HightLavelIRParser::EQ);
    setState(172);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      setState(167);
      math_op();
      break;
    }

    case 2: {
      setState(168);
      functionCall();
      break;
    }

    case 3: {
      setState(169);
      cast();
      break;
    }

    case 4: {
      setState(170);
      number();
      break;
    }

    case 5: {
      setState(171);
      antlrcpp::downCast<ExprContext *>(_localctx)->anotherVarName = match(HightLavelIRParser::IDENTIFIER);
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
  enterRule(_localctx, 40, HightLavelIRParser::RuleNumber);
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
    setState(174);
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
  enterRule(_localctx, 42, HightLavelIRParser::RuleDataFormat);
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
    setState(176);
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
  enterRule(_localctx, 44, HightLavelIRParser::RuleVarTypes);
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
