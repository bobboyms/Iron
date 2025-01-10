; ModuleID = 'file_1'
source_filename = "file_1"
target triple = "arm64-apple-macosx15.0.0"

define void @gfn_main_block(i32 %a) {
entry:
  ret void
}

define void @sub() {
entry:
  ret void
}

define void @main() {
entry:
  %block = alloca ptr, align 8
  store ptr @gfn_main_block, ptr %block, align 8
  %loaded_block = load ptr, ptr %block, align 8
  call void %loaded_block(i32 10)
  call void @sub()
  ret void
}