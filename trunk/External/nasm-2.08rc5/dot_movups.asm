;===============================================================================
; SlimMath.Vector4.Dot(SlimMath.Vector4, SlimMath.Vector4)
; chunk: 0
;===============================================================================
BITS 64
entry_point:

		movups xmm0, [rcx];
		movups xmm1, [rdx];
		dpps xmm0, xmm1, 0xFF;
		rep ret;

		times 106 - ($-$$) db 0xCC ; fill remaining space with int3.
