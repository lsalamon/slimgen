;-------------------------------------------------------------------------------
; nasm -fbin -odp.sse3 dp.sse3.asm
; SlimGenTest.Vector4.DotProduct
; Calling convention is __fastcall:
;  X86: First two arguments in registers ECX and EDX the remainder are on the
;       stack right to left.
;-------------------------------------------------------------------------------
BITS        32
start:
			movups	xmm0, [ecx]	
			movups	xmm1, [edx]
			mulps	xmm0, xmm1
			haddps	xmm0, xmm0
			haddps	xmm0, xmm0
			mov		eax, [esp + 4]
			movss	[eax], xmm0
            ret		4

