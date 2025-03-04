#include "../../headers/Hlir.h"
#include "../../headers/Utils.h"

namespace hlir
{
    /**
     * @brief Represents a function in the HLIR (High-Level Intermediate Representation)
     * 
     * The Function class is responsible for managing function declarations, 
     * their arguments, return types, and scope hierarchy.
     */
    Function::Function() : external(false), variedArguments(false), 
                           languageType(tokenMap::IRON_LANG), inlineFunction(false),
                           argFunction(false), labelId(0), varId(0)
    {
    }

    Function::~Function() = default;

    /**
     * @brief Marks this function as an inline function
     */
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

    std::shared_ptr<Statement> Function::getRootScope()
    {
        return rootStatement;
    }


    void Function::enterLocalScope(const std::shared_ptr<Statement> &statement)
    {
        if (!statement)
        {
            throw std::runtime_error(util::format("Function::enterLocalScope. Scope is null", ""));
        }

        try
        {
            // Garantir que o objeto está sendo gerenciado por um shared_ptr antes de usar shared_from_this
            const std::shared_ptr<Parent> parentPtr = shared_from_this();
            statement->setParent(parentPtr);
            
            // Este cast é redundante, já que estamos em um método Function
            // mas é mantido para verificação de segurança
            if (const auto functionPtr = std::dynamic_pointer_cast<Function>(parentPtr); !functionPtr)
            {
                throw std::runtime_error("Function::enterLocalScope. Failed to cast Parent to Function.");
            }
        }
        catch(const std::bad_weak_ptr& e)
        {
            // Captura exceção se o objeto não for gerenciado por shared_ptr
            throw std::runtime_error("Function::enterLocalScope. Object not managed by shared_ptr, cannot use shared_from_this()");
        }

        if (!rootStatement)
        {
            rootStatement = std::make_shared<Statement>();
        }
        statement->rootStatement = rootStatement;

        statementStack.push(statement);
    }

    void Function::exitLocalScope()
    {
        if (!statementStack.empty())
        {
            statementStack.pop();
        }
    }
    
    ScopeGuard Function::createScopeGuard(const std::shared_ptr<Statement> &statement)
    {
        // Fazemos um dynamic_cast para obter std::shared_ptr<Function>
        auto self = std::dynamic_pointer_cast<Function>(shared_from_this());
        return ScopeGuard(self, statement);
    }


    /**
     * @brief Searches for a variable in all available scopes and function arguments
     * 
     * This method searches for a variable in the following order:
     * 1. Local scope and all parent scopes
     * 2. Function arguments
     * 3. Parent function scopes (recursively)
     * 
     * @param varName Name of the variable to find
     * @param scopeNumbers Counter for tracking scope traversal depth
     * @return std::shared_ptr<Variable> Found variable or nullptr if not found
     */
    std::shared_ptr<Variable> Function::findVarAllScopesAndArg(const std::string &varName, uint scopeNumbers)
    {
        // Search in the local scope and parent scopes
        std::stack tempStack(statementStack);
        while (!tempStack.empty())
        {
            const std::shared_ptr<Statement> currentScope = tempStack.top();
            tempStack.pop();
            
            if (!currentScope)
            {
                continue;
            }
            
            if (auto variable = currentScope->findVarByName(varName))
            {
                if (scopeNumbers > 0)
                {
                    variable->changeToAnotherScope();
                }
                return variable;
            }
        }

        // Search in function arguments
        if (functionArgs)
        {
            if (const auto arg = functionArgs->findArgByName(varName))
            {
                auto variable = std::make_shared<Variable>()->set(arg->name, arg->type);
                if (scopeNumbers > 0)
                {
                    variable->changeToAnotherScope();
                }

                if (arg->signature)
                {
                    variable->setSignature(arg->signature);
                }

                variable->changeToFromFunctionArg();
                return variable;
            }
        }

        // Recursively search in parent function
        if (parentFunction)
        {
            scopeNumbers++;
            return parentFunction->findVarAllScopesAndArg(varName, scopeNumbers);
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
            const auto variable = std::make_shared<Variable>()->set(arg->name, arg->type);

            if (arg->signature)
            {
                variable->setSignature(arg->signature);
            }

            variable->changeToFromFunctionArg();
            return variable;
        }

        return nullptr;
    }

    std::shared_ptr<Variable> Function::getArgByName(const std::string &argName) const
    {

        if (const auto arg = functionArgs->findArgByName(argName))
        {
            return std::make_shared<Variable>()->set(arg->name, arg->type);
        }

        return nullptr;
    }

    std::vector<std::shared_ptr<Block>> Function::getAllBlocks()
    {
        std::vector<std::shared_ptr<Block>> blocks{};
        for (auto stmt: rootStatement->getStatements())
        {
            std::visit(
                    [this, &blocks](const auto &stmtPtr)
                    {
                        using T = std::decay_t<decltype(*stmtPtr)>;
                        if constexpr (std::is_same_v<T, Block>)
                        {
                            blocks.push_back(stmtPtr);
                        }
                    },
                    stmt);
        }

        return blocks;
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

    bool Function::isArgFunction()
    {
        return argFunction;
    }

    void Function::changeToArgFunction()
    {
        argFunction = true;
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

        try
        {
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
        catch(const std::bad_weak_ptr& e)
        {
            // O objeto não está sendo gerenciado por um shared_ptr
            throw HLIRException("Function::set. Object not managed by shared_ptr, cannot use shared_from_this()");
        }
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


        if (external)
        {
            const auto language = tokenMap::getTokenText(languageType);
            sb << util::format("extern {} fn {}({}):{}\n", language, functionName, functionArgs->getText(),
                               functionReturnType->getText());
        }
        else
        {

            sb << util::format("fn {}({}):{} { {}}\n", functionName, functionArgs->getText(),
                               functionReturnType->getText(), rootStatement->getText());
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

    std::shared_ptr<FunctionCall> FunctionCall::set(const std::string &functionCallName,
                                                    const std::shared_ptr<Function> &newFunction,
                                                    const std::shared_ptr<FunctionCallArgs> &newCallArgs)
    {
        if (functionCallName.empty())
        {
            throw HLIRException("FunctionCall::set. The functionCallName can't be empty");
        }

        if (!newFunction)
        {
            throw HLIRException("FunctionCall::set. The function can't be nullptr");
        }

        if (!newCallArgs)
        {
            throw HLIRException("FunctionCall::set. The CallArgs can't be nullptr");
        }

        const std::shared_ptr<Parent> parentPtr = shared_from_this();
        newFunction->setParent(parentPtr);
        newCallArgs->setParent(parentPtr);
        this->functionCallName = functionCallName;

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

    std::string FunctionCall::getFunctionCallName() const
    {
        return functionCallName;
    }

    std::string FunctionCall::getText()
    {
        sb.str("");
        sb.clear();
        sb << util::format("call {} {}({})", function->getFunctionReturnType()->getText(), functionCallName,
                           callArgs->getText());
        return sb.str();
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
        sb << util::format("return {} {}", variable->getVarType()->getText(), variable->getRealName());
        return sb.str();
    }

} // namespace hlir
