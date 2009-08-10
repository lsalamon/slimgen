@ECHO OFF
ECHO ================================================================================This requires administrative permissions to run!
ECHO ================================================================================Working...
C:\Windows\Microsoft.NET\Framework\v2.0.50727\ngen.exe uninstall /silent SlimGen.Performance.Test.exe
C:\Windows\Microsoft.NET\Framework\v2.0.50727\ngen.exe uninstall /silent SlimGen.Performance.Math.dll
C:\Windows\Microsoft.NET\Framework\v2.0.50727\ngen.exe install /silent SlimGen.Performance.Math.dll
C:\Windows\Microsoft.NET\Framework\v2.0.50727\ngen.exe install /silent SlimGen.Performance.Test.exe
SlimGen.Compiler test.xml test.sgen
SlimGen.Client SlimGen.Performance.Math.dll test.sgen > NUL
ECHO ================================================================================Beggining test run
ECHO ================================================================================
SlimGen.Performance.Test.exe

