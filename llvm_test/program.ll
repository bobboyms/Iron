; ModuleID = 'file_1'
source_filename = "file_1"
target triple = "arm64-apple-macosx15.0.0"

declare i32 @printf(ptr, ...)

define i32 @main() {
entry:
  %var_2 = alloca i32, align 4
  %idade = alloca i32, align 4
  store i32 28, ptr %idade, align 4
  %var_1 = alloca [18 x i8], align 1
  store [18 x i8] c"\22Resultado: %i\\n\22\00", ptr %var_1, align 1
  %str_ptr = getelementptr [18 x i8], ptr %var_1, i32 0, i32 0
  %load_idade = load i32, ptr %idade, align 4
  %call_printf = call i32 (ptr, ...) @printf(ptr %str_ptr, i32 %load_idade)
  store i32 0, ptr %var_2, align 4
  %load_var_2 = load i32, ptr %var_2, align 4
  ret i32 %load_var_2
}