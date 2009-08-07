;-------------------------------------------------------------------------------
; nasm -fbin -oSlimDX.Matrix.Multiply.X32 SlimDX.Matrix.Multiply.asm
; SlimDX.Matrix.Multiply
; RVA: 0x266e74
; Length: 659
; Calling convention is __fastcall:
;  X86: First two arguments in registers ECX and EDX the remainder are on the
;       stack right to left.
;-------------------------------------------------------------------------------
BITS        32
ORG         0x266e74
start:
            ret      4
;-------------------------------------------------------------------------------
; Buffer out to the size of the original method: 
; WARNING: DO NOT EXCEED THIS SIZE
            TIMES 0x293-($-$$) DB 0xCC
