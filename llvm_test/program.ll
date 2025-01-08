; ModuleID = 'file_1'
source_filename = "file_1"
target triple = "arm64-apple-macosx15.0.0"

define void @sub(i32 %a, i32 %b) {
entry:
  ret void
}

define void @main() {
entry:
  %n = alloca float, align 4
  %var_12 = alloca float, align 4
  %var_11 = alloca double, align 8
  %var_10 = alloca double, align 8
  %var_9 = alloca float, align 4
  %var_8 = alloca double, align 8
  %var_7 = alloca double, align 8
  %var_6 = alloca double, align 8
  %r = alloca i32, align 4
  %var_5 = alloca i32, align 4
  %var_4 = alloca float, align 4
  %var_3 = alloca float, align 4
  %var_2 = alloca float, align 4
  %var_1 = alloca float, align 4
  %b = alloca float, align 4
  %a = alloca i32, align 4
  store i32 12, ptr %a, align 4
  store float 1.525000e+01, ptr %b, align 4
  store float 2.500000e+01, ptr %var_1, align 4
  %load_b = load float, ptr %b, align 4
  %load_var_1 = load float, ptr %var_1, align 4
  %tmp_var_2 = fmul float %load_b, %load_var_1
  store float %tmp_var_2, ptr %var_2, align 4
  %tmp_var_21 = fmul float %load_b, %load_var_1
  store float %tmp_var_21, ptr %var_2, align 4
  %load_a = load i32, ptr %a, align 4
  %cast_a = sitofp i32 %load_a to float
  store float %cast_a, ptr %var_3, align 4
  %load_var_3 = load float, ptr %var_3, align 4
  %load_var_2 = load float, ptr %var_2, align 4
  %tmp_var_4 = fadd float %load_var_3, %load_var_2
  store float %tmp_var_4, ptr %var_4, align 4
  %load_var_4 = load float, ptr %var_4, align 4
  %cast_var_4 = fptosi float %load_var_4 to i32
  store i32 %cast_var_4, ptr %var_5, align 4
  %load_var_5 = load i32, ptr %var_5, align 4
  store i32 %load_var_5, ptr %r, align 4
  store double 1.254000e+00, ptr %var_6, align 8
  %load_r = load i32, ptr %r, align 4
  %cast_r = sitofp i32 %load_r to double
  store double %cast_r, ptr %var_7, align 8
  %load_var_7 = load double, ptr %var_7, align 8
  %load_var_6 = load double, ptr %var_6, align 8
  %tmp_var_8 = fdiv double %load_var_7, %load_var_6
  store double %tmp_var_8, ptr %var_8, align 8
  store float 0x40365999A0000000, ptr %var_9, align 4
  %load_var_9 = load float, ptr %var_9, align 4
  %cast_var_9 = fpext float %load_var_9 to double
  store double %cast_var_9, ptr %var_10, align 8
  %load_var_8 = load double, ptr %var_8, align 8
  %load_var_10 = load double, ptr %var_10, align 8
  %tmp_var_11 = fsub double %load_var_8, %load_var_10
  store double %tmp_var_11, ptr %var_11, align 8
  %tmp_var_112 = fsub double %load_var_8, %load_var_10
  store double %tmp_var_112, ptr %var_11, align 8
  %load_var_11 = load double, ptr %var_11, align 8
  %cast_var_11 = fptrunc double %load_var_11 to float
  store float %cast_var_11, ptr %var_12, align 4
  %load_var_12 = load float, ptr %var_12, align 4
  store float %load_var_12, ptr %n, align 4
  ret void
}