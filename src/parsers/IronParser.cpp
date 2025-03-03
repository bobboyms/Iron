
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
      "continueStatement", "returnStatement", "whileStatement", "repeatStatement", 
      "forStatement", "intervals", "formatStatement", "formatArguments", 
      "formatArgument", "externBlock", "externFunctionDeclaration", "externFunctionArgs", 
      "externFunctionArg", "cTypes", "functionDeclaration", "arrowFunctionInline", 
      "functionSignature", "functionReturnType", "functionArgs", "functionArg", 
      "fnsignature", "functionCall", "functionCallArgs", "functionCallArg", 
      "varDeclaration", "assignment", "varAssignment", "ifBlock", "ifStatement", 
      "elseStatement", "boolExpr", "expr", "number", "dataFormat", "varTypes"
    },
    std::vector<std::string>{
      "", "'..'", "'f'('", "'extern'", "'...'", "'%'", "", "", "','", "':'", 
      "'='", "';'", "'.'", "'*'", "'{'", "'}'", "'('", "')'", "'+'", "'-'", 
      "'/'", "'['", "']'", "'->'", "'and'", "'or'", "'not'", "'=='", "'!='", 
      "'<'", "'<='", "'>'", "'>='", "'if'", "'fn'", "'let'", "'mut'", "'else'", 
      "'public'", "'import'", "'return'", "'in'", "'for'", "'while'", "'int'", 
      "'char'", "'float'", "'string'", "'boolean'", "'double'", "'void'", 
      "'repeat'", "'continue'", "'break'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "LINE_COMMENT", "BLOCK_COMMENT", "COMMA", 
      "COLON", "EQ", "SEMICOLON", "DOT", "STAR", "L_CURLY", "R_CURLY", "L_PAREN", 
      "R_PAREN", "PLUS", "MINUS", "DIV", "L_BRACKET", "R_BRACKET", "ARROW", 
      "AND", "OR", "NOT", "EQEQ", "NEQ", "LT", "LTE", "GT", "GTE", "IF", 
      "FUNCTION", "LET", "MUT", "ELSE", "PUBLIC", "IMPORT", "RETURN", "IN", 
      "FOR", "WHILE", "TYPE_INT", "TYPE_CHAR", "TYPE_FLOAT", "TYPE_STRING", 
      "TYPE_BOOLEAN", "TYPE_DOUBLE", "TYPE_VOID", "REPEAT", "CONTINUE", 
      "BREAK", "REAL_NUMBER", "INT_NUMBER", "BOOLEAN_VALUE", "STRING_LITERAL", 
      "IDENTIFIER", "NEWLINE", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,60,417,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,1,0,5,0,82,8,0,10,0,12,0,85,
  	9,0,1,0,3,0,88,8,0,1,0,5,0,91,8,0,10,0,12,0,94,9,0,1,0,1,0,1,1,1,1,1,
  	1,1,1,3,1,102,8,1,1,2,1,2,1,2,5,2,107,8,2,10,2,12,2,110,9,2,1,3,1,3,1,
  	3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,5,3,123,8,3,10,3,12,3,126,9,3,1,4,1,
  	4,1,5,1,5,1,6,1,6,1,6,1,6,1,6,3,6,137,8,6,1,7,1,7,1,7,1,7,1,7,1,7,1,8,
  	1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,10,1,10,3,10,
  	162,8,10,1,10,1,10,1,10,3,10,167,8,10,1,11,1,11,1,11,1,11,1,11,1,11,1,
  	12,1,12,1,12,5,12,178,8,12,10,12,12,12,181,9,12,1,13,1,13,1,13,1,13,1,
  	13,3,13,188,8,13,1,14,1,14,1,14,1,14,4,14,194,8,14,11,14,12,14,195,5,
  	14,198,8,14,10,14,12,14,201,9,14,1,14,1,14,1,15,1,15,1,15,1,15,3,15,209,
  	8,15,1,15,1,15,3,15,213,8,15,1,15,1,15,3,15,217,8,15,1,16,1,16,1,16,5,
  	16,222,8,16,10,16,12,16,225,9,16,1,17,1,17,1,17,3,17,230,8,17,1,17,1,
  	17,1,18,1,18,1,19,3,19,237,8,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,
  	20,1,20,1,20,1,20,1,20,1,20,1,20,3,20,253,8,20,1,21,1,21,3,21,257,8,21,
  	1,21,1,21,3,21,261,8,21,1,22,1,22,1,22,1,23,1,23,1,23,5,23,269,8,23,10,
  	23,12,23,272,9,23,1,24,1,24,1,24,1,24,3,24,278,8,24,1,24,3,24,281,8,24,
  	1,25,1,25,1,25,1,26,1,26,1,26,3,26,289,8,26,1,26,1,26,1,27,1,27,1,27,
  	5,27,296,8,27,10,27,12,27,299,9,27,1,28,1,28,1,28,1,28,1,28,1,28,3,28,
  	307,8,28,1,29,3,29,310,8,29,1,29,1,29,1,29,1,29,1,29,3,29,317,8,29,1,
  	30,1,30,1,30,1,30,1,30,1,30,1,30,3,30,326,8,30,1,31,1,31,1,31,1,31,1,
  	31,1,31,3,31,334,8,31,1,32,1,32,3,32,338,8,32,1,32,1,32,1,33,1,33,1,33,
  	1,33,1,33,1,33,1,33,3,33,349,8,33,1,34,1,34,3,34,353,8,34,1,35,1,35,1,
  	35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,3,35,367,8,35,1,35,1,
  	35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,5,35,378,8,35,10,35,12,35,381,9,
  	35,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,3,36,391,8,36,1,36,1,36,1,
  	36,1,36,3,36,397,8,36,1,36,1,36,1,36,1,36,3,36,403,8,36,1,36,5,36,406,
  	8,36,10,36,12,36,409,9,36,1,37,1,37,1,38,1,38,1,39,1,39,1,39,0,2,70,72,
  	40,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,
  	48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,0,5,2,0,44,46,48,50,1,
  	0,27,32,1,0,54,55,1,0,54,57,2,0,34,34,44,49,452,0,83,1,0,0,0,2,97,1,0,
  	0,0,4,103,1,0,0,0,6,124,1,0,0,0,8,127,1,0,0,0,10,129,1,0,0,0,12,131,1,
  	0,0,0,14,138,1,0,0,0,16,144,1,0,0,0,18,151,1,0,0,0,20,161,1,0,0,0,22,
  	168,1,0,0,0,24,174,1,0,0,0,26,187,1,0,0,0,28,189,1,0,0,0,30,204,1,0,0,
  	0,32,218,1,0,0,0,34,226,1,0,0,0,36,233,1,0,0,0,38,236,1,0,0,0,40,245,
  	1,0,0,0,42,254,1,0,0,0,44,262,1,0,0,0,46,265,1,0,0,0,48,273,1,0,0,0,50,
  	282,1,0,0,0,52,285,1,0,0,0,54,292,1,0,0,0,56,300,1,0,0,0,58,309,1,0,0,
  	0,60,318,1,0,0,0,62,327,1,0,0,0,64,335,1,0,0,0,66,341,1,0,0,0,68,352,
  	1,0,0,0,70,366,1,0,0,0,72,390,1,0,0,0,74,410,1,0,0,0,76,412,1,0,0,0,78,
  	414,1,0,0,0,80,82,3,2,1,0,81,80,1,0,0,0,82,85,1,0,0,0,83,81,1,0,0,0,83,
  	84,1,0,0,0,84,87,1,0,0,0,85,83,1,0,0,0,86,88,3,28,14,0,87,86,1,0,0,0,
  	87,88,1,0,0,0,88,92,1,0,0,0,89,91,3,38,19,0,90,89,1,0,0,0,91,94,1,0,0,
  	0,92,90,1,0,0,0,92,93,1,0,0,0,93,95,1,0,0,0,94,92,1,0,0,0,95,96,5,0,0,
  	1,96,1,1,0,0,0,97,98,5,39,0,0,98,101,3,4,2,0,99,100,5,12,0,0,100,102,
  	5,13,0,0,101,99,1,0,0,0,101,102,1,0,0,0,102,3,1,0,0,0,103,108,5,58,0,
  	0,104,105,5,12,0,0,105,107,5,58,0,0,106,104,1,0,0,0,107,110,1,0,0,0,108,
  	106,1,0,0,0,108,109,1,0,0,0,109,5,1,0,0,0,110,108,1,0,0,0,111,123,3,10,
  	5,0,112,123,3,8,4,0,113,123,3,58,29,0,114,123,3,62,31,0,115,123,3,52,
  	26,0,116,123,3,72,36,0,117,123,3,66,33,0,118,123,3,14,7,0,119,123,3,16,
  	8,0,120,123,3,18,9,0,121,123,3,12,6,0,122,111,1,0,0,0,122,112,1,0,0,0,
  	122,113,1,0,0,0,122,114,1,0,0,0,122,115,1,0,0,0,122,116,1,0,0,0,122,117,
  	1,0,0,0,122,118,1,0,0,0,122,119,1,0,0,0,122,120,1,0,0,0,122,121,1,0,0,
  	0,123,126,1,0,0,0,124,122,1,0,0,0,124,125,1,0,0,0,125,7,1,0,0,0,126,124,
  	1,0,0,0,127,128,5,53,0,0,128,9,1,0,0,0,129,130,5,52,0,0,130,11,1,0,0,
  	0,131,136,5,40,0,0,132,137,3,76,38,0,133,137,5,58,0,0,134,137,3,52,26,
  	0,135,137,3,72,36,0,136,132,1,0,0,0,136,133,1,0,0,0,136,134,1,0,0,0,136,
  	135,1,0,0,0,136,137,1,0,0,0,137,13,1,0,0,0,138,139,5,43,0,0,139,140,3,
  	70,35,0,140,141,5,14,0,0,141,142,3,6,3,0,142,143,5,15,0,0,143,15,1,0,
  	0,0,144,145,5,51,0,0,145,146,5,14,0,0,146,147,3,6,3,0,147,148,5,15,0,
  	0,148,149,5,43,0,0,149,150,3,70,35,0,150,17,1,0,0,0,151,152,5,42,0,0,
  	152,153,5,58,0,0,153,154,5,41,0,0,154,155,3,20,10,0,155,156,5,14,0,0,
  	156,157,3,6,3,0,157,158,5,15,0,0,158,19,1,0,0,0,159,162,5,55,0,0,160,
  	162,5,58,0,0,161,159,1,0,0,0,161,160,1,0,0,0,162,163,1,0,0,0,163,166,
  	5,1,0,0,164,167,5,55,0,0,165,167,5,58,0,0,166,164,1,0,0,0,166,165,1,0,
  	0,0,167,21,1,0,0,0,168,169,5,2,0,0,169,170,5,57,0,0,170,171,5,8,0,0,171,
  	172,3,24,12,0,172,173,5,17,0,0,173,23,1,0,0,0,174,179,3,26,13,0,175,176,
  	5,8,0,0,176,178,3,26,13,0,177,175,1,0,0,0,178,181,1,0,0,0,179,177,1,0,
  	0,0,179,180,1,0,0,0,180,25,1,0,0,0,181,179,1,0,0,0,182,188,3,76,38,0,
  	183,188,5,58,0,0,184,188,3,52,26,0,185,188,3,72,36,0,186,188,5,57,0,0,
  	187,182,1,0,0,0,187,183,1,0,0,0,187,184,1,0,0,0,187,185,1,0,0,0,187,186,
  	1,0,0,0,188,27,1,0,0,0,189,190,5,3,0,0,190,191,5,58,0,0,191,199,5,14,
  	0,0,192,194,3,30,15,0,193,192,1,0,0,0,194,195,1,0,0,0,195,193,1,0,0,0,
  	195,196,1,0,0,0,196,198,1,0,0,0,197,193,1,0,0,0,198,201,1,0,0,0,199,197,
  	1,0,0,0,199,200,1,0,0,0,200,202,1,0,0,0,201,199,1,0,0,0,202,203,5,15,
  	0,0,203,29,1,0,0,0,204,205,5,34,0,0,205,206,5,58,0,0,206,208,5,16,0,0,
  	207,209,3,32,16,0,208,207,1,0,0,0,208,209,1,0,0,0,209,212,1,0,0,0,210,
  	211,5,8,0,0,211,213,5,4,0,0,212,210,1,0,0,0,212,213,1,0,0,0,213,214,1,
  	0,0,0,214,216,5,17,0,0,215,217,3,44,22,0,216,215,1,0,0,0,216,217,1,0,
  	0,0,217,31,1,0,0,0,218,223,3,34,17,0,219,220,5,8,0,0,220,222,3,34,17,
  	0,221,219,1,0,0,0,222,225,1,0,0,0,223,221,1,0,0,0,223,224,1,0,0,0,224,
  	33,1,0,0,0,225,223,1,0,0,0,226,227,5,58,0,0,227,229,5,9,0,0,228,230,5,
  	13,0,0,229,228,1,0,0,0,229,230,1,0,0,0,230,231,1,0,0,0,231,232,3,36,18,
  	0,232,35,1,0,0,0,233,234,7,0,0,0,234,37,1,0,0,0,235,237,5,38,0,0,236,
  	235,1,0,0,0,236,237,1,0,0,0,237,238,1,0,0,0,238,239,5,34,0,0,239,240,
  	5,58,0,0,240,241,3,42,21,0,241,242,5,14,0,0,242,243,3,6,3,0,243,244,5,
  	15,0,0,244,39,1,0,0,0,245,246,3,42,21,0,246,252,5,23,0,0,247,253,3,72,
  	36,0,248,249,5,14,0,0,249,250,3,6,3,0,250,251,5,15,0,0,251,253,1,0,0,
  	0,252,247,1,0,0,0,252,248,1,0,0,0,253,41,1,0,0,0,254,256,5,16,0,0,255,
  	257,3,46,23,0,256,255,1,0,0,0,256,257,1,0,0,0,257,258,1,0,0,0,258,260,
  	5,17,0,0,259,261,3,44,22,0,260,259,1,0,0,0,260,261,1,0,0,0,261,43,1,0,
  	0,0,262,263,5,9,0,0,263,264,3,78,39,0,264,45,1,0,0,0,265,270,3,48,24,
  	0,266,267,5,8,0,0,267,269,3,48,24,0,268,266,1,0,0,0,269,272,1,0,0,0,270,
  	268,1,0,0,0,270,271,1,0,0,0,271,47,1,0,0,0,272,270,1,0,0,0,273,274,5,
  	58,0,0,274,277,5,9,0,0,275,278,3,50,25,0,276,278,3,78,39,0,277,275,1,
  	0,0,0,277,276,1,0,0,0,278,280,1,0,0,0,279,281,3,60,30,0,280,279,1,0,0,
  	0,280,281,1,0,0,0,281,49,1,0,0,0,282,283,5,34,0,0,283,284,3,42,21,0,284,
  	51,1,0,0,0,285,286,5,58,0,0,286,288,5,16,0,0,287,289,3,54,27,0,288,287,
  	1,0,0,0,288,289,1,0,0,0,289,290,1,0,0,0,290,291,5,17,0,0,291,53,1,0,0,
  	0,292,297,3,56,28,0,293,294,5,8,0,0,294,296,3,56,28,0,295,293,1,0,0,0,
  	296,299,1,0,0,0,297,295,1,0,0,0,297,298,1,0,0,0,298,55,1,0,0,0,299,297,
  	1,0,0,0,300,301,5,58,0,0,301,306,5,9,0,0,302,307,3,76,38,0,303,307,5,
  	58,0,0,304,307,3,52,26,0,305,307,3,40,20,0,306,302,1,0,0,0,306,303,1,
  	0,0,0,306,304,1,0,0,0,306,305,1,0,0,0,307,57,1,0,0,0,308,310,5,36,0,0,
  	309,308,1,0,0,0,309,310,1,0,0,0,310,311,1,0,0,0,311,312,5,35,0,0,312,
  	313,5,58,0,0,313,314,5,9,0,0,314,316,3,78,39,0,315,317,3,60,30,0,316,
  	315,1,0,0,0,316,317,1,0,0,0,317,59,1,0,0,0,318,325,5,10,0,0,319,326,3,
  	40,20,0,320,326,5,58,0,0,321,326,3,76,38,0,322,326,3,52,26,0,323,326,
  	3,72,36,0,324,326,3,70,35,0,325,319,1,0,0,0,325,320,1,0,0,0,325,321,1,
  	0,0,0,325,322,1,0,0,0,325,323,1,0,0,0,325,324,1,0,0,0,326,61,1,0,0,0,
  	327,328,5,58,0,0,328,333,5,10,0,0,329,334,3,40,20,0,330,334,5,58,0,0,
  	331,334,3,76,38,0,332,334,3,72,36,0,333,329,1,0,0,0,333,330,1,0,0,0,333,
  	331,1,0,0,0,333,332,1,0,0,0,334,63,1,0,0,0,335,337,5,14,0,0,336,338,3,
  	6,3,0,337,336,1,0,0,0,337,338,1,0,0,0,338,339,1,0,0,0,339,340,5,15,0,
  	0,340,65,1,0,0,0,341,342,5,33,0,0,342,343,5,16,0,0,343,344,3,70,35,0,
  	344,345,5,17,0,0,345,348,3,64,32,0,346,347,5,37,0,0,347,349,3,68,34,0,
  	348,346,1,0,0,0,348,349,1,0,0,0,349,67,1,0,0,0,350,353,3,66,33,0,351,
  	353,3,64,32,0,352,350,1,0,0,0,352,351,1,0,0,0,353,69,1,0,0,0,354,355,
  	6,35,-1,0,355,356,5,16,0,0,356,357,3,70,35,0,357,358,5,17,0,0,358,367,
  	1,0,0,0,359,360,5,26,0,0,360,367,3,70,35,6,361,367,5,56,0,0,362,367,3,
  	74,37,0,363,367,5,58,0,0,364,367,3,52,26,0,365,367,3,72,36,0,366,354,
  	1,0,0,0,366,359,1,0,0,0,366,361,1,0,0,0,366,362,1,0,0,0,366,363,1,0,0,
  	0,366,364,1,0,0,0,366,365,1,0,0,0,367,379,1,0,0,0,368,369,10,9,0,0,369,
  	370,7,1,0,0,370,378,3,70,35,10,371,372,10,8,0,0,372,373,5,24,0,0,373,
  	378,3,70,35,9,374,375,10,7,0,0,375,376,5,25,0,0,376,378,3,70,35,8,377,
  	368,1,0,0,0,377,371,1,0,0,0,377,374,1,0,0,0,378,381,1,0,0,0,379,377,1,
  	0,0,0,379,380,1,0,0,0,380,71,1,0,0,0,381,379,1,0,0,0,382,383,6,36,-1,
  	0,383,391,3,74,37,0,384,391,3,52,26,0,385,391,5,58,0,0,386,387,5,16,0,
  	0,387,388,3,72,36,0,388,389,5,17,0,0,389,391,1,0,0,0,390,382,1,0,0,0,
  	390,384,1,0,0,0,390,385,1,0,0,0,390,386,1,0,0,0,391,407,1,0,0,0,392,396,
  	10,6,0,0,393,397,5,13,0,0,394,397,5,5,0,0,395,397,5,20,0,0,396,393,1,
  	0,0,0,396,394,1,0,0,0,396,395,1,0,0,0,397,398,1,0,0,0,398,406,3,72,36,
  	7,399,402,10,5,0,0,400,403,5,18,0,0,401,403,5,19,0,0,402,400,1,0,0,0,
  	402,401,1,0,0,0,403,404,1,0,0,0,404,406,3,72,36,6,405,392,1,0,0,0,405,
  	399,1,0,0,0,406,409,1,0,0,0,407,405,1,0,0,0,407,408,1,0,0,0,408,73,1,
  	0,0,0,409,407,1,0,0,0,410,411,7,2,0,0,411,75,1,0,0,0,412,413,7,3,0,0,
  	413,77,1,0,0,0,414,415,7,4,0,0,415,79,1,0,0,0,44,83,87,92,101,108,122,
  	124,136,161,166,179,187,195,199,208,212,216,223,229,236,252,256,260,270,
  	277,280,288,297,306,309,316,325,333,337,348,352,366,377,379,390,396,402,
  	405,407
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
    setState(83);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::IMPORT) {
      setState(80);
      importStatement();
      setState(85);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(87);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::T__2) {
      setState(86);
      externBlock();
    }
    setState(92);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::FUNCTION

    || _la == IronParser::PUBLIC) {
      setState(89);
      functionDeclaration();
      setState(94);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(95);
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
    setState(97);
    match(IronParser::IMPORT);
    setState(98);
    qualifiedName();
    setState(101);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::DOT) {
      setState(99);
      match(IronParser::DOT);
      setState(100);
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
    setState(103);
    match(IronParser::IDENTIFIER);
    setState(108);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(104);
        match(IronParser::DOT);
        setState(105);
        match(IronParser::IDENTIFIER); 
      }
      setState(110);
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
    setState(124);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 358050575696330752) != 0)) {
      setState(122);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
      case 1: {
        setState(111);
        continueStatement();
        break;
      }

      case 2: {
        setState(112);
        breakStatement();
        break;
      }

      case 3: {
        setState(113);
        varDeclaration();
        break;
      }

      case 4: {
        setState(114);
        varAssignment();
        break;
      }

      case 5: {
        setState(115);
        functionCall();
        break;
      }

      case 6: {
        setState(116);
        expr(0);
        break;
      }

      case 7: {
        setState(117);
        ifStatement();
        break;
      }

      case 8: {
        setState(118);
        whileStatement();
        break;
      }

      case 9: {
        setState(119);
        repeatStatement();
        break;
      }

      case 10: {
        setState(120);
        forStatement();
        break;
      }

      case 11: {
        setState(121);
        returnStatement();
        break;
      }

      default:
        break;
      }
      setState(126);
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
    setState(127);
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
    setState(129);
    match(IronParser::CONTINUE);
   
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
  enterRule(_localctx, 12, IronParser::RuleReturnStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(131);
    match(IronParser::RETURN);
    setState(136);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      setState(132);
      dataFormat();
      break;
    }

    case 2: {
      setState(133);
      antlrcpp::downCast<ReturnStatementContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
      break;
    }

    case 3: {
      setState(134);
      functionCall();
      break;
    }

    case 4: {
      setState(135);
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
  enterRule(_localctx, 14, IronParser::RuleWhileStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(138);
    match(IronParser::WHILE);
    setState(139);
    boolExpr(0);
    setState(140);
    match(IronParser::L_CURLY);
    setState(141);
    statementList();
    setState(142);
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
  enterRule(_localctx, 16, IronParser::RuleRepeatStatement);

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
    match(IronParser::REPEAT);
    setState(145);
    match(IronParser::L_CURLY);
    setState(146);
    statementList();
    setState(147);
    match(IronParser::R_CURLY);
    setState(148);
    match(IronParser::WHILE);
    setState(149);
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
  enterRule(_localctx, 18, IronParser::RuleForStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(151);
    match(IronParser::FOR);
    setState(152);
    match(IronParser::IDENTIFIER);
    setState(153);
    match(IronParser::IN);
    setState(154);
    intervals();
    setState(155);
    match(IronParser::L_CURLY);
    setState(156);
    statementList();
    setState(157);
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
  enterRule(_localctx, 20, IronParser::RuleIntervals);

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
    switch (_input->LA(1)) {
      case IronParser::INT_NUMBER: {
        setState(159);
        antlrcpp::downCast<IntervalsContext *>(_localctx)->firstNumber = match(IronParser::INT_NUMBER);
        break;
      }

      case IronParser::IDENTIFIER: {
        setState(160);
        antlrcpp::downCast<IntervalsContext *>(_localctx)->firstVarName = match(IronParser::IDENTIFIER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(163);
    match(IronParser::T__0);
    setState(166);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IronParser::INT_NUMBER: {
        setState(164);
        antlrcpp::downCast<IntervalsContext *>(_localctx)->secondNumber = match(IronParser::INT_NUMBER);
        break;
      }

      case IronParser::IDENTIFIER: {
        setState(165);
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
  enterRule(_localctx, 22, IronParser::RuleFormatStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(168);
    match(IronParser::T__1);
    setState(169);
    match(IronParser::STRING_LITERAL);
    setState(170);
    match(IronParser::COMMA);

    setState(171);
    formatArguments();
    setState(172);
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
  enterRule(_localctx, 24, IronParser::RuleFormatArguments);
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
    formatArgument();
    setState(179);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::COMMA) {
      setState(175);
      match(IronParser::COMMA);
      setState(176);
      formatArgument();
      setState(181);
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
  enterRule(_localctx, 26, IronParser::RuleFormatArgument);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(187);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      setState(182);
      dataFormat();
      break;
    }

    case 2: {
      setState(183);
      antlrcpp::downCast<FormatArgumentContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
      break;
    }

    case 3: {
      setState(184);
      functionCall();
      break;
    }

    case 4: {
      setState(185);
      expr(0);
      break;
    }

    case 5: {
      setState(186);
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
  enterRule(_localctx, 28, IronParser::RuleExternBlock);
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
    setState(189);
    match(IronParser::T__2);
    setState(190);
    antlrcpp::downCast<ExternBlockContext *>(_localctx)->language = match(IronParser::IDENTIFIER);
    setState(191);
    match(IronParser::L_CURLY);
    setState(199);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::FUNCTION) {
      setState(193); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(192);
                externFunctionDeclaration();
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(195); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      setState(201);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(202);
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
  enterRule(_localctx, 30, IronParser::RuleExternFunctionDeclaration);
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
    setState(204);
    match(IronParser::FUNCTION);
    setState(205);
    antlrcpp::downCast<ExternFunctionDeclarationContext *>(_localctx)->exterFunctionName = match(IronParser::IDENTIFIER);
    setState(206);
    match(IronParser::L_PAREN);
    setState(208);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::IDENTIFIER) {
      setState(207);
      externFunctionArgs();
    }
    setState(212);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::COMMA) {
      setState(210);
      match(IronParser::COMMA);
      setState(211);
      antlrcpp::downCast<ExternFunctionDeclarationContext *>(_localctx)->varied = match(IronParser::T__3);
    }
    setState(214);
    match(IronParser::R_PAREN);
    setState(216);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::COLON) {
      setState(215);
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
  enterRule(_localctx, 32, IronParser::RuleExternFunctionArgs);

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
    setState(218);
    externFunctionArg();
    setState(223);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(219);
        match(IronParser::COMMA);
        setState(220);
        externFunctionArg(); 
      }
      setState(225);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
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
  enterRule(_localctx, 34, IronParser::RuleExternFunctionArg);
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
    setState(226);
    antlrcpp::downCast<ExternFunctionArgContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(227);
    match(IronParser::COLON);
    setState(229);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::STAR) {
      setState(228);
      antlrcpp::downCast<ExternFunctionArgContext *>(_localctx)->ptr = match(IronParser::STAR);
    }
    setState(231);
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
  enterRule(_localctx, 36, IronParser::RuleCTypes);
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
    setState(233);
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
  enterRule(_localctx, 38, IronParser::RuleFunctionDeclaration);
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
    setState(236);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::PUBLIC) {
      setState(235);
      match(IronParser::PUBLIC);
    }
    setState(238);
    match(IronParser::FUNCTION);
    setState(239);
    antlrcpp::downCast<FunctionDeclarationContext *>(_localctx)->functionName = match(IronParser::IDENTIFIER);
    setState(240);
    functionSignature();
    setState(241);
    match(IronParser::L_CURLY);
    setState(242);
    statementList();
    setState(243);
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
  enterRule(_localctx, 40, IronParser::RuleArrowFunctionInline);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(245);
    functionSignature();
    setState(246);
    match(IronParser::ARROW);
    setState(252);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IronParser::L_PAREN:
      case IronParser::REAL_NUMBER:
      case IronParser::INT_NUMBER:
      case IronParser::IDENTIFIER: {
        setState(247);
        expr(0);
        break;
      }

      case IronParser::L_CURLY: {
        setState(248);
        match(IronParser::L_CURLY);
        setState(249);
        statementList();
        setState(250);
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
  enterRule(_localctx, 42, IronParser::RuleFunctionSignature);
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
    setState(254);
    match(IronParser::L_PAREN);
    setState(256);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::IDENTIFIER) {
      setState(255);
      functionArgs();
    }
    setState(258);
    match(IronParser::R_PAREN);
    setState(260);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::COLON) {
      setState(259);
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
  enterRule(_localctx, 44, IronParser::RuleFunctionReturnType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(262);
    match(IronParser::COLON);
    setState(263);
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
  enterRule(_localctx, 46, IronParser::RuleFunctionArgs);
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
    setState(265);
    functionArg();
    setState(270);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::COMMA) {
      setState(266);
      match(IronParser::COMMA);
      setState(267);
      functionArg();
      setState(272);
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
  enterRule(_localctx, 48, IronParser::RuleFunctionArg);
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
    setState(273);
    antlrcpp::downCast<FunctionArgContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(274);
    match(IronParser::COLON);
    setState(277);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      setState(275);
      fnsignature();
      break;
    }

    case 2: {
      setState(276);
      varTypes();
      break;
    }

    default:
      break;
    }
    setState(280);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::EQ) {
      setState(279);
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
  enterRule(_localctx, 50, IronParser::RuleFnsignature);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(282);
    match(IronParser::FUNCTION);
    setState(283);
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
  enterRule(_localctx, 52, IronParser::RuleFunctionCall);
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
    setState(285);
    antlrcpp::downCast<FunctionCallContext *>(_localctx)->functionName = match(IronParser::IDENTIFIER);
    setState(286);
    match(IronParser::L_PAREN);
    setState(288);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::IDENTIFIER) {
      setState(287);
      functionCallArgs();
    }
    setState(290);
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
  enterRule(_localctx, 54, IronParser::RuleFunctionCallArgs);
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
    setState(292);
    functionCallArg();
    setState(297);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IronParser::COMMA) {
      setState(293);
      match(IronParser::COMMA);
      setState(294);
      functionCallArg();
      setState(299);
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
  enterRule(_localctx, 56, IronParser::RuleFunctionCallArg);

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
    antlrcpp::downCast<FunctionCallArgContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(301);
    match(IronParser::COLON);
    setState(306);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      setState(302);
      dataFormat();
      break;
    }

    case 2: {
      setState(303);
      antlrcpp::downCast<FunctionCallArgContext *>(_localctx)->anotherVarName = match(IronParser::IDENTIFIER);
      break;
    }

    case 3: {
      setState(304);
      functionCall();
      break;
    }

    case 4: {
      setState(305);
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

IronParser::VarTypesContext* IronParser::VarDeclarationContext::varTypes() {
  return getRuleContext<IronParser::VarTypesContext>(0);
}

tree::TerminalNode* IronParser::VarDeclarationContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
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
  enterRule(_localctx, 58, IronParser::RuleVarDeclaration);
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
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::MUT) {
      setState(308);
      match(IronParser::MUT);
    }
    setState(311);
    match(IronParser::LET);
    setState(312);
    antlrcpp::downCast<VarDeclarationContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(313);
    match(IronParser::COLON);
    setState(314);
    varTypes();
    setState(316);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::EQ) {
      setState(315);
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

IronParser::FunctionCallContext* IronParser::AssignmentContext::functionCall() {
  return getRuleContext<IronParser::FunctionCallContext>(0);
}

IronParser::ExprContext* IronParser::AssignmentContext::expr() {
  return getRuleContext<IronParser::ExprContext>(0);
}

IronParser::BoolExprContext* IronParser::AssignmentContext::boolExpr() {
  return getRuleContext<IronParser::BoolExprContext>(0);
}

tree::TerminalNode* IronParser::AssignmentContext::IDENTIFIER() {
  return getToken(IronParser::IDENTIFIER, 0);
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
  enterRule(_localctx, 60, IronParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(318);
    match(IronParser::EQ);
    setState(325);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      setState(319);
      arrowFunctionInline();
      break;
    }

    case 2: {
      setState(320);
      antlrcpp::downCast<AssignmentContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
      break;
    }

    case 3: {
      setState(321);
      dataFormat();
      break;
    }

    case 4: {
      setState(322);
      functionCall();
      break;
    }

    case 5: {
      setState(323);
      expr(0);
      break;
    }

    case 6: {
      setState(324);
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

//----------------- VarAssignmentContext ------------------------------------------------------------------

IronParser::VarAssignmentContext::VarAssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IronParser::VarAssignmentContext::EQ() {
  return getToken(IronParser::EQ, 0);
}

std::vector<tree::TerminalNode *> IronParser::VarAssignmentContext::IDENTIFIER() {
  return getTokens(IronParser::IDENTIFIER);
}

tree::TerminalNode* IronParser::VarAssignmentContext::IDENTIFIER(size_t i) {
  return getToken(IronParser::IDENTIFIER, i);
}

IronParser::ArrowFunctionInlineContext* IronParser::VarAssignmentContext::arrowFunctionInline() {
  return getRuleContext<IronParser::ArrowFunctionInlineContext>(0);
}

IronParser::DataFormatContext* IronParser::VarAssignmentContext::dataFormat() {
  return getRuleContext<IronParser::DataFormatContext>(0);
}

IronParser::ExprContext* IronParser::VarAssignmentContext::expr() {
  return getRuleContext<IronParser::ExprContext>(0);
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
  enterRule(_localctx, 62, IronParser::RuleVarAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(327);
    antlrcpp::downCast<VarAssignmentContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
    setState(328);
    match(IronParser::EQ);
    setState(333);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      setState(329);
      arrowFunctionInline();
      break;
    }

    case 2: {
      setState(330);
      antlrcpp::downCast<VarAssignmentContext *>(_localctx)->anotherVarName = match(IronParser::IDENTIFIER);
      break;
    }

    case 3: {
      setState(331);
      dataFormat();
      break;
    }

    case 4: {
      setState(332);
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
  enterRule(_localctx, 64, IronParser::RuleIfBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(335);
    match(IronParser::L_CURLY);
    setState(337);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      setState(336);
      statementList();
      break;
    }

    default:
      break;
    }
    setState(339);
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
  enterRule(_localctx, 66, IronParser::RuleIfStatement);
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
    setState(341);
    match(IronParser::IF);
    setState(342);
    match(IronParser::L_PAREN);
    setState(343);
    boolExpr(0);
    setState(344);
    match(IronParser::R_PAREN);
    setState(345);
    ifBlock();
    setState(348);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IronParser::ELSE) {
      setState(346);
      match(IronParser::ELSE);
      setState(347);
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
  enterRule(_localctx, 68, IronParser::RuleElseStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(352);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IronParser::IF: {
        enterOuterAlt(_localctx, 1);
        setState(350);
        ifStatement();
        break;
      }

      case IronParser::L_CURLY: {
        enterOuterAlt(_localctx, 2);
        setState(351);
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
  size_t startState = 70;
  enterRecursionRule(_localctx, 70, IronParser::RuleBoolExpr, precedence);

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
    setState(366);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      setState(355);
      match(IronParser::L_PAREN);
      setState(356);
      boolExpr(0);
      setState(357);
      match(IronParser::R_PAREN);
      break;
    }

    case 2: {
      setState(359);
      antlrcpp::downCast<BoolExprContext *>(_localctx)->not_ = match(IronParser::NOT);
      setState(360);
      boolExpr(6);
      break;
    }

    case 3: {
      setState(361);
      antlrcpp::downCast<BoolExprContext *>(_localctx)->booleanValue = match(IronParser::BOOLEAN_VALUE);
      break;
    }

    case 4: {
      setState(362);
      number();
      break;
    }

    case 5: {
      setState(363);
      antlrcpp::downCast<BoolExprContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
      break;
    }

    case 6: {
      setState(364);
      functionCall();
      break;
    }

    case 7: {
      setState(365);
      expr(0);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(379);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(377);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BoolExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleBoolExpr);
          setState(368);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(369);
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
          setState(370);
          antlrcpp::downCast<BoolExprContext *>(_localctx)->right = boolExpr(10);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BoolExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleBoolExpr);
          setState(371);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(372);
          antlrcpp::downCast<BoolExprContext *>(_localctx)->op = match(IronParser::AND);
          setState(373);
          antlrcpp::downCast<BoolExprContext *>(_localctx)->right = boolExpr(9);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BoolExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleBoolExpr);
          setState(374);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(375);
          antlrcpp::downCast<BoolExprContext *>(_localctx)->op = match(IronParser::OR);
          setState(376);
          antlrcpp::downCast<BoolExprContext *>(_localctx)->right = boolExpr(8);
          break;
        }

        default:
          break;
        } 
      }
      setState(381);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
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
  size_t startState = 72;
  enterRecursionRule(_localctx, 72, IronParser::RuleExpr, precedence);

    

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
    setState(390);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
    case 1: {
      setState(383);
      number();
      break;
    }

    case 2: {
      setState(384);
      functionCall();
      break;
    }

    case 3: {
      setState(385);
      antlrcpp::downCast<ExprContext *>(_localctx)->varName = match(IronParser::IDENTIFIER);
      break;
    }

    case 4: {
      setState(386);
      match(IronParser::L_PAREN);
      setState(387);
      expr(0);
      setState(388);
      match(IronParser::R_PAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(407);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(405);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(392);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(396);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case IronParser::STAR: {
              setState(393);
              antlrcpp::downCast<ExprContext *>(_localctx)->mult = match(IronParser::STAR);
              break;
            }

            case IronParser::T__4: {
              setState(394);
              antlrcpp::downCast<ExprContext *>(_localctx)->mod = match(IronParser::T__4);
              break;
            }

            case IronParser::DIV: {
              setState(395);
              antlrcpp::downCast<ExprContext *>(_localctx)->div = match(IronParser::DIV);
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(398);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(7);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(399);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(402);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case IronParser::PLUS: {
              setState(400);
              antlrcpp::downCast<ExprContext *>(_localctx)->plus = match(IronParser::PLUS);
              break;
            }

            case IronParser::MINUS: {
              setState(401);
              antlrcpp::downCast<ExprContext *>(_localctx)->minus = match(IronParser::MINUS);
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(404);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(6);
          break;
        }

        default:
          break;
        } 
      }
      setState(409);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx);
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
  enterRule(_localctx, 74, IronParser::RuleNumber);
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
    setState(410);
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
  enterRule(_localctx, 76, IronParser::RuleDataFormat);
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
    setState(412);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 270215977642229760) != 0))) {
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
  enterRule(_localctx, 78, IronParser::RuleVarTypes);
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
    setState(414);
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
    case 35: return boolExprSempred(antlrcpp::downCast<BoolExprContext *>(context), predicateIndex);
    case 36: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

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
