/**
 * @file Statements.cpp
 * @brief Implementation of the Statement class and related functionality
 * @author Thiago Rodrigues
 * @date 2025-03-02
 */
#include "../../headers/Hlir.h"
#include "../../headers/Utils.h"

namespace hlir
{
    /**
     * @brief Represents a statement in the HLIR
     * 
     * The Statement class is responsible for managing a list of statements
     * and providing operations for working with them.
     */
    Statement::Statement() : varId(0), logged(false) 
    {
    }
    
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


    /**
     * @brief Inserts statements at a specific position in the statement list
     * 
     * @param stmts Statements to insert
     * @param pos Position at which to insert the statements
     */
    void Statement::insertStatementsAt(const std::vector<ValidStatement> &stmts, size_t pos)
    {
        // Ensure the position doesn't exceed the current list size
        pos = std::min(pos, statementList.size());
        
        if (logged) {
            util::printf(">> Inserting {} statements at position {} (current size: {})\n", 
                        stmts.size(), pos, statementList.size());
        }

        statementList.insert(statementList.begin() + pos, stmts.begin(), stmts.end());

        if (logged) {
            util::printf(">> New size of statementList after insertion: {}\n", statementList.size());
        }
    }


    void Statement::addStatement(ValidStatement statement)
    {

        // const auto function = std::dynamic_pointer_cast<FuncReturn>(statement->getParent());
        // if (!function)
        // {
        //     throw HLIRException("Failed to cast Function to Statement.");
        // }

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
        if (rootStatement)
        {
            rootStatement->addStatement(statement);
        }

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
                            sb << util::format("    {}\n", stmtPtr->getText());
                        }
                        else if constexpr (std::is_same_v<T, Expr>)
                        {
                            sb << util::format("    {}\n", stmtPtr->getText());
                        }
                        else if constexpr (std::is_same_v<T, FunctionCall>)
                        {
                            sb << util::format("    {}\n", stmtPtr->getText());
                        }
                        else if constexpr (std::is_same_v<T, FuncReturn>)
                        {
                            sb << util::format("    {}\n", stmtPtr->getText());
                        }
                        else if constexpr (std::is_same_v<T, Block>)
                        {
                            sb << util::format("{}\n", "");
                            sb << util::format(" {}\n", stmtPtr->getText());
                        }
                        else if constexpr (std::is_same_v<T, Conditional>)
                        {
                            sb << util::format("    {}\n", stmtPtr->getText());
                        }
                        else if constexpr (std::is_same_v<T, Jump>)
                        {
                            sb << util::format("    {}\n", stmtPtr->getText());
                        }
                    },
                    stmt);
        }

        return sb.str();
    }

    std::shared_ptr<Value> Statement::getValueFromVariable(std::string varName)
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

    bool Statement::haveReturn() const
    {
        bool haveReturn{false};
        for (auto stmt: statementList)
        {
            std::visit(
                    [this, &haveReturn](const auto &stmtPtr)
                    {
                        using T = std::decay_t<decltype(*stmtPtr)>;
                        if constexpr (std::is_same_v<T, FuncReturn>)
                        {
                            haveReturn = true;
                        }
                    },
                    stmt);

            if (haveReturn)
            {
                break;
            }
        }

        return haveReturn;
    }


    void Statement::addDeclaredVariable(const std::shared_ptr<Variable> &variable)
    {
        if (!variable)
        {
            throw HLIRException("Statement::addDeclaredVariable. Attempted to add a nullptr variable in "
                                "addDeclaredVariable method.");
        }

        if (findVarByName(variable->getVarName()))
        {
            throw std::invalid_argument("Attempted to add a variable with duplicate name.");
        }

        variableMap.insert({variable->getVarName(), variable});
    }

    std::shared_ptr<Variable> Statement::findVarByName(const std::string &varName)
    {

        if (const auto it = variableMap.find(varName); it != variableMap.end())
        {
            return it->second;
        }

        return nullptr;
    }

}