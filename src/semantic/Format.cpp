// #include <string>
// #include "../headers/SemanticAnalysis.h"
//
// namespace iron
// {
//
//     void SemanticAnalysis::visitFormatStatement(IronParser::FormatStatementContext *ctx)
//     {
//         const uint line = ctx->getStart()->getLine();
//         const uint col = ctx->getStart()->getCharPositionInLine();
//         auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);
//
//         if (const auto specifiers = parseFormatSpecifiers(ctx->format->getText(), line, caretLine, codeLine);
//             !specifiers.empty())
//         {
//             visitFormatArguments(ctx->formatArguments(), specifiers);
//         }
//     }
//
//     void SemanticAnalysis::visitFormatArguments(IronParser::FormatArgumentsContext *ctx,
//                                                 const std::vector<std::pair<std::string, int>> &specifiers)
//     {
//
//         const uint line = ctx->getStart()->getLine();
//         const uint col = ctx->getStart()->getCharPositionInLine();
//         auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);
//
//         auto argSize = 0;
//         for (auto const child: ctx->children)
//         {
//             if (const auto specifierArg = dynamic_cast<IronParser::FormatArgumentContext *>(child))
//             {
//                 argSize++;
//             }
//         }
//
//         if (argSize != specifiers.size())
//         {
//             throw ArgumentCountMismatchException(util::format(
//                     "the number of arguments must have the same number of specifiers\n"
//                     "Line: {}, Scope: {}\n\n"
//                     "{}\n"
//                     "{}\n",
//                     color::colorText(std::to_string(line), color::YELLOW),
//                     color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
//         }
//
//         size_t specIndex = 0;
//         for (auto *child: ctx->children)
//         {
//             // Verifica se é de fato um nó do tipo FormatArgumentContext
//             if (const auto specifierArg = dynamic_cast<IronParser::FormatArgumentContext *>(child))
//             {
//                 // Pegamos o specifier correspondente a este argumento
//                 const auto &specifier = specifiers[specIndex++];
//                 visitFormatArgument(specifierArg, specifier);
//             }
//         }
//     }
//
//
//     void SemanticAnalysis::visitFormatArgument(IronParser::FormatArgumentContext *ctx,
//                                                const std::pair<std::string, int> &specifier)
//     {
//         const uint line = ctx->getStart()->getLine();
//         const uint col = ctx->getStart()->getCharPositionInLine();
//         auto [caretLine, codeLine] = getCodeLineAndCaretLine(line, col, 0);
//
//         if (ctx->dataFormat())
//         {
//             const auto value = ctx->dataFormat()->getText();
//             auto type = tokenMap::determineType(value);
//
//             if (auto [spec, specifierType] = specifier; type != specifierType)
//             {
//                 auto strSpecifierType = specifierType == tokenMap::REAL_NUMBER ? "Float / Double"
//                                                                                : tokenMap::getTokenText(specifierType);
//
//                 auto strExprType = type == tokenMap::REAL_NUMBER ? "Float / Double" : tokenMap::getTokenText(type);
//
//                 throw TypeMismatchException(util::format(
//                         "Specifier {} has a type {}, but the value {} type is {}\n"
//                         "Line: {}, Scope: {}\n\n"
//                         "{}\n"
//                         "{}\n",
//                         color::colorText(spec, color::BOLD_GREEN),
//                         color::colorText(strSpecifierType, color::BOLD_GREEN),
//                         color::colorText(value, color::BOLD_BLUE),
//                         color::colorText(tokenMap::getTokenText(type), color::BOLD_BLUE),
//                         color::colorText(std::to_string(line), color::YELLOW),
//                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
//             }
//         }
//
//         if (ctx->varName)
//         {
//
//
//             const auto varName = ctx->varName->getText();
//             const auto currentFunction = getCurrentFunction();
//             const auto variable = currentFunction->findVarAllScopesAndArg(varName);
//             if (!variable)
//             {
//                 throw VariableNotFoundException(util::format(
//                         "Variable '{}' not found.\n"
//                         "Line: {}, Scope: {}\n\n"
//                         "{}\n"
//                         "{}\n",
//                         color::colorText(varName, color::BOLD_GREEN),
//                         color::colorText(std::to_string(line), color::YELLOW),
//                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
//             }
//
//             auto varType = variable->type;
//             if (varType == tokenMap::TYPE_FLOAT || varType == tokenMap::TYPE_DOUBLE)
//             {
//                 varType = tokenMap::REAL_NUMBER;
//             }
//
//             if (auto [spec, specifierType] = specifier; variable->type != specifierType)
//             {
//
//                 auto strSpecifierType = specifierType == tokenMap::REAL_NUMBER ? "Float / Double"
//                                                                                : tokenMap::getTokenText(specifierType);
//                 auto strExprType =
//                         varType == tokenMap::REAL_NUMBER ? "Float / Double" : tokenMap::getTokenText(varType);
//
//
//                 throw TypeMismatchException(util::format(
//                         "Specifier {} has a type {}, but the variable {} type is {}\n"
//                         "Line: {}, Scope: {}\n\n"
//                         "{}\n"
//                         "{}\n",
//                         color::colorText(spec, color::BOLD_GREEN),
//                         color::colorText(tokenMap::getTokenText(specifierType), color::BOLD_GREEN),
//                         color::colorText(varName, color::BOLD_BLUE),
//                         color::colorText(tokenMap::getTokenText(variable->type), color::BOLD_BLUE),
//                         color::colorText(std::to_string(line), color::YELLOW),
//                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
//             }
//         }
//
//         if (ctx->expr())
//         {
//             //.
//             auto [_, exprType] = visitExpr(ctx->expr());
//
//             if (exprType == tokenMap::TYPE_FLOAT || exprType == tokenMap::TYPE_DOUBLE)
//             {
//                 exprType = tokenMap::REAL_NUMBER;
//             }
//
//             if (auto [spec, specifierType] = specifier; exprType != specifierType)
//             {
//                 auto strSpecifierType = specifierType == tokenMap::REAL_NUMBER ? "Float / Double"
//                                                                                : tokenMap::getTokenText(specifierType);
//                 auto strExprType =
//                         exprType == tokenMap::REAL_NUMBER ? "Float / Double" : tokenMap::getTokenText(exprType);
//
//                 throw TypeMismatchException(util::format(
//                         "Specifier {} has a type {}, but is incompatible with result of the expression type {}\n"
//                         "Line: {}, Scope: {}\n\n"
//                         "{}\n"
//                         "{}\n",
//                         color::colorText(spec, color::BOLD_GREEN),
//                         color::colorText(strSpecifierType, color::BOLD_GREEN),
//                         color::colorText(strExprType, color::BOLD_BLUE),
//                         color::colorText(std::to_string(line), color::YELLOW),
//                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
//             }
//         }
//
//         if (ctx->functionCall())
//         {
//             const auto functionCallName = ctx->functionCall()->functionName->getText();
//             const auto calledFunction = scopeManager->getFunctionDeclarationByName(functionCallName);
//             if (!calledFunction)
//             {
//                 throw FunctionNotFoundException(util::format(
//                         "Function {} not found.\n"
//                         "Line: {}, Scope: {}\n\n"
//                         "{}\n"
//                         "{}\n",
//                         color::colorText(functionCallName, color::BOLD_GREEN),
//                         color::colorText(std::to_string(line), color::YELLOW),
//                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
//             }
//
//             auto funcReturnType = calledFunction->getReturnType();
//             if (funcReturnType == tokenMap::TYPE_FLOAT || funcReturnType == tokenMap::TYPE_DOUBLE)
//             {
//                 funcReturnType = tokenMap::REAL_NUMBER;
//             }
//
//             if (auto [spec, specifierType] = specifier; funcReturnType != specifierType)
//             {
//                 auto strSpecifierType = specifierType == tokenMap::REAL_NUMBER ? "Float / Double"
//                                                                                : tokenMap::getTokenText(specifierType);
//                 throw TypeMismatchException(util::format(
//                         "Specifier {} has a type {}, but is incompatible with result of the function {} with return "
//                         "type {}\n"
//                         "Line: {}, Scope: {}\n\n"
//                         "{}\n"
//                         "{}\n",
//                         color::colorText(spec, color::BOLD_GREEN),
//                         color::colorText(strSpecifierType, color::BOLD_GREEN),
//                         color::colorText(functionCallName, color::BOLD_BLUE),
//                         color::colorText(tokenMap::getTokenText(calledFunction->getReturnType()), color::BOLD_BLUE),
//                         color::colorText(std::to_string(line), color::YELLOW),
//                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
//             }
//         }
//     }
//
//
//     // Função que analisa a string de formatação e retorna os especificadores encontrados
//     std::vector<std::pair<std::string, int>> SemanticAnalysis::parseFormatSpecifiers(const std::string &format,
//                                                                                      uint line,
//                                                                                      const std::string &caretLine,
//                                                                                      const std::string &codeLine) const
//     {
//
//         std::vector<std::pair<std::string, int>> specifiers;
//
//         // Expressão regular para identificar um especificador printf
//         // Explicação rápida:
//         // %                             -> inicia o especificador
//         // ([-+0 #]*)?                  -> flags opcionais
//         // (\d+)?                       -> largura (width) opcional
//         // (\.\d+)?                     -> precisão opcional (ponto seguido de dígitos)
//         // (hh|h|ll|l|L)?               -> modificador de comprimento (length) opcional
//         // ([diufFeEgGxXoscpaA%])        -> conversor obrigatório (o tipo)
//         std::regex pattern(R"(%([-+0 #]*)?(\d+)?(\.\d+)?(hh|h|ll|l|L)?([diufFeEgGxXoscpaA%]))");
//         auto begin = std::sregex_iterator(format.begin(), format.end(), pattern);
//         auto end = std::sregex_iterator();
//
//         for (auto it = begin; it != end; ++it)
//         {
//             const std::smatch &match = *it;
//             // match.str(0) contém o especificador completo, por exemplo, "%5.2f"
//             std::string fullSpec = match.str(0);
//             // O grupo 5 contém o conversor, ou seja, o caractere que indica o tipo
//             std::string conv = match.str(5);
//
//             // Determine o tipo com base no conversor
//             int type;
//             if (conv == "d" || conv == "i" || conv == "u" || conv == "x" || conv == "X" || conv == "o")
//             {
//                 type = tokenMap::TYPE_INT;
//             }
//             else if (conv == "f" || conv == "F" || conv == "e" || conv == "E" || conv == "g" || conv == "G")
//             {
//                 type = tokenMap::REAL_NUMBER;
//             }
//             else if (conv == "c")
//             {
//                 type = tokenMap::TYPE_CHAR;
//             }
//             else if (conv == "s")
//             {
//                 type = tokenMap::TYPE_STRING;
//             }
//             else
//             {
//                 throw UnrecognizedIdentifierException(util::format(
//                         "Specifier {} has not been recognized.\n"
//                         "Line: {}, Scope: {}\n\n"
//                         "{}\n"
//                         "{}\n",
//                         color::colorText(fullSpec, color::BOLD_GREEN),
//                         color::colorText(std::to_string(line), color::YELLOW),
//                         color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW), codeLine, caretLine));
//             }
//
//             specifiers.emplace_back(fullSpec, type);
//         }
//
//         return specifiers;
//     }
//
//     // Função que exibe os identificadores (conversion specifiers),
//     // o tipo de dado que cada um aceita e exemplos de uso.
//     void SemanticAnalysis::showConversionSpecifiersHelp()
//     {
//     }
//
// } // namespace iron
