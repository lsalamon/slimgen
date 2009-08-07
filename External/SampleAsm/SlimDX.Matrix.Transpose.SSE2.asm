;-------------------------------------------------------------------------------
; nasm -fbin -oSlimDX.Matrix.Transpose.X32 SlimDX.Matrix.Transpose.asm
; SlimDX.Matrix.Transpose
; RVA: 0x269b94
; Length: 134
; Calling convention is __fastcall:
;  X86: First two arguments in registers ECX and EDX the remainder are on the
;       stack right to left.
;-------------------------------------------------------------------------------
BITS        32
ORG         0x269b94
start:
            ret      4
;-------------------------------------------------------------------------------
; Buffer out to the size of the original method: 
; WARNING: DO NOT EXCEED THIS SIZE
            TIMES 0x86-($-$$) DB 0xCC
