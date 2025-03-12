
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
      "program", "importStatement", "qualifiedName", "statementList", "breakStatement", 
      "continueStatement", "structStatement", "structBody", "optionsStatement", 
      "optionsBody", "returnStatement", "whileStatement", "repeatStatement", 
      "forStatement", "intervals", "formatStatement", "formatArguments", 
      "formatArgument", "externBlock", "externFunctionDeclaration", "externFunctionArgs", 
      "externFunctionArg", "cTypes", "functionDeclaration", "arrowFunctionInline", 
      "functionSignature", "functionReturnType", "functionArgs", "functionArg", 
      "fnsignature", "functionCall", "functionCallArgs", "functionCallArg", 
      "varDeclaration", "assignment", "structInit", "structInitBody", "variableQualifiedName", 
      "varAssignment", "ifBlock", "ifStatement", "elseStatement", "boolExpr", 
      "expr", "number", "dataFormat", "varTypes"
    },
    std::vector<std::string>{
      "", "'..'", "'f'('", "'extern'", "'...'", "'%'", "", "", "','", "':'", 
      "'='", "';'", "'.'", "'*'", "'{'", "'}'", "'('", "')'", "'+'", "'-'", 
      "'/'", "'['", "']'", "'->'", "'and'", "'or'", "'not'", "'=='", "'!='", 
      "'<'", "'<='", "'>'", "'>='", "'if'", "'fn'", "'let'", "'mut'", "'else'", 
      "'public'", "'import'", "'return'", "'in'", "'for'", "'while'", "'int'", 
      "'char'", "'float'", "'string'", "'boolean'", "'double'", "'void'", 
      "'repeat'", "'struct'", "'options'", "'continue'", "'break'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "LINE_COMMENT", "BLOCK_COMMENT", "COMMA", 
      "COLON", "EQ", "SEMICOLON", "DOT", "STAR", "L_CURLY", "R_CURLY", "L_PAREN", 
      "R_PAREN", "PLUS", "MINUS", "DIV", "L_BRACKET", "R_BRACKET", "ARROW", 
      "AND", "OR", "NOT", "EQEQ", "NEQ", "LT", "LTE", "GT", "GTE", "IF", 
      "FUNCTION", "LET", "MUT", "ELSE", "PUBLIC", "IMPORT", "RETURN", "IN", 
      "FOR", "WHILE", "TYPE_INT", "TYPE_CHAR", "TYPE_FLOAT", "TYPE_STRING", 
      "TYPE_BOOLEAN", "TYPE_DOUBLE", "TYPE_VOID", "REPEAT", "STRUCT", "OPTIONS", 
      "CONTINUE", "BREAK", "REAL_NUMBER", "INT_NUMBER", "BOOLEAN_VALUE", 
      "STRING_LITERAL", "IDENTIFIER", "NEWLINE", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,62,511,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,1,0,5,0,96,8,0,10,0,12,0,99,
  	9,0,1,0,3,0,102,8,0,1,0,1,0,1,0,5,0,107,8,0,10,0,12,0,110,9,0,1,0,1,0,
  	1,1,1,1,1,1,1,1,3,1,118,8,1,1,2,1,2,1,2,5,2,123,8,2,10,2,12,2,126,9,2,
  	1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,5,3,139,8,3,10,3,12,3,142,
  	9,3,1,4,1,4,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,6,5,6,154,8,6,10,6,12,6,157,
  	9,6,1,6,1,6,1,7,3,7,162,8,7,1,7,1,7,1,7,1,7,3,7,168,8,7,1,8,1,8,1,8,1,
  	8,1,8,1,8,5,8,176,8,8,10,8,12,8,179,9,8,1,8,1,8,1,9,1,9,3,9,185,8,9,1,
  	10,1,10,1,10,1,10,1,10,3,10,192,8,10,1,11,1,11,1,11,1,11,1,11,1,11,1,
  	12,1,12,1,12,1,12,1,12,1,12,1,12,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,
  	13,1,14,1,14,3,14,217,8,14,1,14,1,14,1,14,3,14,222,8,14,1,15,1,15,1,15,
  	1,15,1,15,1,15,1,16,1,16,1,16,5,16,233,8,16,10,16,12,16,236,9,16,1,17,
  	1,17,1,17,1,17,1,17,3,17,243,8,17,1,18,1,18,1,18,1,18,4,18,249,8,18,11,
  	18,12,18,250,5,18,253,8,18,10,18,12,18,256,9,18,1,18,1,18,1,19,1,19,1,
  	19,1,19,3,19,264,8,19,1,19,1,19,3,19,268,8,19,1,19,1,19,3,19,272,8,19,
  	1,20,1,20,1,20,5,20,277,8,20,10,20,12,20,280,9,20,1,21,1,21,1,21,3,21,
  	285,8,21,1,21,1,21,1,22,1,22,1,23,3,23,292,8,23,1,23,1,23,1,23,1,23,1,
  	23,1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,24,1,24,3,24,308,8,24,1,25,1,
  	25,3,25,312,8,25,1,25,1,25,3,25,316,8,25,1,26,1,26,1,26,1,27,1,27,1,27,
  	5,27,324,8,27,10,27,12,27,327,9,27,1,28,1,28,1,28,1,28,3,28,333,8,28,
  	1,28,3,28,336,8,28,1,29,1,29,1,29,1,30,1,30,1,30,3,30,344,8,30,1,30,1,
  	30,1,31,1,31,1,31,5,31,351,8,31,10,31,12,31,354,9,31,1,32,1,32,1,32,1,
  	32,1,32,1,32,3,32,362,8,32,1,33,3,33,365,8,33,1,33,1,33,1,33,1,33,1,33,
  	3,33,372,8,33,1,33,3,33,375,8,33,1,34,1,34,1,34,1,34,1,34,1,34,1,34,1,
  	34,3,34,385,8,34,1,35,3,35,388,8,35,1,35,1,35,1,35,1,35,5,35,394,8,35,
  	10,35,12,35,397,9,35,3,35,399,8,35,1,35,1,35,1,36,1,36,1,36,1,36,1,36,
  	1,36,1,36,3,36,410,8,36,1,37,1,37,1,37,5,37,415,8,37,10,37,12,37,418,
  	9,37,1,38,1,38,1,38,1,38,1,38,1,38,1,38,1,38,3,38,428,8,38,1,39,1,39,
  	3,39,432,8,39,1,39,1,39,1,40,1,40,1,40,1,40,1,40,1,40,1,40,3,40,443,8,
  	40,1,41,1,41,3,41,447,8,41,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,
  	42,1,42,1,42,1,42,3,42,461,8,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,
  	42,1,42,5,42,472,8,42,10,42,12,42,475,9,42,1,43,1,43,1,43,1,43,1,43,1,
  	43,1,43,1,43,3,43,485,8,43,1,43,1,43,1,43,1,43,3,43,491,8,43,1,43,1,43,
  	1,43,1,43,3,43,497,8,43,1,43,5,43,500,8,43,10,43,12,43,503,9,43,1,44,
  	1,44,1,45,1,45,1,46,1,46,1,46,0,2,84,86,47,0,2,4,6,8,10,12,14,16,18,20,
  	22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,
  	68,70,72,74,76,78,80,82,84,86,88,90,92,0,5,2,0,44,46,48,50,1,0,27,32,
  	1,0,56,57,1,0,56,59,2,0,34,34,44,49,558,0,97,1,0,0,0,2,113,1,0,0,0,4,
  	119,1,0,0,0,6,140,1,0,0,0,8,143,1,0,0,0,10,145,1,0,0,0,12,147,1,0,0,0,
  	14,161,1,0,0,0,16,169,1,0,0,0,18,182,1,0,0,0,20,186,1,0,0,0,22,193,1,
  	0,0,0,24,199,1,0,0,0,26,206,1,0,0,0,28,216,1,0,0,0,30,223,1,0,0,0,32,
  	229,1,0,0,0,34,242,1,0,0,0,36,244,1,0,0,0,38,259,1,0,0,0,40,273,1,0,0,
  	0,42,281,1,0,0,0,44,288,1,0,0,0,46,291,1,0,0,0,48,300,1,0,0,0,50,309,
  	1,0,0,0,52,317,1,0,0,0,54,320,1,0,0,0,56,328,1,0,0,0,58,337,1,0,0,0,60,
  	340,1,0,0,0,62,347,1,0,0,0,64,355,1,0,0,0,66,364,1,0,0,0,68,376,1,0,0,
  	0,70,387,1,0,0,0,72,402,1,0,0,0,74,411,1,0,0,0,76,419,1,0,0,0,78,429,
  	1,0,0,0,80,435,1,0,0,0,82,446,1,0,0,0,84,460,1,0,0,0,86,484,1,0,0,0,88,
  	504,1,0,0,0,90,506,1,0,0,0,92,508,1,0,0,0,94,96,3,2,1,0,95,94,1,0,0,0,
  	96,99,1,0,0,0,97,95,1,0,0,0,97,98,1,0,0,0,98,101,1,0,0,0,99,97,1,0,0,
  	0,100,102,3,36,18,0,101,100,1,0,0,0,101,102,1,0,0,0,102,108,1,0,0,0,103,
  	107,3,46,23,0,104,107,3,12,6,0,105,107,3,16,8,0,106,103,1,0,0,0,106,104,
  	1,0,0,0,106,105,1,0,0,0,107,110,1,0,0,0,108,106,1,0,0,0,108,109,1,0,0,
  	0,109,111,1,0,0,0,110,108,1,0,0,0,111,112,5,0,0,1,112,1,1,0,0,0,113,114,
  	5,39,0,0,114,117,3,4,2,0,115,116,5,12,0,0,116,118,5,13,0,0,117,115,1,
  	0,0,0,117,118,1,0,0,0,118,3,1,0,0,0,119,124,5,60,0,0,120,121,5,12,0,0,
  	121,123,5,60,0,0,122,120,1,0,0,0,123,126,1,0,0,0,124,122,1,0,0,0,124,
  	125,1,0,0,0,125,5,1,0,0,0,126,124,1,0,0,0,127,139,3,10,5,0,128,139,3,
  	8,4,0,129,139,3,66,33,0,130,139,3,76,38,0,131,139,3,60,30,0,132,139,3,
  	86,43,0,133,139,3,80,40,0,134,139,3,22,11,0,135,139,3,24,12,0,136,139,
  	3,26,13,0,137,139,3,20,10,0,138,127,1,0,0,0,138,128,1,0,0,0,138,129,1,
  	0,0,0,138,130,1,0,0,0,138,131,1,0,0,0,138,132,1,0,0,0,138,133,1,0,0,0,
  	138,134,1,0,0,0,138,135,1,0,0,0,138,136,1,0,0,0,138,137,1,0,0,0,139,142,
  	1,0,0,0,140,138,1,0,0,0,140,141,1,0,0,0,141,7,1,0,0,0,142,140,1,0,0,0,
  	143,144,5,55,0,0,144,9,1,0,0,0,145,146,5,54,0,0,146,11,1,0,0,0,147,148,
  	5,52,0,0,148,149,5,60,0,0,149,150,5,14,0,0,150,155,3,14,7,0,151,152,5,
  	8,0,0,152,154,3,14,7,0,153,151,1,0,0,0,154,157,1,0,0,0,155,153,1,0,0,
  	0,155,156,1,0,0,0,156,158,1,0,0,0,157,155,1,0,0,0,158,159,5,15,0,0,159,
  	13,1,0,0,0,160,162,5,36,0,0,161,160,1,0,0,0,161,162,1,0,0,0,162,163,1,
  	0,0,0,163,164,5,60,0,0,164,167,5,9,0,0,165,168,3,92,46,0,166,168,5,60,
  	0,0,167,165,1,0,0,0,167,166,1,0,0,0,168,15,1,0,0,0,169,170,5,53,0,0,170,
  	171,5,60,0,0,171,172,5,14,0,0,172,177,3,18,9,0,173,174,5,8,0,0,174,176,
  	3,18,9,0,175,173,1,0,0,0,176,179,1,0,0,0,177,175,1,0,0,0,177,178,1,0,
  	0,0,178,180,1,0,0,0,179,177,1,0,0,0,180,181,5,15,0,0,181,17,1,0,0,0,182,
  	184,5,60,0,0,183,185,3,50,25,0,184,183,1,0,0,0,184,185,1,0,0,0,185,19,
  	1,0,0,0,186,191,5,40,0,0,187,192,3,90,45,0,188,192,5,60,0,0,189,192,3,
  	60,30,0,190,192,3,86,43,0,191,187,1,0,0,0,191,188,1,0,0,0,191,189,1,0,
  	0,0,191,190,1,0,0,0,191,192,1,0,0,0,192,21,1,0,0,0,193,194,5,43,0,0,194,
  	195,3,84,42,0,195,196,5,14,0,0,196,197,3,6,3,0,197,198,5,15,0,0,198,23,
  	1,0,0,0,199,200,5,51,0,0,200,201,5,14,0,0,201,202,3,6,3,0,202,203,5,15,
  	0,0,203,204,5,43,0,0,204,205,3,84,42,0,205,25,1,0,0,0,206,207,5,42,0,
  	0,207,208,5,60,0,0,208,209,5,41,0,0,209,210,3,28,14,0,210,211,5,14,0,
  	0,211,212,3,6,3,0,212,213,5,15,0,0,213,27,1,0,0,0,214,217,5,57,0,0,215,
  	217,5,60,0,0,216,214,1,0,0,0,216,215,1,0,0,0,217,218,1,0,0,0,218,221,
  	5,1,0,0,219,222,5,57,0,0,220,222,5,60,0,0,221,219,1,0,0,0,221,220,1,0,
  	0,0,222,29,1,0,0,0,223,224,5,2,0,0,224,225,5,59,0,0,225,226,5,8,0,0,226,
  	227,3,32,16,0,227,228,5,17,0,0,228,31,1,0,0,0,229,234,3,34,17,0,230,231,
  	5,8,0,0,231,233,3,34,17,0,232,230,1,0,0,0,233,236,1,0,0,0,234,232,1,0,
  	0,0,234,235,1,0,0,0,235,33,1,0,0,0,236,234,1,0,0,0,237,243,3,90,45,0,
  	238,243,5,60,0,0,239,243,3,60,30,0,240,243,3,86,43,0,241,243,5,59,0,0,
  	242,237,1,0,0,0,242,238,1,0,0,0,242,239,1,0,0,0,242,240,1,0,0,0,242,241,
  	1,0,0,0,243,35,1,0,0,0,244,245,5,3,0,0,245,246,5,60,0,0,246,254,5,14,
  	0,0,247,249,3,38,19,0,248,247,1,0,0,0,249,250,1,0,0,0,250,248,1,0,0,0,
  	250,251,1,0,0,0,251,253,1,0,0,0,252,248,1,0,0,0,253,256,1,0,0,0,254,252,
  	1,0,0,0,254,255,1,0,0,0,255,257,1,0,0,0,256,254,1,0,0,0,257,258,5,15,
  	0,0,258,37,1,0,0,0,259,260,5,34,0,0,260,261,5,60,0,0,261,263,5,16,0,0,
  	262,264,3,40,20,0,263,262,1,0,0,0,263,264,1,0,0,0,264,267,1,0,0,0,265,
  	266,5,8,0,0,266,268,5,4,0,0,267,265,1,0,0,0,267,268,1,0,0,0,268,269,1,
  	0,0,0,269,271,5,17,0,0,270,272,3,52,26,0,271,270,1,0,0,0,271,272,1,0,
  	0,0,272,39,1,0,0,0,273,278,3,42,21,0,274,275,5,8,0,0,275,277,3,42,21,
  	0,276,274,1,0,0,0,277,280,1,0,0,0,278,276,1,0,0,0,278,279,1,0,0,0,279,
  	41,1,0,0,0,280,278,1,0,0,0,281,282,5,60,0,0,282,284,5,9,0,0,283,285,5,
  	13,0,0,284,283,1,0,0,0,284,285,1,0,0,0,285,286,1,0,0,0,286,287,3,44,22,
  	0,287,43,1,0,0,0,288,289,7,0,0,0,289,45,1,0,0,0,290,292,5,38,0,0,291,
  	290,1,0,0,0,291,292,1,0,0,0,292,293,1,0,0,0,293,294,5,34,0,0,294,295,
  	5,60,0,0,295,296,3,50,25,0,296,297,5,14,0,0,297,298,3,6,3,0,298,299,5,
  	15,0,0,299,47,1,0,0,0,300,301,3,50,25,0,301,307,5,23,0,0,302,308,3,86,
  	43,0,303,304,5,14,0,0,304,305,3,6,3,0,305,306,5,15,0,0,306,308,1,0,0,
  	0,307,302,1,0,0,0,307,303,1,0,0,0,308,49,1,0,0,0,309,311,5,16,0,0,310,
  	312,3,54,27,0,311,310,1,0,0,0,311,312,1,0,0,0,312,313,1,0,0,0,313,315,
  	5,17,0,0,314,316,3,52,26,0,315,314,1,0,0,0,315,316,1,0,0,0,316,51,1,0,
  	0,0,317,318,5,9,0,0,318,319,3,92,46,0,319,53,1,0,0,0,320,325,3,56,28,
  	0,321,322,5,8,0,0,322,324,3,56,28,0,323,321,1,0,0,0,324,327,1,0,0,0,325,
  	323,1,0,0,0,325,326,1,0,0,0,326,55,1,0,0,0,327,325,1,0,0,0,328,329,5,
  	60,0,0,329,332,5,9,0,0,330,333,3,58,29,0,331,333,3,92,46,0,332,330,1,
  	0,0,0,332,331,1,0,0,0,333,335,1,0,0,0,334,336,3,68,34,0,335,334,1,0,0,
  	0,335,336,1,0,0,0,336,57,1,0,0,0,337,338,5,34,0,0,338,339,3,50,25,0,339,
  	59,1,0,0,0,340,341,5,60,0,0,341,343,5,16,0,0,342,344,3,62,31,0,343,342,
  	1,0,0,0,343,344,1,0,0,0,344,345,1,0,0,0,345,346,5,17,0,0,346,61,1,0,0,
  	0,347,352,3,64,32,0,348,349,5,8,0,0,349,351,3,64,32,0,350,348,1,0,0,0,
  	351,354,1,0,0,0,352,350,1,0,0,0,352,353,1,0,0,0,353,63,1,0,0,0,354,352,
  	1,0,0,0,355,356,5,60,0,0,356,361,5,9,0,0,357,362,3,90,45,0,358,362,5,
  	60,0,0,359,362,3,60,30,0,360,362,3,48,24,0,361,357,1,0,0,0,361,358,1,
  	0,0,0,361,359,1,0,0,0,361,360,1,0,0,0,362,65,1,0,0,0,363,365,5,36,0,0,
  	364,363,1,0,0,0,364,365,1,0,0,0,365,366,1,0,0,0,366,367,5,35,0,0,367,
  	368,5,60,0,0,368,371,5,9,0,0,369,372,3,92,46,0,370,372,5,60,0,0,371,369,
  	1,0,0,0,371,370,1,0,0,0,372,374,1,0,0,0,373,375,3,68,34,0,374,373,1,0,
  	0,0,374,375,1,0,0,0,375,67,1,0,0,0,376,384,5,10,0,0,377,385,3,48,24,0,
  	378,385,3,74,37,0,379,385,3,90,45,0,380,385,3,70,35,0,381,385,3,60,30,
  	0,382,385,3,86,43,0,383,385,3,84,42,0,384,377,1,0,0,0,384,378,1,0,0,0,
  	384,379,1,0,0,0,384,380,1,0,0,0,384,381,1,0,0,0,384,382,1,0,0,0,384,383,
  	1,0,0,0,385,69,1,0,0,0,386,388,5,60,0,0,387,386,1,0,0,0,387,388,1,0,0,
  	0,388,389,1,0,0,0,389,398,5,14,0,0,390,395,3,72,36,0,391,392,5,8,0,0,
  	392,394,3,72,36,0,393,391,1,0,0,0,394,397,1,0,0,0,395,393,1,0,0,0,395,
  	396,1,0,0,0,396,399,1,0,0,0,397,395,1,0,0,0,398,390,1,0,0,0,398,399,1,
  	0,0,0,399,400,1,0,0,0,400,401,5,15,0,0,401,71,1,0,0,0,402,403,5,60,0,
  	0,403,409,5,9,0,0,404,410,3,90,45,0,405,410,5,60,0,0,406,410,3,70,35,
  	0,407,410,3,60,30,0,408,410,3,48,24,0,409,404,1,0,0,0,409,405,1,0,0,0,
  	409,406,1,0,0,0,409,407,1,0,0,0,409,408,1,0,0,0,410,73,1,0,0,0,411,416,
  	5,60,0,0,412,413,5,12,0,0,413,415,5,60,0,0,414,412,1,0,0,0,415,418,1,
  	0,0,0,416,414,1,0,0,0,416,417,1,0,0,0,417,75,1,0,0,0,418,416,1,0,0,0,
  	419,420,3,74,37,0,420,427,5,10,0,0,421,428,3,48,24,0,422,428,3,60,30,
  	0,423,428,3,70,35,0,424,428,5,60,0,0,425,428,3,90,45,0,426,428,3,86,43,
  	0,427,421,1,0,0,0,427,422,1,0,0,0,427,423,1,0,0,0,427,424,1,0,0,0,427,
  	425,1,0,0,0,427,426,1,0,0,0,428,77,1,0,0,0,429,431,5,14,0,0,430,432,3,
  	6,3,0,431,430,1,0,0,0,431,432,1,0,0,0,432,433,1,0,0,0,433,434,5,15,0,
  	0,434,79,1,0,0,0,435,436,5,33,0,0,436,437,5,16,0,0,437,438,3,84,42,0,
  	438,439,5,17,0,0,439,442,3,78,39,0,440,441,5,37,0,0,441,443,3,82,41,0,
  	442,440,1,0,0,0,442,443,1,0,0,0,443,81,1,0,0,0,444,447,3,80,40,0,445,
  	447,3,78,39,0,446,444,1,0,0,0,446,445,1,0,0,0,447,83,1,0,0,0,448,449,
  	6,42,-1,0,449,450,5,16,0,0,450,451,3,84,42,0,451,452,5,17,0,0,452,461,
  	1,0,0,0,453,454,5,26,0,0,454,461,3,84,42,6,455,461,5,58,0,0,456,461,3,
  	88,44,0,457,461,5,60,0,0,458,461,3,60,30,0,459,461,3,86,43,0,460,448,
  	1,0,0,0,460,453,1,0,0,0,460,455,1,0,0,0,460,456,1,0,0,0,460,457,1,0,0,
  	0,460,458,1,0,0,0,460,459,1,0,0,0,461,473,1,0,0,0,462,463,10,9,0,0,463,
  	464,7,1,0,0,464,472,3,84,42,10,465,466,10,8,0,0,466,467,5,24,0,0,467,
  	472,3,84,42,9,468,469,10,7,0,0,469,470,5,25,0,0,470,472,3,84,42,8,471,
  	462,1,0,0,0,471,465,1,0,0,0,471,468,1,0,0,0,472,475,1,0,0,0,473,471,1,
  	0,0,0,473,474,1,0,0,0,474,85,1,0,0,0,475,473,1,0,0,0,476,477,6,43,-1,
  	0,477,485,3,88,44,0,478,485,3,60,30,0,479,485,5,60,0,0,480,481,5,16,0,
  	0,481,482,3,86,43,0,482,483,5,17,0,0,483,485,1,0,0,0,484,476,1,0,0,0,
  	484,478,1,0,0,0,484,479,1,0,0,0,484,480,1,0,0,0,485,501,1,0,0,0,486,490,
  	10,6,0,0,487,491,5,13,0,0,488,491,5,5,0,0,489,491,5,20,0,0,490,487,1,
  	0,0,0,490,488,1,0,0,0,490,489,1,0,0,0,491,492,1,0,0,0,492,500,3,86,43,
  	7,493,496,10,5,0,0,494,497,5,18,0,0,495,497,5,19,0,0,496,494,1,0,0,0,
  	496,495,1,0,0,0,497,498,1,0,0,0,498,500,3,86,43,6,499,486,1,0,0,0,499,
  	493,1,0,0,0,500,503,1,0,0,0,501,499,1,0,0,0,501,502,1,0,0,0,502,87,1,
  	0,0,0,503,501,1,0,0,0,504,505,7,2,0,0,505,89,1,0,0,0,506,507,7,3,0,0,
  	507,91,1,0,0,0,508,509,7,4,0,0,509,93,1,0,0,0,56,97,101,106,108,117,124,
  	138,140,155,161,167,177,184,191,216,221,234,242,250,254,263,267,271,278,
  	284,291,307,311,315,325,332,335,343,352,361,364,371,374,384,387,395,398,
  	409,416,427,431,442,446,460,471,473,484,490,496,499,501
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

tree::TerminalNode* IronParser::ProgramContext::EOF() {
  return getToken(IronParser::EOF, 0);
}

std::vector<IronParser::ImportStatementContext *> IronParser::ProgramContext::importStatement() {
  return getRuleContexts<IronParser::ImportStatementContext>();
}

IronParser::ImportStatementContext* IronParser::ProgramContext::importStatement(size_t i) {
  return getRuleContext<IronParser::ImportStatementContext>(i);
}

IronParser::ExternBlockContext* IronParser::ProgramContext::externBlock() {
  return getRuleContext<IronParser::ExternBlockContext>(0);
}

std::vector<IronParser::FunctionDeclarationContext *> IronParser::ProgramContext::functionDeclaration() {
  return getRuleContexts<IronParser::FunctionDeclarationContext>();
}

IronParser::FunctionDeclarationContext* IronParser::ProgramContext::functionDeclaration(size_t i) {
  return getRuleContext<IronParser::FunctionDeclarationContext>(i);
}

std::vector<IronParser::StructStatementContext *> IronParser::ProgramContext::structStatement() {
  return getRuleContexts<IronParser::StructStatementContext>();
}

IronParser::StructStatementContext* IronParser::ProgramContext::structStatement(size_t i) {
  return getRuleContext<IronParser::StructStatementContext>(i);
}

std::vector<IronParser::OptionsStatementContext *> IronParser::ProgramContext::optionsStatement() {
  return getRuleContexts<IronParser::OptionsStatementContext>();
}

IronParser::OptionsStatementContext* IronParser::ProgramContext::optionsStatement(size_t i) {
  return getRuleContext<IronParser::OptionsStatementContext>(i);
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
    setState(97);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::IMPORT) {
      setState(94);
      importStatement();
      setState(99);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(101);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::T__2) {
      setState(100);
      externBlock();
    }
    setState(108);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 13511090939887616) != 0)) {
      setState(106);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case IronParser::FUNCTION:
        case IronParser::PUBLIC: {
          setState(103);
          functionDeclaration();
          break;
        }

        case IronParser::STRUCT: {
          setState(104);
          structStatement();
          break;
        }

        case IronParser::OPTIONS: {
          setState(105);
          optionsStatement();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(110);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(111);
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
    setState(113);
    match(IronParser::IMPORT);
    setState(114);
    qualifiedName();
    setState(117);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::DOT) {
      setState(115);
      match(IronParser::DOT);
      setState(116);
      match(IronParser::STAR);
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
    setState(119);
    match(IronParser::IDENTIFIER);
    setState(124);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(120);
        match(IronParser::DOT);
        setState(121);
        match(IronParser::IDENTIFIER); 
      }
      setState(126);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
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

IronParser::StatementListContext::StatementListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IronParser::ContinueStatementContext *> IronParser::StatementListContext::continueStatement() {
  return getRuleContexts<IronParser::ContinueStatementContext>();
}

IronParser::ContinueStatementContext* IronParser::StatementListContext::continueStatement(size_t i) {
  return getRuleContext<IronParser::ContinueStatementContext>(i);
}

std::vector<IronParser::BreakStatementContext *> IronParser::StatementListContext::breakStatement() {
  return getRuleContexts<IronParser::BreakStatementContext>();
}

IronParser::BreakStatementContext* IronParser::StatementListContext::breakStatement(size_t i) {
  return getRuleContext<IronParser::BreakStatementContext>(i);
}

std::vector<IronParser::VarDeclarationContext *> IronParser::StatementListContext::varDeclaration() {
  return getRuleContexts<IronParser::VarDeclarationContext>();
}

IronParser::VarDeclarationContext* IronParser::StatementListContext::varDeclaration(size_t i) {
  return getRuleContext<IronParser::VarDeclarationContext>(i);
}

std::vector<IronParser::VarAssignmentContext *> IronParser::StatementListContext::varAssignment() {
  return getRuleContexts<IronParser::VarAssignmentContext>();
}

IronParser::VarAssignmentContext* IronParser::StatementListContext::varAssignment(size_t i) {
  return getRuleContext<IronParser::VarAssignmentContext>(i);
}

std::vector<IronParser::FunctionCallContext *> IronParser::StatementListContext::functionCall() {
  return getRuleContexts<IronParser::FunctionCallContext>();
}

IronParser::FunctionCallContext* IronParser::StatementListContext::functionCall(size_t i) {
  return getRuleContext<IronParser::FunctionCallContext>(i);
}

std::vector<IronParser::ExprContext *> IronParser::StatementListContext::expr() {
  return getRuleContexts<IronParser::ExprContext>();
}

IronParser::ExprContext* IronParser::StatementListContext::expr(size_t i) {
  return getRuleContext<IronParser::ExprContext>(i);
}

std::vector<IronParser::IfStatementContext *> IronParser::StatementListContext::ifStatement() {
  return getRuleContexts<IronParser::IfStatementContext>();
}

IronParser::IfStatementContext* IronParser::StatementListContext::ifStatement(size_t i) {
  return getRuleContext<IronParser::IfStatementContext>(i);
}

std::vector<IronParser::WhileStatementContext *> IronParser::StatementListContext::whileStatement() {
  return getRuleContexts<IronParser::WhileStatementContext>();
}

IronParser::WhileStatementContext* IronParser::StatementListContext::whileStatement(size_t i) {
  return getRuleContext<IronParser::WhileStatementContext>(i);
}

std::vector<IronParser::RepeatStatementContext *> IronParser::StatementListContext::repeatStatement() {
  return getRuleContexts<IronParser::RepeatStatementContext>();
}

IronParser::RepeatStatementContext* IronParser::StatementListContext::repeatStatement(size_t i) {
  return getRuleContext<IronParser::RepeatStatementContext>(i);
}

std::vector<IronParser::ForStatementContext *> IronParser::StatementListContext::forStatement() {
  return getRuleContexts<IronParser::ForStatementContext>();
}

IronParser::ForStatementContext* IronParser::StatementListContext::forStatement(size_t i) {
  return getRuleContext<IronParser::ForStatementContext>(i);
}

std::vector<IronParser::ReturnStatementContext *> IronParser::StatementListContext::returnStatement() {
  return getRuleContexts<IronParser::ReturnStatementContext>();
}

IronParser::ReturnStatementContext* IronParser::StatementListContext::returnStatement(size_t i) {
  return getRuleContext<IronParser::ReturnStatementContext>(i);
}


size_t IronParser::StatementListContext::getRuleIndex() const {
  return IronParser::RuleStatementList;
}

void IronParser::StatementListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatementList(this);
}

void IronParser::StatementListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatementList(this);
}

IronParser::StatementListContext* IronParser::statementList() {
  StatementListContext *_localctx = _tracker.createInstance<StatementListContext>(_ctx, getState());
  enterRule(_localctx, 6, IronParser::RuleStatementList);
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
    setState(140);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1425403687383138304) != 0)) {
      setState(138);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
      case 1: {
        setState(127);
        continueStatement();
        break;
      }

      case 2: {
        setState(128);
        breakStatement();
        break;
      }

      case 3: {
        setState(129);
        varDeclaration();
        break;
      }

      case 4: {
        setState(130);
        varAssignment();
        break;
      }

      case 5: {
        setState(131);
        functionCall();
        break;
      }

      case 6: {
        setState(132);
        expr(0);
        break;
      }

      case 7: {
        setState(133);
        ifStatement();
        break;
      }

      case 8: {
        setState(134);
        whileStatement();
        break;
      }

      case 9: {
        setState(135);
        repeatStatement();
        break;
      }

      case 10: {
        setState(136);
        forStatement();
        break;
      }

      case 11: {
        setState(137);
        returnStatement();
        break;
      }

      default:
        break;
      }
      setState(142);
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

//----------------- BreakStatementContext ------------------------------------------------------------------

IronParser::BreakStatementContext::BreakStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::BreakStatementContext::BREAK() {
  return getToken(IronParser::BREAK, 0);
}


size_t IronParser::BreakStatementContext::getRuleIndex() const {
  return IronParser::RuleBreakStatement;
}

void IronParser::BreakStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBreakStatement(this);
}

void IronParser::BreakStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBreakStatement(this);
}

IronParser::BreakStatementContext* IronParser::breakStatement() {
  BreakStatementContext *_localctx = _tracker.createInstance<BreakStatementContext>(_ctx, getState());
  enterRule(_localctx, 8, IronParser::RuleBreakStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(143);
    match(IronParser::BREAK);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContinueStatementContext ------------------------------------------------------------------

IronParser::ContinueStatementContext::ContinueStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::ContinueStatementContext::CONTINUE() {
  return getToken(IronParser::CONTINUE, 0);
}


size_t IronParser::ContinueStatementContext::getRuleIndex() const {
  return IronParser::RuleContinueStatement;
}

void IronParser::ContinueStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContinueStatement(this);
}

void IronParser::ContinueStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContinueStatement(this);
}

IronParser::ContinueStatementContext* IronParser::continueStatement() {
  ContinueStatementContext *_localctx = _tracker.createInstance<ContinueStatementContext>(_ctx, getState());
  enterRule(_localctx, 10, IronParser::RuleContinueStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(145);
    match(IronParser::CONTINUE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructStatementContext ------------------------------------------------------------------

IronParser::StructStatementContext::StructStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::StructStatementContext::STRUCT() {
  return getToken(IronParser::STRUCT, 0);
}

tree::TerminalNode* IronParser::StructStatementContext::L_CURLY() {
  return getToken(IronParser::L_CURLY, 0);
}

std::vector<IronParser::StructBodyContext *> IronParser::StructStatementContext::structBody() {
  return getRuleContexts<IronParser::StructBodyContext>();
}

IronParser::StructBodyContext* IronParser::StructStatementContext::structBody(size_t i) {
  return getRuleContext<IronParser::StructBodyContext>(i);
}

tree::TerminalNode* IronParser::StructStatementContext::R_CURLY() {
  return getToken(IronParser::R_CURLY, 0);
}

tree::TerminalNode* IronParser::StructStatementContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

std::vector<tree::TerminalNode *> IronParser::StructStatementContext::COMMA() {
  return getTokens(IronParser::COMMA);
}

tree::TerminalNode* IronParser::StructStatementContext::COMMA(size_t i) {
  return getToken(IronParser::COMMA, i);
}


size_t IronParser::StructStatementContext::getRuleIndex() const {
  return IronParser::RuleStructStatement;
}

void IronParser::StructStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructStatement(this);
}

void IronParser::StructStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructStatement(this);
}

IronParser::StructStatementContext* IronParser::structStatement() {
  StructStatementContext *_localctx = _tracker.createInstance<StructStatementContext>(_ctx, getState());
  enterRule(_localctx, 12, IronParser::RuleStructStatement);
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
    setState(147);
    match(IronParser::STRUCT);
    setState(148);
    antlrcpp::downCast<StructStatementContext *>(_localctx)->structName = match(IronParser::IDENTIFIER);
    setState(149);
    match(IronParser::L_CURLY);
    setState(150);
    structBody();
    setState(155);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::COMMA) {
      setState(151);
      match(IronParser::COMMA);
      setState(152);
      structBody();
      setState(157);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(158);
    match(IronParser::R_CURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructBodyContext ------------------------------------------------------------------

IronParser::StructBodyContext::StructBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::StructBodyContext::COLON() {
  return getToken(IronParser::COLON, 0);
}

std::vector<tree::TerminalNode *> IronParser::StructBodyContext::IDENTIFIER() {
  return getTokens(IronParser::IDENTIFIER);
}

tree::TerminalNode* IronParser::StructBodyContext::IDENTIFIER(size_t i) {
  return getToken(IronParser::IDENTIFIER, i);
}

IronParser::VarTypesContext* IronParser::StructBodyContext::varTypes() {
  return getRuleContext<IronParser::VarTypesContext>(0);
}

tree::TerminalNode* IronParser::StructBodyContext::MUT() {
  return getToken(IronParser::MUT, 0);
}


size_t IronParser::StructBodyContext::getRuleIndex() const {
  return IronParser::RuleStructBody;
}

void IronParser::StructBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructBody(this);
}

void IronParser::StructBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructBody(this);
}

IronParser::StructBodyContext* IronParser::structBody() {
  StructBodyContext *_localctx = _tracker.createInstance<StructBodyContext>(_ctx, getState());
  enterRule(_localctx, 14, IronParser::RuleStructBody);
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
    setState(161);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::MUT) {
      setState(160);
      match(IronParser::MUT);
    }
    setState(163);
    antlrcpp::downCast<StructBodyContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(164);
    match(IronParser::COLON);
    setState(167);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IronParser::FUNCTION:
      case IronParser::TYPE_INT:
      case IronParser::TYPE_CHAR:
      case IronParser::TYPE_FLOAT:
      case IronParser::TYPE_STRING:
      case IronParser::TYPE_BOOLEAN:
      case IronParser::TYPE_DOUBLE: {
        setState(165);
        varTypes();
        break;
      }

      case IronParser::IDENTIFIER: {
        setState(166);
        antlrcpp::downCast<StructBodyContext *>(_localctx)->anotherType = match(IronParser::IDENTIFIER);
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

//----------------- OptionsStatementContext ------------------------------------------------------------------

IronParser::OptionsStatementContext::OptionsStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::OptionsStatementContext::OPTIONS() {
  return getToken(IronParser::OPTIONS, 0);
}

tree::TerminalNode* IronParser::OptionsStatementContext::L_CURLY() {
  return getToken(IronParser::L_CURLY, 0);
}

std::vector<IronParser::OptionsBodyContext *> IronParser::OptionsStatementContext::optionsBody() {
  return getRuleContexts<IronParser::OptionsBodyContext>();
}

IronParser::OptionsBodyContext* IronParser::OptionsStatementContext::optionsBody(size_t i) {
  return getRuleContext<IronParser::OptionsBodyContext>(i);
}

tree::TerminalNode* IronParser::OptionsStatementContext::R_CURLY() {
  return getToken(IronParser::R_CURLY, 0);
}

tree::TerminalNode* IronParser::OptionsStatementContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

std::vector<tree::TerminalNode *> IronParser::OptionsStatementContext::COMMA() {
  return getTokens(IronParser::COMMA);
}

tree::TerminalNode* IronParser::OptionsStatementContext::COMMA(size_t i) {
  return getToken(IronParser::COMMA, i);
}


size_t IronParser::OptionsStatementContext::getRuleIndex() const {
  return IronParser::RuleOptionsStatement;
}

void IronParser::OptionsStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOptionsStatement(this);
}

void IronParser::OptionsStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOptionsStatement(this);
}

IronParser::OptionsStatementContext* IronParser::optionsStatement() {
  OptionsStatementContext *_localctx = _tracker.createInstance<OptionsStatementContext>(_ctx, getState());
  enterRule(_localctx, 16, IronParser::RuleOptionsStatement);
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
    setState(169);
    match(IronParser::OPTIONS);
    setState(170);
    antlrcpp::downCast<OptionsStatementContext *>(_localctx)->optionName = match(IronParser::IDENTIFIER);
    setState(171);
    match(IronParser::L_CURLY);
    setState(172);
    optionsBody();
    setState(177);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::COMMA) {
      setState(173);
      match(IronParser::COMMA);
      setState(174);
      optionsBody();
      setState(179);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(180);
    match(IronParser::R_CURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OptionsBodyContext ------------------------------------------------------------------

IronParser::OptionsBodyContext::OptionsBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::OptionsBodyContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

IronParser::FunctionSignatureContext* IronParser::OptionsBodyContext::functionSignature() {
  return getRuleContext<IronParser::FunctionSignatureContext>(0);
}


size_t IronParser::OptionsBodyContext::getRuleIndex() const {
  return IronParser::RuleOptionsBody;
}

void IronParser::OptionsBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOptionsBody(this);
}

void IronParser::OptionsBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOptionsBody(this);
}

IronParser::OptionsBodyContext* IronParser::optionsBody() {
  OptionsBodyContext *_localctx = _tracker.createInstance<OptionsBodyContext>(_ctx, getState());
  enterRule(_localctx, 18, IronParser::RuleOptionsBody);
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
    antlrcpp::downCast<OptionsBodyContext *>(_localctx)->itemName = match(IronParser::IDENTIFIER);
    setState(184);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::L_PAREN) {
      setState(183);
      functionSignature();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStatementContext ------------------------------------------------------------------

IronParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::ReturnStatementContext::RETURN() {
  return getToken(IronParser::RETURN, 0);
}

IronParser::DataFormatContext* IronParser::ReturnStatementContext::dataFormat() {
  return getRuleContext<IronParser::DataFormatContext>(0);
}

IronParser::FunctionCallContext* IronParser::ReturnStatementContext::functionCall() {
  return getRuleContext<IronParser::FunctionCallContext>(0);
}

IronParser::ExprContext* IronParser::ReturnStatementContext::expr() {
  return getRuleContext<IronParser::ExprContext>(0);
}

tree::TerminalNode* IronParser::ReturnStatementContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}


size_t IronParser::ReturnStatementContext::getRuleIndex() const {
  return IronParser::RuleReturnStatement;
}

void IronParser::ReturnStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStatement(this);
}

void IronParser::ReturnStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStatement(this);
}

IronParser::ReturnStatementContext* IronParser::returnStatement() {
  ReturnStatementContext *_localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 20, IronParser::RuleReturnStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(186);
    match(IronParser::RETURN);
    setState(191);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      setState(187);
      dataFormat();
      break;
    }

    case 2: {
      setState(188);
      antlrcpp::downCast<ReturnStatementContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
      break;
    }

    case 3: {
      setState(189);
      functionCall();
      break;
    }

    case 4: {
      setState(190);
      expr(0);
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

//----------------- WhileStatementContext ------------------------------------------------------------------

IronParser::WhileStatementContext::WhileStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::WhileStatementContext::WHILE() {
  return getToken(IronParser::WHILE, 0);
}

IronParser::BoolExprContext* IronParser::WhileStatementContext::boolExpr() {
  return getRuleContext<IronParser::BoolExprContext>(0);
}

tree::TerminalNode* IronParser::WhileStatementContext::L_CURLY() {
  return getToken(IronParser::L_CURLY, 0);
}

IronParser::StatementListContext* IronParser::WhileStatementContext::statementList() {
  return getRuleContext<IronParser::StatementListContext>(0);
}

tree::TerminalNode* IronParser::WhileStatementContext::R_CURLY() {
  return getToken(IronParser::R_CURLY, 0);
}


size_t IronParser::WhileStatementContext::getRuleIndex() const {
  return IronParser::RuleWhileStatement;
}

void IronParser::WhileStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhileStatement(this);
}

void IronParser::WhileStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhileStatement(this);
}

IronParser::WhileStatementContext* IronParser::whileStatement() {
  WhileStatementContext *_localctx = _tracker.createInstance<WhileStatementContext>(_ctx, getState());
  enterRule(_localctx, 22, IronParser::RuleWhileStatement);

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
    match(IronParser::WHILE);
    setState(194);
    boolExpr(0);
    setState(195);
    match(IronParser::L_CURLY);
    setState(196);
    statementList();
    setState(197);
    match(IronParser::R_CURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RepeatStatementContext ------------------------------------------------------------------

IronParser::RepeatStatementContext::RepeatStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::RepeatStatementContext::REPEAT() {
  return getToken(IronParser::REPEAT, 0);
}

tree::TerminalNode* IronParser::RepeatStatementContext::L_CURLY() {
  return getToken(IronParser::L_CURLY, 0);
}

IronParser::StatementListContext* IronParser::RepeatStatementContext::statementList() {
  return getRuleContext<IronParser::StatementListContext>(0);
}

tree::TerminalNode* IronParser::RepeatStatementContext::R_CURLY() {
  return getToken(IronParser::R_CURLY, 0);
}

tree::TerminalNode* IronParser::RepeatStatementContext::WHILE() {
  return getToken(IronParser::WHILE, 0);
}

IronParser::BoolExprContext* IronParser::RepeatStatementContext::boolExpr() {
  return getRuleContext<IronParser::BoolExprContext>(0);
}


size_t IronParser::RepeatStatementContext::getRuleIndex() const {
  return IronParser::RuleRepeatStatement;
}

void IronParser::RepeatStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRepeatStatement(this);
}

void IronParser::RepeatStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRepeatStatement(this);
}

IronParser::RepeatStatementContext* IronParser::repeatStatement() {
  RepeatStatementContext *_localctx = _tracker.createInstance<RepeatStatementContext>(_ctx, getState());
  enterRule(_localctx, 24, IronParser::RuleRepeatStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(199);
    match(IronParser::REPEAT);
    setState(200);
    match(IronParser::L_CURLY);
    setState(201);
    statementList();
    setState(202);
    match(IronParser::R_CURLY);
    setState(203);
    match(IronParser::WHILE);
    setState(204);
    boolExpr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForStatementContext ------------------------------------------------------------------

IronParser::ForStatementContext::ForStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::ForStatementContext::FOR() {
  return getToken(IronParser::FOR, 0);
}

tree::TerminalNode* IronParser::ForStatementContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

tree::TerminalNode* IronParser::ForStatementContext::IN() {
  return getToken(IronParser::IN, 0);
}

IronParser::IntervalsContext* IronParser::ForStatementContext::intervals() {
  return getRuleContext<IronParser::IntervalsContext>(0);
}

tree::TerminalNode* IronParser::ForStatementContext::L_CURLY() {
  return getToken(IronParser::L_CURLY, 0);
}

IronParser::StatementListContext* IronParser::ForStatementContext::statementList() {
  return getRuleContext<IronParser::StatementListContext>(0);
}

tree::TerminalNode* IronParser::ForStatementContext::R_CURLY() {
  return getToken(IronParser::R_CURLY, 0);
}


size_t IronParser::ForStatementContext::getRuleIndex() const {
  return IronParser::RuleForStatement;
}

void IronParser::ForStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForStatement(this);
}

void IronParser::ForStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForStatement(this);
}

IronParser::ForStatementContext* IronParser::forStatement() {
  ForStatementContext *_localctx = _tracker.createInstance<ForStatementContext>(_ctx, getState());
  enterRule(_localctx, 26, IronParser::RuleForStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(206);
    match(IronParser::FOR);
    setState(207);
    match(IronParser::IDENTIFIER);
    setState(208);
    match(IronParser::IN);
    setState(209);
    intervals();
    setState(210);
    match(IronParser::L_CURLY);
    setState(211);
    statementList();
    setState(212);
    match(IronParser::R_CURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntervalsContext ------------------------------------------------------------------

IronParser::IntervalsContext::IntervalsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> IronParser::IntervalsContext::INT_NUMBER() {
  return getTokens(IronParser::INT_NUMBER);
}

tree::TerminalNode* IronParser::IntervalsContext::INT_NUMBER(size_t i) {
  return getToken(IronParser::INT_NUMBER, i);
}

std::vector<tree::TerminalNode *> IronParser::IntervalsContext::IDENTIFIER() {
  return getTokens(IronParser::IDENTIFIER);
}

tree::TerminalNode* IronParser::IntervalsContext::IDENTIFIER(size_t i) {
  return getToken(IronParser::IDENTIFIER, i);
}


size_t IronParser::IntervalsContext::getRuleIndex() const {
  return IronParser::RuleIntervals;
}

void IronParser::IntervalsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntervals(this);
}

void IronParser::IntervalsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntervals(this);
}

IronParser::IntervalsContext* IronParser::intervals() {
  IntervalsContext *_localctx = _tracker.createInstance<IntervalsContext>(_ctx, getState());
  enterRule(_localctx, 28, IronParser::RuleIntervals);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(216);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IronParser::INT_NUMBER: {
        setState(214);
        antlrcpp::downCast<IntervalsContext *>(_localctx)->firstNumber = match(IronParser::INT_NUMBER);
        break;
      }

      case IronParser::IDENTIFIER: {
        setState(215);
        antlrcpp::downCast<IntervalsContext *>(_localctx)->firstVarName = match(IronParser::IDENTIFIER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(218);
    match(IronParser::T__0);
    setState(221);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IronParser::INT_NUMBER: {
        setState(219);
        antlrcpp::downCast<IntervalsContext *>(_localctx)->secondNumber = match(IronParser::INT_NUMBER);
        break;
      }

      case IronParser::IDENTIFIER: {
        setState(220);
        antlrcpp::downCast<IntervalsContext *>(_localctx)->secondVarName = match(IronParser::IDENTIFIER);
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

//----------------- FormatStatementContext ------------------------------------------------------------------

IronParser::FormatStatementContext::FormatStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::FormatStatementContext::STRING_LITERAL() {
  return getToken(IronParser::STRING_LITERAL, 0);
}

tree::TerminalNode* IronParser::FormatStatementContext::COMMA() {
  return getToken(IronParser::COMMA, 0);
}

tree::TerminalNode* IronParser::FormatStatementContext::R_PAREN() {
  return getToken(IronParser::R_PAREN, 0);
}

IronParser::FormatArgumentsContext* IronParser::FormatStatementContext::formatArguments() {
  return getRuleContext<IronParser::FormatArgumentsContext>(0);
}


size_t IronParser::FormatStatementContext::getRuleIndex() const {
  return IronParser::RuleFormatStatement;
}

void IronParser::FormatStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormatStatement(this);
}

void IronParser::FormatStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormatStatement(this);
}

IronParser::FormatStatementContext* IronParser::formatStatement() {
  FormatStatementContext *_localctx = _tracker.createInstance<FormatStatementContext>(_ctx, getState());
  enterRule(_localctx, 30, IronParser::RuleFormatStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(223);
    match(IronParser::T__1);
    setState(224);
    match(IronParser::STRING_LITERAL);
    setState(225);
    match(IronParser::COMMA);

    setState(226);
    formatArguments();
    setState(227);
    match(IronParser::R_PAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormatArgumentsContext ------------------------------------------------------------------

IronParser::FormatArgumentsContext::FormatArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IronParser::FormatArgumentContext *> IronParser::FormatArgumentsContext::formatArgument() {
  return getRuleContexts<IronParser::FormatArgumentContext>();
}

IronParser::FormatArgumentContext* IronParser::FormatArgumentsContext::formatArgument(size_t i) {
  return getRuleContext<IronParser::FormatArgumentContext>(i);
}

std::vector<tree::TerminalNode *> IronParser::FormatArgumentsContext::COMMA() {
  return getTokens(IronParser::COMMA);
}

tree::TerminalNode* IronParser::FormatArgumentsContext::COMMA(size_t i) {
  return getToken(IronParser::COMMA, i);
}


size_t IronParser::FormatArgumentsContext::getRuleIndex() const {
  return IronParser::RuleFormatArguments;
}

void IronParser::FormatArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormatArguments(this);
}

void IronParser::FormatArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormatArguments(this);
}

IronParser::FormatArgumentsContext* IronParser::formatArguments() {
  FormatArgumentsContext *_localctx = _tracker.createInstance<FormatArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 32, IronParser::RuleFormatArguments);
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
    setState(229);
    formatArgument();
    setState(234);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::COMMA) {
      setState(230);
      match(IronParser::COMMA);
      setState(231);
      formatArgument();
      setState(236);
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

//----------------- FormatArgumentContext ------------------------------------------------------------------

IronParser::FormatArgumentContext::FormatArgumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IronParser::DataFormatContext* IronParser::FormatArgumentContext::dataFormat() {
  return getRuleContext<IronParser::DataFormatContext>(0);
}

IronParser::FunctionCallContext* IronParser::FormatArgumentContext::functionCall() {
  return getRuleContext<IronParser::FunctionCallContext>(0);
}

IronParser::ExprContext* IronParser::FormatArgumentContext::expr() {
  return getRuleContext<IronParser::ExprContext>(0);
}

tree::TerminalNode* IronParser::FormatArgumentContext::STRING_LITERAL() {
  return getToken(IronParser::STRING_LITERAL, 0);
}

tree::TerminalNode* IronParser::FormatArgumentContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}


size_t IronParser::FormatArgumentContext::getRuleIndex() const {
  return IronParser::RuleFormatArgument;
}

void IronParser::FormatArgumentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormatArgument(this);
}

void IronParser::FormatArgumentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormatArgument(this);
}

IronParser::FormatArgumentContext* IronParser::formatArgument() {
  FormatArgumentContext *_localctx = _tracker.createInstance<FormatArgumentContext>(_ctx, getState());
  enterRule(_localctx, 34, IronParser::RuleFormatArgument);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(242);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      setState(237);
      dataFormat();
      break;
    }

    case 2: {
      setState(238);
      antlrcpp::downCast<FormatArgumentContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
      break;
    }

    case 3: {
      setState(239);
      functionCall();
      break;
    }

    case 4: {
      setState(240);
      expr(0);
      break;
    }

    case 5: {
      setState(241);
      match(IronParser::STRING_LITERAL);
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

//----------------- ExternBlockContext ------------------------------------------------------------------

IronParser::ExternBlockContext::ExternBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::ExternBlockContext::L_CURLY() {
  return getToken(IronParser::L_CURLY, 0);
}

tree::TerminalNode* IronParser::ExternBlockContext::R_CURLY() {
  return getToken(IronParser::R_CURLY, 0);
}

tree::TerminalNode* IronParser::ExternBlockContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

std::vector<IronParser::ExternFunctionDeclarationContext *> IronParser::ExternBlockContext::externFunctionDeclaration() {
  return getRuleContexts<IronParser::ExternFunctionDeclarationContext>();
}

IronParser::ExternFunctionDeclarationContext* IronParser::ExternBlockContext::externFunctionDeclaration(size_t i) {
  return getRuleContext<IronParser::ExternFunctionDeclarationContext>(i);
}


size_t IronParser::ExternBlockContext::getRuleIndex() const {
  return IronParser::RuleExternBlock;
}

void IronParser::ExternBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExternBlock(this);
}

void IronParser::ExternBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExternBlock(this);
}

IronParser::ExternBlockContext* IronParser::externBlock() {
  ExternBlockContext *_localctx = _tracker.createInstance<ExternBlockContext>(_ctx, getState());
  enterRule(_localctx, 36, IronParser::RuleExternBlock);
  size_t _la = 0;

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
    setState(244);
    match(IronParser::T__2);
    setState(245);
    antlrcpp::downCast<ExternBlockContext *>(_localctx)->language = match(IronParser::IDENTIFIER);
    setState(246);
    match(IronParser::L_CURLY);
    setState(254);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::FUNCTION) {
      setState(248); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(247);
                externFunctionDeclaration();
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(250); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      setState(256);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(257);
    match(IronParser::R_CURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExternFunctionDeclarationContext ------------------------------------------------------------------

IronParser::ExternFunctionDeclarationContext::ExternFunctionDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::ExternFunctionDeclarationContext::FUNCTION() {
  return getToken(IronParser::FUNCTION, 0);
}

tree::TerminalNode* IronParser::ExternFunctionDeclarationContext::L_PAREN() {
  return getToken(IronParser::L_PAREN, 0);
}

tree::TerminalNode* IronParser::ExternFunctionDeclarationContext::R_PAREN() {
  return getToken(IronParser::R_PAREN, 0);
}

tree::TerminalNode* IronParser::ExternFunctionDeclarationContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

IronParser::ExternFunctionArgsContext* IronParser::ExternFunctionDeclarationContext::externFunctionArgs() {
  return getRuleContext<IronParser::ExternFunctionArgsContext>(0);
}

tree::TerminalNode* IronParser::ExternFunctionDeclarationContext::COMMA() {
  return getToken(IronParser::COMMA, 0);
}

IronParser::FunctionReturnTypeContext* IronParser::ExternFunctionDeclarationContext::functionReturnType() {
  return getRuleContext<IronParser::FunctionReturnTypeContext>(0);
}


size_t IronParser::ExternFunctionDeclarationContext::getRuleIndex() const {
  return IronParser::RuleExternFunctionDeclaration;
}

void IronParser::ExternFunctionDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExternFunctionDeclaration(this);
}

void IronParser::ExternFunctionDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExternFunctionDeclaration(this);
}

IronParser::ExternFunctionDeclarationContext* IronParser::externFunctionDeclaration() {
  ExternFunctionDeclarationContext *_localctx = _tracker.createInstance<ExternFunctionDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 38, IronParser::RuleExternFunctionDeclaration);
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
    setState(259);
    match(IronParser::FUNCTION);
    setState(260);
    antlrcpp::downCast<ExternFunctionDeclarationContext *>(_localctx)->exterFunctionName = match(IronParser::IDENTIFIER);
    setState(261);
    match(IronParser::L_PAREN);
    setState(263);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::IDENTIFIER) {
      setState(262);
      externFunctionArgs();
    }
    setState(267);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::COMMA) {
      setState(265);
      match(IronParser::COMMA);
      setState(266);
      antlrcpp::downCast<ExternFunctionDeclarationContext *>(_localctx)->varied = match(IronParser::T__3);
    }
    setState(269);
    match(IronParser::R_PAREN);
    setState(271);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::COLON) {
      setState(270);
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

//----------------- ExternFunctionArgsContext ------------------------------------------------------------------

IronParser::ExternFunctionArgsContext::ExternFunctionArgsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IronParser::ExternFunctionArgContext *> IronParser::ExternFunctionArgsContext::externFunctionArg() {
  return getRuleContexts<IronParser::ExternFunctionArgContext>();
}

IronParser::ExternFunctionArgContext* IronParser::ExternFunctionArgsContext::externFunctionArg(size_t i) {
  return getRuleContext<IronParser::ExternFunctionArgContext>(i);
}

std::vector<tree::TerminalNode *> IronParser::ExternFunctionArgsContext::COMMA() {
  return getTokens(IronParser::COMMA);
}

tree::TerminalNode* IronParser::ExternFunctionArgsContext::COMMA(size_t i) {
  return getToken(IronParser::COMMA, i);
}


size_t IronParser::ExternFunctionArgsContext::getRuleIndex() const {
  return IronParser::RuleExternFunctionArgs;
}

void IronParser::ExternFunctionArgsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExternFunctionArgs(this);
}

void IronParser::ExternFunctionArgsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExternFunctionArgs(this);
}

IronParser::ExternFunctionArgsContext* IronParser::externFunctionArgs() {
  ExternFunctionArgsContext *_localctx = _tracker.createInstance<ExternFunctionArgsContext>(_ctx, getState());
  enterRule(_localctx, 40, IronParser::RuleExternFunctionArgs);

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
    setState(273);
    externFunctionArg();
    setState(278);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(274);
        match(IronParser::COMMA);
        setState(275);
        externFunctionArg(); 
      }
      setState(280);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExternFunctionArgContext ------------------------------------------------------------------

IronParser::ExternFunctionArgContext::ExternFunctionArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::ExternFunctionArgContext::COLON() {
  return getToken(IronParser::COLON, 0);
}

IronParser::CTypesContext* IronParser::ExternFunctionArgContext::cTypes() {
  return getRuleContext<IronParser::CTypesContext>(0);
}

tree::TerminalNode* IronParser::ExternFunctionArgContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

tree::TerminalNode* IronParser::ExternFunctionArgContext::STAR() {
  return getToken(IronParser::STAR, 0);
}


size_t IronParser::ExternFunctionArgContext::getRuleIndex() const {
  return IronParser::RuleExternFunctionArg;
}

void IronParser::ExternFunctionArgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExternFunctionArg(this);
}

void IronParser::ExternFunctionArgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExternFunctionArg(this);
}

IronParser::ExternFunctionArgContext* IronParser::externFunctionArg() {
  ExternFunctionArgContext *_localctx = _tracker.createInstance<ExternFunctionArgContext>(_ctx, getState());
  enterRule(_localctx, 42, IronParser::RuleExternFunctionArg);
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
    setState(281);
    antlrcpp::downCast<ExternFunctionArgContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(282);
    match(IronParser::COLON);
    setState(284);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::STAR) {
      setState(283);
      antlrcpp::downCast<ExternFunctionArgContext *>(_localctx)->ptr = match(IronParser::STAR);
    }
    setState(286);
    cTypes();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CTypesContext ------------------------------------------------------------------

IronParser::CTypesContext::CTypesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::CTypesContext::TYPE_BOOLEAN() {
  return getToken(IronParser::TYPE_BOOLEAN, 0);
}

tree::TerminalNode* IronParser::CTypesContext::TYPE_CHAR() {
  return getToken(IronParser::TYPE_CHAR, 0);
}

tree::TerminalNode* IronParser::CTypesContext::TYPE_DOUBLE() {
  return getToken(IronParser::TYPE_DOUBLE, 0);
}

tree::TerminalNode* IronParser::CTypesContext::TYPE_FLOAT() {
  return getToken(IronParser::TYPE_FLOAT, 0);
}

tree::TerminalNode* IronParser::CTypesContext::TYPE_INT() {
  return getToken(IronParser::TYPE_INT, 0);
}

tree::TerminalNode* IronParser::CTypesContext::TYPE_VOID() {
  return getToken(IronParser::TYPE_VOID, 0);
}


size_t IronParser::CTypesContext::getRuleIndex() const {
  return IronParser::RuleCTypes;
}

void IronParser::CTypesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCTypes(this);
}

void IronParser::CTypesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCTypes(this);
}

IronParser::CTypesContext* IronParser::cTypes() {
  CTypesContext *_localctx = _tracker.createInstance<CTypesContext>(_ctx, getState());
  enterRule(_localctx, 44, IronParser::RuleCTypes);
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
    setState(288);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2093470139285504) != 0))) {
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

//----------------- FunctionDeclarationContext ------------------------------------------------------------------

IronParser::FunctionDeclarationContext::FunctionDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::FunctionDeclarationContext::FUNCTION() {
  return getToken(IronParser::FUNCTION, 0);
}

IronParser::FunctionSignatureContext* IronParser::FunctionDeclarationContext::functionSignature() {
  return getRuleContext<IronParser::FunctionSignatureContext>(0);
}

tree::TerminalNode* IronParser::FunctionDeclarationContext::L_CURLY() {
  return getToken(IronParser::L_CURLY, 0);
}

IronParser::StatementListContext* IronParser::FunctionDeclarationContext::statementList() {
  return getRuleContext<IronParser::StatementListContext>(0);
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
  enterRule(_localctx, 46, IronParser::RuleFunctionDeclaration);
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
    setState(291);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::PUBLIC) {
      setState(290);
      match(IronParser::PUBLIC);
    }
    setState(293);
    match(IronParser::FUNCTION);
    setState(294);
    antlrcpp::downCast<FunctionDeclarationContext *>(_localctx)->functionName = match(IronParser::IDENTIFIER);
    setState(295);
    functionSignature();
    setState(296);
    match(IronParser::L_CURLY);
    setState(297);
    statementList();
    setState(298);
    match(IronParser::R_CURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrowFunctionInlineContext ------------------------------------------------------------------

IronParser::ArrowFunctionInlineContext::ArrowFunctionInlineContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IronParser::FunctionSignatureContext* IronParser::ArrowFunctionInlineContext::functionSignature() {
  return getRuleContext<IronParser::FunctionSignatureContext>(0);
}

tree::TerminalNode* IronParser::ArrowFunctionInlineContext::ARROW() {
  return getToken(IronParser::ARROW, 0);
}

IronParser::ExprContext* IronParser::ArrowFunctionInlineContext::expr() {
  return getRuleContext<IronParser::ExprContext>(0);
}

tree::TerminalNode* IronParser::ArrowFunctionInlineContext::L_CURLY() {
  return getToken(IronParser::L_CURLY, 0);
}

IronParser::StatementListContext* IronParser::ArrowFunctionInlineContext::statementList() {
  return getRuleContext<IronParser::StatementListContext>(0);
}

tree::TerminalNode* IronParser::ArrowFunctionInlineContext::R_CURLY() {
  return getToken(IronParser::R_CURLY, 0);
}


size_t IronParser::ArrowFunctionInlineContext::getRuleIndex() const {
  return IronParser::RuleArrowFunctionInline;
}

void IronParser::ArrowFunctionInlineContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrowFunctionInline(this);
}

void IronParser::ArrowFunctionInlineContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrowFunctionInline(this);
}

IronParser::ArrowFunctionInlineContext* IronParser::arrowFunctionInline() {
  ArrowFunctionInlineContext *_localctx = _tracker.createInstance<ArrowFunctionInlineContext>(_ctx, getState());
  enterRule(_localctx, 48, IronParser::RuleArrowFunctionInline);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(300);
    functionSignature();
    setState(301);
    match(IronParser::ARROW);
    setState(307);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IronParser::L_PAREN:
      case IronParser::REAL_NUMBER:
      case IronParser::INT_NUMBER:
      case IronParser::IDENTIFIER: {
        setState(302);
        expr(0);
        break;
      }

      case IronParser::L_CURLY: {
        setState(303);
        match(IronParser::L_CURLY);
        setState(304);
        statementList();
        setState(305);
        match(IronParser::R_CURLY);
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

//----------------- FunctionSignatureContext ------------------------------------------------------------------

IronParser::FunctionSignatureContext::FunctionSignatureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::FunctionSignatureContext::L_PAREN() {
  return getToken(IronParser::L_PAREN, 0);
}

tree::TerminalNode* IronParser::FunctionSignatureContext::R_PAREN() {
  return getToken(IronParser::R_PAREN, 0);
}

IronParser::FunctionArgsContext* IronParser::FunctionSignatureContext::functionArgs() {
  return getRuleContext<IronParser::FunctionArgsContext>(0);
}

IronParser::FunctionReturnTypeContext* IronParser::FunctionSignatureContext::functionReturnType() {
  return getRuleContext<IronParser::FunctionReturnTypeContext>(0);
}


size_t IronParser::FunctionSignatureContext::getRuleIndex() const {
  return IronParser::RuleFunctionSignature;
}

void IronParser::FunctionSignatureContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionSignature(this);
}

void IronParser::FunctionSignatureContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionSignature(this);
}

IronParser::FunctionSignatureContext* IronParser::functionSignature() {
  FunctionSignatureContext *_localctx = _tracker.createInstance<FunctionSignatureContext>(_ctx, getState());
  enterRule(_localctx, 50, IronParser::RuleFunctionSignature);
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
    setState(309);
    match(IronParser::L_PAREN);
    setState(311);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::IDENTIFIER) {
      setState(310);
      functionArgs();
    }
    setState(313);
    match(IronParser::R_PAREN);
    setState(315);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::COLON) {
      setState(314);
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

IronParser::FunctionReturnTypeContext::FunctionReturnTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::FunctionReturnTypeContext::COLON() {
  return getToken(IronParser::COLON, 0);
}

IronParser::VarTypesContext* IronParser::FunctionReturnTypeContext::varTypes() {
  return getRuleContext<IronParser::VarTypesContext>(0);
}


size_t IronParser::FunctionReturnTypeContext::getRuleIndex() const {
  return IronParser::RuleFunctionReturnType;
}

void IronParser::FunctionReturnTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionReturnType(this);
}

void IronParser::FunctionReturnTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionReturnType(this);
}

IronParser::FunctionReturnTypeContext* IronParser::functionReturnType() {
  FunctionReturnTypeContext *_localctx = _tracker.createInstance<FunctionReturnTypeContext>(_ctx, getState());
  enterRule(_localctx, 52, IronParser::RuleFunctionReturnType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(317);
    match(IronParser::COLON);
    setState(318);
    varTypes();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionArgsContext ------------------------------------------------------------------

IronParser::FunctionArgsContext::FunctionArgsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IronParser::FunctionArgContext *> IronParser::FunctionArgsContext::functionArg() {
  return getRuleContexts<IronParser::FunctionArgContext>();
}

IronParser::FunctionArgContext* IronParser::FunctionArgsContext::functionArg(size_t i) {
  return getRuleContext<IronParser::FunctionArgContext>(i);
}

std::vector<tree::TerminalNode *> IronParser::FunctionArgsContext::COMMA() {
  return getTokens(IronParser::COMMA);
}

tree::TerminalNode* IronParser::FunctionArgsContext::COMMA(size_t i) {
  return getToken(IronParser::COMMA, i);
}


size_t IronParser::FunctionArgsContext::getRuleIndex() const {
  return IronParser::RuleFunctionArgs;
}

void IronParser::FunctionArgsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionArgs(this);
}

void IronParser::FunctionArgsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionArgs(this);
}

IronParser::FunctionArgsContext* IronParser::functionArgs() {
  FunctionArgsContext *_localctx = _tracker.createInstance<FunctionArgsContext>(_ctx, getState());
  enterRule(_localctx, 54, IronParser::RuleFunctionArgs);
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
    setState(320);
    functionArg();
    setState(325);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::COMMA) {
      setState(321);
      match(IronParser::COMMA);
      setState(322);
      functionArg();
      setState(327);
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

IronParser::FunctionArgContext::FunctionArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::FunctionArgContext::COLON() {
  return getToken(IronParser::COLON, 0);
}

tree::TerminalNode* IronParser::FunctionArgContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

IronParser::FnsignatureContext* IronParser::FunctionArgContext::fnsignature() {
  return getRuleContext<IronParser::FnsignatureContext>(0);
}

IronParser::VarTypesContext* IronParser::FunctionArgContext::varTypes() {
  return getRuleContext<IronParser::VarTypesContext>(0);
}

IronParser::AssignmentContext* IronParser::FunctionArgContext::assignment() {
  return getRuleContext<IronParser::AssignmentContext>(0);
}


size_t IronParser::FunctionArgContext::getRuleIndex() const {
  return IronParser::RuleFunctionArg;
}

void IronParser::FunctionArgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionArg(this);
}

void IronParser::FunctionArgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionArg(this);
}

IronParser::FunctionArgContext* IronParser::functionArg() {
  FunctionArgContext *_localctx = _tracker.createInstance<FunctionArgContext>(_ctx, getState());
  enterRule(_localctx, 56, IronParser::RuleFunctionArg);
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
    setState(328);
    antlrcpp::downCast<FunctionArgContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(329);
    match(IronParser::COLON);
    setState(332);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      setState(330);
      fnsignature();
      break;
    }

    case 2: {
      setState(331);
      varTypes();
      break;
    }

    default:
      break;
    }
    setState(335);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::EQ) {
      setState(334);
      assignment();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FnsignatureContext ------------------------------------------------------------------

IronParser::FnsignatureContext::FnsignatureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::FnsignatureContext::FUNCTION() {
  return getToken(IronParser::FUNCTION, 0);
}

IronParser::FunctionSignatureContext* IronParser::FnsignatureContext::functionSignature() {
  return getRuleContext<IronParser::FunctionSignatureContext>(0);
}


size_t IronParser::FnsignatureContext::getRuleIndex() const {
  return IronParser::RuleFnsignature;
}

void IronParser::FnsignatureContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnsignature(this);
}

void IronParser::FnsignatureContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnsignature(this);
}

IronParser::FnsignatureContext* IronParser::fnsignature() {
  FnsignatureContext *_localctx = _tracker.createInstance<FnsignatureContext>(_ctx, getState());
  enterRule(_localctx, 58, IronParser::RuleFnsignature);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(337);
    match(IronParser::FUNCTION);
    setState(338);
    functionSignature();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallContext ------------------------------------------------------------------

IronParser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::FunctionCallContext::L_PAREN() {
  return getToken(IronParser::L_PAREN, 0);
}

tree::TerminalNode* IronParser::FunctionCallContext::R_PAREN() {
  return getToken(IronParser::R_PAREN, 0);
}

tree::TerminalNode* IronParser::FunctionCallContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

IronParser::FunctionCallArgsContext* IronParser::FunctionCallContext::functionCallArgs() {
  return getRuleContext<IronParser::FunctionCallArgsContext>(0);
}


size_t IronParser::FunctionCallContext::getRuleIndex() const {
  return IronParser::RuleFunctionCall;
}

void IronParser::FunctionCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCall(this);
}

void IronParser::FunctionCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCall(this);
}

IronParser::FunctionCallContext* IronParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 60, IronParser::RuleFunctionCall);
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
    setState(340);
    antlrcpp::downCast<FunctionCallContext *>(_localctx)->functionName = match(IronParser::IDENTIFIER);
    setState(341);
    match(IronParser::L_PAREN);
    setState(343);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::IDENTIFIER) {
      setState(342);
      functionCallArgs();
    }
    setState(345);
    match(IronParser::R_PAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallArgsContext ------------------------------------------------------------------

IronParser::FunctionCallArgsContext::FunctionCallArgsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IronParser::FunctionCallArgContext *> IronParser::FunctionCallArgsContext::functionCallArg() {
  return getRuleContexts<IronParser::FunctionCallArgContext>();
}

IronParser::FunctionCallArgContext* IronParser::FunctionCallArgsContext::functionCallArg(size_t i) {
  return getRuleContext<IronParser::FunctionCallArgContext>(i);
}

std::vector<tree::TerminalNode *> IronParser::FunctionCallArgsContext::COMMA() {
  return getTokens(IronParser::COMMA);
}

tree::TerminalNode* IronParser::FunctionCallArgsContext::COMMA(size_t i) {
  return getToken(IronParser::COMMA, i);
}


size_t IronParser::FunctionCallArgsContext::getRuleIndex() const {
  return IronParser::RuleFunctionCallArgs;
}

void IronParser::FunctionCallArgsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCallArgs(this);
}

void IronParser::FunctionCallArgsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCallArgs(this);
}

IronParser::FunctionCallArgsContext* IronParser::functionCallArgs() {
  FunctionCallArgsContext *_localctx = _tracker.createInstance<FunctionCallArgsContext>(_ctx, getState());
  enterRule(_localctx, 62, IronParser::RuleFunctionCallArgs);
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
    setState(347);
    functionCallArg();
    setState(352);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::COMMA) {
      setState(348);
      match(IronParser::COMMA);
      setState(349);
      functionCallArg();
      setState(354);
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

IronParser::FunctionCallArgContext::FunctionCallArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::FunctionCallArgContext::COLON() {
  return getToken(IronParser::COLON, 0);
}

std::vector<tree::TerminalNode *> IronParser::FunctionCallArgContext::IDENTIFIER() {
  return getTokens(IronParser::IDENTIFIER);
}

tree::TerminalNode* IronParser::FunctionCallArgContext::IDENTIFIER(size_t i) {
  return getToken(IronParser::IDENTIFIER, i);
}

IronParser::DataFormatContext* IronParser::FunctionCallArgContext::dataFormat() {
  return getRuleContext<IronParser::DataFormatContext>(0);
}

IronParser::FunctionCallContext* IronParser::FunctionCallArgContext::functionCall() {
  return getRuleContext<IronParser::FunctionCallContext>(0);
}

IronParser::ArrowFunctionInlineContext* IronParser::FunctionCallArgContext::arrowFunctionInline() {
  return getRuleContext<IronParser::ArrowFunctionInlineContext>(0);
}


size_t IronParser::FunctionCallArgContext::getRuleIndex() const {
  return IronParser::RuleFunctionCallArg;
}

void IronParser::FunctionCallArgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCallArg(this);
}

void IronParser::FunctionCallArgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCallArg(this);
}

IronParser::FunctionCallArgContext* IronParser::functionCallArg() {
  FunctionCallArgContext *_localctx = _tracker.createInstance<FunctionCallArgContext>(_ctx, getState());
  enterRule(_localctx, 64, IronParser::RuleFunctionCallArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(355);
    antlrcpp::downCast<FunctionCallArgContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(356);
    match(IronParser::COLON);
    setState(361);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      setState(357);
      dataFormat();
      break;
    }

    case 2: {
      setState(358);
      antlrcpp::downCast<FunctionCallArgContext *>(_localctx)->anotherVarName = match(IronParser::IDENTIFIER);
      break;
    }

    case 3: {
      setState(359);
      functionCall();
      break;
    }

    case 4: {
      setState(360);
      arrowFunctionInline();
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

std::vector<tree::TerminalNode *> IronParser::VarDeclarationContext::IDENTIFIER() {
  return getTokens(IronParser::IDENTIFIER);
}

tree::TerminalNode* IronParser::VarDeclarationContext::IDENTIFIER(size_t i) {
  return getToken(IronParser::IDENTIFIER, i);
}

IronParser::VarTypesContext* IronParser::VarDeclarationContext::varTypes() {
  return getRuleContext<IronParser::VarTypesContext>(0);
}

tree::TerminalNode* IronParser::VarDeclarationContext::MUT() {
  return getToken(IronParser::MUT, 0);
}

IronParser::AssignmentContext* IronParser::VarDeclarationContext::assignment() {
  return getRuleContext<IronParser::AssignmentContext>(0);
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
  enterRule(_localctx, 66, IronParser::RuleVarDeclaration);
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
    setState(364);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::MUT) {
      setState(363);
      match(IronParser::MUT);
    }
    setState(366);
    match(IronParser::LET);
    setState(367);
    antlrcpp::downCast<VarDeclarationContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(368);
    match(IronParser::COLON);
    setState(371);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IronParser::FUNCTION:
      case IronParser::TYPE_INT:
      case IronParser::TYPE_CHAR:
      case IronParser::TYPE_FLOAT:
      case IronParser::TYPE_STRING:
      case IronParser::TYPE_BOOLEAN:
      case IronParser::TYPE_DOUBLE: {
        setState(369);
        varTypes();
        break;
      }

      case IronParser::IDENTIFIER: {
        setState(370);
        antlrcpp::downCast<VarDeclarationContext *>(_localctx)->anotherType = match(IronParser::IDENTIFIER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(374);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::EQ) {
      setState(373);
      assignment();
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

IronParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::AssignmentContext::EQ() {
  return getToken(IronParser::EQ, 0);
}

IronParser::ArrowFunctionInlineContext* IronParser::AssignmentContext::arrowFunctionInline() {
  return getRuleContext<IronParser::ArrowFunctionInlineContext>(0);
}

IronParser::DataFormatContext* IronParser::AssignmentContext::dataFormat() {
  return getRuleContext<IronParser::DataFormatContext>(0);
}

IronParser::StructInitContext* IronParser::AssignmentContext::structInit() {
  return getRuleContext<IronParser::StructInitContext>(0);
}

IronParser::FunctionCallContext* IronParser::AssignmentContext::functionCall() {
  return getRuleContext<IronParser::FunctionCallContext>(0);
}

IronParser::ExprContext* IronParser::AssignmentContext::expr() {
  return getRuleContext<IronParser::ExprContext>(0);
}

IronParser::BoolExprContext* IronParser::AssignmentContext::boolExpr() {
  return getRuleContext<IronParser::BoolExprContext>(0);
}

IronParser::VariableQualifiedNameContext* IronParser::AssignmentContext::variableQualifiedName() {
  return getRuleContext<IronParser::VariableQualifiedNameContext>(0);
}


size_t IronParser::AssignmentContext::getRuleIndex() const {
  return IronParser::RuleAssignment;
}

void IronParser::AssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignment(this);
}

void IronParser::AssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignment(this);
}

IronParser::AssignmentContext* IronParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 68, IronParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(376);
    match(IronParser::EQ);
    setState(384);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
    case 1: {
      setState(377);
      arrowFunctionInline();
      break;
    }

    case 2: {
      setState(378);
      antlrcpp::downCast<AssignmentContext *>(_localctx)->anotherVarName = variableQualifiedName();
      break;
    }

    case 3: {
      setState(379);
      dataFormat();
      break;
    }

    case 4: {
      setState(380);
      structInit();
      break;
    }

    case 5: {
      setState(381);
      functionCall();
      break;
    }

    case 6: {
      setState(382);
      expr(0);
      break;
    }

    case 7: {
      setState(383);
      boolExpr(0);
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

//----------------- StructInitContext ------------------------------------------------------------------

IronParser::StructInitContext::StructInitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::StructInitContext::L_CURLY() {
  return getToken(IronParser::L_CURLY, 0);
}

tree::TerminalNode* IronParser::StructInitContext::R_CURLY() {
  return getToken(IronParser::R_CURLY, 0);
}

std::vector<IronParser::StructInitBodyContext *> IronParser::StructInitContext::structInitBody() {
  return getRuleContexts<IronParser::StructInitBodyContext>();
}

IronParser::StructInitBodyContext* IronParser::StructInitContext::structInitBody(size_t i) {
  return getRuleContext<IronParser::StructInitBodyContext>(i);
}

tree::TerminalNode* IronParser::StructInitContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

std::vector<tree::TerminalNode *> IronParser::StructInitContext::COMMA() {
  return getTokens(IronParser::COMMA);
}

tree::TerminalNode* IronParser::StructInitContext::COMMA(size_t i) {
  return getToken(IronParser::COMMA, i);
}


size_t IronParser::StructInitContext::getRuleIndex() const {
  return IronParser::RuleStructInit;
}

void IronParser::StructInitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructInit(this);
}

void IronParser::StructInitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructInit(this);
}

IronParser::StructInitContext* IronParser::structInit() {
  StructInitContext *_localctx = _tracker.createInstance<StructInitContext>(_ctx, getState());
  enterRule(_localctx, 70, IronParser::RuleStructInit);
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
    setState(387);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::IDENTIFIER) {
      setState(386);
      antlrcpp::downCast<StructInitContext *>(_localctx)->structName = match(IronParser::IDENTIFIER);
    }
    setState(389);
    match(IronParser::L_CURLY);
    setState(398);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::IDENTIFIER) {
      setState(390);
      structInitBody();
      setState(395);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == IronParser::COMMA) {
        setState(391);
        match(IronParser::COMMA);
        setState(392);
        structInitBody();
        setState(397);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(400);
    match(IronParser::R_CURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructInitBodyContext ------------------------------------------------------------------

IronParser::StructInitBodyContext::StructInitBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::StructInitBodyContext::COLON() {
  return getToken(IronParser::COLON, 0);
}

std::vector<tree::TerminalNode *> IronParser::StructInitBodyContext::IDENTIFIER() {
  return getTokens(IronParser::IDENTIFIER);
}

tree::TerminalNode* IronParser::StructInitBodyContext::IDENTIFIER(size_t i) {
  return getToken(IronParser::IDENTIFIER, i);
}

IronParser::DataFormatContext* IronParser::StructInitBodyContext::dataFormat() {
  return getRuleContext<IronParser::DataFormatContext>(0);
}

IronParser::StructInitContext* IronParser::StructInitBodyContext::structInit() {
  return getRuleContext<IronParser::StructInitContext>(0);
}

IronParser::FunctionCallContext* IronParser::StructInitBodyContext::functionCall() {
  return getRuleContext<IronParser::FunctionCallContext>(0);
}

IronParser::ArrowFunctionInlineContext* IronParser::StructInitBodyContext::arrowFunctionInline() {
  return getRuleContext<IronParser::ArrowFunctionInlineContext>(0);
}


size_t IronParser::StructInitBodyContext::getRuleIndex() const {
  return IronParser::RuleStructInitBody;
}

void IronParser::StructInitBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructInitBody(this);
}

void IronParser::StructInitBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructInitBody(this);
}

IronParser::StructInitBodyContext* IronParser::structInitBody() {
  StructInitBodyContext *_localctx = _tracker.createInstance<StructInitBodyContext>(_ctx, getState());
  enterRule(_localctx, 72, IronParser::RuleStructInitBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(402);
    antlrcpp::downCast<StructInitBodyContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(403);
    match(IronParser::COLON);
    setState(409);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      setState(404);
      dataFormat();
      break;
    }

    case 2: {
      setState(405);
      antlrcpp::downCast<StructInitBodyContext *>(_localctx)->anotherVarName = match(IronParser::IDENTIFIER);
      break;
    }

    case 3: {
      setState(406);
      structInit();
      break;
    }

    case 4: {
      setState(407);
      functionCall();
      break;
    }

    case 5: {
      setState(408);
      arrowFunctionInline();
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

//----------------- VariableQualifiedNameContext ------------------------------------------------------------------

IronParser::VariableQualifiedNameContext::VariableQualifiedNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> IronParser::VariableQualifiedNameContext::IDENTIFIER() {
  return getTokens(IronParser::IDENTIFIER);
}

tree::TerminalNode* IronParser::VariableQualifiedNameContext::IDENTIFIER(size_t i) {
  return getToken(IronParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> IronParser::VariableQualifiedNameContext::DOT() {
  return getTokens(IronParser::DOT);
}

tree::TerminalNode* IronParser::VariableQualifiedNameContext::DOT(size_t i) {
  return getToken(IronParser::DOT, i);
}


size_t IronParser::VariableQualifiedNameContext::getRuleIndex() const {
  return IronParser::RuleVariableQualifiedName;
}

void IronParser::VariableQualifiedNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableQualifiedName(this);
}

void IronParser::VariableQualifiedNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableQualifiedName(this);
}

IronParser::VariableQualifiedNameContext* IronParser::variableQualifiedName() {
  VariableQualifiedNameContext *_localctx = _tracker.createInstance<VariableQualifiedNameContext>(_ctx, getState());
  enterRule(_localctx, 74, IronParser::RuleVariableQualifiedName);
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
    setState(411);
    antlrcpp::downCast<VariableQualifiedNameContext *>(_localctx)->base = match(IronParser::IDENTIFIER);
    setState(416);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::DOT) {
      setState(412);
      match(IronParser::DOT);
      setState(413);
      antlrcpp::downCast<VariableQualifiedNameContext *>(_localctx)->identifierToken = match(IronParser::IDENTIFIER);
      antlrcpp::downCast<VariableQualifiedNameContext *>(_localctx)->rest.push_back(antlrcpp::downCast<VariableQualifiedNameContext *>(_localctx)->identifierToken);
      setState(418);
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

//----------------- VarAssignmentContext ------------------------------------------------------------------

IronParser::VarAssignmentContext::VarAssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::VarAssignmentContext::EQ() {
  return getToken(IronParser::EQ, 0);
}

IronParser::VariableQualifiedNameContext* IronParser::VarAssignmentContext::variableQualifiedName() {
  return getRuleContext<IronParser::VariableQualifiedNameContext>(0);
}

IronParser::ArrowFunctionInlineContext* IronParser::VarAssignmentContext::arrowFunctionInline() {
  return getRuleContext<IronParser::ArrowFunctionInlineContext>(0);
}

IronParser::FunctionCallContext* IronParser::VarAssignmentContext::functionCall() {
  return getRuleContext<IronParser::FunctionCallContext>(0);
}

IronParser::StructInitContext* IronParser::VarAssignmentContext::structInit() {
  return getRuleContext<IronParser::StructInitContext>(0);
}

IronParser::DataFormatContext* IronParser::VarAssignmentContext::dataFormat() {
  return getRuleContext<IronParser::DataFormatContext>(0);
}

IronParser::ExprContext* IronParser::VarAssignmentContext::expr() {
  return getRuleContext<IronParser::ExprContext>(0);
}

tree::TerminalNode* IronParser::VarAssignmentContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}


size_t IronParser::VarAssignmentContext::getRuleIndex() const {
  return IronParser::RuleVarAssignment;
}

void IronParser::VarAssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarAssignment(this);
}

void IronParser::VarAssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarAssignment(this);
}

IronParser::VarAssignmentContext* IronParser::varAssignment() {
  VarAssignmentContext *_localctx = _tracker.createInstance<VarAssignmentContext>(_ctx, getState());
  enterRule(_localctx, 76, IronParser::RuleVarAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(419);
    antlrcpp::downCast<VarAssignmentContext *>(_localctx)->varName = variableQualifiedName();
    setState(420);
    match(IronParser::EQ);
    setState(427);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx)) {
    case 1: {
      setState(421);
      arrowFunctionInline();
      break;
    }

    case 2: {
      setState(422);
      functionCall();
      break;
    }

    case 3: {
      setState(423);
      structInit();
      break;
    }

    case 4: {
      setState(424);
      antlrcpp::downCast<VarAssignmentContext *>(_localctx)->anotherVarName = match(IronParser::IDENTIFIER);
      break;
    }

    case 5: {
      setState(425);
      dataFormat();
      break;
    }

    case 6: {
      setState(426);
      expr(0);
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

//----------------- IfBlockContext ------------------------------------------------------------------

IronParser::IfBlockContext::IfBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::IfBlockContext::L_CURLY() {
  return getToken(IronParser::L_CURLY, 0);
}

tree::TerminalNode* IronParser::IfBlockContext::R_CURLY() {
  return getToken(IronParser::R_CURLY, 0);
}

IronParser::StatementListContext* IronParser::IfBlockContext::statementList() {
  return getRuleContext<IronParser::StatementListContext>(0);
}


size_t IronParser::IfBlockContext::getRuleIndex() const {
  return IronParser::RuleIfBlock;
}

void IronParser::IfBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfBlock(this);
}

void IronParser::IfBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfBlock(this);
}

IronParser::IfBlockContext* IronParser::ifBlock() {
  IfBlockContext *_localctx = _tracker.createInstance<IfBlockContext>(_ctx, getState());
  enterRule(_localctx, 78, IronParser::RuleIfBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(429);
    match(IronParser::L_CURLY);
    setState(431);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
    case 1: {
      setState(430);
      statementList();
      break;
    }

    default:
      break;
    }
    setState(433);
    match(IronParser::R_CURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

IronParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::IfStatementContext::IF() {
  return getToken(IronParser::IF, 0);
}

tree::TerminalNode* IronParser::IfStatementContext::L_PAREN() {
  return getToken(IronParser::L_PAREN, 0);
}

IronParser::BoolExprContext* IronParser::IfStatementContext::boolExpr() {
  return getRuleContext<IronParser::BoolExprContext>(0);
}

tree::TerminalNode* IronParser::IfStatementContext::R_PAREN() {
  return getToken(IronParser::R_PAREN, 0);
}

IronParser::IfBlockContext* IronParser::IfStatementContext::ifBlock() {
  return getRuleContext<IronParser::IfBlockContext>(0);
}

tree::TerminalNode* IronParser::IfStatementContext::ELSE() {
  return getToken(IronParser::ELSE, 0);
}

IronParser::ElseStatementContext* IronParser::IfStatementContext::elseStatement() {
  return getRuleContext<IronParser::ElseStatementContext>(0);
}


size_t IronParser::IfStatementContext::getRuleIndex() const {
  return IronParser::RuleIfStatement;
}

void IronParser::IfStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStatement(this);
}

void IronParser::IfStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStatement(this);
}

IronParser::IfStatementContext* IronParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 80, IronParser::RuleIfStatement);
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
    setState(435);
    match(IronParser::IF);
    setState(436);
    match(IronParser::L_PAREN);
    setState(437);
    boolExpr(0);
    setState(438);
    match(IronParser::R_PAREN);
    setState(439);
    ifBlock();
    setState(442);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::ELSE) {
      setState(440);
      match(IronParser::ELSE);
      setState(441);
      elseStatement();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElseStatementContext ------------------------------------------------------------------

IronParser::ElseStatementContext::ElseStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IronParser::IfStatementContext* IronParser::ElseStatementContext::ifStatement() {
  return getRuleContext<IronParser::IfStatementContext>(0);
}

IronParser::IfBlockContext* IronParser::ElseStatementContext::ifBlock() {
  return getRuleContext<IronParser::IfBlockContext>(0);
}


size_t IronParser::ElseStatementContext::getRuleIndex() const {
  return IronParser::RuleElseStatement;
}

void IronParser::ElseStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElseStatement(this);
}

void IronParser::ElseStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElseStatement(this);
}

IronParser::ElseStatementContext* IronParser::elseStatement() {
  ElseStatementContext *_localctx = _tracker.createInstance<ElseStatementContext>(_ctx, getState());
  enterRule(_localctx, 82, IronParser::RuleElseStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(446);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IronParser::IF: {
        enterOuterAlt(_localctx, 1);
        setState(444);
        ifStatement();
        break;
      }

      case IronParser::L_CURLY: {
        enterOuterAlt(_localctx, 2);
        setState(445);
        ifBlock();
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

//----------------- BoolExprContext ------------------------------------------------------------------

IronParser::BoolExprContext::BoolExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::BoolExprContext::L_PAREN() {
  return getToken(IronParser::L_PAREN, 0);
}

std::vector<IronParser::BoolExprContext *> IronParser::BoolExprContext::boolExpr() {
  return getRuleContexts<IronParser::BoolExprContext>();
}

IronParser::BoolExprContext* IronParser::BoolExprContext::boolExpr(size_t i) {
  return getRuleContext<IronParser::BoolExprContext>(i);
}

tree::TerminalNode* IronParser::BoolExprContext::R_PAREN() {
  return getToken(IronParser::R_PAREN, 0);
}

tree::TerminalNode* IronParser::BoolExprContext::NOT() {
  return getToken(IronParser::NOT, 0);
}

tree::TerminalNode* IronParser::BoolExprContext::BOOLEAN_VALUE() {
  return getToken(IronParser::BOOLEAN_VALUE, 0);
}

IronParser::NumberContext* IronParser::BoolExprContext::number() {
  return getRuleContext<IronParser::NumberContext>(0);
}

tree::TerminalNode* IronParser::BoolExprContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

IronParser::FunctionCallContext* IronParser::BoolExprContext::functionCall() {
  return getRuleContext<IronParser::FunctionCallContext>(0);
}

IronParser::ExprContext* IronParser::BoolExprContext::expr() {
  return getRuleContext<IronParser::ExprContext>(0);
}

tree::TerminalNode* IronParser::BoolExprContext::EQEQ() {
  return getToken(IronParser::EQEQ, 0);
}

tree::TerminalNode* IronParser::BoolExprContext::NEQ() {
  return getToken(IronParser::NEQ, 0);
}

tree::TerminalNode* IronParser::BoolExprContext::LT() {
  return getToken(IronParser::LT, 0);
}

tree::TerminalNode* IronParser::BoolExprContext::LTE() {
  return getToken(IronParser::LTE, 0);
}

tree::TerminalNode* IronParser::BoolExprContext::GT() {
  return getToken(IronParser::GT, 0);
}

tree::TerminalNode* IronParser::BoolExprContext::GTE() {
  return getToken(IronParser::GTE, 0);
}

tree::TerminalNode* IronParser::BoolExprContext::AND() {
  return getToken(IronParser::AND, 0);
}

tree::TerminalNode* IronParser::BoolExprContext::OR() {
  return getToken(IronParser::OR, 0);
}


size_t IronParser::BoolExprContext::getRuleIndex() const {
  return IronParser::RuleBoolExpr;
}

void IronParser::BoolExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolExpr(this);
}

void IronParser::BoolExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolExpr(this);
}


IronParser::BoolExprContext* IronParser::boolExpr() {
   return boolExpr(0);
}

IronParser::BoolExprContext* IronParser::boolExpr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  IronParser::BoolExprContext *_localctx = _tracker.createInstance<BoolExprContext>(_ctx, parentState);
  IronParser::BoolExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 84;
  enterRecursionRule(_localctx, 84, IronParser::RuleBoolExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(460);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
    case 1: {
      setState(449);
      match(IronParser::L_PAREN);
      setState(450);
      boolExpr(0);
      setState(451);
      match(IronParser::R_PAREN);
      break;
    }

    case 2: {
      setState(453);
      antlrcpp::downCast<BoolExprContext *>(_localctx)->not_ = match(IronParser::NOT);
      setState(454);
      boolExpr(6);
      break;
    }

    case 3: {
      setState(455);
      antlrcpp::downCast<BoolExprContext *>(_localctx)->booleanValue = match(IronParser::BOOLEAN_VALUE);
      break;
    }

    case 4: {
      setState(456);
      number();
      break;
    }

    case 5: {
      setState(457);
      antlrcpp::downCast<BoolExprContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
      break;
    }

    case 6: {
      setState(458);
      functionCall();
      break;
    }

    case 7: {
      setState(459);
      expr(0);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(473);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(471);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BoolExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleBoolExpr);
          setState(462);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(463);
          antlrcpp::downCast<BoolExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 8455716864) != 0))) {
            antlrcpp::downCast<BoolExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(464);
          antlrcpp::downCast<BoolExprContext *>(_localctx)->right = boolExpr(10);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BoolExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleBoolExpr);
          setState(465);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(466);
          antlrcpp::downCast<BoolExprContext *>(_localctx)->op = match(IronParser::AND);
          setState(467);
          antlrcpp::downCast<BoolExprContext *>(_localctx)->right = boolExpr(9);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BoolExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleBoolExpr);
          setState(468);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(469);
          antlrcpp::downCast<BoolExprContext *>(_localctx)->op = match(IronParser::OR);
          setState(470);
          antlrcpp::downCast<BoolExprContext *>(_localctx)->right = boolExpr(8);
          break;
        }

        default:
          break;
        } 
      }
      setState(475);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

IronParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IronParser::NumberContext* IronParser::ExprContext::number() {
  return getRuleContext<IronParser::NumberContext>(0);
}

IronParser::FunctionCallContext* IronParser::ExprContext::functionCall() {
  return getRuleContext<IronParser::FunctionCallContext>(0);
}

tree::TerminalNode* IronParser::ExprContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
}

tree::TerminalNode* IronParser::ExprContext::L_PAREN() {
  return getToken(IronParser::L_PAREN, 0);
}

std::vector<IronParser::ExprContext *> IronParser::ExprContext::expr() {
  return getRuleContexts<IronParser::ExprContext>();
}

IronParser::ExprContext* IronParser::ExprContext::expr(size_t i) {
  return getRuleContext<IronParser::ExprContext>(i);
}

tree::TerminalNode* IronParser::ExprContext::R_PAREN() {
  return getToken(IronParser::R_PAREN, 0);
}

tree::TerminalNode* IronParser::ExprContext::STAR() {
  return getToken(IronParser::STAR, 0);
}

tree::TerminalNode* IronParser::ExprContext::DIV() {
  return getToken(IronParser::DIV, 0);
}

tree::TerminalNode* IronParser::ExprContext::PLUS() {
  return getToken(IronParser::PLUS, 0);
}

tree::TerminalNode* IronParser::ExprContext::MINUS() {
  return getToken(IronParser::MINUS, 0);
}


size_t IronParser::ExprContext::getRuleIndex() const {
  return IronParser::RuleExpr;
}

void IronParser::ExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr(this);
}

void IronParser::ExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr(this);
}


IronParser::ExprContext* IronParser::expr() {
   return expr(0);
}

IronParser::ExprContext* IronParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  IronParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  IronParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 86;
  enterRecursionRule(_localctx, 86, IronParser::RuleExpr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(484);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
    case 1: {
      setState(477);
      number();
      break;
    }

    case 2: {
      setState(478);
      functionCall();
      break;
    }

    case 3: {
      setState(479);
      antlrcpp::downCast<ExprContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
      break;
    }

    case 4: {
      setState(480);
      match(IronParser::L_PAREN);
      setState(481);
      expr(0);
      setState(482);
      match(IronParser::R_PAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(501);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(499);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(486);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(490);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case IronParser::STAR: {
              setState(487);
              antlrcpp::downCast<ExprContext *>(_localctx)->mult = match(IronParser::STAR);
              break;
            }

            case IronParser::T__4: {
              setState(488);
              antlrcpp::downCast<ExprContext *>(_localctx)->mod = match(IronParser::T__4);
              break;
            }

            case IronParser::DIV: {
              setState(489);
              antlrcpp::downCast<ExprContext *>(_localctx)->div = match(IronParser::DIV);
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(492);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(7);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(493);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(496);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case IronParser::PLUS: {
              setState(494);
              antlrcpp::downCast<ExprContext *>(_localctx)->plus = match(IronParser::PLUS);
              break;
            }

            case IronParser::MINUS: {
              setState(495);
              antlrcpp::downCast<ExprContext *>(_localctx)->minus = match(IronParser::MINUS);
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(498);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(6);
          break;
        }

        default:
          break;
        } 
      }
      setState(503);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx);
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

IronParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::NumberContext::REAL_NUMBER() {
  return getToken(IronParser::REAL_NUMBER, 0);
}

tree::TerminalNode* IronParser::NumberContext::INT_NUMBER() {
  return getToken(IronParser::INT_NUMBER, 0);
}


size_t IronParser::NumberContext::getRuleIndex() const {
  return IronParser::RuleNumber;
}

void IronParser::NumberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumber(this);
}

void IronParser::NumberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IronListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumber(this);
}

IronParser::NumberContext* IronParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 88, IronParser::RuleNumber);
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
    setState(504);
    _la = _input->LA(1);
    if (!(_la == IronParser::REAL_NUMBER

    || _la == IronParser::INT_NUMBER)) {
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
  enterRule(_localctx, 90, IronParser::RuleDataFormat);
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
    setState(506);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1080863910568919040) != 0))) {
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

tree::TerminalNode* IronParser::VarTypesContext::FUNCTION() {
  return getToken(IronParser::FUNCTION, 0);
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
  enterRule(_localctx, 92, IronParser::RuleVarTypes);
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
    setState(508);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1108324900667392) != 0))) {
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

bool IronParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 42: return boolExprSempred(antlrcpp::downCast<BoolExprContext *>(context), predicateIndex);
    case 43: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool IronParser::boolExprSempred(BoolExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 9);
    case 1: return precpred(_ctx, 8);
    case 2: return precpred(_ctx, 7);

  default:
    break;
  }
  return true;
}

bool IronParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 6);
    case 4: return precpred(_ctx, 5);

  default:
    break;
  }
  return true;
}

void IronParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  ironParserInitialize();
#else
  ::antlr4::internal::call_once(ironParserOnceFlag, ironParserInitialize);
#endif
}
