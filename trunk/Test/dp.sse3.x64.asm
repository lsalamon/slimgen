BITS 64
dp:
        movups  xmm0, [rcx]
        movups  xmm1, [rdx]
        mulps   xmm1,xmm0
        movaps  xmm0,xmm1
        haddps  xmm0, xmm0
        haddps  xmm0, xmm0
        movss   [r8],xmm0
        rep ret          