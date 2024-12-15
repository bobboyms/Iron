
// Generated from Iron.g4 by ANTLR 4.13.2


#include "IronListener.h"

#include "IronParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct IronParserStaticData final {
  IronParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  IronParserStaticData(const IronParserStaticData&) = delete;
  IronParserStaticData(IronParserStaticData&&) = delete;
  IronParserStaticData& operator=(const IronParserStaticData&) = delete;
  IronParserStaticData& operator=(IronParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag ironParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<IronParserStaticData> ironParserStaticData = nullptr;

void ironParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (ironParserStaticData != nullptr) {
    return;
  }
#else
  assert(ironParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<IronParserStaticData>(
    std::vector<std::string>{
      "program", "importStatement", "qualifiedName", "entryPoint", "body", 
      "functionDeclaration", "statement", "varDeclaration", "dataFormat", 
      "varTypes"
    },
    std::vector<std::string>{
      "", "'@main'", "':'", "'='", "';'", "'.'", "'*'", "'{'", "'}'", "'['", 
      "']'", "'('", "')'", "'fn'", "'let'", "'public'", "'import'", "'int'", 
      "'char'", "'float'", "'string'", "'boolean'", "'double'"
    },
    std::vector<std::string>{
      "", "", "COLON", "EQ", "SEMICOLON", "DOT", "STAR", "L_CURLY", "R_CURLY", 
      "L_BRACKET", "R_BRACKET", "L_PAREN", "R_PAREN", "FUNCTION", "LET", 
      "PUBLIC", "IMPORT", "TYPE_INT", "TYPE_CHAR", "TYPE_FLOAT", "TYPE_STRING", 
      "TYPE_BOOLEAN", "TYPE_DOUBLE", "REAL_NUMBER", "INT_NUMBER", "BOOLEAN_VALUE", 
      "STRING_LITERAL", "IDENTIFIER", "NEWLINE", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,29,110,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,1,0,5,0,22,8,0,10,0,12,0,25,9,0,1,0,1,0,3,0,29,
  	8,0,1,0,3,0,32,8,0,1,0,1,0,1,1,1,1,1,1,1,1,3,1,40,8,1,1,1,1,1,1,2,1,2,
  	1,2,5,2,47,8,2,10,2,12,2,50,9,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,5,3,59,8,
  	3,10,3,12,3,62,9,3,1,3,1,3,3,3,66,8,3,1,3,3,3,69,8,3,1,4,1,4,1,4,5,4,
  	74,8,4,10,4,12,4,77,9,4,1,5,3,5,80,8,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,88,
  	8,5,1,5,1,5,3,5,92,8,5,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,3,7,102,8,7,1,
  	7,1,7,1,8,1,8,1,9,1,9,1,9,0,0,10,0,2,4,6,8,10,12,14,16,18,0,2,1,0,23,
  	26,1,0,17,22,115,0,23,1,0,0,0,2,35,1,0,0,0,4,43,1,0,0,0,6,51,1,0,0,0,
  	8,75,1,0,0,0,10,79,1,0,0,0,12,93,1,0,0,0,14,95,1,0,0,0,16,105,1,0,0,0,
  	18,107,1,0,0,0,20,22,3,2,1,0,21,20,1,0,0,0,22,25,1,0,0,0,23,21,1,0,0,
  	0,23,24,1,0,0,0,24,26,1,0,0,0,25,23,1,0,0,0,26,28,3,8,4,0,27,29,3,6,3,
  	0,28,27,1,0,0,0,28,29,1,0,0,0,29,31,1,0,0,0,30,32,5,28,0,0,31,30,1,0,
  	0,0,31,32,1,0,0,0,32,33,1,0,0,0,33,34,5,0,0,1,34,1,1,0,0,0,35,36,5,16,
  	0,0,36,39,3,4,2,0,37,38,5,5,0,0,38,40,5,6,0,0,39,37,1,0,0,0,39,40,1,0,
  	0,0,40,41,1,0,0,0,41,42,5,28,0,0,42,3,1,0,0,0,43,48,5,27,0,0,44,45,5,
  	5,0,0,45,47,5,27,0,0,46,44,1,0,0,0,47,50,1,0,0,0,48,46,1,0,0,0,48,49,
  	1,0,0,0,49,5,1,0,0,0,50,48,1,0,0,0,51,52,5,1,0,0,52,53,5,11,0,0,53,54,
  	5,27,0,0,54,55,5,12,0,0,55,60,5,7,0,0,56,59,3,12,6,0,57,59,5,28,0,0,58,
  	56,1,0,0,0,58,57,1,0,0,0,59,62,1,0,0,0,60,58,1,0,0,0,60,61,1,0,0,0,61,
  	63,1,0,0,0,62,60,1,0,0,0,63,65,5,8,0,0,64,66,5,28,0,0,65,64,1,0,0,0,65,
  	66,1,0,0,0,66,68,1,0,0,0,67,69,5,0,0,1,68,67,1,0,0,0,68,69,1,0,0,0,69,
  	7,1,0,0,0,70,74,3,12,6,0,71,74,3,10,5,0,72,74,5,28,0,0,73,70,1,0,0,0,
  	73,71,1,0,0,0,73,72,1,0,0,0,74,77,1,0,0,0,75,73,1,0,0,0,75,76,1,0,0,0,
  	76,9,1,0,0,0,77,75,1,0,0,0,78,80,5,15,0,0,79,78,1,0,0,0,79,80,1,0,0,0,
  	80,81,1,0,0,0,81,82,5,13,0,0,82,83,5,27,0,0,83,84,5,11,0,0,84,85,5,12,
  	0,0,85,87,5,7,0,0,86,88,5,28,0,0,87,86,1,0,0,0,87,88,1,0,0,0,88,89,1,
  	0,0,0,89,91,5,8,0,0,90,92,5,28,0,0,91,90,1,0,0,0,91,92,1,0,0,0,92,11,
  	1,0,0,0,93,94,3,14,7,0,94,13,1,0,0,0,95,96,5,14,0,0,96,97,5,27,0,0,97,
  	98,5,2,0,0,98,101,3,18,9,0,99,100,5,3,0,0,100,102,3,16,8,0,101,99,1,0,
  	0,0,101,102,1,0,0,0,102,103,1,0,0,0,103,104,5,28,0,0,104,15,1,0,0,0,105,
  	106,7,0,0,0,106,17,1,0,0,0,107,108,7,1,0,0,108,19,1,0,0,0,15,23,28,31,
  	39,48,58,60,65,68,73,75,79,87,91,101
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  ironParserStaticData = std::move(staticData);
}

}

IronParser::IronParser(TokenStream *input) : IronParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

IronParser::IronParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  IronParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *ironParserStaticData->atn, ironParserStaticData->decisionToDFA, ironParserStaticData->sharedContextCache, options);
}

IronParser::~IronParser() {
  delete _interpreter;
}

const atn::ATN& IronParser::getATN() const {
  return *ironParserStaticData->atn;
}

std::string IronParser::getGrammarFileName() const {
  return "Iron.g4";
}

const std::vector<std::string>& IronParser::getRuleNames() const {
  return ironParserStaticData->ruleNames;
}

const dfa::Vocabulary& IronParser::getVocabulary() const {
  return ironParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView IronParser::getSerializedATN() const {
  return ironParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

IronParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IronParser::BodyContext* IronParser::ProgramContext::body() {
  return getRuleContext<IronParser::BodyContext>(0);
}

tree::TerminalNode* IronParser::ProgramContext::EOF() {
  return getToken(IronParser::EOF, 0);
}

std::vector<IronParser::ImportStatementContext *> IronParser::ProgramContext::importStatement() {
  return getRuleContexts<IronParser::ImportStatementContext>();
}

IronParser::ImportStatementContext* IronParser::ProgramContext::importStatement(size_t i) {
  return getRuleContext<IronParser::ImportStatementContext>(i);
}

IronParser::EntryPointContext* IronParser::ProgramContext::entryPoint() {
  return getRuleContext<IronParser::EntryPointContext>(0);
}

tree::TerminalNode* IronParser::ProgramContext::NEWLINE() {
  return getToken(IronParser::NEWLINE, 0);
}


size_t IronParser::ProgramContext::getRuleIndex() const {
  return IronParser::RuleProgram;
}

void IronParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void IronParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}

IronParser::ProgramContext* IronParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, IronParser::RuleProgram);
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
    setState(23);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::IMPORT) {
      setState(20);
      importStatement();
      setState(25);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(26);
    body();
    setState(28);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::T__0) {
      setState(27);
      entryPoint();
    }
    setState(31);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::NEWLINE) {
      setState(30);
      match(IronParser::NEWLINE);
    }
    setState(33);
    match(IronParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportStatementContext ------------------------------------------------------------------

IronParser::ImportStatementContext::ImportStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::ImportStatementContext::IMPORT() {
  return getToken(IronParser::IMPORT, 0);
}

IronParser::QualifiedNameContext* IronParser::ImportStatementContext::qualifiedName() {
  return getRuleContext<IronParser::QualifiedNameContext>(0);
}

tree::TerminalNode* IronParser::ImportStatementContext::NEWLINE() {
  return getToken(IronParser::NEWLINE, 0);
}

tree::TerminalNode* IronParser::ImportStatementContext::DOT() {
  return getToken(IronParser::DOT, 0);
}

tree::TerminalNode* IronParser::ImportStatementContext::STAR() {
  return getToken(IronParser::STAR, 0);
}


size_t IronParser::ImportStatementContext::getRuleIndex() const {
  return IronParser::RuleImportStatement;
}

void IronParser::ImportStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportStatement(this);
}

void IronParser::ImportStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportStatement(this);
}

IronParser::ImportStatementContext* IronParser::importStatement() {
  ImportStatementContext *_localctx = _tracker.createInstance<ImportStatementContext>(_ctx, getState());
  enterRule(_localctx, 2, IronParser::RuleImportStatement);
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
    setState(35);
    match(IronParser::IMPORT);
    setState(36);
    qualifiedName();
    setState(39);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::DOT) {
      setState(37);
      match(IronParser::DOT);
      setState(38);
      match(IronParser::STAR);
    }
    setState(41);
    match(IronParser::NEWLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QualifiedNameContext ------------------------------------------------------------------

IronParser::QualifiedNameContext::QualifiedNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> IronParser::QualifiedNameContext::IDENTIFIER() {
  return getTokens(IronParser::IDENTIFIER);
}

tree::TerminalNode* IronParser::QualifiedNameContext::IDENTIFIER(size_t i) {
  return getToken(IronParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> IronParser::QualifiedNameContext::DOT() {
  return getTokens(IronParser::DOT);
}

tree::TerminalNode* IronParser::QualifiedNameContext::DOT(size_t i) {
  return getToken(IronParser::DOT, i);
}


size_t IronParser::QualifiedNameContext::getRuleIndex() const {
  return IronParser::RuleQualifiedName;
}

void IronParser::QualifiedNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterQualifiedName(this);
}

void IronParser::QualifiedNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitQualifiedName(this);
}

IronParser::QualifiedNameContext* IronParser::qualifiedName() {
  QualifiedNameContext *_localctx = _tracker.createInstance<QualifiedNameContext>(_ctx, getState());
  enterRule(_localctx, 4, IronParser::RuleQualifiedName);

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
    setState(43);
    match(IronParser::IDENTIFIER);
    setState(48);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(44);
        match(IronParser::DOT);
        setState(45);
        match(IronParser::IDENTIFIER); 
      }
      setState(50);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EntryPointContext ------------------------------------------------------------------

IronParser::EntryPointContext::EntryPointContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::EntryPointContext::L_PAREN() {
  return getToken(IronParser::L_PAREN, 0);
}

tree::TerminalNode* IronParser::EntryPointContext::R_PAREN() {
  return getToken(IronParser::R_PAREN, 0);
}

tree::TerminalNode* IronParser::EntryPointContext::L_CURLY() {
  return getToken(IronParser::L_CURLY, 0);
}

tree::TerminalNode* IronParser::EntryPointContext::R_CURLY() {
  return getToken(IronParser::R_CURLY, 0);
}

tree::TerminalNode* IronParser::EntryPointContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

std::vector<IronParser::StatementContext *> IronParser::EntryPointContext::statement() {
  return getRuleContexts<IronParser::StatementContext>();
}

IronParser::StatementContext* IronParser::EntryPointContext::statement(size_t i) {
  return getRuleContext<IronParser::StatementContext>(i);
}

std::vector<tree::TerminalNode *> IronParser::EntryPointContext::NEWLINE() {
  return getTokens(IronParser::NEWLINE);
}

tree::TerminalNode* IronParser::EntryPointContext::NEWLINE(size_t i) {
  return getToken(IronParser::NEWLINE, i);
}

tree::TerminalNode* IronParser::EntryPointContext::EOF() {
  return getToken(IronParser::EOF, 0);
}


size_t IronParser::EntryPointContext::getRuleIndex() const {
  return IronParser::RuleEntryPoint;
}

void IronParser::EntryPointContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEntryPoint(this);
}

void IronParser::EntryPointContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEntryPoint(this);
}

IronParser::EntryPointContext* IronParser::entryPoint() {
  EntryPointContext *_localctx = _tracker.createInstance<EntryPointContext>(_ctx, getState());
  enterRule(_localctx, 6, IronParser::RuleEntryPoint);
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
    match(IronParser::T__0);
    setState(52);
    match(IronParser::L_PAREN);
    setState(53);
    antlrcpp::downCast<EntryPointContext *>(_localctx)->argVar = match(IronParser::IDENTIFIER);
    setState(54);
    match(IronParser::R_PAREN);
    setState(55);
    match(IronParser::L_CURLY);
    setState(60);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::LET

    || _la == IronParser::NEWLINE) {
      setState(58);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case IronParser::LET: {
          setState(56);
          statement();
          break;
        }

        case IronParser::NEWLINE: {
          setState(57);
          match(IronParser::NEWLINE);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(62);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(63);
    match(IronParser::R_CURLY);
    setState(65);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      setState(64);
      match(IronParser::NEWLINE);
      break;
    }

    default:
      break;
    }
    setState(68);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      setState(67);
      match(IronParser::EOF);
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

//----------------- BodyContext ------------------------------------------------------------------

IronParser::BodyContext::BodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IronParser::StatementContext *> IronParser::BodyContext::statement() {
  return getRuleContexts<IronParser::StatementContext>();
}

IronParser::StatementContext* IronParser::BodyContext::statement(size_t i) {
  return getRuleContext<IronParser::StatementContext>(i);
}

std::vector<IronParser::FunctionDeclarationContext *> IronParser::BodyContext::functionDeclaration() {
  return getRuleContexts<IronParser::FunctionDeclarationContext>();
}

IronParser::FunctionDeclarationContext* IronParser::BodyContext::functionDeclaration(size_t i) {
  return getRuleContext<IronParser::FunctionDeclarationContext>(i);
}

std::vector<tree::TerminalNode *> IronParser::BodyContext::NEWLINE() {
  return getTokens(IronParser::NEWLINE);
}

tree::TerminalNode* IronParser::BodyContext::NEWLINE(size_t i) {
  return getToken(IronParser::NEWLINE, i);
}


size_t IronParser::BodyContext::getRuleIndex() const {
  return IronParser::RuleBody;
}

void IronParser::BodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBody(this);
}

void IronParser::BodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBody(this);
}

IronParser::BodyContext* IronParser::body() {
  BodyContext *_localctx = _tracker.createInstance<BodyContext>(_ctx, getState());
  enterRule(_localctx, 8, IronParser::RuleBody);

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
    setState(75);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(73);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case IronParser::LET: {
            setState(70);
            statement();
            break;
          }

          case IronParser::FUNCTION:
          case IronParser::PUBLIC: {
            setState(71);
            functionDeclaration();
            break;
          }

          case IronParser::NEWLINE: {
            setState(72);
            match(IronParser::NEWLINE);
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(77);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
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

IronParser::FunctionDeclarationContext::FunctionDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::FunctionDeclarationContext::FUNCTION() {
  return getToken(IronParser::FUNCTION, 0);
}

tree::TerminalNode* IronParser::FunctionDeclarationContext::L_PAREN() {
  return getToken(IronParser::L_PAREN, 0);
}

tree::TerminalNode* IronParser::FunctionDeclarationContext::R_PAREN() {
  return getToken(IronParser::R_PAREN, 0);
}

tree::TerminalNode* IronParser::FunctionDeclarationContext::L_CURLY() {
  return getToken(IronParser::L_CURLY, 0);
}

tree::TerminalNode* IronParser::FunctionDeclarationContext::R_CURLY() {
  return getToken(IronParser::R_CURLY, 0);
}

tree::TerminalNode* IronParser::FunctionDeclarationContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

tree::TerminalNode* IronParser::FunctionDeclarationContext::PUBLIC() {
  return getToken(IronParser::PUBLIC, 0);
}

std::vector<tree::TerminalNode *> IronParser::FunctionDeclarationContext::NEWLINE() {
  return getTokens(IronParser::NEWLINE);
}

tree::TerminalNode* IronParser::FunctionDeclarationContext::NEWLINE(size_t i) {
  return getToken(IronParser::NEWLINE, i);
}


size_t IronParser::FunctionDeclarationContext::getRuleIndex() const {
  return IronParser::RuleFunctionDeclaration;
}

void IronParser::FunctionDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDeclaration(this);
}

void IronParser::FunctionDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDeclaration(this);
}

IronParser::FunctionDeclarationContext* IronParser::functionDeclaration() {
  FunctionDeclarationContext *_localctx = _tracker.createInstance<FunctionDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 10, IronParser::RuleFunctionDeclaration);
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
    if (_la == IronParser::PUBLIC) {
      setState(78);
      match(IronParser::PUBLIC);
    }
    setState(81);
    match(IronParser::FUNCTION);
    setState(82);
    antlrcpp::downCast<FunctionDeclarationContext *>(_localctx)->functionName = match(IronParser::IDENTIFIER);
    setState(83);
    match(IronParser::L_PAREN);
    setState(84);
    match(IronParser::R_PAREN);
    setState(85);
    match(IronParser::L_CURLY);
    setState(87);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::NEWLINE) {
      setState(86);
      match(IronParser::NEWLINE);
    }
    setState(89);
    match(IronParser::R_CURLY);
    setState(91);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      setState(90);
      match(IronParser::NEWLINE);
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

//----------------- StatementContext ------------------------------------------------------------------

IronParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IronParser::VarDeclarationContext* IronParser::StatementContext::varDeclaration() {
  return getRuleContext<IronParser::VarDeclarationContext>(0);
}


size_t IronParser::StatementContext::getRuleIndex() const {
  return IronParser::RuleStatement;
}

void IronParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void IronParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}

IronParser::StatementContext* IronParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 12, IronParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(93);
    varDeclaration();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclarationContext ------------------------------------------------------------------

IronParser::VarDeclarationContext::VarDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::VarDeclarationContext::LET() {
  return getToken(IronParser::LET, 0);
}

tree::TerminalNode* IronParser::VarDeclarationContext::COLON() {
  return getToken(IronParser::COLON, 0);
}

IronParser::VarTypesContext* IronParser::VarDeclarationContext::varTypes() {
  return getRuleContext<IronParser::VarTypesContext>(0);
}

tree::TerminalNode* IronParser::VarDeclarationContext::NEWLINE() {
  return getToken(IronParser::NEWLINE, 0);
}

tree::TerminalNode* IronParser::VarDeclarationContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

tree::TerminalNode* IronParser::VarDeclarationContext::EQ() {
  return getToken(IronParser::EQ, 0);
}

IronParser::DataFormatContext* IronParser::VarDeclarationContext::dataFormat() {
  return getRuleContext<IronParser::DataFormatContext>(0);
}


size_t IronParser::VarDeclarationContext::getRuleIndex() const {
  return IronParser::RuleVarDeclaration;
}

void IronParser::VarDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDeclaration(this);
}

void IronParser::VarDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDeclaration(this);
}

IronParser::VarDeclarationContext* IronParser::varDeclaration() {
  VarDeclarationContext *_localctx = _tracker.createInstance<VarDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 14, IronParser::RuleVarDeclaration);
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
    setState(95);
    match(IronParser::LET);
    setState(96);
    antlrcpp::downCast<VarDeclarationContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(97);
    match(IronParser::COLON);
    setState(98);
    varTypes();
    setState(101);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::EQ) {
      setState(99);
      match(IronParser::EQ);
      setState(100);
      dataFormat();
    }
    setState(103);
    match(IronParser::NEWLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DataFormatContext ------------------------------------------------------------------

IronParser::DataFormatContext::DataFormatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::DataFormatContext::REAL_NUMBER() {
  return getToken(IronParser::REAL_NUMBER, 0);
}

tree::TerminalNode* IronParser::DataFormatContext::INT_NUMBER() {
  return getToken(IronParser::INT_NUMBER, 0);
}

tree::TerminalNode* IronParser::DataFormatContext::BOOLEAN_VALUE() {
  return getToken(IronParser::BOOLEAN_VALUE, 0);
}

tree::TerminalNode* IronParser::DataFormatContext::STRING_LITERAL() {
  return getToken(IronParser::STRING_LITERAL, 0);
}


size_t IronParser::DataFormatContext::getRuleIndex() const {
  return IronParser::RuleDataFormat;
}

void IronParser::DataFormatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDataFormat(this);
}

void IronParser::DataFormatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDataFormat(this);
}

IronParser::DataFormatContext* IronParser::dataFormat() {
  DataFormatContext *_localctx = _tracker.createInstance<DataFormatContext>(_ctx, getState());
  enterRule(_localctx, 16, IronParser::RuleDataFormat);
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
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 125829120) != 0))) {
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

IronParser::VarTypesContext::VarTypesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::VarTypesContext::TYPE_BOOLEAN() {
  return getToken(IronParser::TYPE_BOOLEAN, 0);
}

tree::TerminalNode* IronParser::VarTypesContext::TYPE_CHAR() {
  return getToken(IronParser::TYPE_CHAR, 0);
}

tree::TerminalNode* IronParser::VarTypesContext::TYPE_DOUBLE() {
  return getToken(IronParser::TYPE_DOUBLE, 0);
}

tree::TerminalNode* IronParser::VarTypesContext::TYPE_FLOAT() {
  return getToken(IronParser::TYPE_FLOAT, 0);
}

tree::TerminalNode* IronParser::VarTypesContext::TYPE_INT() {
  return getToken(IronParser::TYPE_INT, 0);
}

tree::TerminalNode* IronParser::VarTypesContext::TYPE_STRING() {
  return getToken(IronParser::TYPE_STRING, 0);
}


size_t IronParser::VarTypesContext::getRuleIndex() const {
  return IronParser::RuleVarTypes;
}

void IronParser::VarTypesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarTypes(this);
}

void IronParser::VarTypesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarTypes(this);
}

IronParser::VarTypesContext* IronParser::varTypes() {
  VarTypesContext *_localctx = _tracker.createInstance<VarTypesContext>(_ctx, getState());
  enterRule(_localctx, 18, IronParser::RuleVarTypes);
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
    setState(107);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8257536) != 0))) {
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

void IronParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  ironParserInitialize();
#else
  ::antlr4::internal::call_once(ironParserOnceFlag, ironParserInitialize);
#endif
}
