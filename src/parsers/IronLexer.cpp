
// Generated from Iron.g4 by ANTLR 4.13.2


#include "IronLexer.h"


using namespace antlr4;


using namespace antlr4;

namespace
{

    struct IronLexerStaticData final
    {
        IronLexerStaticData(std::vector<std::string> ruleNames, std::vector<std::string> channelNames,
                            std::vector<std::string> modeNames, std::vector<std::string> literalNames,
                            std::vector<std::string> symbolicNames) :
            ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)), modeNames(std::move(modeNames)),
            literalNames(std::move(literalNames)), symbolicNames(std::move(symbolicNames)),
            vocabulary(this->literalNames, this->symbolicNames)
        {
        }

        IronLexerStaticData(const IronLexerStaticData &) = delete;
        IronLexerStaticData(IronLexerStaticData &&) = delete;
        IronLexerStaticData &operator=(const IronLexerStaticData &) = delete;
        IronLexerStaticData &operator=(IronLexerStaticData &&) = delete;

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
            std::unique_ptr<IronLexerStaticData>
                    ironlexerLexerStaticData = nullptr;

    void ironlexerLexerInitialize()
    {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
        if (ironlexerLexerStaticData != nullptr)
        {
            return;
        }
#else
        assert(ironlexerLexerStaticData == nullptr);
#endif
        auto staticData = std::make_unique<IronLexerStaticData>(
                std::vector<std::string>{"T__0",
                                         "LINE_COMMENT",
                                         "BLOCK_COMMENT",
                                         "COMMA",
                                         "COLON",
                                         "EQ",
                                         "SEMICOLON",
                                         "DOT",
                                         "STAR",
                                         "L_CURLY",
                                         "R_CURLY",
                                         "L_PAREN",
                                         "R_PAREN",
                                         "PLUS",
                                         "MINUS",
                                         "DIV",
                                         "L_BRACKET",
                                         "R_BRACKET",
                                         "ARROW",
                                         "FUNCTION",
                                         "LET",
                                         "PUBLIC",
                                         "IMPORT",
                                         "RETURN",
                                         "TYPE_INT",
                                         "TYPE_CHAR",
                                         "TYPE_FLOAT",
                                         "TYPE_STRING",
                                         "TYPE_BOOLEAN",
                                         "TYPE_DOUBLE",
                                         "REAL_NUMBER",
                                         "INT_NUMBER",
                                         "BOOLEAN_VALUE",
                                         "STRING_LITERAL",
                                         "IDENTIFIER",
                                         "NEWLINE",
                                         "WS"},
                std::vector<std::string>{"DEFAULT_TOKEN_CHANNEL", "HIDDEN"}, std::vector<std::string>{"DEFAULT_MODE"},
                std::vector<std::string>{"",         "'@main'",   "",         "",         "','",   "':'",    "'='",
                                         "';'",      "'.'",       "'*'",      "'{'",      "'}'",   "'('",    "')'",
                                         "'+'",      "'-'",       "'/'",      "'['",      "']'",   "'->'",   "'fn'",
                                         "'let'",    "'public'",  "'import'", "'return'", "'int'", "'char'", "'float'",
                                         "'string'", "'boolean'", "'double'"},
                std::vector<std::string>{"",
                                         "",
                                         "LINE_COMMENT",
                                         "BLOCK_COMMENT",
                                         "COMMA",
                                         "COLON",
                                         "EQ",
                                         "SEMICOLON",
                                         "DOT",
                                         "STAR",
                                         "L_CURLY",
                                         "R_CURLY",
                                         "L_PAREN",
                                         "R_PAREN",
                                         "PLUS",
                                         "MINUS",
                                         "DIV",
                                         "L_BRACKET",
                                         "R_BRACKET",
                                         "ARROW",
                                         "FUNCTION",
                                         "LET",
                                         "PUBLIC",
                                         "IMPORT",
                                         "RETURN",
                                         "TYPE_INT",
                                         "TYPE_CHAR",
                                         "TYPE_FLOAT",
                                         "TYPE_STRING",
                                         "TYPE_BOOLEAN",
                                         "TYPE_DOUBLE",
                                         "REAL_NUMBER",
                                         "INT_NUMBER",
                                         "BOOLEAN_VALUE",
                                         "STRING_LITERAL",
                                         "IDENTIFIER",
                                         "NEWLINE",
                                         "WS"});
        static const int32_t serializedATNSegment[] = {
                4,   0,   37,  281, 6,   -1,  2,   0,   7,   0,  2,   1,   7,   1,   2,   2,   7,   2,   2,   3,   7,
                3,   2,   4,   7,   4,   2,   5,   7,   5,   2,  6,   7,   6,   2,   7,   7,   7,   2,   8,   7,   8,
                2,   9,   7,   9,   2,   10,  7,   10,  2,   11, 7,   11,  2,   12,  7,   12,  2,   13,  7,   13,  2,
                14,  7,   14,  2,   15,  7,   15,  2,   16,  7,  16,  2,   17,  7,   17,  2,   18,  7,   18,  2,   19,
                7,   19,  2,   20,  7,   20,  2,   21,  7,   21, 2,   22,  7,   22,  2,   23,  7,   23,  2,   24,  7,
                24,  2,   25,  7,   25,  2,   26,  7,   26,  2,  27,  7,   27,  2,   28,  7,   28,  2,   29,  7,   29,
                2,   30,  7,   30,  2,   31,  7,   31,  2,   32, 7,   32,  2,   33,  7,   33,  2,   34,  7,   34,  2,
                35,  7,   35,  2,   36,  7,   36,  1,   0,   1,  0,   1,   0,   1,   0,   1,   0,   1,   0,   1,   1,
                1,   1,   1,   1,   1,   1,   5,   1,   86,  8,  1,   10,  1,   12,  1,   89,  9,   1,   1,   1,   1,
                1,   1,   2,   1,   2,   1,   2,   1,   2,   5,  2,   97,  8,   2,   10,  2,   12,  2,   100, 9,   2,
                1,   2,   1,   2,   1,   2,   1,   2,   1,   2,  1,   3,   1,   3,   1,   4,   1,   4,   1,   5,   1,
                5,   1,   6,   1,   6,   1,   7,   1,   7,   1,  8,   1,   8,   1,   9,   1,   9,   1,   10,  1,   10,
                1,   11,  1,   11,  1,   12,  1,   12,  1,   13, 1,   13,  1,   14,  1,   14,  1,   15,  1,   15,  1,
                16,  1,   16,  1,   17,  1,   17,  1,   18,  1,  18,  1,   18,  1,   19,  1,   19,  1,   19,  1,   20,
                1,   20,  1,   20,  1,   20,  1,   21,  1,   21, 1,   21,  1,   21,  1,   21,  1,   21,  1,   21,  1,
                22,  1,   22,  1,   22,  1,   22,  1,   22,  1,  22,  1,   22,  1,   23,  1,   23,  1,   23,  1,   23,
                1,   23,  1,   23,  1,   23,  1,   24,  1,   24, 1,   24,  1,   24,  1,   25,  1,   25,  1,   25,  1,
                25,  1,   25,  1,   26,  1,   26,  1,   26,  1,  26,  1,   26,  1,   26,  1,   27,  1,   27,  1,   27,
                1,   27,  1,   27,  1,   27,  1,   27,  1,   28, 1,   28,  1,   28,  1,   28,  1,   28,  1,   28,  1,
                28,  1,   28,  1,   29,  1,   29,  1,   29,  1,  29,  1,   29,  1,   29,  1,   29,  1,   30,  3,   30,
                206, 8,   30,  1,   30,  4,   30,  209, 8,   30, 11,  30,  12,  30,  210, 1,   30,  1,   30,  4,   30,
                215, 8,   30,  11,  30,  12,  30,  216, 1,   30, 1,   30,  3,   30,  221, 8,   30,  1,   30,  4,   30,
                224, 8,   30,  11,  30,  12,  30,  225, 3,   30, 228, 8,   30,  1,   30,  3,   30,  231, 8,   30,  1,
                31,  3,   31,  234, 8,   31,  1,   31,  4,   31, 237, 8,   31,  11,  31,  12,  31,  238, 1,   32,  1,
                32,  1,   32,  1,   32,  1,   32,  1,   32,  1,  32,  1,   32,  1,   32,  3,   32,  250, 8,   32,  1,
                33,  1,   33,  5,   33,  254, 8,   33,  10,  33, 12,  33,  257, 9,   33,  1,   33,  1,   33,  1,   34,
                1,   34,  5,   34,  263, 8,   34,  10,  34,  12, 34,  266, 9,   34,  1,   35,  3,   35,  269, 8,   35,
                1,   35,  1,   35,  1,   35,  1,   35,  1,   36, 4,   36,  276, 8,   36,  11,  36,  12,  36,  277, 1,
                36,  1,   36,  1,   98,  0,   37,  1,   1,   3,  2,   5,   3,   7,   4,   9,   5,   11,  6,   13,  7,
                15,  8,   17,  9,   19,  10,  21,  11,  23,  12, 25,  13,  27,  14,  29,  15,  31,  16,  33,  17,  35,
                18,  37,  19,  39,  20,  41,  21,  43,  22,  45, 23,  47,  24,  49,  25,  51,  26,  53,  27,  55,  28,
                57,  29,  59,  30,  61,  31,  63,  32,  65,  33, 67,  34,  69,  35,  71,  36,  73,  37,  1,   0,   9,
                2,   0,   10,  10,  13,  13,  1,   0,   48,  57, 2,   0,   69,  69,  101, 101, 2,   0,   43,  43,  45,
                45,  2,   0,   68,  68,  70,  70,  3,   0,   10, 10,  13,  13,  34,  34,  3,   0,   65,  90,  95,  95,
                97,  122, 4,   0,   48,  57,  65,  90,  95,  95, 97,  122, 2,   0,   9,   9,   32,  32,  296, 0,   1,
                1,   0,   0,   0,   0,   3,   1,   0,   0,   0,  0,   5,   1,   0,   0,   0,   0,   7,   1,   0,   0,
                0,   0,   9,   1,   0,   0,   0,   0,   11,  1,  0,   0,   0,   0,   13,  1,   0,   0,   0,   0,   15,
                1,   0,   0,   0,   0,   17,  1,   0,   0,   0,  0,   19,  1,   0,   0,   0,   0,   21,  1,   0,   0,
                0,   0,   23,  1,   0,   0,   0,   0,   25,  1,  0,   0,   0,   0,   27,  1,   0,   0,   0,   0,   29,
                1,   0,   0,   0,   0,   31,  1,   0,   0,   0,  0,   33,  1,   0,   0,   0,   0,   35,  1,   0,   0,
                0,   0,   37,  1,   0,   0,   0,   0,   39,  1,  0,   0,   0,   0,   41,  1,   0,   0,   0,   0,   43,
                1,   0,   0,   0,   0,   45,  1,   0,   0,   0,  0,   47,  1,   0,   0,   0,   0,   49,  1,   0,   0,
                0,   0,   51,  1,   0,   0,   0,   0,   53,  1,  0,   0,   0,   0,   55,  1,   0,   0,   0,   0,   57,
                1,   0,   0,   0,   0,   59,  1,   0,   0,   0,  0,   61,  1,   0,   0,   0,   0,   63,  1,   0,   0,
                0,   0,   65,  1,   0,   0,   0,   0,   67,  1,  0,   0,   0,   0,   69,  1,   0,   0,   0,   0,   71,
                1,   0,   0,   0,   0,   73,  1,   0,   0,   0,  1,   75,  1,   0,   0,   0,   3,   81,  1,   0,   0,
                0,   5,   92,  1,   0,   0,   0,   7,   106, 1,  0,   0,   0,   9,   108, 1,   0,   0,   0,   11,  110,
                1,   0,   0,   0,   13,  112, 1,   0,   0,   0,  15,  114, 1,   0,   0,   0,   17,  116, 1,   0,   0,
                0,   19,  118, 1,   0,   0,   0,   21,  120, 1,  0,   0,   0,   23,  122, 1,   0,   0,   0,   25,  124,
                1,   0,   0,   0,   27,  126, 1,   0,   0,   0,  29,  128, 1,   0,   0,   0,   31,  130, 1,   0,   0,
                0,   33,  132, 1,   0,   0,   0,   35,  134, 1,  0,   0,   0,   37,  136, 1,   0,   0,   0,   39,  139,
                1,   0,   0,   0,   41,  142, 1,   0,   0,   0,  43,  146, 1,   0,   0,   0,   45,  153, 1,   0,   0,
                0,   47,  160, 1,   0,   0,   0,   49,  167, 1,  0,   0,   0,   51,  171, 1,   0,   0,   0,   53,  176,
                1,   0,   0,   0,   55,  182, 1,   0,   0,   0,  57,  189, 1,   0,   0,   0,   59,  197, 1,   0,   0,
                0,   61,  205, 1,   0,   0,   0,   63,  233, 1,  0,   0,   0,   65,  249, 1,   0,   0,   0,   67,  251,
                1,   0,   0,   0,   69,  260, 1,   0,   0,   0,  71,  268, 1,   0,   0,   0,   73,  275, 1,   0,   0,
                0,   75,  76,  5,   64,  0,   0,   76,  77,  5,  109, 0,   0,   77,  78,  5,   97,  0,   0,   78,  79,
                5,   105, 0,   0,   79,  80,  5,   110, 0,   0,  80,  2,   1,   0,   0,   0,   81,  82,  5,   47,  0,
                0,   82,  83,  5,   47,  0,   0,   83,  87,  1,  0,   0,   0,   84,  86,  8,   0,   0,   0,   85,  84,
                1,   0,   0,   0,   86,  89,  1,   0,   0,   0,  87,  85,  1,   0,   0,   0,   87,  88,  1,   0,   0,
                0,   88,  90,  1,   0,   0,   0,   89,  87,  1,  0,   0,   0,   90,  91,  6,   1,   0,   0,   91,  4,
                1,   0,   0,   0,   92,  93,  5,   47,  0,   0,  93,  94,  5,   42,  0,   0,   94,  98,  1,   0,   0,
                0,   95,  97,  9,   0,   0,   0,   96,  95,  1,  0,   0,   0,   97,  100, 1,   0,   0,   0,   98,  99,
                1,   0,   0,   0,   98,  96,  1,   0,   0,   0,  99,  101, 1,   0,   0,   0,   100, 98,  1,   0,   0,
                0,   101, 102, 5,   42,  0,   0,   102, 103, 5,  47,  0,   0,   103, 104, 1,   0,   0,   0,   104, 105,
                6,   2,   0,   0,   105, 6,   1,   0,   0,   0,  106, 107, 5,   44,  0,   0,   107, 8,   1,   0,   0,
                0,   108, 109, 5,   58,  0,   0,   109, 10,  1,  0,   0,   0,   110, 111, 5,   61,  0,   0,   111, 12,
                1,   0,   0,   0,   112, 113, 5,   59,  0,   0,  113, 14,  1,   0,   0,   0,   114, 115, 5,   46,  0,
                0,   115, 16,  1,   0,   0,   0,   116, 117, 5,  42,  0,   0,   117, 18,  1,   0,   0,   0,   118, 119,
                5,   123, 0,   0,   119, 20,  1,   0,   0,   0,  120, 121, 5,   125, 0,   0,   121, 22,  1,   0,   0,
                0,   122, 123, 5,   40,  0,   0,   123, 24,  1,  0,   0,   0,   124, 125, 5,   41,  0,   0,   125, 26,
                1,   0,   0,   0,   126, 127, 5,   43,  0,   0,  127, 28,  1,   0,   0,   0,   128, 129, 5,   45,  0,
                0,   129, 30,  1,   0,   0,   0,   130, 131, 5,  47,  0,   0,   131, 32,  1,   0,   0,   0,   132, 133,
                5,   91,  0,   0,   133, 34,  1,   0,   0,   0,  134, 135, 5,   93,  0,   0,   135, 36,  1,   0,   0,
                0,   136, 137, 5,   45,  0,   0,   137, 138, 5,  62,  0,   0,   138, 38,  1,   0,   0,   0,   139, 140,
                5,   102, 0,   0,   140, 141, 5,   110, 0,   0,  141, 40,  1,   0,   0,   0,   142, 143, 5,   108, 0,
                0,   143, 144, 5,   101, 0,   0,   144, 145, 5,  116, 0,   0,   145, 42,  1,   0,   0,   0,   146, 147,
                5,   112, 0,   0,   147, 148, 5,   117, 0,   0,  148, 149, 5,   98,  0,   0,   149, 150, 5,   108, 0,
                0,   150, 151, 5,   105, 0,   0,   151, 152, 5,  99,  0,   0,   152, 44,  1,   0,   0,   0,   153, 154,
                5,   105, 0,   0,   154, 155, 5,   109, 0,   0,  155, 156, 5,   112, 0,   0,   156, 157, 5,   111, 0,
                0,   157, 158, 5,   114, 0,   0,   158, 159, 5,  116, 0,   0,   159, 46,  1,   0,   0,   0,   160, 161,
                5,   114, 0,   0,   161, 162, 5,   101, 0,   0,  162, 163, 5,   116, 0,   0,   163, 164, 5,   117, 0,
                0,   164, 165, 5,   114, 0,   0,   165, 166, 5,  110, 0,   0,   166, 48,  1,   0,   0,   0,   167, 168,
                5,   105, 0,   0,   168, 169, 5,   110, 0,   0,  169, 170, 5,   116, 0,   0,   170, 50,  1,   0,   0,
                0,   171, 172, 5,   99,  0,   0,   172, 173, 5,  104, 0,   0,   173, 174, 5,   97,  0,   0,   174, 175,
                5,   114, 0,   0,   175, 52,  1,   0,   0,   0,  176, 177, 5,   102, 0,   0,   177, 178, 5,   108, 0,
                0,   178, 179, 5,   111, 0,   0,   179, 180, 5,  97,  0,   0,   180, 181, 5,   116, 0,   0,   181, 54,
                1,   0,   0,   0,   182, 183, 5,   115, 0,   0,  183, 184, 5,   116, 0,   0,   184, 185, 5,   114, 0,
                0,   185, 186, 5,   105, 0,   0,   186, 187, 5,  110, 0,   0,   187, 188, 5,   103, 0,   0,   188, 56,
                1,   0,   0,   0,   189, 190, 5,   98,  0,   0,  190, 191, 5,   111, 0,   0,   191, 192, 5,   111, 0,
                0,   192, 193, 5,   108, 0,   0,   193, 194, 5,  101, 0,   0,   194, 195, 5,   97,  0,   0,   195, 196,
                5,   110, 0,   0,   196, 58,  1,   0,   0,   0,  197, 198, 5,   100, 0,   0,   198, 199, 5,   111, 0,
                0,   199, 200, 5,   117, 0,   0,   200, 201, 5,  98,  0,   0,   201, 202, 5,   108, 0,   0,   202, 203,
                5,   101, 0,   0,   203, 60,  1,   0,   0,   0,  204, 206, 5,   45,  0,   0,   205, 204, 1,   0,   0,
                0,   205, 206, 1,   0,   0,   0,   206, 208, 1,  0,   0,   0,   207, 209, 7,   1,   0,   0,   208, 207,
                1,   0,   0,   0,   209, 210, 1,   0,   0,   0,  210, 208, 1,   0,   0,   0,   210, 211, 1,   0,   0,
                0,   211, 212, 1,   0,   0,   0,   212, 214, 5,  46,  0,   0,   213, 215, 7,   1,   0,   0,   214, 213,
                1,   0,   0,   0,   215, 216, 1,   0,   0,   0,  216, 214, 1,   0,   0,   0,   216, 217, 1,   0,   0,
                0,   217, 227, 1,   0,   0,   0,   218, 220, 7,  2,   0,   0,   219, 221, 7,   3,   0,   0,   220, 219,
                1,   0,   0,   0,   220, 221, 1,   0,   0,   0,  221, 223, 1,   0,   0,   0,   222, 224, 7,   1,   0,
                0,   223, 222, 1,   0,   0,   0,   224, 225, 1,  0,   0,   0,   225, 223, 1,   0,   0,   0,   225, 226,
                1,   0,   0,   0,   226, 228, 1,   0,   0,   0,  227, 218, 1,   0,   0,   0,   227, 228, 1,   0,   0,
                0,   228, 230, 1,   0,   0,   0,   229, 231, 7,  4,   0,   0,   230, 229, 1,   0,   0,   0,   230, 231,
                1,   0,   0,   0,   231, 62,  1,   0,   0,   0,  232, 234, 5,   45,  0,   0,   233, 232, 1,   0,   0,
                0,   233, 234, 1,   0,   0,   0,   234, 236, 1,  0,   0,   0,   235, 237, 7,   1,   0,   0,   236, 235,
                1,   0,   0,   0,   237, 238, 1,   0,   0,   0,  238, 236, 1,   0,   0,   0,   238, 239, 1,   0,   0,
                0,   239, 64,  1,   0,   0,   0,   240, 241, 5,  116, 0,   0,   241, 242, 5,   114, 0,   0,   242, 243,
                5,   117, 0,   0,   243, 250, 5,   101, 0,   0,  244, 245, 5,   102, 0,   0,   245, 246, 5,   97,  0,
                0,   246, 247, 5,   108, 0,   0,   247, 248, 5,  115, 0,   0,   248, 250, 5,   101, 0,   0,   249, 240,
                1,   0,   0,   0,   249, 244, 1,   0,   0,   0,  250, 66,  1,   0,   0,   0,   251, 255, 5,   34,  0,
                0,   252, 254, 8,   5,   0,   0,   253, 252, 1,  0,   0,   0,   254, 257, 1,   0,   0,   0,   255, 253,
                1,   0,   0,   0,   255, 256, 1,   0,   0,   0,  256, 258, 1,   0,   0,   0,   257, 255, 1,   0,   0,
                0,   258, 259, 5,   34,  0,   0,   259, 68,  1,  0,   0,   0,   260, 264, 7,   6,   0,   0,   261, 263,
                7,   7,   0,   0,   262, 261, 1,   0,   0,   0,  263, 266, 1,   0,   0,   0,   264, 262, 1,   0,   0,
                0,   264, 265, 1,   0,   0,   0,   265, 70,  1,  0,   0,   0,   266, 264, 1,   0,   0,   0,   267, 269,
                5,   13,  0,   0,   268, 267, 1,   0,   0,   0,  268, 269, 1,   0,   0,   0,   269, 270, 1,   0,   0,
                0,   270, 271, 5,   10,  0,   0,   271, 272, 1,  0,   0,   0,   272, 273, 6,   35,  0,   0,   273, 72,
                1,   0,   0,   0,   274, 276, 7,   8,   0,   0,  275, 274, 1,   0,   0,   0,   276, 277, 1,   0,   0,
                0,   277, 275, 1,   0,   0,   0,   277, 278, 1,  0,   0,   0,   278, 279, 1,   0,   0,   0,   279, 280,
                6,   36,  0,   0,   280, 74,  1,   0,   0,   0,  17,  0,   87,  98,  205, 210, 216, 220, 225, 227, 230,
                233, 238, 249, 255, 264, 268, 277, 1,   6,   0,  0};
        staticData->serializedATN = antlr4::atn::SerializedATNView(
                serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

        antlr4::atn::ATNDeserializer deserializer;
        staticData->atn = deserializer.deserialize(staticData->serializedATN);

        const size_t count = staticData->atn->getNumberOfDecisions();
        staticData->decisionToDFA.reserve(count);
        for (size_t i = 0; i < count; i++)
        {
            staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
        }
        ironlexerLexerStaticData = std::move(staticData);
    }

} // namespace

IronLexer::IronLexer(CharStream *input) : Lexer(input)
{
    IronLexer::initialize();
    _interpreter =
            new atn::LexerATNSimulator(this, *ironlexerLexerStaticData->atn, ironlexerLexerStaticData->decisionToDFA,
                                       ironlexerLexerStaticData->sharedContextCache);
}

IronLexer::~IronLexer()
{
    delete _interpreter;
}

std::string IronLexer::getGrammarFileName() const
{
    return "Iron.g4";
}

const std::vector<std::string> &IronLexer::getRuleNames() const
{
    return ironlexerLexerStaticData->ruleNames;
}

const std::vector<std::string> &IronLexer::getChannelNames() const
{
    return ironlexerLexerStaticData->channelNames;
}

const std::vector<std::string> &IronLexer::getModeNames() const
{
    return ironlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary &IronLexer::getVocabulary() const
{
    return ironlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView IronLexer::getSerializedATN() const
{
    return ironlexerLexerStaticData->serializedATN;
}

const atn::ATN &IronLexer::getATN() const
{
    return *ironlexerLexerStaticData->atn;
}


void IronLexer::initialize()
{
#if ANTLR4_USE_THREAD_LOCAL_CACHE
    ironlexerLexerInitialize();
#else
    ::antlr4::internal::call_once(ironlexerLexerOnceFlag, ironlexerLexerInitialize);
#endif
}
