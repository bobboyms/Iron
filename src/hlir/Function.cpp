#include "../headers/Hlir.h"

namespace hlir
{
    Function::Function(std::string functionName, std::shared_ptr<FunctionArgs> functionArgs, std::shared_ptr<Type> functionReturnType)
        : functionName(functionName), functionArgs(functionArgs), functionReturnType(functionReturnType)
    {
    }

    Function::Function(const std::string functionName,
                       const std::shared_ptr<FunctionArgs> functionArgs,
                       const std::shared_ptr<Type> functionReturnType,
                       const std::shared_ptr<Statement> statement)
        : functionName(functionName),
          functionArgs(functionArgs),
          functionReturnType(functionReturnType),
          statement(statement)
    {
    }

    Function::~Function() {}

    std::string Function::getFunctionName()
    {
        return functionName;
    }

    std::shared_ptr<Type> Function::getFunctionReturnType()
    {
        return functionReturnType;
    }

    std::string Function::getText()
    {
        sb.str("");
        sb.clear();

        if (statement->getStatements().size() > 0)
        {
            sb << util::format("fn {}({}):{} { {}}\n", functionName, functionArgs->getText(), functionReturnType->getText(), statement->getText());
        }
        else
        {
            sb << util::format("fn {}({}):{} { }\n", functionName, functionArgs->getText(), functionReturnType->getText());
        }

        return sb.str();
    }

    // Function Call

    FunctionCallArgs::FunctionCallArgs(std::vector<std::shared_ptr<FunctionCallArg>> callArgs)
        : callArgs(callArgs)
    {
    }

    FunctionCallArgs::FunctionCallArgs()
    {
        // pode estar vazio, mas precisa existir
    }

    FunctionCallArgs::~FunctionCallArgs()
    {
        // se não precisa fazer nada, pode deixar vazio
    }

    std::string FunctionCallArgs::getText()
    {

        sb.str("");
        sb.clear();

        int commaCount = callArgs.size();
        int argIndex = 1;
        for (auto arg : callArgs)
        {
            bool hasComma = (argIndex < commaCount);
            sb << util::format("{}:{}", arg->argument, arg->value->getText());
            if (hasComma)
            {
                sb << ",";
            }

            argIndex++;
        }

        return sb.str();
    }

    void FunctionCallArgs::addCallArg(std::shared_ptr<FunctionCallArg> callArg)
    {
        callArgs.push_back(callArg);
    }

    // Function Call
    FunctionCall::FunctionCall(std::shared_ptr<Function> function, std::shared_ptr<FunctionCallArgs> callArgs)
        : function(function), callArgs(callArgs)
    {
    }

    FunctionCall::~FunctionCall()
    {
    }

    std::string FunctionCall::getText()
    {
        sb.str("");
        sb.clear();
        sb << util::format("call {} {}({})", function->getFunctionReturnType()->getText(), function->getFunctionName(), callArgs->getText());
        return sb.str();
    }

    Statement::Statement()
        : statementList()
    {
    }

    Statement::Statement(std::vector<ValidStatement> statementList)
        : statementList(statementList)
    {
    }

    Statement::~Statement()
    {
    }

    void Statement::addStatement(ValidStatement statement)
    {

        std::visit([](const auto &stmtPtr)
                   {
        if (!stmtPtr) {
            throw HLIRException("Attempted to add a nullptr statement.");
        } }, statement);

        statementList.emplace_back(statement);
    }

    std::vector<ValidStatement> Statement::getStatements()
    {
        return statementList;
    }

    std::string Statement::getText()
    {
        sb.str("");
        sb.clear();

        sb << "\n";

        for (const auto &stmt : statementList)
        {
            std::visit([this](const auto &stmtPtr)
                       {
                           using T = std::decay_t<decltype(*stmtPtr)>;

                           if constexpr (std::is_same_v<T, Expr>)
                           {
                               sb << util::format(" {}\n", stmtPtr->getText());
                           }
                           else if constexpr (std::is_same_v<T, FunctionCall>)
                           {
                               sb << util::format(" {}\n", stmtPtr->getText());
                           } },
                       stmt);
        }

        return sb.str();
    }
}