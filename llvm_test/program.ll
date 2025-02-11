formatname; ModuleID = 'file_1'
source_filename = "file_1"
target triple = "arm64-apple-macosx15.0.0"

declare i32 @printf(ptr, ...)

define i32 @main() {
entry:
  %var_1 = alloca i32, align 4
  %myStrLocal = alloca [10 x i8], align 1
  store [10 x i8] c"\22Nome %s\22\00", ptr %myStrLocal, align 1
  %str_ptr = getelementptr [10 x i8], ptr %myStrLocal, i32 0, i32 0
  %myStrLocal1 = alloca [9 x i8], align 1
  store [9 x i8] c"\22Taliba\22\00", ptr %myStrLocal1, align 1
  %str_ptr2 = getelementptr [9 x i8], ptr %myStrLocal1, i32 0, i32 0
  %call_printf = call i32 (ptr, ...) @printf(ptr %str_ptr, ptr %str_ptr2)
  store i32 0, ptr %var_1, align 4
  %load_var_1 = load i32, ptr %var_1, align 4
  ret i32 %load_var_1
}