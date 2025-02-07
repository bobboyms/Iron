
// Generated from Iron.g4 by ANTLR 4.13.2

#pragma once


#include "IronParser.h"
#include "antlr4-runtime.h"


/**
 * This interface defines an abstract listener for a parse tree produced by IronParser.
 */
class IronListener : public antlr4::tree::ParseTreeListener
{
public:
    virtual void enterProgram(IronParser::ProgramContext *ctx) = 0;
    virtual void exitProgram(IronParser::ProgramContext *ctx) = 0;

    virtual void enterImportStatement(IronParser::ImportStatementContext *ctx) = 0;
    virtual void exitImportStatement(IronParser::ImportStatementContext *ctx) = 0;

    virtual void enterQualifiedName(IronParser::QualifiedNameContext *ctx) = 0;
    virtual void exitQualifiedName(IronParser::QualifiedNameContext *ctx) = 0;

    virtual void enterEntryPoint(IronParser::EntryPointContext *ctx) = 0;
    virtual void exitEntryPoint(IronParser::EntryPointContext *ctx) = 0;

    virtual void enterStatementList(IronParser::StatementListContext *ctx) = 0;
    virtual void exitStatementList(IronParser::StatementListContext *ctx) = 0;

    virtual void enterReturnStatement(IronParser::ReturnStatementContext *ctx) = 0;
    virtual void exitReturnStatement(IronParser::ReturnStatementContext *ctx) = 0;

    virtual void enterFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx) = 0;
    virtual void exitFunctionDeclaration(IronParser::FunctionDeclarationContext *ctx) = 0;

    virtual void enterArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx) = 0;
    virtual void exitArrowFunctionInline(IronParser::ArrowFunctionInlineContext *ctx) = 0;

    virtual void enterArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx) = 0;
    virtual void exitArrowFunctionBlock(IronParser::ArrowFunctionBlockContext *ctx) = 0;

    virtual void enterFunctionSignature(IronParser::FunctionSignatureContext *ctx) = 0;
    virtual void exitFunctionSignature(IronParser::FunctionSignatureContext *ctx) = 0;

    virtual void enterFunctionReturnType(IronParser::FunctionReturnTypeContext *ctx) = 0;
    virtual void exitFunctionReturnType(IronParser::FunctionReturnTypeContext *ctx) = 0;

    virtual void enterFunctionArgs(IronParser::FunctionArgsContext *ctx) = 0;
    virtual void exitFunctionArgs(IronParser::FunctionArgsContext *ctx) = 0;

    virtual void enterFunctionArg(IronParser::FunctionArgContext *ctx) = 0;
    virtual void exitFunctionArg(IronParser::FunctionArgContext *ctx) = 0;

    virtual void enterFunctionCall(IronParser::FunctionCallContext *ctx) = 0;
    virtual void exitFunctionCall(IronParser::FunctionCallContext *ctx) = 0;

    virtual void enterFunctionCallArgs(IronParser::FunctionCallArgsContext *ctx) = 0;
    virtual void exitFunctionCallArgs(IronParser::FunctionCallArgsContext *ctx) = 0;

    virtual void enterFunctionCallArg(IronParser::FunctionCallArgContext *ctx) = 0;
    virtual void exitFunctionCallArg(IronParser::FunctionCallArgContext *ctx) = 0;

    virtual void enterVarDeclaration(IronParser::VarDeclarationContext *ctx) = 0;
    virtual void exitVarDeclaration(IronParser::VarDeclarationContext *ctx) = 0;

    virtual void enterAssignment(IronParser::AssignmentContext *ctx) = 0;
    virtual void exitAssignment(IronParser::AssignmentContext *ctx) = 0;

    virtual void enterVarAssignment(IronParser::VarAssignmentContext *ctx) = 0;
    virtual void exitVarAssignment(IronParser::VarAssignmentContext *ctx) = 0;

    virtual void enterExpr(IronParser::ExprContext *ctx) = 0;
    virtual void exitExpr(IronParser::ExprContext *ctx) = 0;

    virtual void enterNumber(IronParser::NumberContext *ctx) = 0;
    virtual void exitNumber(IronParser::NumberContext *ctx) = 0;

    virtual void enterDataFormat(IronParser::DataFormatContext *ctx) = 0;
    virtual void exitDataFormat(IronParser::DataFormatContext *ctx) = 0;

    virtual void enterVarTypes(IronParser::VarTypesContext *ctx) = 0;
    virtual void exitVarTypes(IronParser::VarTypesContext *ctx) = 0;
};
