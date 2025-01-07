; ModuleID = 'file_1'
source_filename = "file_1"
target triple = "arm64-apple-macosx15.0.0"

define void @main() {
entry:
  %r = alloca i32, align 4
  %tmp_1 = alloca i32, align 4
  %b = alloca i32, align 4
  %a = alloca i32, align 4
  store i32 12, ptr %a, align 4
  store i32 15, ptr %b, align 4
  %load_a = load i32, ptr %a, align 4
  %load_b = load i32, ptr %b, align 4
  %tmp_tmp_1 = add i32 %load_a, %load_b
  store i32 %tmp_tmp_1, ptr %tmp_1, align 4
  ret void
}