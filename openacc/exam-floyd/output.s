; ModuleID = 'floyd.cpp'
target datalayout = "e-p:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

define internal void @pgCplus_compiled.() noinline {
L.entry:
	ret void
}


define linkonce_odr signext i32 @_Z5indexii(i32 signext %i.arg, i32 signext %j.arg) #0 inlinehint mustprogress !dbg !15 {
L.entry:
	%i.addr = alloca i32, align 4
	%j.addr = alloca i32, align 4

	store i32 %i.arg, ptr %i.addr, align 4
	store i32 %j.arg, ptr %j.addr, align 4
	%0 = load i32, ptr %j.addr, align 4, !dbg !19
	%1 = load i32, ptr %i.addr, align 4, !dbg !19
	%2 = mul i32  %1, 6000, !dbg !19
	%3 = add i32  %0,  %2, !dbg !19
	ret i32  %3, !dbg !19
}

define dso_local signext i32 @main() #0 mustprogress !dbg !24 {
L.entry:
	%size2.addr = alloca i32, align 4
	%_T1_5539.addr = alloca i64, align 8
	%data.addr = alloca ptr, align 8
	%i.addr = alloca i32, align 4
	%i.addr.1 = alloca i32, align 4
	%prev.addr = alloca i32, align 4
	%next.addr = alloca i32, align 4
	%_T2_5539.addr = alloca i32, align 4
	%_T3_5539.addr = alloca i32, align 4
	%_T4_5539.addr = alloca i32, align 4
	%_T5_5539.addr = alloca i32, align 4
	%t.addr = alloca double, align 8
	%processor.addr = alloca i32, align 4
	%blocksize.addr = alloca i32, align 4
	%dik.addr = alloca ptr, align 8
	%dkj.addr = alloca ptr, align 8
	%i.addr.2 = alloca i32, align 4
	%id.addr = alloca i32, align 4
	%start.addr = alloca i32, align 4
	%end.addr = alloca i32, align 4
	%k.addr = alloca i32, align 4
	%i.addr.3 = alloca i32, align 4
	%j.addr = alloca i32, align 4
	%i.addr.4 = alloca i32, align 4
	%i.addr.5 = alloca i32, align 4
	%i.addr.6 = alloca i32, align 4
	%prev.addr.1 = alloca i32, align 4
	%next.addr.1 = alloca i32, align 4
	%_T9_5539.addr = alloca i32, align 4
	%_T10_5539.addr = alloca i32, align 4
	%_T11_5539.addr = alloca i32, align 4
	%_T12_5539.addr = alloca i32, align 4
	%_T13_5539.addr = alloca double, align 8

	store i32 36000000, ptr %size2.addr, align 4, !dbg !60
	store i64 144000000, ptr %_T1_5539.addr, align 8, !dbg !29
	%0 = load i64, ptr %_T1_5539.addr, align 8, !dbg !29
	%1 = call noalias ptr  @_Znam (i64  %0) mustprogress, !dbg !29
	store ptr  %1, ptr %data.addr, align 8, !dbg !29
	store i32 0, ptr %i.addr, align 4, !dbg !61
	br label %L.B0001
L.B0001:
	%2 = load i32, ptr %i.addr, align 4, !dbg !61
	%3 = icmp sge i32  %2, 36000000, !dbg !61
	br i1  %3, label %L.B0002, label %L.B0056, !llvm.loop !62, !dbg !61
L.B0056:
	%4 = load i32, ptr %i.addr, align 4, !dbg !65
	%5 = sext i32  %4 to i64, !dbg !65
	%6 = load ptr, ptr %data.addr, align 8, !dbg !65
	%7 = getelementptr float, ptr  %6, i64  %5, !dbg !65
	store float 0xC16312D000000000, ptr  %7, align 4, !dbg !65

	%8 = add i32  %4, 1, !dbg !65
	store i32  %8, ptr %i.addr, align 4, !dbg !65
	br label %L.B0001, !llvm.loop !66, !dbg !65
L.B0002:
	call void  @srand (i32 6000) mustprogress, !dbg !31
	store i32 0, ptr %i.addr.1, align 4, !dbg !33
	br label %L.B0005
L.B0005:
	%9 = load i32, ptr %i.addr.1, align 4, !dbg !33
	%10 = icmp sge i32  %9, 120000, !dbg !33
	br i1  %10, label %L.B0006, label %L.B0057, !llvm.loop !67, !dbg !33
L.B0057:
	%11 = call i32  @rand () mustprogress, !dbg !68
	%12 = sext i32  %11 to i64, !dbg !68
	%13 = mul i64  %12, 91625969, !dbg !68
	%14 = sext i32 32 to i64, !dbg !68
	%15 = lshr i64  %13,  %14, !dbg !68
	%16 = trunc i64  %15 to i32, !dbg !68
	%17 = ashr i32  %16, 7, !dbg !68
	%18 = ashr i32  %11, 31, !dbg !68
	%19 = sub i32  %17,  %18, !dbg !68
	%20 = mul i32  %19, 6000, !dbg !68
	%21 = sub i32  %11,  %20, !dbg !68
	store i32  %21, ptr %prev.addr, align 4, !dbg !68
	%22 = call i32  @rand () mustprogress, !dbg !69
	%23 = sext i32  %22 to i64, !dbg !69
	%24 = mul i64  %23, 91625969, !dbg !69
	%25 = sext i32 32 to i64, !dbg !69
	%26 = lshr i64  %24,  %25, !dbg !69
	%27 = trunc i64  %26 to i32, !dbg !69
	%28 = ashr i32  %27, 7, !dbg !69
	%29 = ashr i32  %22, 31, !dbg !69
	%30 = sub i32  %28,  %29, !dbg !69
	%31 = mul i32  %30, 6000, !dbg !69
	%32 = sub i32  %22,  %31, !dbg !69
	store i32  %32, ptr %next.addr, align 4, !dbg !69
	%33 = load i32, ptr %prev.addr, align 4, !dbg !70
	%34 = icmp eq i32  %33,  %32, !dbg !70
	br i1  %34, label %L.B0009, label %L.B0058, !llvm.loop !71, !dbg !70
L.B0058:
	%35 = load i32, ptr %prev.addr, align 4, !dbg !70
	store i32  %35, ptr %_T2_5539.addr, align 4, !dbg !70
	%36 = load i32, ptr %next.addr, align 4, !dbg !70
	store i32  %36, ptr %_T3_5539.addr, align 4, !dbg !70
	%37 = call i32  @_Z5indexii (i32  %35, i32  %36) mustprogress, !dbg !70
	%38 = sext i32  %37 to i64, !dbg !70
	%39 = load ptr, ptr %data.addr, align 8, !dbg !70
	%40 = getelementptr float, ptr  %39, i64  %38, !dbg !70
	%41 = load float, ptr  %40, align 4, !dbg !70
	%42 = fcmp ule float  %41, 0xC16312D000000000, !dbg !70
	br i1  %42, label %L.B0008, label %L.B0009, !llvm.loop !72, !dbg !70
L.B0009:
	%43 = load i32, ptr %i.addr.1, align 4, !dbg !73

	%44 = sub i32  %43, 1, !dbg !73
	store i32  %44, ptr %i.addr.1, align 4, !dbg !73
	br label %L_T6_5539, !llvm.loop !75, !dbg !74
L.B0008:
	%45 = load i32, ptr %prev.addr, align 4, !dbg !76
	store i32  %45, ptr %_T4_5539.addr, align 4, !dbg !76
	%46 = load i32, ptr %next.addr, align 4, !dbg !76
	store i32  %46, ptr %_T5_5539.addr, align 4, !dbg !76
	%47 = call i32  @rand () mustprogress, !dbg !76
	%48 = sext i32  %47 to i64, !dbg !76
	%49 = mul i64  %48, -1518422781, !dbg !76
	%50 = sext i32 32 to i64, !dbg !76
	%51 = lshr i64  %49,  %50, !dbg !76
	%52 = trunc i64  %51 to i32, !dbg !76
	%53 = add i32  %47,  %52, !dbg !76
	%54 = ashr i32  %53, 6, !dbg !76
	%55 = ashr i32  %47, 31, !dbg !76
	%56 = sub i32  %54,  %55, !dbg !76
	%57 = mul i32  %56, 99, !dbg !76
	%58 = sub i32  %47,  %57, !dbg !76
	%59 = sitofp i32  %58 to double, !dbg !76
	%60 = fadd double  %59,  1.00000000000000000E+0, !dbg !76
	%61 = fdiv double  %60,  1.00000000000000000E+2, !dbg !76
	%62 = call double @__fd_log_1 (double  %61) mustprogress, !dbg !76
	%63 = fptrunc double  %62 to float, !dbg !76
	%64 = load i32, ptr %_T4_5539.addr, align 4, !dbg !76
	%65 = load i32, ptr %_T5_5539.addr, align 4, !dbg !76
	%66 = call i32  @_Z5indexii (i32  %64, i32  %65) mustprogress, !dbg !76
	%67 = sext i32  %66 to i64, !dbg !76
	%68 = load ptr, ptr %data.addr, align 8, !dbg !76
	%69 = getelementptr float, ptr  %68, i64  %67, !dbg !76
	store float  %63, ptr  %69, align 4, !dbg !76
	br label %L_T6_5539
L_T6_5539:
	%70 = load i32, ptr %i.addr.1, align 4, !dbg !77

	%71 = add i32  %70, 1, !dbg !77
	store i32  %71, ptr %i.addr.1, align 4, !dbg !77
	br label %L.B0005, !llvm.loop !78, !dbg !77
L.B0006:
	%72 = call double  @omp_get_wtime () mustprogress, !dbg !79
	store double  %72, ptr %t.addr, align 8, !dbg !79
	store i32 3, ptr %processor.addr, align 4, !dbg !80
	%73 = sdiv i32 6000, 3, !dbg !81
	store i32  %73, ptr %blocksize.addr, align 4, !dbg !81
	store i64 24000, ptr %_T1_5539.addr, align 8, !dbg !82
	%74 = call noalias ptr  @_Znam (i64 24000) mustprogress, !dbg !82
	store ptr  %74, ptr %dik.addr, align 8, !dbg !82
	store i64 24000, ptr %_T1_5539.addr, align 8, !dbg !35
	%75 = call noalias ptr  @_Znam (i64 24000) mustprogress, !dbg !35
	store ptr  %75, ptr %dkj.addr, align 8, !dbg !35
	store i32 0, ptr %i.addr.2, align 4, !dbg !83
	br label %L.B0013
L.B0013:
	%76 = load i32, ptr %i.addr.2, align 4, !dbg !83
	%77 = icmp sge i32  %76, 6000, !dbg !83
	br i1  %77, label %L.B0014, label %L.B0059, !llvm.loop !84, !dbg !83
L.B0059:
	%78 = load i32, ptr %i.addr.2, align 4, !dbg !85
	%79 = mul i32  %78, 6000, !dbg !85
	%80 = sext i32  %79 to i64, !dbg !85
	%81 = load ptr, ptr %data.addr, align 8, !dbg !85
	%82 = getelementptr float, ptr  %81, i64  %80, !dbg !85
	%83 = load float, ptr  %82, align 4, !dbg !85
	%84 = sext i32  %78 to i64, !dbg !85
	%85 = load ptr, ptr %dik.addr, align 8, !dbg !85
	%86 = getelementptr float, ptr  %85, i64  %84, !dbg !85
	store float  %83, ptr  %86, align 4, !dbg !85
	%87 = getelementptr float, ptr  %81, i64  %84, !dbg !86
	%88 = load float, ptr  %87, align 4, !dbg !86
	%89 = load ptr, ptr %dkj.addr, align 8, !dbg !86
	%90 = getelementptr float, ptr  %89, i64  %84, !dbg !86
	store float  %88, ptr  %90, align 4, !dbg !86

	%91 = add i32  %78, 1, !dbg !87
	store i32  %91, ptr %i.addr.2, align 4, !dbg !87
	br label %L.B0013, !llvm.loop !88, !dbg !87
L.B0014:
	%92 = call i32  @omp_get_thread_num () mustprogress, !dbg !89
	store i32  %92, ptr %id.addr, align 4, !dbg !89
	call void  @acc_set_device_num (i32  %92, i32 4) mustprogress, !dbg !90
	%93 = load i32, ptr %id.addr, align 4, !dbg !91
	%94 = load i32, ptr %blocksize.addr, align 4, !dbg !91
	%95 = mul i32  %93,  %94, !dbg !91
	store i32  %95, ptr %start.addr, align 4, !dbg !91
	%96 = add i32  %94,  %95, !dbg !92
	store i32  %96, ptr %end.addr, align 4, !dbg !92
	store i32 0, ptr %k.addr, align 4, !dbg !45
	br label %L.B0019
L.B0019:
	%97 = load i32, ptr %k.addr, align 4, !dbg !45
	%98 = icmp sge i32  %97, 6000, !dbg !45
	br i1  %98, label %L.B0020, label %L.B0060, !llvm.loop !93, !dbg !45
L.B0060:
	%99 = load i32, ptr %start.addr, align 4, !dbg !94
	store i32  %99, ptr %i.addr.3, align 4, !dbg !94
	br label %L.B0023
L.B0023:
	%100 = load i32, ptr %i.addr.3, align 4, !dbg !94
	%101 = load i32, ptr %end.addr, align 4, !dbg !94
	%102 = icmp sge i32  %100,  %101, !dbg !94
	br i1  %102, label %L.B0024, label %L.B0061, !llvm.loop !95, !dbg !94
L.B0061:
	store i32 0, ptr %j.addr, align 4, !dbg !96
	br label %L.B0027
L.B0027:
	%103 = load i32, ptr %j.addr, align 4, !dbg !96
	%104 = icmp sge i32  %103, 6000, !dbg !96
	br i1  %104, label %L.B0028, label %L.B0062, !llvm.loop !97, !dbg !96
L.B0062:
	%105 = load i32, ptr %j.addr, align 4, !dbg !98
	%106 = load i32, ptr %i.addr.3, align 4, !dbg !98
	%107 = mul i32  %106, 6000, !dbg !98
	%108 = add i32  %105,  %107, !dbg !98
	%109 = sext i32  %108 to i64, !dbg !98
	%110 = load ptr, ptr %data.addr, align 8, !dbg !98
	%111 = getelementptr float, ptr  %110, i64  %109, !dbg !98
	%112 = load float, ptr  %111, align 4, !dbg !98
	%113 = sext i32  %105 to i64, !dbg !98
	%114 = load ptr, ptr %dkj.addr, align 8, !dbg !98
	%115 = getelementptr float, ptr  %114, i64  %113, !dbg !98
	%116 = load float, ptr  %115, align 4, !dbg !98
	%117 = sext i32  %106 to i64, !dbg !98
	%118 = load ptr, ptr %dik.addr, align 8, !dbg !98
	%119 = getelementptr float, ptr  %118, i64  %117, !dbg !98
	%120 = load float, ptr  %119, align 4, !dbg !98
	%121 = fadd float  %116,  %120, !dbg !98
	%122 = fcmp oge float  %112,  %121, !dbg !98
	br i1  %122, label %L_T7_5539, label %L.B0063, !llvm.loop !99, !dbg !98
L.B0063:
	%123 = load i32, ptr %j.addr, align 4, !dbg !100
	%124 = sext i32  %123 to i64, !dbg !100
	%125 = load ptr, ptr %dkj.addr, align 8, !dbg !100
	%126 = getelementptr float, ptr  %125, i64  %124, !dbg !100
	%127 = load float, ptr  %126, align 4, !dbg !100
	%128 = load i32, ptr %i.addr.3, align 4, !dbg !100
	%129 = sext i32  %128 to i64, !dbg !100
	%130 = load ptr, ptr %dik.addr, align 8, !dbg !100
	%131 = getelementptr float, ptr  %130, i64  %129, !dbg !100
	%132 = load float, ptr  %131, align 4, !dbg !100
	%133 = fadd float  %127,  %132, !dbg !100
	%134 = mul i32  %128, 6000, !dbg !100
	%135 = add i32  %123,  %134, !dbg !100
	%136 = sext i32  %135 to i64, !dbg !100
	%137 = load ptr, ptr %data.addr, align 8, !dbg !100
	%138 = getelementptr float, ptr  %137, i64  %136, !dbg !100
	store float  %133, ptr  %138, align 4, !dbg !100
	br label %L_T7_5539
L_T7_5539:
	%139 = load i32, ptr %j.addr, align 4, !dbg !101

	%140 = add i32  %139, 1, !dbg !101
	store i32  %140, ptr %j.addr, align 4, !dbg !101
	br label %L.B0027, !llvm.loop !102, !dbg !101
L.B0028:
	%141 = load i32, ptr %i.addr.3, align 4, !dbg !103

	%142 = add i32  %141, 1, !dbg !103
	store i32  %142, ptr %i.addr.3, align 4, !dbg !103
	br label %L.B0023, !llvm.loop !104, !dbg !103
L.B0024:
	%143 = load i32, ptr %k.addr, align 4, !dbg !51
	%144 = icmp eq i32  %143, 5999, !dbg !51
	br i1  %144, label %L_T8_5539, label %L.B0064, !llvm.loop !105, !dbg !51
L.B0064:
	%145 = load i32, ptr %start.addr, align 4, !dbg !106
	store i32  %145, ptr %i.addr.4, align 4, !dbg !106
	br label %L.B0035
L.B0035:
	%146 = load i32, ptr %i.addr.4, align 4, !dbg !106
	%147 = load i32, ptr %end.addr, align 4, !dbg !106
	%148 = icmp sge i32  %146,  %147, !dbg !106
	br i1  %148, label %L.B0036, label %L.B0065, !llvm.loop !107, !dbg !106
L.B0065:
	%149 = load i32, ptr %k.addr, align 4, !dbg !108
	%150 = load i32, ptr %i.addr.4, align 4, !dbg !108
	%151 = mul i32  %150, 6000, !dbg !108
	%152 = add i32  %149,  %151, !dbg !108
	%153 = sext i32  %152 to i64, !dbg !108
	%154 = load ptr, ptr %data.addr, align 8, !dbg !108
	%155 = getelementptr i8, ptr  %154, i64 4, !dbg !108
	%156 = getelementptr float, ptr  %155, i64  %153, !dbg !108
	%157 = load float, ptr  %156, align 4, !dbg !108
	%158 = sext i32  %150 to i64, !dbg !108
	%159 = load ptr, ptr %dik.addr, align 8, !dbg !108
	%160 = getelementptr float, ptr  %159, i64  %158, !dbg !108
	store float  %157, ptr  %160, align 4, !dbg !108

	%161 = add i32  %150, 1, !dbg !109
	store i32  %161, ptr %i.addr.4, align 4, !dbg !109
	br label %L.B0035, !llvm.loop !110, !dbg !109
L.B0036:
	%162 = load i32, ptr %k.addr, align 4, !dbg !55
	%163 = add i32  %162, 1, !dbg !55
	%164 = load i32, ptr %start.addr, align 4, !dbg !55
	%165 = icmp slt i32  %163,  %164, !dbg !55
	br i1  %165, label %L.B0038, label %L.B0066, !llvm.loop !111, !dbg !55
L.B0066:
	%166 = load i32, ptr %k.addr, align 4, !dbg !55
	%167 = add i32  %166, 1, !dbg !55
	%168 = load i32, ptr %end.addr, align 4, !dbg !55
	%169 = icmp sge i32  %167,  %168, !dbg !55
	br i1  %169, label %L.B0038, label %L.B0067, !llvm.loop !112, !dbg !55
L.B0067:
	store i32 0, ptr %i.addr.5, align 4, !dbg !113
	br label %L.B0041
L.B0041:
	%170 = load i32, ptr %i.addr.5, align 4, !dbg !113
	%171 = icmp sge i32  %170, 6000, !dbg !113
	br i1  %171, label %L.B0042, label %L.B0068, !llvm.loop !114, !dbg !113
L.B0068:
	%172 = load i32, ptr %i.addr.5, align 4, !dbg !115
	%173 = load i32, ptr %k.addr, align 4, !dbg !115
	%174 = add i32  %173, 1, !dbg !115
	%175 = mul i32  %174, 6000, !dbg !115
	%176 = add i32  %172,  %175, !dbg !115
	%177 = sext i32  %176 to i64, !dbg !115
	%178 = load ptr, ptr %data.addr, align 8, !dbg !115
	%179 = getelementptr float, ptr  %178, i64  %177, !dbg !115
	%180 = load float, ptr  %179, align 4, !dbg !115
	%181 = sext i32  %172 to i64, !dbg !115
	%182 = load ptr, ptr %dkj.addr, align 8, !dbg !115
	%183 = getelementptr float, ptr  %182, i64  %181, !dbg !115
	store float  %180, ptr  %183, align 4, !dbg !115

	%184 = add i32  %172, 1, !dbg !115
	store i32  %184, ptr %i.addr.5, align 4, !dbg !115
	br label %L.B0041, !llvm.loop !116, !dbg !115
L.B0042:
	br label %L.B0038
L.B0038:
	br label %L_T8_5539
L_T8_5539:
	%185 = load i32, ptr %k.addr, align 4, !dbg !117

	%186 = add i32  %185, 1, !dbg !117
	store i32  %186, ptr %k.addr, align 4, !dbg !117
	br label %L.B0019, !llvm.loop !118, !dbg !117
L.B0020:
	%187 = call double  @omp_get_wtime () mustprogress, !dbg !119
	%188 = load double, ptr %t.addr, align 8, !dbg !119
	%189 = fsub double  %187,  %188, !dbg !119
	store double  %189, ptr %t.addr, align 8, !dbg !119
	%190 = call i32 (ptr, ...)  @printf (ptr @.S05807, double  %189, i32 6000) mustprogress, !dbg !57
	store i32 0, ptr %i.addr.6, align 4, !dbg !59
	br label %L.B0050
L.B0050:
	%191 = load i32, ptr %i.addr.6, align 4, !dbg !59
	%192 = icmp sge i32  %191, 20, !dbg !59
	br i1  %192, label %L.B0051, label %L.B0069, !llvm.loop !120, !dbg !59
L.B0069:
	%193 = call i32  @rand () mustprogress, !dbg !121
	%194 = sext i32  %193 to i64, !dbg !121
	%195 = mul i64  %194, 91625969, !dbg !121
	%196 = sext i32 32 to i64, !dbg !121
	%197 = lshr i64  %195,  %196, !dbg !121
	%198 = trunc i64  %197 to i32, !dbg !121
	%199 = ashr i32  %198, 7, !dbg !121
	%200 = ashr i32  %193, 31, !dbg !121
	%201 = sub i32  %199,  %200, !dbg !121
	%202 = mul i32  %201, 6000, !dbg !121
	%203 = sub i32  %193,  %202, !dbg !121
	store i32  %203, ptr %prev.addr.1, align 4, !dbg !121
	%204 = call i32  @rand () mustprogress, !dbg !122
	%205 = sext i32  %204 to i64, !dbg !122
	%206 = mul i64  %205, 91625969, !dbg !122
	%207 = sext i32 32 to i64, !dbg !122
	%208 = lshr i64  %206,  %207, !dbg !122
	%209 = trunc i64  %208 to i32, !dbg !122
	%210 = ashr i32  %209, 7, !dbg !122
	%211 = ashr i32  %204, 31, !dbg !122
	%212 = sub i32  %210,  %211, !dbg !122
	%213 = mul i32  %212, 6000, !dbg !122
	%214 = sub i32  %204,  %213, !dbg !122
	store i32  %214, ptr %next.addr.1, align 4, !dbg !122
	%215 = load i32, ptr %prev.addr.1, align 4, !dbg !123
	%216 = icmp ne i32  %215,  %214, !dbg !123
	br i1  %216, label %L.B0053, label %L.B0070, !llvm.loop !124, !dbg !123
L.B0070:
	%217 = load i32, ptr %i.addr.6, align 4, !dbg !125

	%218 = sub i32  %217, 1, !dbg !125
	store i32  %218, ptr %i.addr.6, align 4, !dbg !125
	br label %L_T14_5539, !llvm.loop !127, !dbg !126
L.B0053:
	%219 = load i32, ptr %prev.addr.1, align 4, !dbg !128
	store i32  %219, ptr %_T9_5539.addr, align 4, !dbg !128
	%220 = load i32, ptr %next.addr.1, align 4, !dbg !128
	store i32  %220, ptr %_T10_5539.addr, align 4, !dbg !128
	store i32  %219, ptr %_T11_5539.addr, align 4, !dbg !128
	store i32  %220, ptr %_T12_5539.addr, align 4, !dbg !128
	%221 = call i32  @_Z5indexii (i32  %219, i32  %220) mustprogress, !dbg !128
	%222 = sext i32  %221 to i64, !dbg !128
	%223 = load ptr, ptr %data.addr, align 8, !dbg !128
	%224 = getelementptr float, ptr  %223, i64  %222, !dbg !128
	%225 = load float, ptr  %224, align 4, !dbg !128
	%226 = fpext float  %225 to double, !dbg !128
	store double  %226, ptr %_T13_5539.addr, align 8, !dbg !128
	%227 = load i32, ptr %_T9_5539.addr, align 4, !dbg !128
	%228 = load i32, ptr %_T10_5539.addr, align 4, !dbg !128
	%229 = call i32 (ptr, ...)  @printf (ptr @.S05827, i32  %227, i32  %228, double  %226) mustprogress, !dbg !128
	br label %L_T14_5539
L_T14_5539:
	%230 = load i32, ptr %i.addr.6, align 4, !dbg !129

	%231 = add i32  %230, 1, !dbg !129
	store i32  %231, ptr %i.addr.6, align 4, !dbg !129
	br label %L.B0050, !llvm.loop !130, !dbg !129
L.B0051:
	ret i32 0, !dbg !129
}

@.S05827 = internal constant [15 x i8] [i8 116,i8 101,i8 115,i8 116,i8 32,i8 37,i8 100,i8 32,i8 37,i8 100,i8 32,i8 37,i8 102,i8 10,i8 0], align 1
@.S05807 = internal constant [12 x i8] [i8 116,i8 105,i8 109,i8 101,i8 32,i8 37,i8 102,i8 32,i8 37,i8 100,i8 10,i8 0], align 1
@llvm.global_ctors = appending global [3 x { i32, ptr, ptr }] [{ i32, ptr, ptr } { i32 65535, ptr @__nv_init_env, ptr null}, { i32, ptr, ptr } { i32 65535, ptr @__flushz, ptr null}, { i32, ptr, ptr } { i32 65535, ptr @__daz, ptr null}]
attributes #0 = { null_pointer_is_valid }

declare void @__daz()
declare void @__flushz()
declare void @__nv_init_env()
declare dso_local signext i32 @printf(ptr, ...) #0
declare dso_local void @acc_set_device_num(i32 signext, i32 zeroext) #0
declare dso_local signext i32 @omp_get_thread_num() #0
declare dso_local double @omp_get_wtime() #0
declare dso_local double @__fd_log_1(double) #0 noinline nounwind mustprogress willreturn readnone "no-infs-fp-math"="true" "no-nans-fp-math"="true" "unsafe-fp-math"="true" "use-soft-float"="false" "no-signed-zeros-fp-math"="true"
declare dso_local signext i32 @rand() #0
declare dso_local void @srand(i32 zeroext) #0
declare dso_local ptr @_Znam(i64) #0
declare i32 @__gxx_personality_v0(...)

; Named metadata
!llvm.module.flags = !{ !1, !2 }
!llvm.dbg.cu = !{ !10 }

; Metadata
!1 = !{ i32 2, !"Dwarf Version", i32 4 }
!2 = !{ i32 2, !"Debug Info Version", i32 3 }
!3 = !DIFile(filename: "floyd.cpp", directory: "/home/koi/openacc/exam-floyd")
; !4 = !DIFile(tag: DW_TAG_file_type, pair: !3)
!4 = !{ i32 41, !3 }
!5 = !{  }
!6 = !{  }
!7 = !{ !15, !24 }
!8 = !{  }
!9 = !{  }
!10 = distinct !DICompileUnit(file: !3, language: DW_LANG_C_plus_plus, producer: " NVC++ 23.3-0", enums: !5, retainedTypes: !6, globals: !8, emissionKind: FullDebug, imports: !9)
!11 = !DIBasicType(tag: DW_TAG_base_type, name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!12 = !{ !11, !11, !11 }
!13 = !DISubroutineType(types: !12)
!14 = !{  }
!15 = distinct !DISubprogram(file: !3, scope: !10, name: "_Z5indexii", line: 13, type: !13, spFlags: 8, unit: !10, scopeLine: 13)
!16 = !DILocation(line: 13, column: 1, scope: !15)
!17 = !DILexicalBlock(file: !3, scope: !15, line: 13, column: 1)
!18 = !DILocation(line: 13, column: 1, scope: !17)
!19 = !DILocation(line: 14, column: 1, scope: !17)
!20 = !DILocation(line: 15, column: 1, scope: !17)
!21 = !{ !11 }
!22 = !DISubroutineType(types: !21)
!23 = !{  }
!24 = distinct !DISubprogram(file: !3, scope: !10, name: "main", line: 20, type: !22, spFlags: 8, unit: !10, scopeLine: 20)
!25 = !DILocation(line: 20, column: 1, scope: !24)
!26 = !DILexicalBlock(file: !3, scope: !24, line: 20, column: 1)
!27 = !DILocation(line: 20, column: 1, scope: !26)
!28 = !DILexicalBlock(file: !3, scope: !26, line: 22, column: 1)
!29 = !DILocation(line: 22, column: 1, scope: !28)
!30 = !DILexicalBlock(file: !3, scope: !26, line: 26, column: 1)
!31 = !DILocation(line: 26, column: 1, scope: !30)
!32 = !DILexicalBlock(file: !3, scope: !30, line: 27, column: 1)
!33 = !DILocation(line: 27, column: 1, scope: !32)
!34 = !DILexicalBlock(file: !3, scope: !26, line: 43, column: 1)
!35 = !DILocation(line: 43, column: 1, scope: !34)
!36 = !DILexicalBlock(file: !3, scope: !26, line: 51, column: 1)
!37 = !DILocation(line: 51, column: 1, scope: !36)
!38 = !DILexicalBlock(file: !3, scope: !36, line: 58, column: 1)
!39 = !DILocation(line: 58, column: 1, scope: !38)
!40 = !DILexicalBlock(file: !3, scope: !38, line: 58, column: 1)
!41 = !DILocation(line: 58, column: 1, scope: !40)
!42 = !DILexicalBlock(file: !3, scope: !40, line: 59, column: 1)
!43 = !DILocation(line: 59, column: 1, scope: !42)
!44 = !DILexicalBlock(file: !3, scope: !42, line: 59, column: 1)
!45 = !DILocation(line: 59, column: 1, scope: !44)
!46 = !DILexicalBlock(file: !3, scope: !44, line: 63, column: 1)
!47 = !DILocation(line: 63, column: 1, scope: !46)
!48 = !DILexicalBlock(file: !3, scope: !46, line: 63, column: 1)
!49 = !DILocation(line: 63, column: 1, scope: !48)
!50 = !DILexicalBlock(file: !3, scope: !42, line: 72, column: 1)
!51 = !DILocation(line: 72, column: 1, scope: !50)
!52 = !DILexicalBlock(file: !3, scope: !42, line: 78, column: 1)
!53 = !DILocation(line: 78, column: 1, scope: !52)
!54 = !DILexicalBlock(file: !3, scope: !52, line: 78, column: 1)
!55 = !DILocation(line: 78, column: 1, scope: !54)
!56 = !DILexicalBlock(file: !3, scope: !26, line: 92, column: 1)
!57 = !DILocation(line: 92, column: 1, scope: !56)
!58 = !DILexicalBlock(file: !3, scope: !56, line: 94, column: 1)
!59 = !DILocation(line: 94, column: 1, scope: !58)
!60 = !DILocation(line: 21, column: 1, scope: !26)
!61 = !DILocation(line: 23, column: 1, scope: !28)
!62 = !{ !62, !63, !64 }
!63 = !{ !"llvm.loop.vectorize.width", i32 1 }
!64 = !{ !"llvm.loop.unroll.count", i32 1 }
!65 = !DILocation(line: 24, column: 1, scope: !28)
!66 = !{ !66, !63, !64 }
!67 = !{ !67, !63, !64 }
!68 = !DILocation(line: 28, column: 1, scope: !32)
!69 = !DILocation(line: 29, column: 1, scope: !32)
!70 = !DILocation(line: 30, column: 1, scope: !32)
!71 = !{ !71, !63, !64 }
!72 = !{ !72, !63, !64 }
!73 = !DILocation(line: 31, column: 1, scope: !32)
!74 = !DILocation(line: 32, column: 1, scope: !32)
!75 = !{ !75, !63, !64 }
!76 = !DILocation(line: 34, column: 1, scope: !32)
!77 = !DILocation(line: 35, column: 1, scope: !30)
!78 = !{ !78, !63, !64 }
!79 = !DILocation(line: 37, column: 1, scope: !26)
!80 = !DILocation(line: 40, column: 1, scope: !26)
!81 = !DILocation(line: 41, column: 1, scope: !26)
!82 = !DILocation(line: 42, column: 1, scope: !26)
!83 = !DILocation(line: 45, column: 1, scope: !34)
!84 = !{ !84, !63, !64 }
!85 = !DILocation(line: 47, column: 1, scope: !34)
!86 = !DILocation(line: 48, column: 1, scope: !34)
!87 = !DILocation(line: 49, column: 1, scope: !34)
!88 = !{ !88, !63, !64 }
!89 = !DILocation(line: 52, column: 1, scope: !36)
!90 = !DILocation(line: 53, column: 1, scope: !36)
!91 = !DILocation(line: 54, column: 1, scope: !36)
!92 = !DILocation(line: 55, column: 1, scope: !36)
!93 = !{ !93, !63, !64 }
!94 = !DILocation(line: 62, column: 1, scope: !44)
!95 = !{ !95, !63, !64 }
!96 = !DILocation(line: 66, column: 1, scope: !48)
!97 = !{ !97, !63, !64 }
!98 = !DILocation(line: 68, column: 1, scope: !48)
!99 = !{ !99, !63, !64 }
!100 = !DILocation(line: 69, column: 1, scope: !48)
!101 = !DILocation(line: 70, column: 1, scope: !48)
!102 = !{ !102, !63, !64 }
!103 = !DILocation(line: 71, column: 1, scope: !44)
!104 = !{ !104, !63, !64 }
!105 = !{ !105, !63, !64 }
!106 = !DILocation(line: 74, column: 1, scope: !50)
!107 = !{ !107, !63, !64 }
!108 = !DILocation(line: 75, column: 1, scope: !50)
!109 = !DILocation(line: 76, column: 1, scope: !50)
!110 = !{ !110, !63, !64 }
!111 = !{ !111, !63, !64 }
!112 = !{ !112, !63, !64 }
!113 = !DILocation(line: 80, column: 1, scope: !54)
!114 = !{ !114, !63, !64 }
!115 = !DILocation(line: 81, column: 1, scope: !54)
!116 = !{ !116, !63, !64 }
!117 = !DILocation(line: 85, column: 1, scope: !40)
!118 = !{ !118, !63, !64 }
!119 = !DILocation(line: 91, column: 1, scope: !26)
!120 = !{ !120, !63, !64 }
!121 = !DILocation(line: 95, column: 1, scope: !58)
!122 = !DILocation(line: 96, column: 1, scope: !58)
!123 = !DILocation(line: 97, column: 1, scope: !58)
!124 = !{ !124, !63, !64 }
!125 = !DILocation(line: 98, column: 1, scope: !58)
!126 = !DILocation(line: 99, column: 1, scope: !58)
!127 = !{ !127, !63, !64 }
!128 = !DILocation(line: 101, column: 1, scope: !58)
!129 = !DILocation(line: 102, column: 1, scope: !56)
!130 = !{ !130, !63, !64 }
!131 = !DILocation(line: 103, column: 1, scope: !26)
