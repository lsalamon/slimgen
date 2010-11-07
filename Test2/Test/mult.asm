BITS 64
entry_point:

		lddqu  xmm4, [rdx]
		lddqu  xmm5, [rdx + 0x10]
		lddqu  xmm6, [rdx + 0x20]
		lddqu  xmm7, [rdx + 0x30]

		lddqu  xmm0, [ecx]
		movaps  xmm1, xmm0
		movaps  xmm2, xmm0
		movaps  xmm3, xmm0
		shufps  xmm0, xmm1, 0x00
		shufps  xmm1, xmm1, 0x55
		shufps  xmm2, xmm2, 0xAA
		shufps  xmm3, xmm3, 0xFF

		mulps   xmm0, xmm4
		mulps   xmm1, xmm5
		mulps   xmm2, xmm6
		mulps   xmm3, xmm7
		addps   xmm0, xmm2
		addps   xmm1, xmm3
		addps   xmm0, xmm1

		lddqu  [r8], xmm0 ; store row 0 of new matrix

		lddqu  xmm0, [ecx + 0x10]
		movaps  xmm1, xmm0
		movaps  xmm2, xmm0
		movaps  xmm3, xmm0
		shufps  xmm0, xmm0, 0x00
		shufps  xmm1, xmm1, 0x55
		shufps  xmm2, xmm2, 0xAA
		shufps  xmm3, xmm3, 0xFF

		mulps   xmm0, xmm4
		mulps   xmm1, xmm5
		mulps   xmm2, xmm6
		mulps   xmm3, xmm7
		addps   xmm0, xmm2
		addps   xmm1, xmm3
		addps   xmm0, xmm1

		lddqu  [esp - 0x30], xmm0 ; store row 1 of new matrix

		lddqu  xmm0, [ecx + 0x20]
		movaps  xmm1, xmm0
		movaps  xmm2, xmm0
		movaps  xmm3, xmm0
		shufps  xmm0, xmm0, 0x00
		shufps  xmm1, xmm1, 0x55
		shufps  xmm2, xmm2, 0xAA
		shufps  xmm3, xmm3, 0xFF

		mulps   xmm0, xmm4
		mulps   xmm1, xmm5
		mulps   xmm2, xmm6
		mulps   xmm3, xmm7
		addps   xmm0, xmm2
		addps   xmm1, xmm3
		addps   xmm0, xmm1

		lddqu  [esp - 0x40], xmm0 ; store row 2 of new matrix

		lddqu  xmm0, [ecx + 0x30]
		movaps  xmm1, xmm0
		movaps  xmm2, xmm0
		movaps  xmm3, xmm0
		shufps  xmm0, xmm0, 0x00
		shufps  xmm1, xmm1, 0x55
		shufps  xmm2, xmm2, 0xAA
		shufps  xmm3, xmm3, 0xFF

		mulps   xmm0, xmm4
		mulps   xmm1, xmm5
		mulps   xmm2, xmm6
		mulps   xmm3, xmm7
		addps   xmm0, xmm2
		addps   xmm1, xmm3
		addps   xmm0, xmm1

		lddqu  [eax + 0x30], xmm0 ; store row 3 of new matrix
		lddqu  xmm0, [esp - 0x40]
		lddqu  [eax + 0x20], xmm0
		lddqu  xmm0, [esp - 0x30]
		lddqu  [eax + 0x10], xmm0
		lddqu  xmm0, [esp - 0x20]
		lddqu  [eax], xmm0
		ret     4