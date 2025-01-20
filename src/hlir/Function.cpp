#include "../headers/Hlir.h"

namespace hlir
{
    Function::Function() {}
    Function::~Function() {}

    void Function::enableInline()
    {
        inlineFunction = true;
    }

    bool Function::getInline()
    {
        return inlineFunction;
    }

    void Function::setParentFunction(std::shared_ptr<Function> function)
    {
        parentFunction = function;
    }

    std::shared_ptr<Statement> Function::getStatement()
    {
        return statement;
    }

    std::shared_ptr<Function> Function::set(std::string newFunctionName, std::shared_ptr<FunctionArgs> newFunctionArgs, std::shared_ptr<Type> newFunctionReturnType)
    {
        functionName = newFunctionName;
        functionArgs = newFunctionArgs;
        functionReturnType = newFunctionReturnType;

        if (!functionArgs)
        {
            throw HLIRException("FunctionArgs cannot be null.");
        }
        if (!functionReturnType)
        {
            throw HLIRException("FunctionReturnType cannot be null.");
        }

        std::shared_ptr<Parent> parentPtr = shared_from_this();

        functionArgs->setParent(parentPtr);
        functionReturnType->setParent(parentPtr);

        auto assignPtr = std::dynamic_pointer_cast<Function>(parentPtr);
        if (!assignPtr)
        {
            throw HLIRException("Failed to cast Parent to Function.");
        }

        return assignPtr;
    }

    std::shared_ptr<FunctionArgs> Function::getFunctionArgs()
    {
        return functionArgs;
    }

    std::shared_ptr<Function> Function::getParentFunction()
    {
        return parentFunction;
    }

    std::shared_ptr<Function> Function::set(const std::string newFunctionName,
                                            const std::shared_ptr<FunctionArgs> newFunctionArgs,
                                            const std::shared_ptr<Type> newFunctionReturnType,
                                            const std::shared_ptr<Statement> newStatement)
    {
        functionName = newFunctionName;
        functionArgs = newFunctionArgs;
        functionReturnType = newFunctionReturnType;
        statement = newStatement;

        if (!functionArgs)
        {
            throw HLIRException("FunctionArgs cannot be null.");
        }
        if (!functionReturnType)
        {
            throw HLIRException("FunctionReturnType cannot be null.");
        }
        if (!statement)
        {
            throw HLIRException("Statement cannot be null.");
        }

        std::shared_ptr<Parent> parentPtr = shared_from_this();

        functionArgs->setParent(parentPtr);
        functionReturnType->setParent(parentPtr);
        statement->setParent(parentPtr);

        auto assignPtr = std::dynamic_pointer_cast<Function>(parentPtr);
        if (!assignPtr)
        {
            throw HLIRException("Failed to cast Parent to Function.");
        }

        return assignPtr;
    }

    std::string Function::getFunctionName()
    {
        return functionName;
    }

    std::shared_ptr<Type> Function::getFunctionReturnType()
    {
        return functionReturnType;
    }

    // void Function::setParent(std::shared_ptr<Parent> newParent)
    //{
    //     parent = newParent;
    // }

    std::string Function::getText()
    {
        sb.str("");
        sb.clear();
        if (statement && statement->getStatements().size() > 0)
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

    std::vector<std::shared_ptr<FunctionCallArg>> FunctionCallArgs::getCallArgs()
    {
        return callArgs;
    }

    FunctionCallArgs::FunctionCallArgs()
    {
    }

    FunctionCallArgs::~FunctionCallArgs()
    {
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
        if (!callArg)
        {
            throw HLIRException("FunctionCallArg cannot be nullptr.");
        }

        std::shared_ptr<Parent> parentPtr = shared_from_this();
        callArg->setParent(parentPtr);
        callArgs.push_back(callArg);
    }

    std::shared_ptr<Function> FunctionCall::getFunction()
    {
        return function;
    }

    std::shared_ptr<FunctionCall> FunctionCall::set(std::shared_ptr<Function> newFunction, std::shared_ptr<FunctionCallArgs> newCallArgs)
    {
        if (!newFunction)
        {
            throw HLIRException("The function can't be nullptr");
        }

        if (!newCallArgs)
        {
            throw HLIRException("The CallArgs can't be nullptr");
        }

        std::shared_ptr<Parent> parentPtr = shared_from_this();
        newFunction->setParent(parentPtr);
        newCallArgs->setParent(parentPtr);

        function = newFunction;
        callArgs = newCallArgs;

        // Realiza o cast para std::shared_ptr<FunctionCall>
        auto assignPtr = std::dynamic_pointer_cast<FunctionCall>(parentPtr);
        if (!assignPtr)
        {
            throw HLIRException("Failed to cast Parent to FunctionCall.");
        }

        return assignPtr;
    }

    // Function Call
    FunctionCall::FunctionCall()
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

    Statement::~Statement()
    {
    }

    std::shared_ptr<Statement> Statement::set(ValidStatement statement)
    {
        if (isValidStatementNull(statement))
        {
            throw HLIRException("Null statement provided to set method.");
        }

        std::shared_ptr<Parent> parentPtr = shared_from_this();
        statementList.push_back(statement);

        bool hasParentType = false;
        std::visit([parentPtr](auto &&arg)
                   {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::shared_ptr<Assign>>)
        {
            if (arg)
            {
                arg->setParent(parentPtr);
            }
        }
        if constexpr (std::is_same_v<T, std::shared_ptr<Expr>>)
        {
            if (arg)
            {
                arg->setParent(parentPtr);
            }
        }
        else if constexpr (std::is_same_v<T, std::shared_ptr<FunctionCall>>)
        {
            if (arg)
            {
                arg->setParent(parentPtr);
            }
        }
        else
        {
            throw HLIRException("Unsupported expression type encountered in set method.");
        } }, statement);

        auto assignPtr = std::dynamic_pointer_cast<Statement>(parentPtr);
        if (!assignPtr)
        {
            throw HLIRException("Failed to cast Parent to Statement in set method.");
        }

        return assignPtr;
    }

    std::string Statement::getNewVarName()
    {
        varId++;
        return util::format("var_{}", varId);
    }

    void Statement::addStatement(ValidStatement statement)
    {
        if (isValidStatementNull(statement))
        {
            throw HLIRException("Attempted to add a nullptr statement in addStatement method.");
        }

        std::visit([](const auto &stmtPtr)
                   {
        if (!stmtPtr) {
            throw HLIRException("Attempted to add a nullptr statement in addStatement method.");
        } }, statement);

        statementList.emplace_back(statement);

        if (logged)
        {
            util::printf("{}", getText());
        }
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
                        if constexpr (std::is_same_v<T, Assign>)
                       {
                           sb << util::format(" {}\n", stmtPtr->getText());
                       }else if constexpr (std::is_same_v<T, Expr>)
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

    std::shared_ptr<Variable> Statement::findVarByName(std::string varName)
    {

        std::shared_ptr<Variable> variable = nullptr;
        for (auto stmt : statementList)
        {
            std::visit([this, varName, &variable](const auto &stmtPtr)
                       {
                       using T = std::decay_t<decltype(*stmtPtr)>;
                        if constexpr (std::is_same_v<T, Assign>)
                       {

                        if (stmtPtr->getVariable()->getVarName() == varName) {
                            variable = stmtPtr->getVariable();
                        }

                       }else if constexpr (std::is_same_v<T, Expr>)
                       {
                        if (stmtPtr->getVariable()->getVarName() == varName) {
                            variable = stmtPtr->getVariable();
                        }
                       } },
                       stmt);

            if (variable != nullptr)
            {
                return variable;
            }
        }

        return nullptr;
    }
}
