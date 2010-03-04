;* Copyright (c) 2007-2010 SlimGen Group
;* 
;* Permission is hereby granted, free of charge, to any person obtaining a copy
;* of this software and associated documentation files (the "Software"), to deal
;* in the Software without restriction, including without limitation the rights
;* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
;* copies of the Software, and to permit persons to whom the Software is
;* furnished to do so, subject to the following conditions:
;* 
;* The above copyright notice and this permission notice shall be included in
;* all copies or substantial portions of the Software.
;* 
;* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
;* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
;* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
;* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
;* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
;* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
;* THE SOFTWARE.
;-------------------------------------------------------------------------------
; nasm -fbin -odp.sse3 dp.sse3.asm
; SlimGenTest.Vector4.DotProduct
; Calling convention is __fastcall:
;  X86: First two arguments in registers ECX and EDX the remainder are on the
;       stack right to left.
;-------------------------------------------------------------------------------
BITS        32
start:
			movups	xmm0, [ecx]	
			movups	xmm1, [edx]
			mulps	xmm0, xmm1
			haddps	xmm0, xmm0
			haddps	xmm0, xmm0
			mov		eax, [esp + 4]
			movss	[eax], xmm0
            ret		4

