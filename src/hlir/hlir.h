#ifndef HLIR_H
#define HLIR_H

#include "WriterCodeHLIR.h"
#include "Exceptions.h"
#include "TokenMap.h"
#include "Utils.h"
#include "WriterCodeHLIR.h"
#include <memory>
#include <stack>

namespace hlir
{

    class Context
    {
    private:
        std::shared_ptr<std::stringstream> localSb;

    public:
        Context(/* args */);
        ~Context();
    };

    class Basic
    {
    public:
        virtual ~Basic() = default;

        virtual std::string getText() = 0;
    };

    class Type : public Basic
    {
    private:
        int type;
        std::stringstream sb;

    public:
        int getType();
        std::string getText() override;

        Type(int type);
        ~Type();
    };

    struct Arg
    {
        std::string name;
        std::shared_ptr<Type> type;

        // Construtor que recebe nome e type
        Arg(const std::string &name, std::shared_ptr<Type> t)
            : name(name), type(std::move(t)) {}
    };

    class FunctionArgs : public Basic
    {
    private:
        std::stringstream sb;
        std::vector<std::shared_ptr<Arg>> args;

    public:
        void
        addArg(std::shared_ptr<Arg> arg);
        std::string getText() override;

        FunctionArgs();
        FunctionArgs(std::vector<std::shared_ptr<Arg>> args);

        ~FunctionArgs();
    };

    class Function : public Basic
    {
    private:
        std::stringstream sb;
        std::string functionName;
        std::shared_ptr<FunctionArgs> functionArgs;
        std::shared_ptr<Type> functionReturnType;

    public:
        std::string getFunctionName();
        std::string getText() override;
        Function(std::string functionName, std::shared_ptr<FunctionArgs> functionArgs, std::shared_ptr<Type> functionReturnType);
        ~Function();
    };

    class Variable : public Basic
    {
    private:
        std::stringstream sb;
        std::string varName;
        std::shared_ptr<Type> varType;

    public:
        std::string getVarName();
        std::string getText() override;
        std::shared_ptr<Type> getVarType();
        Variable(const std::string &varName, std::shared_ptr<Type> varType);
        ~Variable();
    };

    using Data = std::variant<
        std::shared_ptr<Function>,
        std::string,
        int,
        float,
        double,
        bool>;

    class Value : public Basic
    {
    public:
        Value(Data value, std::shared_ptr<Type> valueType);
        ~Value();

        Data getValue();
        std::string getText() override;
        std::shared_ptr<Type> getValueType();

    private:
        Data value;                      // O "Data" que guarda qualquer tipo
        std::shared_ptr<Type> valueType; // O tipo (hlir::Type) associado
        std::ostringstream sb;           // Pode ser útil p/ formar strings
    };

    class Assign : public Basic
    {
    public:
        Assign(std::shared_ptr<Variable> variable, std::shared_ptr<Value> value);
        ~Assign();

        std::string getText() override;

    private:
        std::ostringstream sb;
        std::shared_ptr<Variable> variable;
        std::shared_ptr<Value> value;
    };

    struct FunctionCallArg
    {
        std::string argument;
        std::shared_ptr<Type> argumentType;
        std::shared_ptr<Value> value;

        // Construtor que recebe nome e type
        FunctionCallArg(const std::string &argument, std::shared_ptr<Type> type, std::shared_ptr<Value> value)
            : argument(argument), argumentType(std::move(type)), value(std::move(value)) {}
    };

    class FunctionCallArgs : public Basic
    {
    private:
        std::ostringstream sb;
        std::vector<std::shared_ptr<FunctionCallArg>> callArgs;

    public:
        std::string getText() override;
        FunctionCallArgs(std::vector<std::shared_ptr<FunctionCallArg>> callArgs);
        FunctionCallArgs();

        void addCallArg(std::shared_ptr<FunctionCallArg> callArg);
        ~FunctionCallArgs();
    };

}

#endif
