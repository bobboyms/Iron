#include "test_semantic_common.cpp"

// Test fixture for import and module tests
class SemanticModuleTests : public SemanticAnalysisTestBase {};

TEST_F(SemanticModuleTests, TestMissingImport)
{
    const std::string input = R"(
        //import std.output.printf

        fn main():int
        {
            printf(format:"Idade: %u, Sexo: %s", idade:25, sexo:"masculina")
            return 0
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::FunctionNotFoundException);
}

TEST_F(SemanticModuleTests, TestValidImport)
{
    const std::string input = R"(
        import std.output.printf

        fn main():int
        {
            printf(format:"Idade: %u, Sexo: %s", idade:25, sexo:"masculina")
            return 0
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticModuleTests, TestNonexistentModule)
{
    const std::string input = R"(
        import std.output.printex

        fn main():int
        {
            printf(format:"Idade: %u, Sexo: %s", idade:25, sexo:"masculina")
            return 0
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ModuleNotFoundException);
}

TEST_F(SemanticModuleTests, TestDuplicateImport)
{
    const std::string input = R"(
        import std.output.printf
        import std.output.printf

        fn main():int
        {
            printf(format:"Idade: %u, Sexo: %s", idade:25, sexo:"masculina")
            return 0
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::ModuleRedefinitionException);
}

TEST_F(SemanticModuleTests, TestMissingFunctionImport)
{
    const std::string input = R"(
        import std.output.printf
        // import std.math.PI

        fn main():int
        {
            printf(format:"Idade: %u, Sexo: %s", idade:25, sexo:"masculina", pi:PI())
            return 0
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::FunctionNotFoundException);
}

TEST_F(SemanticModuleTests, TestImportedFunctionAsVariable)
{
    const std::string input = R"(
        import std.output.printf

        fn main() {
            let inline:fn = (a:int):int -> a * 8
            let x:fn = printf
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticModuleTests, TestTransferringImportedFunction)
{
    const std::string input = R"(
        import std.output.printf

        fn main() {
            let x:fn = printf
            let y:fn = x
            let z:fn = y
        }
    )";
    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticModuleTests, TestUnimportedFunction)
{
    const std::string input = R"(
        fn main() {
            let x:fn = printf
        }
    )";
    EXPECT_THROW(runAnalysis(input), iron::FunctionNotFoundException);
}