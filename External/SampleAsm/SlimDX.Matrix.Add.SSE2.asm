;-------------------------------------------------------------------------------
; nasm -fbin -oSlimDX.Matrix.Add.X32 SlimDX.Matrix.Add.asm
; SlimDX.Matrix.Add
; RVA: 0x2666d4
; Length: 185
; Calling convention is __fastcall:
;  X86: First two arguments in registers ECX and EDX the remainder are on the
;       stack right to left.
;-------------------------------------------------------------------------------
BITS        32
ORG         0x2666d4
start:
            ret      4
;-------------------------------------------------------------------------------
; Buffer out to the size of the original method: 
; WARNING: DO NOT EXCEED THIS SIZE
            TIMES 0xb9-($-$$) DB 0xCC
