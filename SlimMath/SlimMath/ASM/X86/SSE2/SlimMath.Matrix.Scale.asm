;-------------------------------------------------------------------------------
; nasm -fbin -oSlimMath.Matrix.Scale.X32 SlimMath.Matrix.Scale.asm
; SlimMath.Matrix.Scale
; RVA: 0x6bc0
; Length: 310
; Calling convention is clr __fastcall:
;  X86: First two arguments in registers ECX and EDX the remainder are on the
;       stack right to left.
;-------------------------------------------------------------------------------
BITS        32
ORG         0x6bc0
start:
			mov		eax, [esp + 0x04]
			mov		[esp - 0x10], edx
			movss	xmm0, [esp - 0x10]
			shufps	xmm0, 0x00
			movups	xmm1, [ecx]
			movups	xmm2, [ecx + 0x10]
			movups	xmm3, [ecx + 0x20]
			movups	xmm4, [ecx + 0x30]
			mulps	xmm1, xmm0
			mulps	xmm2, xmm0
			mulps	xmm3, xmm0
			mulps	xmm4, xmm0
			movups	[eax], xmm1
			movups	[eax + 0x10], xmm2
			movups	[eax + 0x20], xmm3
			movups	[eax + 0x30], xmm4
            ret     4
;-------------------------------------------------------------------------------
; Buffer out to the size of the original method: 
; WARNING: DO NOT EXCEED THIS SIZE
            TIMES 0x136-($-$$) DB 0xCC
;===============================================================================
; WARNING: DO NOT REMOVE {
;===============================================================================
%define methodName      'SlimMath.Matrix.Scale'
%define methodSignature '(ref SlimMath.Matrix, ref float32, ref SlimMath.Matrix)'
;===============================================================================
; WARNING: DO NOT REMOVE }
;===============================================================================
