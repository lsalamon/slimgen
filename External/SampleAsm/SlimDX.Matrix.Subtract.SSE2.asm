;-------------------------------------------------------------------------------
; nasm -fbin -oSlimDX.Matrix.Subtract.X32 SlimDX.Matrix.Subtract.asm
; SlimDX.Matrix.Subtract
; RVA: 0x266880
; Length: 185
; Calling convention is __fastcall:
;  X86: First two arguments in registers ECX and EDX the remainder are on the
;       stack right to left.
;-------------------------------------------------------------------------------
BITS        32
ORG         0x266880
start:
            ret      4
;-------------------------------------------------------------------------------
; Buffer out to the size of the original method: 
; WARNING: DO NOT EXCEED THIS SIZE
            TIMES 0xb9-($-$$) DB 0xCC
