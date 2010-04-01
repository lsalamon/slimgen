/*
* Copyright (c) 2007-2010 SlimGen Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Win32.SafeHandles;
using System.IO;

namespace SlimGen
{
    class AnonymousPipe : IDisposable
    {
        SafeFileHandle clientHandle;
        FileStream writeStream;

        public string ClientHandle
        {
            get { return clientHandle.DangerousGetHandle().ToString(); }
        }

        public Stream Stream
        {
            get { return writeStream; }
        }

        public AnonymousPipe()
        {
            SafeFileHandle readHandle, writeHandle;
            SECURITY_ATTRIBUTES security = new SECURITY_ATTRIBUTES(true);

            if (!NativeMethods.CreatePipe(out readHandle, out writeHandle, ref security, 0))
                throw new InvalidOperationException("Could not create pipe");

            clientHandle = readHandle;
            writeStream = new FileStream(writeHandle, FileAccess.Write);
        }

        public void Dispose()
        {
            if (clientHandle != null && !clientHandle.IsClosed)
                clientHandle.Close();

            if (writeStream != null)
                writeStream.Close();

            clientHandle = null;
            writeStream = null;
        }
    }
}
