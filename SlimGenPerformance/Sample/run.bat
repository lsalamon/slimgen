@ECHO OFF
ECHO ================================================================================This requires administrative permissions to run!
ECHO ================================================================================Working...
NGEN uninstall /silent SlimGen.Performance.Math.dll
NGEN install /silent SlimGen.Performance.Math.dll
NGEN uninstall /silent SlimGen.Performance.Test.exe
NGEN install /silent SlimGen.Performance.Test.exe
SlimGen.Compiler test.xml test.sgen
SlimGen.Client SlimGen.Performance.Math.dll test.sgen > NUL
ECHO ================================================================================Beggining test run
ECHO ================================================================================
ECHO Test Run 1:
SlimGen.Performance.Test.exe
ECHO Test Run 2:
SlimGen.Performance.Test.exe
ECHO Test Run 3:
SlimGen.Performance.Test.exe
ECHO Test Run 4:
SlimGen.Performance.Test.exe