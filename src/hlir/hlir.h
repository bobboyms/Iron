#include "WriterCodeHLIR.h"
#include "../parsers/HightLavelIRParser.h"
#include "../parsers/HightLavelIRLexer.h"
#include "ScopeManager.h"
#include <memory>
#include <stack>

namespace hlir
{

    class Type
    {
    private:
        int type;

    public:
        Type(int type);
        ~Type();
    };

    struct Arg
    {
        std::string name;
        Type type;
    };

    class FunctionArgs
    {
    private:
        std::vector<Arg> args;

    public:
        void addArg(Arg arg);

        FunctionArgs(/* args */);
        ~FunctionArgs();
    };

} // namespace hli
