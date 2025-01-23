; ModuleID = 'file_1'
source_filename = "file_1"
target triple = "arm64-apple-macosx15.0.0"

define i32 @sub(i32 %n, i32 %j) {
entry:
  ret i32 0
}

define i32 @main() {
entry:
  %x = alloca i32, align 4
  store i32 25, ptr %x, align 4
  %load_x = load i32, ptr %x, align 4
  %call_gfn_main_block = call i32 @gfn_main_block(i32 10, i32 20, i32 %load_x)
  ret i32 0
}

define i32 @gfn_main_block(i32 %a, i32 %b, i32 %x) {
entry:
  %v = alloca i32, align 4
  %var_5 = alloca i32, align 4
  %x_alloca4 = alloca i32, align 4
  %a_alloca2 = alloca i32, align 4
  %var_4 = alloca i32, align 4
  %n = alloca i32, align 4
  %var_3 = alloca i32, align 4
  %var_2 = alloca i32, align 4
  %x_alloca = alloca i32, align 4
  %a_alloca = alloca i32, align 4
  %var_1 = alloca i32, align 4
  store i32 %a, ptr %a_alloca, align 4
  %load_a = load i32, ptr %a_alloca, align 4
  store i32 %x, ptr %x_alloca, align 4
  %load_x = load i32, ptr %x_alloca, align 4
  %call_sub = call i32 @sub(i32 %load_a, i32 %load_x)
  store i32 %call_sub, ptr %var_1, align 4
  %call_sub1 = call i32 @sub(i32 5, i32 9)
  store i32 %call_sub1, ptr %var_2, align 4
  %load_var_1 = load i32, ptr %var_1, align 4
  %load_var_2 = load i32, ptr %var_2, align 4
  %rmult = sdiv i32 %load_var_1, %load_var_2
  store i32 %rmult, ptr %var_3, align 4
  %load_var_3 = load i32, ptr %var_3, align 4
  store i32 %load_var_3, ptr %n, align 4
  store i32 %a, ptr %a_alloca2, align 4
  %load_a3 = load i32, ptr %a_alloca2, align 4
  %load_n = load i32, ptr %n, align 4
  store i32 %x, ptr %x_alloca4, align 4
  %load_x5 = load i32, ptr %x_alloca4, align 4
  %call_gfn_gfn_main_block_block = call i32 @gfn_gfn_main_block_block(i32 %load_a3, i32 20, i32 %load_n, i32 %load_x5)
  store i32 %call_gfn_gfn_main_block_block, ptr %var_4, align 4
  %load_var_4 = load i32, ptr %var_4, align 4
  %load_n6 = load i32, ptr %n, align 4
  %rmult7 = sdiv i32 %load_var_4, %load_n6
  store i32 %rmult7, ptr %var_5, align 4
  %load_var_5 = load i32, ptr %var_5, align 4
  store i32 %load_var_5, ptr %v, align 4
  ret i32 0
}

define i32 @gfn_gfn_main_block_block(i32 %a, i32 %b, i32 %n, i32 %x) {
entry:
  %r = alloca i32, align 4
  %n_alloca5 = alloca i32, align 4
  %var_7 = alloca i32, align 4
  %var_6 = alloca i32, align 4
  %g = alloca float, align 4
  %var_5 = alloca float, align 4
  %x_alloca2 = alloca i32, align 4
  %var_4 = alloca i32, align 4
  %var_3 = alloca i32, align 4
  %var_2 = alloca i32, align 4
  %x_alloca = alloca i32, align 4
  %n_alloca = alloca i32, align 4
  %var_1 = alloca i32, align 4
  store i32 %n, ptr %n_alloca, align 4
  %load_n = load i32, ptr %n_alloca, align 4
  store i32 %x, ptr %x_alloca, align 4
  %load_x = load i32, ptr %x_alloca, align 4
  %call_sub = call i32 @sub(i32 %load_n, i32 %load_x)
  store i32 %call_sub, ptr %var_1, align 4
  %call_sub1 = call i32 @sub(i32 5, i32 9)
  store i32 %call_sub1, ptr %var_2, align 4
  %load_var_1 = load i32, ptr %var_1, align 4
  %load_var_2 = load i32, ptr %var_2, align 4
  %rmult = sdiv i32 %load_var_1, %load_var_2
  store i32 %rmult, ptr %var_3, align 4
  store i32 %x, ptr %x_alloca2, align 4
  %load_var_3 = load i32, ptr %var_3, align 4
  %load_x3 = load i32, ptr %x_alloca2, align 4
  %rmult4 = sdiv i32 %load_var_3, %load_x3
  store i32 %rmult4, ptr %var_4, align 4
  %load_var_4 = load i32, ptr %var_4, align 4
  %cast_var_4 = sitofp i32 %load_var_4 to float
  store float %cast_var_4, ptr %var_5, align 4
  %load_var_5 = load i32, ptr %var_5, align 4
  store i32 %load_var_5, ptr %g, align 4
  %load_g = load float, ptr %g, align 4
  %call_gfn_gfn_gfn_main_block_block_block = call i32 @gfn_gfn_gfn_main_block_block_block(float %load_g, i32 20)
  store i32 %call_gfn_gfn_gfn_main_block_block_block, ptr %var_6, align 4
  store i32 %n, ptr %n_alloca5, align 4
  %load_var_6 = load i32, ptr %var_6, align 4
  %load_n6 = load i32, ptr %n_alloca5, align 4
  %rmult7 = sdiv i32 %load_var_6, %load_n6
  store i32 %rmult7, ptr %var_7, align 4
  %load_var_7 = load i32, ptr %var_7, align 4
  store i32 %load_var_7, ptr %r, align 4
  ret i32 0
}

define i32 @gfn_gfn_gfn_main_block_block_block(float %a, i32 %b) {
entry:
  ret i32 0
}