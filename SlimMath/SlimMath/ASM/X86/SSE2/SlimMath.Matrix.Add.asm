;-------------------------------------------------------------------------------
; nasm -fbin -oSlimMath.Matrix.Add.X32 SlimMath.Matrix.Add.asm
; SlimMath.Matrix.Add
; RVA: 0x6920
; Length: 325
; Calling convention is clr __fastcall:
;  X86: First two arguments in registers ECX and EDX the remainder are on the
;       stack right to left.
;-------------------------------------------------------------------------------
BITS        32
ORG         0x6920
start:
			mov		eax,  [esp + 0x04]
			movups	xmm0, [ecx]
			movups	xmm1, [ecx + 0x10]
			movups	xmm2, [ecx + 0x20]
			movups	xmm3, [ecx + 0x30]
			movups	xmm4, [edx]
			movups	xmm5, [edx + 0x10]
			movups	xmm6, [edx + 0x20]
			movups  xmm7, [edx + 0x30]
			addps	xmm0, xmm4
			addps	xmm1, xmm5
			addps	xmm2, xmm6
			addps	xmm3, xmm7
			movups	[eax], xmm0
			movups	[eax + 0x10], xmm1
			movups	[eax + 0x20], xmm2
			movups	[eax + 0x30], xmm3
            ret     4
;-------------------------------------------------------------------------------
; Buffer out to the size of the original method: 
; WARNING: DO NOT EXCEED THIS SIZE
            TIMES 0x145-($-$$) DB 0xCC
;===============================================================================
; WARNING: DO NOT REMOVE {
;===============================================================================
%define methodName      'SlimMath.Matrix.Add'
%define methodSignature '(ref SlimMath.Matrix, ref SlimMath.Matrix, ref SlimMath.Matrix)'
;===============================================================================
; WARNING: DO NOT REMOVE }
;===============================================================================
