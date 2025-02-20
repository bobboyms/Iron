#include "../../headers/Hlir.h"
#include "../../headers/Utils.h"

namespace hlir
{
    Function::Function() : external(false), variedArguments(false), languageType(tokenMap::IRON_LANG)
    {
    }

    Function::~Function()
    {
    }

    void Function::enableInline()
    {
        inlineFunction = true;
    }

    bool Function::isExternal() const
    {
        return external;
    }

    int Function::getLanguageType() const
    {
        return languageType;
    }

    void Function::setLanguageType(const int type)
    {
        languageType = type;
    }

    void Function::changeToExternal()
    {
        external = true;
    }

    void Function::changeToVariedArguments()
    {
        variedArguments = true;
    }

    bool Function::isVariedArguments() const
    {
        return variedArguments;
    }

    bool Function::getInline() const
    {
        return inlineFunction;
    }

    void Function::setParentFunction(const std::shared_ptr<Function> &function)
    {
        if (!function)
        {
            throw HLIRException("Function::parentFunction is null");
        }

        parentFunction = function;
    }

    std::shared_ptr<Statement> Function::getCurrentLocalScope()
    {
        if (!statementStack.empty())
        {
            return statementStack.top();
        }
        return nullptr;
    }

    void Function::enterLocalScope(const std::shared_ptr<Statement>& statement)
    {
        if (!statement)
        {
            throw std::runtime_error(util::format("Function::enterLocalScope. Scope is null", ""));
        }

        const std::shared_ptr<Parent> parentPtr = shared_from_this();
        statement->setParent(parentPtr);

        if (const auto functionPtr = std::dynamic_pointer_cast<Function>(parentPtr); !functionPtr)
        {
            throw std::runtime_error("Function::enterLocalScope. Failed to cast Parent to Function.");
        }

        statementList.push_back(statement);
        statementStack.push(statement);
    }

    void Function::exitLocalScope()
    {
        if (!statementStack.empty())
        {
            statementStack.pop();
        }
    }

    std::shared_ptr<Variable> Function::findVarAllScopesAndArg(const std::string &varName)
    {

        // verifica no escopo local e superiores
        std::stack<std::shared_ptr<Statement>> tempStack(statementStack);
        uint scopeNumbers = 0;
        while (!tempStack.empty())
        {
            auto currentScope = tempStack.top();
            tempStack.pop();

            if (const auto statementsScope = std::dynamic_pointer_cast<Statement>(currentScope))
            {
                if (auto variable = statementsScope->findVarByName(varName))
                {
                    if (scopeNumbers > 0)
                    {
                        variable->changeToAnotherScope();
                        return variable;
                    }
                    return variable;
                }
            }
            scopeNumbers++;
        }

        // verifica nos argumentos da função
        if (const auto arg = functionArgs->findArgByName(varName))
        {
            return std::make_shared<Variable>()->set(arg->name,arg->type);
        }

        if (parentFunction)
        {
            return parentFunction->findVarAllScopesAndArg(varName);
        }

        return nullptr;
    }

    std::shared_ptr<Variable> Function::findVarCurrentScopeAndArg(const std::string &varName)
    {
        if (const auto statement = std::dynamic_pointer_cast<Statement>(getCurrentLocalScope()))
        {
            if (auto variable = statement->findVarByName(varName))
            {
                return variable;
            }
        }

        if (const auto arg = functionArgs->findArgByName(varName))
        {
            return std::make_shared<Variable>()->set(arg->name,arg->type);
        }

        return nullptr;
    }

    std::shared_ptr<Variable> Function::getArgByName(const std::string &argName) const
    {

        if (const auto arg = functionArgs->findArgByName(argName))
        {
            return std::make_shared<Variable>()->set(arg->name,arg->type);
        }

        return nullptr;

    }

    std::shared_ptr<FunctionArgs> Function::getFunctionArgs()
    {
        return functionArgs;
    }

    std::shared_ptr<Function> Function::getParentFunction()
    {
        return parentFunction;
    }

    std::shared_ptr<Function> Function::clone() const
    {
        const auto newFunction = std::make_shared<Function>(); //->set(functionName, functionArgs, functionReturnType);
        newFunction->functionName = functionName;
        newFunction->functionArgs = functionArgs;
        newFunction->functionReturnType = functionReturnType;
        newFunction->parent = parent;
        newFunction->statementStack = statementStack;
        newFunction->languageType = languageType;
        newFunction->external = external;
        newFunction->variedArguments = variedArguments;
        newFunction->inlineFunction = inlineFunction;

        return newFunction;
    }

    std::string Function::generateLabel(const std::string &label)
    {
        return util::format("{}_{}", label, labelId++);
    }

    std::string Function::generateVarName()
    {
        return util::format("var_{}", varId++);
    }

    std::shared_ptr<Function> Function::set(const std::string &functionName,
                                            const std::shared_ptr<FunctionArgs> &functionArgs,
                                            const std::shared_ptr<Type> &functionReturnType)
    {


        if (!functionArgs)
        {
            throw HLIRException("FunctionArgs cannot be null.");
        }
        if (!functionReturnType)
        {
            throw HLIRException("FunctionReturnType cannot be null.");
        }

        const std::shared_ptr<Parent> parentPtr = shared_from_this();

        this->functionName = functionName;
        this->functionArgs = functionArgs;
        this->functionReturnType = functionReturnType;
        this->functionArgs->setParent(parentPtr);
        this->functionReturnType->setParent(parentPtr);

        auto functionPtr = std::dynamic_pointer_cast<Function>(parentPtr);
        if (!functionPtr)
        {
            throw HLIRException("Failed to cast Parent to Function.");
        }

        return functionPtr;
    }
    std::vector<std::shared_ptr<Statement>> Function::getStatementList()
    {
        return statementList;
    }

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


        for (const auto statement: statementList)
        {
            if (external)
            {
                const auto language = tokenMap::getTokenText(languageType);
                sb << util::format("extern {} fn {}({}):{}\n", language, functionName, functionArgs->getText(),
                                   functionReturnType->getText());
            }
            else
            {
                sb << util::format("fn {}({}):{} { {}}\n", functionName, functionArgs->getText(),
                           functionReturnType->getText(), statement->getText());
            }
        }

        return sb.str();
    }

    // Function Call

    std::vector<std::shared_ptr<FunctionCallArg>> FunctionCallArgs::getCallArgs()
    {
        return callArgs;
    }

    FunctionCallArgs::FunctionCallArgs() = default;

    FunctionCallArgs::~FunctionCallArgs() = default;

    FunctionCallArgs::FunctionCallArgs(const std::vector<std::shared_ptr<FunctionCallArg>> &callArgs) :
        callArgs(callArgs)
    {
    }

    std::string FunctionCallArgs::getText()
    {

        sb.str("");
        sb.clear();

        const uint commaCount = callArgs.size();
        int argIndex = 1;
        for (const auto &arg: callArgs)
        {
            const bool hasComma = (argIndex < commaCount);
            sb << util::format("{}:{}", arg->argument, arg->value->getText());
            if (hasComma)
            {
                sb << ",";
            }

            argIndex++;
        }

        return sb.str();
    }

    void FunctionCallArgs::addCallArg(const std::shared_ptr<FunctionCallArg> &callArg)
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

    std::shared_ptr<FunctionCallArgs> FunctionCall::getCallArgs()
    {
        return callArgs;
    }

    std::shared_ptr<FunctionCall> FunctionCall::set(const std::shared_ptr<Function> &newFunction,
                                                    const std::shared_ptr<FunctionCallArgs> &newCallArgs)
    {
        if (!newFunction)
        {
            throw HLIRException("The function can't be nullptr");
        }

        if (!newCallArgs)
        {
            throw HLIRException("The CallArgs can't be nullptr");
        }

        const std::shared_ptr<Parent> parentPtr = shared_from_this();
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
    FunctionCall::FunctionCall() = default;

    FunctionCall::~FunctionCall() = default;

    std::string FunctionCall::getText()
    {
        sb.str("");
        sb.clear();
        sb << util::format("call {} {}({})", function->getFunctionReturnType()->getText(), function->getFunctionName(),
                           callArgs->getText());
        return sb.str();
    }

    Statement::Statement() = default;
    Statement::~Statement() = default;

    std::shared_ptr<Statement> Statement::set(ValidStatement statement)
    {
        if (isValidStatementNull(statement))
        {
            throw HLIRException("Null statement provided to set method.");
        }

        std::shared_ptr<Parent> parentPtr = shared_from_this();
        statementList.push_back(statement);

        std::visit(
                [parentPtr](auto &&arg)
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
                    }
                },
                statement);

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

        std::visit(
                [](const auto &stmtPtr)
                {
                    if (!stmtPtr)
                    {
                        throw HLIRException("Attempted to add a nullptr statement in addStatement method.");
                    }
                },
                statement);

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

        for (const auto &stmt: statementList)
        {
            std::visit(
                    [this](const auto &stmtPtr)
                    {
                        using T = std::decay_t<decltype(*stmtPtr)>;
                        if constexpr (std::is_same_v<T, Assign>)
                        {
                            sb << util::format(" {}\n", stmtPtr->getText());
                        }
                        else if constexpr (std::is_same_v<T, Expr>)
                        {
                            sb << util::format(" {}\n", stmtPtr->getText());
                        }
                        else if constexpr (std::is_same_v<T, FunctionCall>)
                        {
                            sb << util::format(" {}\n", stmtPtr->getText());
                        }
                        else if constexpr (std::is_same_v<T, FuncReturn>)
                        {
                            sb << util::format(" {}\n", stmtPtr->getText());
                        }
                        else if constexpr (std::is_same_v<T, Block>)
                        {
                            sb << util::format(" {}\n", stmtPtr->getText());
                        }
                        else if constexpr (std::is_same_v<T, Conditional>)
                        {
                            sb << util::format(" {}\n", stmtPtr->getText());
                        }
                    },
                    stmt);
        }

        return sb.str();
    }

    std::shared_ptr<Value> Statement::getVariableValue(std::string varName)
    {
        std::shared_ptr<Value> value = nullptr;
        for (auto stmt: statementList)
        {
            std::visit(
                    [this, varName, &value](const auto &stmtPtr)
                    {
                        using T = std::decay_t<decltype(*stmtPtr)>;
                        if constexpr (std::is_same_v<T, Assign>)
                        {
                            if (stmtPtr->getVariable()->getVarName() == varName)
                            {
                                value = stmtPtr->getValue();
                            }
                        }
                    },
                    stmt);

            if (value != nullptr)
            {
                return value;
            }
        }

        return nullptr;
    }

    void Statement::addDeclaredVariable(const std::shared_ptr<Variable> &variable)
    {
        if (!variable)
        {
            throw HLIRException("Statement::addDeclaredVariable. Attempted to add a nullptr variable in addDeclaredVariable method.");
        }




        variableMap.insert({variable->getVarName(), variable});
    }

    std::shared_ptr<Variable> Statement::findVarByName(const std::string& varName)
    {

        if (const auto it = variableMap.find(varName); it != variableMap.end())
        {
            return it->second;
        }

        return nullptr;

    }


    // Function Return
    FuncReturn::FuncReturn(const std::shared_ptr<Function> &function, const std::shared_ptr<Variable> &variable)
    {
        if (!variable)
        {
            throw HLIRException("Variable is a nullptr.");
        }

        if (!function)
        {
            throw HLIRException("Function is a nullptr.");
        }

        if (function->getFunctionReturnType()->getType() != variable->getVarType()->getType())
        {
            throw HLIRException("Function returned a wrong type.");
        }

        this->function = function;
        this->variable = variable;
    }

    FuncReturn::~FuncReturn() = default;

    std::shared_ptr<Variable> FuncReturn::getVariable()
    {
        return variable;
    }

    std::string FuncReturn::getText()
    {
        sb.str("");
        sb.clear();
        sb << util::format("return {} {}", variable->getVarType()->getText(), variable->getVarName());
        return sb.str();
    }

} // namespace hlir
