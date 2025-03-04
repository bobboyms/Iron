// #include <string>
// #include <regex>
// #include "../headers/SemanticAnalysis.h"
//
// namespace iron
// {
//     /**
//      * @brief Processes a format statement (printf-style string formatting)
//      *
//      * Analyzes a format string, extracts format specifiers, and validates that
//      * the provided arguments match the types required by the specifiers.
//      *
//      * @param ctx The format statement context from the parser
//      */
//     void SemanticAnalysis::visitFormatStatement(IronParser::FormatStatementContext *ctx)
//     {
//         const auto lineNumber = ctx->getStart()->getLine();
//         const auto columnPosition = ctx->getStart()->getCharPositionInLine();
//         auto [caretLine, codeLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);
//
//         // Parse format string and extract specifiers
//         const auto specifiers = parseFormatSpecifiers(
//             ctx->format->getText(),
//             lineNumber,
//             caretLine,
//             codeLine
//         );
//
//         // If we found specifiers, validate the format arguments
//         if (!specifiers.empty() && ctx->formatArguments())
//         {
//             visitFormatArguments(ctx->formatArguments(), specifiers);
//         }
//     }
//
//     /**
//      * @brief Processes the arguments of a format statement
//      *
//      * Verifies that the number of arguments matches the number of format specifiers
//      * and that each argument's type matches its corresponding specifier.
//      *
//      * @param ctx The format arguments context from the parser
//      * @param specifiers The parsed specifiers from the format string
//      */
//     void SemanticAnalysis::visitFormatArguments(
//         IronParser::FormatArgumentsContext *ctx,
//         const std::vector<std::pair<std::string, int>> &specifiers)
//     {
//         const auto lineNumber = ctx->getStart()->getLine();
//         const auto columnPosition = ctx->getStart()->getCharPositionInLine();
//         auto [caretLine, codeLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);
//
//         // Count the number of format arguments
//         size_t argumentCount = 0;
//         for (const auto& child : ctx->children)
//         {
//             if (dynamic_cast<IronParser::FormatArgumentContext*>(child))
//             {
//                 argumentCount++;
//             }
//         }
//
//         // Verify argument count matches specifier count
//         if (argumentCount != specifiers.size())
//         {
//             throw ArgumentCountMismatchException(util::format(
//                 "Format error: Expected {} arguments to match {} format specifiers.\n"
//                 "Line: {}, Scope: {}\n\n"
//                 "{}\n"
//                 "{}\n",
//                 color::colorText(std::to_string(specifiers.size()), color::BOLD_GREEN),
//                 color::colorText(std::to_string(argumentCount), color::BOLD_BLUE),
//                 color::colorText(std::to_string(lineNumber), color::YELLOW),
//                 color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
//                 codeLine, caretLine));
//         }
//
//         // Process each format argument
//         size_t specifierIndex = 0;
//         for (const auto& child : ctx->children)
//         {
//             if (auto formatArgument = dynamic_cast<IronParser::FormatArgumentContext*>(child))
//             {
//                 const auto& specifier = specifiers[specifierIndex++];
//                 visitFormatArgument(formatArgument, specifier);
//             }
//         }
//     }
//
//     /**
//      * @brief Processes a single format argument
//      *
//      * Validates that the argument's type matches the format specifier's required type.
//      * Handles different kinds of arguments (literals, variables, expressions, function calls).
//      *
//      * @param ctx The format argument context from the parser
//      * @param specifier The format specifier this argument corresponds to
//      */
//     void SemanticAnalysis::visitFormatArgument(
//         IronParser::FormatArgumentContext *ctx,
//         const std::pair<std::string, int> &specifier)
//     {
//         const auto lineNumber = ctx->getStart()->getLine();
//         const auto columnPosition = ctx->getStart()->getCharPositionInLine();
//         auto [caretLine, codeLine] = getCodeLineAndCaretLine(lineNumber, columnPosition, 0);
//
//         // Unpack the specifier information
//         const auto& [specifierString, specifierType] = specifier;
//
//         // Format specifier type for display
//         const std::string displaySpecifierType =
//             specifierType == tokenMap::REAL_NUMBER
//             ? "Float / Double"
//             : tokenMap::getTokenText(specifierType);
//
//         // Handle literal value argument
//         if (ctx->dataFormat())
//         {
//             const auto literalValue = ctx->dataFormat()->getText();
//             auto valueType = tokenMap::determineType(literalValue);
//
//             if (valueType != specifierType)
//             {
//                 const std::string displayValueType =
//                     valueType == tokenMap::REAL_NUMBER
//                     ? "Float / Double"
//                     : tokenMap::getTokenText(valueType);
//
//                 throw TypeMismatchException(util::format(
//                     "Format error: Specifier '{}' requires type '{}', but literal value '{}' has type '{}'.\n"
//                     "Line: {}, Scope: {}\n\n"
//                     "{}\n"
//                     "{}\n",
//                     color::colorText(specifierString, color::BOLD_GREEN),
//                     color::colorText(displaySpecifierType, color::BOLD_GREEN),
//                     color::colorText(literalValue, color::BOLD_BLUE),
//                     color::colorText(displayValueType, color::BOLD_BLUE),
//                     color::colorText(std::to_string(lineNumber), color::YELLOW),
//                     color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
//                     codeLine, caretLine));
//             }
//         }
//         // Handle variable argument
//         else if (ctx->varName)
//         {
//             const auto variableName = ctx->varName->getText();
//             const auto currentFunction = getCurrentFunction();
//             const auto variable = currentFunction->findVarAllScopesAndArg(variableName);
//
//             // Verify variable exists
//             if (!variable)
//             {
//                 throw VariableNotFoundException(util::format(
//                     "Variable '{}' not found in format argument.\n"
//                     "Line: {}, Scope: {}\n\n"
//                     "{}\n"
//                     "{}\n",
//                     color::colorText(variableName, color::BOLD_GREEN),
//                     color::colorText(std::to_string(lineNumber), color::YELLOW),
//                     color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
//                     codeLine, caretLine));
//             }
//
//             // Handle floating point type normalization
//             auto variableType = variable->type;
//             if (variableType == tokenMap::TYPE_FLOAT || variableType == tokenMap::TYPE_DOUBLE)
//             {
//                 variableType = tokenMap::REAL_NUMBER;
//             }
//
//             // Verify type compatibility
//             if (variableType != specifierType)
//             {
//                 const std::string displayVariableType =
//                     variableType == tokenMap::REAL_NUMBER
//                     ? "Float / Double"
//                     : tokenMap::getTokenText(variableType);
//
//                 throw TypeMismatchException(util::format(
//                     "Format error: Specifier '{}' requires type '{}', but variable '{}' has type '{}'.\n"
//                     "Line: {}, Scope: {}\n\n"
//                     "{}\n"
//                     "{}\n",
//                     color::colorText(specifierString, color::BOLD_GREEN),
//                     color::colorText(displaySpecifierType, color::BOLD_GREEN),
//                     color::colorText(variableName, color::BOLD_BLUE),
//                     color::colorText(displayVariableType, color::BOLD_BLUE),
//                     color::colorText(std::to_string(lineNumber), color::YELLOW),
//                     color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
//                     codeLine, caretLine));
//             }
//         }
//         // Handle expression argument
//         else if (ctx->expr())
//         {
//             // Evaluate the expression's type
//             auto [expressionName, expressionType] = visitExpr(ctx->expr());
//
//             // Handle floating point type normalization
//             if (expressionType == tokenMap::TYPE_FLOAT || expressionType == tokenMap::TYPE_DOUBLE)
//             {
//                 expressionType = tokenMap::REAL_NUMBER;
//             }
//
//             // Verify type compatibility
//             if (expressionType != specifierType)
//             {
//                 const std::string displayExpressionType =
//                     expressionType == tokenMap::REAL_NUMBER
//                     ? "Float / Double"
//                     : tokenMap::getTokenText(expressionType);
//
//                 throw TypeMismatchException(util::format(
//                     "Format error: Specifier '{}' requires type '{}', but expression result has type '{}'.\n"
//                     "Line: {}, Scope: {}\n\n"
//                     "{}\n"
//                     "{}\n",
//                     color::colorText(specifierString, color::BOLD_GREEN),
//                     color::colorText(displaySpecifierType, color::BOLD_GREEN),
//                     color::colorText(displayExpressionType, color::BOLD_BLUE),
//                     color::colorText(std::to_string(lineNumber), color::YELLOW),
//                     color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
//                     codeLine, caretLine));
//             }
//         }
//         // Handle function call argument
//         else if (ctx->functionCall())
//         {
//             const auto functionName = ctx->functionCall()->functionName->getText();
//             const auto function = verifyFunctionExists(functionName, lineNumber, columnPosition);
//
//             // Handle floating point type normalization
//             auto returnType = function->getReturnType();
//             if (returnType == tokenMap::TYPE_FLOAT || returnType == tokenMap::TYPE_DOUBLE)
//             {
//                 returnType = tokenMap::REAL_NUMBER;
//             }
//
//             // Verify type compatibility
//             if (returnType != specifierType)
//             {
//                 throw TypeMismatchException(util::format(
//                     "Format error: Specifier '{}' requires type '{}', but function '{}' returns type '{}'.\n"
//                     "Line: {}, Scope: {}\n\n"
//                     "{}\n"
//                     "{}\n",
//                     color::colorText(specifierString, color::BOLD_GREEN),
//                     color::colorText(displaySpecifierType, color::BOLD_GREEN),
//                     color::colorText(functionName, color::BOLD_BLUE),
//                     color::colorText(tokenMap::getTokenText(function->getReturnType()), color::BOLD_BLUE),
//                     color::colorText(std::to_string(lineNumber), color::YELLOW),
//                     color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
//                     codeLine, caretLine));
//             }
//
//             // Process the function call
//             visitFunctionCall(ctx->functionCall());
//         }
//     }
//
//     /**
//      * @brief Parses a format string to extract format specifiers
//      *
//      * Uses a regular expression to identify format specifiers in a printf-style
//      * format string and determine the expected type for each specifier.
//      *
//      * @param formatString The format string to parse
//      * @param lineNumber Line number for error reporting
//      * @param caretLine Caret line for error reporting
//      * @param codeLine Source code line for error reporting
//      * @return std::vector<std::pair<std::string, int>> List of specifiers and their types
//      */
//     std::vector<std::pair<std::string, int>> SemanticAnalysis::parseFormatSpecifiers(
//         const std::string &formatString,
//         uint lineNumber,
//         const std::string &caretLine,
//         const std::string &codeLine) const
//     {
//         std::vector<std::pair<std::string, int>> specifiers;
//
//         // Regular expression for printf-style format specifiers
//         // %                             -> specifier start
//         // ([-+0 #]*)?                  -> optional flags
//         // (\d+)?                       -> optional width
//         // (\.\d+)?                     -> optional precision
//         // (hh|h|ll|l|L)?               -> optional length modifier
//         // ([diufFeEgGxXoscpaA%])       -> required type converter
//         std::regex specifierPattern(R"(%([-+0 #]*)?(\d+)?(\.\d+)?(hh|h|ll|l|L)?([diufFeEgGxXoscpaA%]))");
//
//         auto matchBegin = std::sregex_iterator(formatString.begin(), formatString.end(), specifierPattern);
//         auto matchEnd = std::sregex_iterator();
//
//         for (auto it = matchBegin; it != matchEnd; ++it)
//         {
//             const std::smatch &match = *it;
//             std::string fullSpecifier = match.str(0);  // Complete specifier (e.g., "%5.2f")
//             std::string typeConverter = match.str(5);  // Type character (e.g., "d", "f", "s")
//
//             // Determine type based on the converter character
//             int specifierType;
//             if (typeConverter == "d" || typeConverter == "i" ||
//                 typeConverter == "u" || typeConverter == "x" ||
//                 typeConverter == "X" || typeConverter == "o")
//             {
//                 specifierType = tokenMap::TYPE_INT;
//             }
//             else if (typeConverter == "f" || typeConverter == "F" ||
//                     typeConverter == "e" || typeConverter == "E" ||
//                     typeConverter == "g" || typeConverter == "G")
//             {
//                 specifierType = tokenMap::REAL_NUMBER;
//             }
//             else if (typeConverter == "c")
//             {
//                 specifierType = tokenMap::TYPE_CHAR;
//             }
//             else if (typeConverter == "s")
//             {
//                 specifierType = tokenMap::TYPE_STRING;
//             }
//             else if (typeConverter == "%")
//             {
//                 // %% is a literal % - skip this as it doesn't need an argument
//                 continue;
//             }
//             else
//             {
//                 throw UnrecognizedIdentifierException(util::format(
//                     "Unrecognized format specifier: '{}'.\n"
//                     "Line: {}, Scope: {}\n\n"
//                     "{}\n"
//                     "{}\n\n"
//                     "Hint: Valid type specifiers are d, i, u, f, F, e, E, g, G, x, X, o, c, s.",
//                     color::colorText(fullSpecifier, color::BOLD_GREEN),
//                     color::colorText(std::to_string(lineNumber), color::YELLOW),
//                     color::colorText(scopeManager->currentScopeName(), color::BOLD_YELLOW),
//                     codeLine, caretLine));
//             }
//
//             specifiers.emplace_back(fullSpecifier, specifierType);
//         }
//
//         return specifiers;
//     }
//
//     /**
//      * @brief Provides help information about format specifiers
//      *
//      * Shows information about available format specifiers, their corresponding
//      * data types, and usage examples.
//      */
//     void SemanticAnalysis::showConversionSpecifiersHelp()
//     {
//         // This could be implemented to show help about format specifiers
//         // Currently not used but kept for potential future implementation
//     }
//
// } // namespace iron
