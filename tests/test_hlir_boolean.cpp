#include "test_hlir_common.cpp"

// Test fixture for boolean expression HLIR tests
class HlirBooleanTests : public HlirTestBase {};

TEST_F(HlirBooleanTests, TestComplexBooleanExpressions)
{
    const std::string output = R"(
        fn main():void {
            var_1:boolean = true
            var_2:int = 3
            var_3:int = 1
            var_4:boolean = cmp GT var_2, var_3
            var_5:boolean = NOT var_4, var_1
            var_0:boolean = var_5
            var_7:int = 3
            var_8:int = 1
            var_9:boolean = cmp GT var_7, var_8
            var_6:boolean = var_9
            var_11:int = 3
            var_12:int = 1
            var_13:boolean = cmp NEQ var_11, var_12
            var_10:boolean = var_13
            var_15:int = 3
            var_16:int = 1
            var_17:boolean = cmp EQEQ var_15, var_16
            var_14:boolean = var_17
            var_19:int = 5
            var_20:int = 3
            var_21:boolean = cmp GT var_19, var_20
            var_22:int = 25
            var_23:int = 6
            var_24:int = MULT var_22, var_23
            var_25:boolean = var_24 int to boolean
            var_26:boolean = cmp NEQ var_21, var_25
            var_27:int = 5
            var_28:boolean = var_27 int to boolean
            var_29:boolean = cmp LT var_26, var_28
            var_30:int = 25
            var_31:int = 25
            var_32:boolean = cmp EQEQ var_30, var_31
            var_33:boolean = cmp NEQ var_29, var_32
            var_18:boolean = var_33
            var_35:int = 5
            var_36:int = 3
            var_37:boolean = cmp GT var_35, var_36
            var_38:int = 25
            var_39:int = 6
            var_40:int = MULT var_38, var_39
            var_41:boolean = var_40 int to boolean
            var_42:boolean = cmp NEQ var_37, var_41
            var_43:int = 5
            var_44:boolean = var_43 int to boolean
            var_45:boolean = cmp LT var_42, var_44
            var_46:int = 25
            var_47:int = 25
            var_48:boolean = cmp EQEQ var_46, var_47
            var_49:boolean = cmp NEQ var_45, var_48
            var_50:int = 32
            var_51:int = 2
            var_52:int = DIV var_50, var_51
            var_53:int = 5
            var_54:boolean = cmp GT var_52, var_53
            var_55:boolean = OR var_49, var_54
            var_34:boolean = var_55
            var_56:int = 12
            var_57:float = 1.6
            var_59:int = 5
            var_60:int = 3
            var_61:boolean = cmp GT var_59, var_60
            var_62:int = 6
            var_63:int = MULT var_56, var_62
            var_64:boolean = var_63 int to boolean
            var_65:boolean = cmp NEQ var_61, var_64
            var_66:int = 5
            var_67:boolean = var_66 int to boolean
            var_68:boolean = cmp LT var_65, var_67
            var_69:int = 25
            var_70:float = var_69 int to float
            var_71:boolean = cmp EQEQ var_70, var_57
            var_72:boolean = cmp NEQ var_68, var_71
            var_73:int = 32
            var_74:int = 2
            var_75:int = DIV var_73, var_74
            var_76:boolean = cmp GT var_75, var_56
            var_77:int = 2
            var_78:int = 2
            var_79:boolean = cmp GT var_77, var_78
            var_80:boolean = AND var_76, var_79
            var_81:boolean = OR var_72, var_80
            var_58:boolean = var_81
            var_83:int = 5
            var_84:boolean = cmp GT var_83, var_56
            var_85:int = 25
            var_86:int = 6
            var_87:int = MULT var_85, var_86
            var_88:boolean = cmp LT var_87, var_56
            var_89:int = 2
            var_90:boolean = var_89 int to boolean
            var_91:boolean = cmp NEQ var_88, var_90
            var_92:boolean = cmp NEQ var_84, var_91
            var_93:boolean = true
            var_94:int = 25
            var_95:int = 25
            var_96:boolean = cmp EQEQ var_94, var_95
            var_97:boolean = NOT var_96, var_93
            var_98:boolean = cmp EQEQ var_92, var_97
            var_82:boolean = var_98
        }
    )";

    const std::string input = R"(
        fn main() {
           //false ok
           let exprBool1:boolean = not 3 > 1

           //true ok
           let exprBool2:boolean = 3 > 1

           //true ok
           let exprBool3:boolean = 3 != 1

           //false
           let exprBool4:boolean = 3 == 1

           //false ok
           let exprBool5:boolean = 5 > 3 != (25 * 6) < 5 != (25 == 25)

           //true true ok
           let exprBool6:boolean = 5 > 3 != (25 * 6) < 5 != (25 == 25) or (32 /2) > 5

           let a:int = 12
           let b:float = 1.6

           //true ok
           let exprBool7:boolean = 5 > 3 != (a * 6) < 5 != (25 == b) or (32 /2) > a and 2 > 2

           // false ok
           let exprBool8:boolean = 5 > a != ((25 * 6) < a != 2) == (not (25 == 25))
        }

    )";

    runAnalysis(input, output);
}