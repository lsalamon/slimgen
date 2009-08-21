;-------------------------------------------------------------------------------
; nasm -fbin -oSlimMath.Matrix.Multiply.X32 SlimMath.Matrix.Multiply.asm
; SlimMath.Matrix.Multiply
; RVA: 0x6d00
; Length: 991
; Calling convention is clr __fastcall:
;  X86: First two arguments in registers ECX and EDX the remainder are on the
;       stack right to left.
;-------------------------------------------------------------------------------
BITS        32
ORG         0x6d00
start:		mov 	eax, [esp + 4]
			movups  xmm4, [edx]
			movups  xmm5, [edx + 0x10]
			movups  xmm6, [edx + 0x20]
			movups  xmm7, [edx + 0x30]
			
			movups	xmm0, [ecx]
			movaps	xmm1, xmm0
			movaps	xmm2, xmm0
			movaps	xmm3, xmm0
			shufps  xmm0, xmm1, 0x00
			shufps  xmm1, xmm1, 0x55
			shufps  xmm2, xmm2, 0xAA
			shufps  xmm3, xmm3, 0xFF
			
			mulps	xmm0, xmm4
			mulps	xmm1, xmm5
			mulps	xmm2, xmm6
			mulps	xmm3, xmm7
			addps	xmm0, xmm2
			addps	xmm1, xmm3
			addps	xmm0, xmm1
			
			movups  [esp - 0x20], xmm0 ; store row 0 of new matrix
			
			movups	xmm0, [ecx + 0x10]
			movaps	xmm1, xmm0
			movaps	xmm2, xmm0
			movaps	xmm3, xmm0
			shufps  xmm0, xmm0, 0x00
			shufps  xmm1, xmm1, 0x55
			shufps  xmm2, xmm2, 0xAA
			shufps  xmm3, xmm3, 0xFF
			
			mulps	xmm0, xmm4
			mulps	xmm1, xmm5
			mulps	xmm2, xmm6
			mulps	xmm3, xmm7
			addps	xmm0, xmm2
			addps	xmm1, xmm3
			addps	xmm0, xmm1
			
			movups  [esp - 0x30], xmm0 ; store row 1 of new matrix
			
			movups	xmm0, [ecx + 0x20]
			movaps	xmm1, xmm0
			movaps	xmm2, xmm0
			movaps	xmm3, xmm0
			shufps  xmm0, xmm0, 0x00
			shufps  xmm1, xmm1, 0x55
			shufps  xmm2, xmm2, 0xAA
			shufps  xmm3, xmm3, 0xFF
			
			mulps	xmm0, xmm4
			mulps	xmm1, xmm5
			mulps	xmm2, xmm6
			mulps	xmm3, xmm7
			addps	xmm0, xmm2
			addps	xmm1, xmm3
			addps	xmm0, xmm1
			
			movups  [esp - 0x40], xmm0 ; store row 2 of new matrix
			
			movups	xmm0, [ecx + 0x30]
			movaps	xmm1, xmm0
			movaps	xmm2, xmm0
			movaps	xmm3, xmm0
			shufps  xmm0, xmm0, 0x00
			shufps  xmm1, xmm1, 0x55
			shufps  xmm2, xmm2, 0xAA
			shufps  xmm3, xmm3, 0xFF
			
			mulps	xmm0, xmm4
			mulps	xmm1, xmm5
			mulps	xmm2, xmm6
			mulps	xmm3, xmm7
			addps	xmm0, xmm2
			addps	xmm1, xmm3
			addps	xmm0, xmm1
			
			movups  [eax + 0x30], xmm0 ; store row 3 of new matrix
			movups  xmm0, [esp - 0x40]
			movups  [eax + 0x20], xmm0
			movups  xmm0, [esp - 0x30]
			movups  [eax + 0x10], xmm0
			movups  xmm0, [esp - 0x20]
			movups  [eax], xmm0
            ret     4
;-------------------------------------------------------------------------------
; Buffer out to the size of the original method: 
; WARNING: DO NOT EXCEED THIS SIZE
            TIMES 0x3df-($-$$) DB 0xCC
;===============================================================================
; WARNING: DO NOT REMOVE {
;===============================================================================
%define methodName      'SlimMath.Matrix.Multiply'
%define methodSignature '(ref SlimMath.Matrix, ref SlimMath.Matrix, ref SlimMath.Matrix)'
;===============================================================================
; WARNING: DO NOT REMOVE }
;===============================================================================
