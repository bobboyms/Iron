
// Generated from Iron.g4 by ANTLR 4.13.2


#include "IronLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct IronLexerStaticData final {
  IronLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  IronLexerStaticData(const IronLexerStaticData&) = delete;
  IronLexerStaticData(IronLexerStaticData&&) = delete;
  IronLexerStaticData& operator=(const IronLexerStaticData&) = delete;
  IronLexerStaticData& operator=(IronLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag ironlexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<IronLexerStaticData> ironlexerLexerStaticData = nullptr;

void ironlexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (ironlexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(ironlexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<IronLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "LINE_COMMENT", "BLOCK_COMMENT", "COMMA", 
      "COLON", "EQ", "SEMICOLON", "DOT", "STAR", "L_CURLY", "R_CURLY", "L_PAREN", 
      "R_PAREN", "PLUS", "MINUS", "DIV", "L_BRACKET", "R_BRACKET", "ARROW", 
      "FUNCTION", "LET", "PUBLIC", "IMPORT", "RETURN", "TYPE_INT", "TYPE_CHAR", 
      "TYPE_FLOAT", "TYPE_STRING", "TYPE_BOOLEAN", "TYPE_DOUBLE", "TYPE_VOID", 
      "REAL_NUMBER", "INT_NUMBER", "BOOLEAN_VALUE", "STRING_LITERAL", "IDENTIFIER", 
      "NEWLINE", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'f'('", "'extern'", "'...'", "", "", "','", "':'", "'='", "';'", 
      "'.'", "'*'", "'{'", "'}'", "'('", "')'", "'+'", "'-'", "'/'", "'['", 
      "']'", "'->'", "'fn'", "'let'", "'public'", "'import'", "'return'", 
      "'int'", "'char'", "'float'", "'string'", "'boolean'", "'double'", 
      "'void'"
    },
    std::vector<std::string>{
      "", "", "", "", "LINE_COMMENT", "BLOCK_COMMENT", "COMMA", "COLON", 
      "EQ", "SEMICOLON", "DOT", "STAR", "L_CURLY", "R_CURLY", "L_PAREN", 
      "R_PAREN", "PLUS", "MINUS", "DIV", "L_BRACKET", "R_BRACKET", "ARROW", 
      "FUNCTION", "LET", "PUBLIC", "IMPORT", "RETURN", "TYPE_INT", "TYPE_CHAR", 
      "TYPE_FLOAT", "TYPE_STRING", "TYPE_BOOLEAN", "TYPE_DOUBLE", "TYPE_VOID", 
      "REAL_NUMBER", "INT_NUMBER", "BOOLEAN_VALUE", "STRING_LITERAL", "IDENTIFIER", 
      "NEWLINE", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,40,301,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,1,0,1,0,1,0,1,0,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,5,3,101,8,3,10,3,
  	12,3,104,9,3,1,3,1,3,1,4,1,4,1,4,1,4,5,4,112,8,4,10,4,12,4,115,9,4,1,
  	4,1,4,1,4,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,
  	11,1,11,1,12,1,12,1,13,1,13,1,14,1,14,1,15,1,15,1,16,1,16,1,17,1,17,1,
  	18,1,18,1,19,1,19,1,20,1,20,1,20,1,21,1,21,1,21,1,22,1,22,1,22,1,22,1,
  	23,1,23,1,23,1,23,1,23,1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,
  	25,1,25,1,25,1,25,1,25,1,25,1,25,1,26,1,26,1,26,1,26,1,27,1,27,1,27,1,
  	27,1,27,1,28,1,28,1,28,1,28,1,28,1,28,1,29,1,29,1,29,1,29,1,29,1,29,1,
  	29,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,31,1,31,1,31,1,31,1,31,1,
  	31,1,31,1,32,1,32,1,32,1,32,1,32,1,33,3,33,226,8,33,1,33,4,33,229,8,33,
  	11,33,12,33,230,1,33,1,33,4,33,235,8,33,11,33,12,33,236,1,33,1,33,3,33,
  	241,8,33,1,33,4,33,244,8,33,11,33,12,33,245,3,33,248,8,33,1,33,3,33,251,
  	8,33,1,34,3,34,254,8,34,1,34,4,34,257,8,34,11,34,12,34,258,1,35,1,35,
  	1,35,1,35,1,35,1,35,1,35,1,35,1,35,3,35,270,8,35,1,36,1,36,5,36,274,8,
  	36,10,36,12,36,277,9,36,1,36,1,36,1,37,1,37,5,37,283,8,37,10,37,12,37,
  	286,9,37,1,38,3,38,289,8,38,1,38,1,38,1,38,1,38,1,39,4,39,296,8,39,11,
  	39,12,39,297,1,39,1,39,1,113,0,40,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,
  	17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,20,
  	41,21,43,22,45,23,47,24,49,25,51,26,53,27,55,28,57,29,59,30,61,31,63,
  	32,65,33,67,34,69,35,71,36,73,37,75,38,77,39,79,40,1,0,9,2,0,10,10,13,
  	13,1,0,48,57,2,0,69,69,101,101,2,0,43,43,45,45,2,0,68,68,70,70,3,0,10,
  	10,13,13,34,34,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,2,
  	0,9,9,32,32,316,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,
  	0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,
  	0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,
  	31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,
  	0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,
  	0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,0,0,0,0,
  	63,1,0,0,0,0,65,1,0,0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,0,0,73,1,
  	0,0,0,0,75,1,0,0,0,0,77,1,0,0,0,0,79,1,0,0,0,1,81,1,0,0,0,3,85,1,0,0,
  	0,5,92,1,0,0,0,7,96,1,0,0,0,9,107,1,0,0,0,11,121,1,0,0,0,13,123,1,0,0,
  	0,15,125,1,0,0,0,17,127,1,0,0,0,19,129,1,0,0,0,21,131,1,0,0,0,23,133,
  	1,0,0,0,25,135,1,0,0,0,27,137,1,0,0,0,29,139,1,0,0,0,31,141,1,0,0,0,33,
  	143,1,0,0,0,35,145,1,0,0,0,37,147,1,0,0,0,39,149,1,0,0,0,41,151,1,0,0,
  	0,43,154,1,0,0,0,45,157,1,0,0,0,47,161,1,0,0,0,49,168,1,0,0,0,51,175,
  	1,0,0,0,53,182,1,0,0,0,55,186,1,0,0,0,57,191,1,0,0,0,59,197,1,0,0,0,61,
  	204,1,0,0,0,63,212,1,0,0,0,65,219,1,0,0,0,67,225,1,0,0,0,69,253,1,0,0,
  	0,71,269,1,0,0,0,73,271,1,0,0,0,75,280,1,0,0,0,77,288,1,0,0,0,79,295,
  	1,0,0,0,81,82,5,102,0,0,82,83,5,39,0,0,83,84,5,40,0,0,84,2,1,0,0,0,85,
  	86,5,101,0,0,86,87,5,120,0,0,87,88,5,116,0,0,88,89,5,101,0,0,89,90,5,
  	114,0,0,90,91,5,110,0,0,91,4,1,0,0,0,92,93,5,46,0,0,93,94,5,46,0,0,94,
  	95,5,46,0,0,95,6,1,0,0,0,96,97,5,47,0,0,97,98,5,47,0,0,98,102,1,0,0,0,
  	99,101,8,0,0,0,100,99,1,0,0,0,101,104,1,0,0,0,102,100,1,0,0,0,102,103,
  	1,0,0,0,103,105,1,0,0,0,104,102,1,0,0,0,105,106,6,3,0,0,106,8,1,0,0,0,
  	107,108,5,47,0,0,108,109,5,42,0,0,109,113,1,0,0,0,110,112,9,0,0,0,111,
  	110,1,0,0,0,112,115,1,0,0,0,113,114,1,0,0,0,113,111,1,0,0,0,114,116,1,
  	0,0,0,115,113,1,0,0,0,116,117,5,42,0,0,117,118,5,47,0,0,118,119,1,0,0,
  	0,119,120,6,4,0,0,120,10,1,0,0,0,121,122,5,44,0,0,122,12,1,0,0,0,123,
  	124,5,58,0,0,124,14,1,0,0,0,125,126,5,61,0,0,126,16,1,0,0,0,127,128,5,
  	59,0,0,128,18,1,0,0,0,129,130,5,46,0,0,130,20,1,0,0,0,131,132,5,42,0,
  	0,132,22,1,0,0,0,133,134,5,123,0,0,134,24,1,0,0,0,135,136,5,125,0,0,136,
  	26,1,0,0,0,137,138,5,40,0,0,138,28,1,0,0,0,139,140,5,41,0,0,140,30,1,
  	0,0,0,141,142,5,43,0,0,142,32,1,0,0,0,143,144,5,45,0,0,144,34,1,0,0,0,
  	145,146,5,47,0,0,146,36,1,0,0,0,147,148,5,91,0,0,148,38,1,0,0,0,149,150,
  	5,93,0,0,150,40,1,0,0,0,151,152,5,45,0,0,152,153,5,62,0,0,153,42,1,0,
  	0,0,154,155,5,102,0,0,155,156,5,110,0,0,156,44,1,0,0,0,157,158,5,108,
  	0,0,158,159,5,101,0,0,159,160,5,116,0,0,160,46,1,0,0,0,161,162,5,112,
  	0,0,162,163,5,117,0,0,163,164,5,98,0,0,164,165,5,108,0,0,165,166,5,105,
  	0,0,166,167,5,99,0,0,167,48,1,0,0,0,168,169,5,105,0,0,169,170,5,109,0,
  	0,170,171,5,112,0,0,171,172,5,111,0,0,172,173,5,114,0,0,173,174,5,116,
  	0,0,174,50,1,0,0,0,175,176,5,114,0,0,176,177,5,101,0,0,177,178,5,116,
  	0,0,178,179,5,117,0,0,179,180,5,114,0,0,180,181,5,110,0,0,181,52,1,0,
  	0,0,182,183,5,105,0,0,183,184,5,110,0,0,184,185,5,116,0,0,185,54,1,0,
  	0,0,186,187,5,99,0,0,187,188,5,104,0,0,188,189,5,97,0,0,189,190,5,114,
  	0,0,190,56,1,0,0,0,191,192,5,102,0,0,192,193,5,108,0,0,193,194,5,111,
  	0,0,194,195,5,97,0,0,195,196,5,116,0,0,196,58,1,0,0,0,197,198,5,115,0,
  	0,198,199,5,116,0,0,199,200,5,114,0,0,200,201,5,105,0,0,201,202,5,110,
  	0,0,202,203,5,103,0,0,203,60,1,0,0,0,204,205,5,98,0,0,205,206,5,111,0,
  	0,206,207,5,111,0,0,207,208,5,108,0,0,208,209,5,101,0,0,209,210,5,97,
  	0,0,210,211,5,110,0,0,211,62,1,0,0,0,212,213,5,100,0,0,213,214,5,111,
  	0,0,214,215,5,117,0,0,215,216,5,98,0,0,216,217,5,108,0,0,217,218,5,101,
  	0,0,218,64,1,0,0,0,219,220,5,118,0,0,220,221,5,111,0,0,221,222,5,105,
  	0,0,222,223,5,100,0,0,223,66,1,0,0,0,224,226,5,45,0,0,225,224,1,0,0,0,
  	225,226,1,0,0,0,226,228,1,0,0,0,227,229,7,1,0,0,228,227,1,0,0,0,229,230,
  	1,0,0,0,230,228,1,0,0,0,230,231,1,0,0,0,231,232,1,0,0,0,232,234,5,46,
  	0,0,233,235,7,1,0,0,234,233,1,0,0,0,235,236,1,0,0,0,236,234,1,0,0,0,236,
  	237,1,0,0,0,237,247,1,0,0,0,238,240,7,2,0,0,239,241,7,3,0,0,240,239,1,
  	0,0,0,240,241,1,0,0,0,241,243,1,0,0,0,242,244,7,1,0,0,243,242,1,0,0,0,
  	244,245,1,0,0,0,245,243,1,0,0,0,245,246,1,0,0,0,246,248,1,0,0,0,247,238,
  	1,0,0,0,247,248,1,0,0,0,248,250,1,0,0,0,249,251,7,4,0,0,250,249,1,0,0,
  	0,250,251,1,0,0,0,251,68,1,0,0,0,252,254,5,45,0,0,253,252,1,0,0,0,253,
  	254,1,0,0,0,254,256,1,0,0,0,255,257,7,1,0,0,256,255,1,0,0,0,257,258,1,
  	0,0,0,258,256,1,0,0,0,258,259,1,0,0,0,259,70,1,0,0,0,260,261,5,116,0,
  	0,261,262,5,114,0,0,262,263,5,117,0,0,263,270,5,101,0,0,264,265,5,102,
  	0,0,265,266,5,97,0,0,266,267,5,108,0,0,267,268,5,115,0,0,268,270,5,101,
  	0,0,269,260,1,0,0,0,269,264,1,0,0,0,270,72,1,0,0,0,271,275,5,34,0,0,272,
  	274,8,5,0,0,273,272,1,0,0,0,274,277,1,0,0,0,275,273,1,0,0,0,275,276,1,
  	0,0,0,276,278,1,0,0,0,277,275,1,0,0,0,278,279,5,34,0,0,279,74,1,0,0,0,
  	280,284,7,6,0,0,281,283,7,7,0,0,282,281,1,0,0,0,283,286,1,0,0,0,284,282,
  	1,0,0,0,284,285,1,0,0,0,285,76,1,0,0,0,286,284,1,0,0,0,287,289,5,13,0,
  	0,288,287,1,0,0,0,288,289,1,0,0,0,289,290,1,0,0,0,290,291,5,10,0,0,291,
  	292,1,0,0,0,292,293,6,38,0,0,293,78,1,0,0,0,294,296,7,8,0,0,295,294,1,
  	0,0,0,296,297,1,0,0,0,297,295,1,0,0,0,297,298,1,0,0,0,298,299,1,0,0,0,
  	299,300,6,39,0,0,300,80,1,0,0,0,17,0,102,113,225,230,236,240,245,247,
  	250,253,258,269,275,284,288,297,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  ironlexerLexerStaticData = std::move(staticData);
}

}

IronLexer::IronLexer(CharStream *input) : Lexer(input) {
  IronLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *ironlexerLexerStaticData->atn, ironlexerLexerStaticData->decisionToDFA, ironlexerLexerStaticData->sharedContextCache);
}

IronLexer::~IronLexer() {
  delete _interpreter;
}

std::string IronLexer::getGrammarFileName() const {
  return "Iron.g4";
}

const std::vector<std::string>& IronLexer::getRuleNames() const {
  return ironlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& IronLexer::getChannelNames() const {
  return ironlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& IronLexer::getModeNames() const {
  return ironlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& IronLexer::getVocabulary() const {
  return ironlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView IronLexer::getSerializedATN() const {
  return ironlexerLexerStaticData->serializedATN;
}

const atn::ATN& IronLexer::getATN() const {
  return *ironlexerLexerStaticData->atn;
}




void IronLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  ironlexerLexerInitialize();
#else
  ::antlr4::internal::call_once(ironlexerLexerOnceFlag, ironlexerLexerInitialize);
#endif
}
