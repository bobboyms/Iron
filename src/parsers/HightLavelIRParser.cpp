
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
      "functionCall", "functionCallArgs", "functionCallArg", "returnStatemant", 
      "op", "opRight", "opLeft", "typeRight", "typeLeft", "cast", "mathOp", 
      "expr", "assignment", "functionPtr", "number", "dataFormat", "varTypes"
    },
    std::vector<std::string>{
      "", "'fptr'", "':'", "','", "'='", "';'", "'.'", "'*'", "'{'", "'}'", 
      "'('", "')'", "'MULT'", "'PLUS'", "'MINUS'", "'DIV'", "'['", "']'", 
      "'@'", "'->'", "'_'", "'fn'", "'let'", "'public'", "'private'", "'import'", 
      "'return'", "'to'", "'int'", "'char'", "'float'", "'string'", "'boolean'", 
      "'double'", "'void'", "'cast'", "'call'"
    },
    std::vector<std::string>{
      "", "", "COLON", "COMMA", "EQ", "SEMICOLON", "DOT", "STAR", "L_CURLY", 
      "R_CURLY", "L_PAREN", "R_PAREN", "MULT", "PLUS", "MINUS", "DIV", "L_BRACKET", 
      "R_BRACKET", "AT", "ARROW", "UNDERSCORE", "FUNCTION", "LET", "PUBLIC", 
      "PRIVATE", "IMPORT", "RETURN", "TO", "TYPE_INT", "TYPE_CHAR", "TYPE_FLOAT", 
      "TYPE_STRING", "TYPE_BOOLEAN", "TYPE_DOUBLE", "VOID", "CAST", "CALL", 
      "REAL_NUMBER", "INT_NUMBER", "BOOLEAN_VALUE", "STRING_LITERAL", "IDENTIFIER", 
      "NEWLINE", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,43,200,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,1,0,5,0,54,8,0,10,0,12,0,57,
  	9,0,1,0,5,0,60,8,0,10,0,12,0,63,9,0,1,0,1,0,1,1,1,1,1,1,1,1,3,1,71,8,
  	1,1,2,1,2,1,2,5,2,76,8,2,10,2,12,2,79,9,2,1,3,1,3,1,3,5,3,84,8,3,10,3,
  	12,3,87,9,3,1,4,3,4,90,8,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,5,3,5,101,
  	8,5,1,5,1,5,3,5,105,8,5,1,6,1,6,1,6,3,6,110,8,6,1,7,1,7,1,7,5,7,115,8,
  	7,10,7,12,7,118,9,7,1,8,1,8,1,8,1,8,3,8,124,8,8,1,9,1,9,1,9,1,9,1,9,3,
  	9,131,8,9,1,9,1,9,1,10,1,10,1,10,5,10,138,8,10,10,10,12,10,141,9,10,1,
  	11,1,11,1,11,1,11,1,11,3,11,148,8,11,1,12,1,12,1,12,1,12,1,13,1,13,3,
  	13,156,8,13,1,14,1,14,1,15,1,15,1,16,1,16,1,17,1,17,1,18,1,18,1,18,1,
  	18,1,18,1,19,1,19,1,19,1,19,1,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,
  	20,1,20,1,20,1,20,3,20,187,8,20,1,21,1,21,1,22,1,22,1,22,1,23,1,23,1,
  	24,1,24,1,25,1,25,1,25,0,0,26,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,
  	30,32,34,36,38,40,42,44,46,48,50,0,5,1,0,23,24,1,0,12,15,1,0,37,38,1,
  	0,37,40,2,0,21,21,28,34,196,0,55,1,0,0,0,2,66,1,0,0,0,4,72,1,0,0,0,6,
  	85,1,0,0,0,8,89,1,0,0,0,10,98,1,0,0,0,12,106,1,0,0,0,14,111,1,0,0,0,16,
  	119,1,0,0,0,18,125,1,0,0,0,20,134,1,0,0,0,22,142,1,0,0,0,24,149,1,0,0,
  	0,26,155,1,0,0,0,28,157,1,0,0,0,30,159,1,0,0,0,32,161,1,0,0,0,34,163,
  	1,0,0,0,36,165,1,0,0,0,38,170,1,0,0,0,40,175,1,0,0,0,42,188,1,0,0,0,44,
  	190,1,0,0,0,46,193,1,0,0,0,48,195,1,0,0,0,50,197,1,0,0,0,52,54,3,2,1,
  	0,53,52,1,0,0,0,54,57,1,0,0,0,55,53,1,0,0,0,55,56,1,0,0,0,56,61,1,0,0,
  	0,57,55,1,0,0,0,58,60,3,8,4,0,59,58,1,0,0,0,60,63,1,0,0,0,61,59,1,0,0,
  	0,61,62,1,0,0,0,62,64,1,0,0,0,63,61,1,0,0,0,64,65,5,0,0,1,65,1,1,0,0,
  	0,66,67,5,25,0,0,67,70,3,4,2,0,68,69,5,6,0,0,69,71,5,7,0,0,70,68,1,0,
  	0,0,70,71,1,0,0,0,71,3,1,0,0,0,72,77,5,41,0,0,73,74,5,6,0,0,74,76,5,41,
  	0,0,75,73,1,0,0,0,76,79,1,0,0,0,77,75,1,0,0,0,77,78,1,0,0,0,78,5,1,0,
  	0,0,79,77,1,0,0,0,80,84,3,40,20,0,81,84,3,18,9,0,82,84,3,24,12,0,83,80,
  	1,0,0,0,83,81,1,0,0,0,83,82,1,0,0,0,84,87,1,0,0,0,85,83,1,0,0,0,85,86,
  	1,0,0,0,86,7,1,0,0,0,87,85,1,0,0,0,88,90,7,0,0,0,89,88,1,0,0,0,89,90,
  	1,0,0,0,90,91,1,0,0,0,91,92,5,21,0,0,92,93,5,41,0,0,93,94,3,10,5,0,94,
  	95,5,8,0,0,95,96,3,6,3,0,96,97,5,9,0,0,97,9,1,0,0,0,98,100,5,10,0,0,99,
  	101,3,14,7,0,100,99,1,0,0,0,100,101,1,0,0,0,101,102,1,0,0,0,102,104,5,
  	11,0,0,103,105,3,12,6,0,104,103,1,0,0,0,104,105,1,0,0,0,105,11,1,0,0,
  	0,106,109,5,2,0,0,107,110,3,50,25,0,108,110,5,34,0,0,109,107,1,0,0,0,
  	109,108,1,0,0,0,110,13,1,0,0,0,111,116,3,16,8,0,112,113,5,3,0,0,113,115,
  	3,16,8,0,114,112,1,0,0,0,115,118,1,0,0,0,116,114,1,0,0,0,116,117,1,0,
  	0,0,117,15,1,0,0,0,118,116,1,0,0,0,119,120,5,41,0,0,120,123,5,2,0,0,121,
  	124,3,50,25,0,122,124,3,10,5,0,123,121,1,0,0,0,123,122,1,0,0,0,124,17,
  	1,0,0,0,125,126,5,36,0,0,126,127,3,50,25,0,127,128,5,41,0,0,128,130,5,
  	10,0,0,129,131,3,20,10,0,130,129,1,0,0,0,130,131,1,0,0,0,131,132,1,0,
  	0,0,132,133,5,11,0,0,133,19,1,0,0,0,134,139,3,22,11,0,135,136,5,3,0,0,
  	136,138,3,22,11,0,137,135,1,0,0,0,138,141,1,0,0,0,139,137,1,0,0,0,139,
  	140,1,0,0,0,140,21,1,0,0,0,141,139,1,0,0,0,142,143,5,41,0,0,143,147,5,
  	2,0,0,144,148,5,41,0,0,145,148,3,48,24,0,146,148,3,18,9,0,147,144,1,0,
  	0,0,147,145,1,0,0,0,147,146,1,0,0,0,148,23,1,0,0,0,149,150,5,26,0,0,150,
  	151,3,50,25,0,151,152,5,41,0,0,152,25,1,0,0,0,153,156,5,41,0,0,154,156,
  	3,46,23,0,155,153,1,0,0,0,155,154,1,0,0,0,156,27,1,0,0,0,157,158,3,26,
  	13,0,158,29,1,0,0,0,159,160,3,26,13,0,160,31,1,0,0,0,161,162,3,50,25,
  	0,162,33,1,0,0,0,163,164,3,50,25,0,164,35,1,0,0,0,165,166,5,41,0,0,166,
  	167,3,34,17,0,167,168,5,27,0,0,168,169,3,32,16,0,169,37,1,0,0,0,170,171,
  	7,1,0,0,171,172,3,30,15,0,172,173,5,3,0,0,173,174,3,28,14,0,174,39,1,
  	0,0,0,175,176,5,22,0,0,176,177,5,41,0,0,177,178,5,2,0,0,178,179,3,50,
  	25,0,179,186,5,4,0,0,180,187,3,38,19,0,181,187,3,18,9,0,182,187,3,36,
  	18,0,183,187,3,46,23,0,184,187,3,44,22,0,185,187,3,42,21,0,186,180,1,
  	0,0,0,186,181,1,0,0,0,186,182,1,0,0,0,186,183,1,0,0,0,186,184,1,0,0,0,
  	186,185,1,0,0,0,187,41,1,0,0,0,188,189,5,41,0,0,189,43,1,0,0,0,190,191,
  	5,1,0,0,191,192,5,41,0,0,192,45,1,0,0,0,193,194,7,2,0,0,194,47,1,0,0,
  	0,195,196,7,3,0,0,196,49,1,0,0,0,197,198,7,4,0,0,198,51,1,0,0,0,17,55,
  	61,70,77,83,85,89,100,104,109,116,123,130,139,147,155,186
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
    setState(55);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HightLavelIRParser::IMPORT) {
      setState(52);
      importStatement();
      setState(57);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(61);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 27262976) != 0)) {
      setState(58);
      functionDeclaration();
      setState(63);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(64);
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
    setState(66);
    match(HightLavelIRParser::IMPORT);
    setState(67);
    qualifiedName();
    setState(70);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HightLavelIRParser::DOT) {
      setState(68);
      match(HightLavelIRParser::DOT);
      setState(69);
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
    setState(72);
    match(HightLavelIRParser::IDENTIFIER);
    setState(77);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(73);
        match(HightLavelIRParser::DOT);
        setState(74);
        match(HightLavelIRParser::IDENTIFIER); 
      }
      setState(79);
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

std::vector<HightLavelIRParser::FunctionCallContext *> HightLavelIRParser::StatementListContext::functionCall() {
  return getRuleContexts<HightLavelIRParser::FunctionCallContext>();
}

HightLavelIRParser::FunctionCallContext* HightLavelIRParser::StatementListContext::functionCall(size_t i) {
  return getRuleContext<HightLavelIRParser::FunctionCallContext>(i);
}

std::vector<HightLavelIRParser::ReturnStatemantContext *> HightLavelIRParser::StatementListContext::returnStatemant() {
  return getRuleContexts<HightLavelIRParser::ReturnStatemantContext>();
}

HightLavelIRParser::ReturnStatemantContext* HightLavelIRParser::StatementListContext::returnStatemant(size_t i) {
  return getRuleContext<HightLavelIRParser::ReturnStatemantContext>(i);
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
    setState(85);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 68790779904) != 0)) {
      setState(83);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case HightLavelIRParser::LET: {
          setState(80);
          expr();
          break;
        }

        case HightLavelIRParser::CALL: {
          setState(81);
          functionCall();
          break;
        }

        case HightLavelIRParser::RETURN: {
          setState(82);
          returnStatemant();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(87);
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
    setState(89);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HightLavelIRParser::PUBLIC

    || _la == HightLavelIRParser::PRIVATE) {
      setState(88);
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
    setState(91);
    match(HightLavelIRParser::FUNCTION);
    setState(92);
    antlrcpp::downCast<FunctionDeclarationContext *>(_localctx)->functionName = match(HightLavelIRParser::IDENTIFIER);
    setState(93);
    functionSignature();
    setState(94);
    match(HightLavelIRParser::L_CURLY);
    setState(95);
    statementList();
    setState(96);
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
    setState(98);
    match(HightLavelIRParser::L_PAREN);
    setState(100);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HightLavelIRParser::IDENTIFIER) {
      setState(99);
      functionArgs();
    }
    setState(102);
    match(HightLavelIRParser::R_PAREN);
    setState(104);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HightLavelIRParser::COLON) {
      setState(103);
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
    setState(106);
    match(HightLavelIRParser::COLON);
    setState(109);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(107);
      varTypes();
      break;
    }

    case 2: {
      setState(108);
      match(HightLavelIRParser::VOID);
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
    setState(111);
    functionArg();
    setState(116);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HightLavelIRParser::COMMA) {
      setState(112);
      match(HightLavelIRParser::COMMA);
      setState(113);
      functionArg();
      setState(118);
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
    setState(119);
    antlrcpp::downCast<FunctionArgContext *>(_localctx)->varName = match(HightLavelIRParser::IDENTIFIER);
    setState(120);
    match(HightLavelIRParser::COLON);
    setState(123);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HightLavelIRParser::FUNCTION:
      case HightLavelIRParser::TYPE_INT:
      case HightLavelIRParser::TYPE_CHAR:
      case HightLavelIRParser::TYPE_FLOAT:
      case HightLavelIRParser::TYPE_STRING:
      case HightLavelIRParser::TYPE_BOOLEAN:
      case HightLavelIRParser::TYPE_DOUBLE:
      case HightLavelIRParser::VOID: {
        setState(121);
        varTypes();
        break;
      }

      case HightLavelIRParser::L_PAREN: {
        setState(122);
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

tree::TerminalNode* HightLavelIRParser::FunctionCallContext::CALL() {
  return getToken(HightLavelIRParser::CALL, 0);
}

HightLavelIRParser::VarTypesContext* HightLavelIRParser::FunctionCallContext::varTypes() {
  return getRuleContext<HightLavelIRParser::VarTypesContext>(0);
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
    setState(125);
    match(HightLavelIRParser::CALL);
    setState(126);
    varTypes();
    setState(127);
    antlrcpp::downCast<FunctionCallContext *>(_localctx)->functionName = match(HightLavelIRParser::IDENTIFIER);
    setState(128);
    match(HightLavelIRParser::L_PAREN);
    setState(130);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HightLavelIRParser::IDENTIFIER) {
      setState(129);
      functionCallArgs();
    }
    setState(132);
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
    setState(134);
    functionCallArg();
    setState(139);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HightLavelIRParser::COMMA) {
      setState(135);
      match(HightLavelIRParser::COMMA);
      setState(136);
      functionCallArg();
      setState(141);
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
    setState(142);
    antlrcpp::downCast<FunctionCallArgContext *>(_localctx)->varName = match(HightLavelIRParser::IDENTIFIER);
    setState(143);
    match(HightLavelIRParser::COLON);
    setState(147);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HightLavelIRParser::IDENTIFIER: {
        setState(144);
        antlrcpp::downCast<FunctionCallArgContext *>(_localctx)->anotherVarName = match(HightLavelIRParser::IDENTIFIER);
        break;
      }

      case HightLavelIRParser::REAL_NUMBER:
      case HightLavelIRParser::INT_NUMBER:
      case HightLavelIRParser::BOOLEAN_VALUE:
      case HightLavelIRParser::STRING_LITERAL: {
        setState(145);
        dataFormat();
        break;
      }

      case HightLavelIRParser::CALL: {
        setState(146);
        functionCall();
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

//----------------- ReturnStatemantContext ------------------------------------------------------------------

HightLavelIRParser::ReturnStatemantContext::ReturnStatemantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HightLavelIRParser::ReturnStatemantContext::RETURN() {
  return getToken(HightLavelIRParser::RETURN, 0);
}

HightLavelIRParser::VarTypesContext* HightLavelIRParser::ReturnStatemantContext::varTypes() {
  return getRuleContext<HightLavelIRParser::VarTypesContext>(0);
}

tree::TerminalNode* HightLavelIRParser::ReturnStatemantContext::IDENTIFIER() {
  return getToken(HightLavelIRParser::IDENTIFIER, 0);
}


size_t HightLavelIRParser::ReturnStatemantContext::getRuleIndex() const {
  return HightLavelIRParser::RuleReturnStatemant;
}

void HightLavelIRParser::ReturnStatemantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStatemant(this);
}

void HightLavelIRParser::ReturnStatemantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStatemant(this);
}

HightLavelIRParser::ReturnStatemantContext* HightLavelIRParser::returnStatemant() {
  ReturnStatemantContext *_localctx = _tracker.createInstance<ReturnStatemantContext>(_ctx, getState());
  enterRule(_localctx, 24, HightLavelIRParser::RuleReturnStatemant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(149);
    match(HightLavelIRParser::RETURN);
    setState(150);
    varTypes();
    setState(151);
    antlrcpp::downCast<ReturnStatemantContext *>(_localctx)->varName = match(HightLavelIRParser::IDENTIFIER);
   
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
  enterRule(_localctx, 26, HightLavelIRParser::RuleOp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(155);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HightLavelIRParser::IDENTIFIER: {
        setState(153);
        antlrcpp::downCast<OpContext *>(_localctx)->varName = match(HightLavelIRParser::IDENTIFIER);
        break;
      }

      case HightLavelIRParser::REAL_NUMBER:
      case HightLavelIRParser::INT_NUMBER: {
        setState(154);
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
  enterRule(_localctx, 28, HightLavelIRParser::RuleOpRight);

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
  enterRule(_localctx, 30, HightLavelIRParser::RuleOpLeft);

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
  enterRule(_localctx, 32, HightLavelIRParser::RuleTypeRight);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(161);
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
  enterRule(_localctx, 34, HightLavelIRParser::RuleTypeLeft);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(163);
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
  enterRule(_localctx, 36, HightLavelIRParser::RuleCast);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(165);
    antlrcpp::downCast<CastContext *>(_localctx)->anotherVarName = match(HightLavelIRParser::IDENTIFIER);
    setState(166);
    typeLeft();
    setState(167);
    match(HightLavelIRParser::TO);
    setState(168);
    typeRight();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MathOpContext ------------------------------------------------------------------

HightLavelIRParser::MathOpContext::MathOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HightLavelIRParser::OpLeftContext* HightLavelIRParser::MathOpContext::opLeft() {
  return getRuleContext<HightLavelIRParser::OpLeftContext>(0);
}

tree::TerminalNode* HightLavelIRParser::MathOpContext::COMMA() {
  return getToken(HightLavelIRParser::COMMA, 0);
}

HightLavelIRParser::OpRightContext* HightLavelIRParser::MathOpContext::opRight() {
  return getRuleContext<HightLavelIRParser::OpRightContext>(0);
}

tree::TerminalNode* HightLavelIRParser::MathOpContext::MULT() {
  return getToken(HightLavelIRParser::MULT, 0);
}

tree::TerminalNode* HightLavelIRParser::MathOpContext::DIV() {
  return getToken(HightLavelIRParser::DIV, 0);
}

tree::TerminalNode* HightLavelIRParser::MathOpContext::PLUS() {
  return getToken(HightLavelIRParser::PLUS, 0);
}

tree::TerminalNode* HightLavelIRParser::MathOpContext::MINUS() {
  return getToken(HightLavelIRParser::MINUS, 0);
}


size_t HightLavelIRParser::MathOpContext::getRuleIndex() const {
  return HightLavelIRParser::RuleMathOp;
}

void HightLavelIRParser::MathOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMathOp(this);
}

void HightLavelIRParser::MathOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMathOp(this);
}

HightLavelIRParser::MathOpContext* HightLavelIRParser::mathOp() {
  MathOpContext *_localctx = _tracker.createInstance<MathOpContext>(_ctx, getState());
  enterRule(_localctx, 38, HightLavelIRParser::RuleMathOp);
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
    setState(170);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 61440) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(171);
    opLeft();
    setState(172);
    match(HightLavelIRParser::COMMA);
    setState(173);
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

HightLavelIRParser::MathOpContext* HightLavelIRParser::ExprContext::mathOp() {
  return getRuleContext<HightLavelIRParser::MathOpContext>(0);
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

HightLavelIRParser::FunctionPtrContext* HightLavelIRParser::ExprContext::functionPtr() {
  return getRuleContext<HightLavelIRParser::FunctionPtrContext>(0);
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
  enterRule(_localctx, 40, HightLavelIRParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(175);
    match(HightLavelIRParser::LET);
    setState(176);
    antlrcpp::downCast<ExprContext *>(_localctx)->varName = match(HightLavelIRParser::IDENTIFIER);
    setState(177);
    match(HightLavelIRParser::COLON);
    setState(178);
    varTypes();
    setState(179);
    match(HightLavelIRParser::EQ);
    setState(186);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      setState(180);
      mathOp();
      break;
    }

    case 2: {
      setState(181);
      functionCall();
      break;
    }

    case 3: {
      setState(182);
      cast();
      break;
    }

    case 4: {
      setState(183);
      number();
      break;
    }

    case 5: {
      setState(184);
      functionPtr();
      break;
    }

    case 6: {
      setState(185);
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
  enterRule(_localctx, 42, HightLavelIRParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(188);
    antlrcpp::downCast<AssignmentContext *>(_localctx)->anotherVarName = match(HightLavelIRParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionPtrContext ------------------------------------------------------------------

HightLavelIRParser::FunctionPtrContext::FunctionPtrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HightLavelIRParser::FunctionPtrContext::IDENTIFIER() {
  return getToken(HightLavelIRParser::IDENTIFIER, 0);
}


size_t HightLavelIRParser::FunctionPtrContext::getRuleIndex() const {
  return HightLavelIRParser::RuleFunctionPtr;
}

void HightLavelIRParser::FunctionPtrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionPtr(this);
}

void HightLavelIRParser::FunctionPtrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HightLavelIRListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionPtr(this);
}

HightLavelIRParser::FunctionPtrContext* HightLavelIRParser::functionPtr() {
  FunctionPtrContext *_localctx = _tracker.createInstance<FunctionPtrContext>(_ctx, getState());
  enterRule(_localctx, 44, HightLavelIRParser::RuleFunctionPtr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(190);
    match(HightLavelIRParser::T__0);
    setState(191);
    antlrcpp::downCast<FunctionPtrContext *>(_localctx)->functionName = match(HightLavelIRParser::IDENTIFIER);
   
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
  enterRule(_localctx, 46, HightLavelIRParser::RuleNumber);
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
    setState(193);
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
  enterRule(_localctx, 48, HightLavelIRParser::RuleDataFormat);
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
    setState(195);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2061584302080) != 0))) {
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

tree::TerminalNode* HightLavelIRParser::VarTypesContext::VOID() {
  return getToken(HightLavelIRParser::VOID, 0);
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
  enterRule(_localctx, 50, HightLavelIRParser::RuleVarTypes);
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
    setState(197);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 34093400064) != 0))) {
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
