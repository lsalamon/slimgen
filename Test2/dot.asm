;===============================================================================
; SlimMath.Vector4.Dot(SlimMath.Vector4, SlimMath.Vector4)
; chunk: 0
;===============================================================================

entry_point:

		movaps xmm0, [rcx];
		movaps xmm1, [rdx];
		dpps xmm0, xmm1, 0xFF;
		movss [rax], xmm0;
		rep ret;

		times 106 - ($-$$) db 0xCC ; fill remaining space with int3.
