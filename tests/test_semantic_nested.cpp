#include "test_semantic_common.cpp"

// Test fixture for nested function tests
class SemanticNestedTests : public SemanticAnalysisTestBase {};

TEST_F(SemanticNestedTests, TestBasicNestedFunctions)
{
    const std::string input = R"(
        fn main() {
            let p:int = 16
            let inline:fn = (a:int, b:int):int -> a * b / p

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - p
                    let block:fn = (a:int, x:int):int -> {
                        return ((a * x) / r) - p
                    }

                    return r
                }
                return block(a:10,x:20)
            }

            block(a:10,x:30)
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticNestedTests, TestNestedFunctionTypeMismatch)
{
    std::string input = R"(
        fn main() {
            let p:int = 16
            let inline:fn = (a:int, b:int):int -> a * b / p

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - p
                    let block:fn = (a:int, x:int):int -> {
                        return ((a * x) / r) - p
                    }
                    return r
                }
                return block(a:10,x:20.25)
            }

            block(a:10,x:30)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticNestedTests, TestOuterCallTypeMismatch)
{
    const std::string input = R"(
        fn main() {
            let p:int = 16
            let inline:fn = (a:int, b:int):int -> a * b / p

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - p
                    let block:fn = (a:int, x:int):int -> {
                        return ((a * x) / r) - p
                    }
                    return r
                }
                return block(a:10,x:20)
            }

            block(a:10,x:30.5)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticNestedTests, TestUndefinedVariableInNestedFunction)
{
    std::string input = R"(
        fn main() {
            // let p:int = 16
            let inline:fn = (a:int, b:int):int -> a * b / p

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - p
                    let block:fn = (a:int, x:int):int -> {
                        return ((a * x) / r) - p
                    }
                    return r
                }
                return block(a:10,x:20)
            }

            block(a:10,x:30.5)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}

TEST_F(SemanticNestedTests, TestTypeMismatchInNestedFunction)
{
    const std::string input = R"(
        fn main() {
            let p:string = "16"
            let inline:fn = (a:int, b:int):int -> a * b / p

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - p
                    let block:fn = (a:int, x:int):int -> {
                        return ((a * x) / r) - p
                    }
                    return 25

                }
                return block(a:10,x:20)
            }

            block(a:10,x:30.5)
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::TypeMismatchException);
}

TEST_F(SemanticNestedTests, TestFunctionCallInNestedFunction)
{
    const std::string input = R"(
        fn sub(a:int):int { return 0 }

        fn main() {
            let p:int = 16
            let inline:fn = (a:int, b:int):int -> a * b / p

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - p
                    let block:fn = (a:int, x:int):int -> {
                        return ((a * x) / r) - p
                    }
                    return r
                }
                return block(a:10,x:sub(a:25))
            }

            block(a:10,x:30)
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticNestedTests, TestComplexNestedFunctions)
{
    std::string input = R"(
        fn sub(a:int):int {return 0}

        fn main() {
            let p:string = "16"
            let inline:fn = (a:int, b:int):int -> a * b

            let block2:fn = (a:int, x:int):int -> {
                    let p:int = 12
                    let r:int = a * x
                    let block:fn = (a:int, x:int):int -> {
                       return ((a * x) / r) - p
                    }
                    return 0
                }

            let block:fn = (a:int, x:int):int -> {
                let block:fn = (a:int, x:int):int -> {
                    let r:int = a * x - 10
                    let block:fn = (a:int, x:int):int -> {
                        return ((a * x) / r) - 20 * inline(a:a,b:x)
                    }
                    return 2
                }

                return block(a:10,x:block2(a:25, x:sub(a:12)))
            }

            (block(a:10,x:30) - block2(a:25, x:sub(a:12)) * 2.98) / sub(a:15)
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticNestedTests, TestNestedScopeVariableRedeclaration)
{
    const std::string input = R"(
        fn soma(n:float): int {
            let x: float = 25.32
            let block:fn = (a:int, b:float):int -> {
                let block:fn = (a:int, b:float):int -> {
                    let block:fn = (a:int, b:float):int -> {return 0}
                    let result:float =  block(a:12, b:12.26) * x
                    return 0
                }
                let result:int =  27 * block(a:12, b:12.26)
                return 22
            }
            return 0
        }
    )";

    EXPECT_NO_THROW(runAnalysis(input));
}

TEST_F(SemanticNestedTests, TestUndefinedVariableInNestedScope)
{
    std::string input = R"(
        fn soma(n:float): int {
            let x: float = 25.32
            let block:fn = (a:int, b:float):int -> {
                let block:fn = (a:int, b:float):int -> {
                    let block:fn = (a:int, b:float):int -> {return 0}
                    let result:float =  block(a:12, b:12.26) * xt
                    return 0
                }
                let result:float =  block(a:12, b:12.26)
                return 0
            }
            return 0
        }
    )";

    EXPECT_THROW(runAnalysis(input), iron::VariableNotFoundException);
}