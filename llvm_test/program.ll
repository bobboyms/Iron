; ModuleID = 'file_1'
source_filename = "file_1"
target triple = "arm64-apple-macosx15.0.0"

declare i32 @printf(ptr, ...)

define i32 @main() {
entry:
  %var_6 = alloca i32, align 4
  %idade = alloca i32, align 4
  %var_3 = alloca i32, align 4
  %var_2 = alloca i32, align 4
  %var_1 = alloca i32, align 4
  store i32 28, ptr %var_1, align 4
  store i32 3, ptr %var_2, align 4
  %load_var_1 = load i32, ptr %var_1, align 4
  %load_var_2 = load i32, ptr %var_2, align 4
  %rplus = add i32 %load_var_1, %load_var_2
  store i32 %rplus, ptr %var_3, align 4
  %load_var_3 = load i32, ptr %var_3, align 4
  store i32 %load_var_3, ptr %idade, align 4
  %var_4 = alloca [24 x i8], align 1
  store [21 x i8] c"Idade: %u Nome: %s \0A\00", ptr %var_4, align 1
  %var_5 = alloca [9 x i8], align 1
  store [7 x i8] c"Taliba\00", ptr %var_5, align 1
  %str_ptr = getelementptr [24 x i8], ptr %var_4, i32 0, i32 0
  %load_idade = load i32, ptr %idade, align 4
  %str_ptr1 = getelementptr [9 x i8], ptr %var_5, i32 0, i32 0
  %call_printf = call i32 (ptr, ...) @printf(ptr %str_ptr, i32 %load_idade, ptr %str_ptr1)
  store i32 0, ptr %var_6, align 4
  %load_var_6 = load i32, ptr %var_6, align 4
  ret i32 %load_var_6
}