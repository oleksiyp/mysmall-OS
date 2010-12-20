# Microsoft Developer Studio Project File - Name="kernel" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=kernel - Win32 XPOS Testing
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "kernel.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "kernel.mak" CFG="kernel - Win32 XPOS Testing"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "kernel - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "kernel - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "kernel - Win32 XPOS Testing" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "kernel - Win32 XPOS Testing Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "kernel - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "KERNEL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /O2 /X /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "KERNEL_EXPORTS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x422 /d "NDEBUG"
# ADD RSC /l 0x422 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 /nologo /base:"0x200000" /entry:"EntryPoint" /dll /machine:I386 /nodefaultlib

!ELSEIF  "$(CFG)" == "kernel - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "KERNEL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /X /I "." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "KERNEL_EXPORTS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x422 /d "_DEBUG"
# ADD RSC /l 0x422 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /base:"0x200000" /entry:"EntryPoint" /dll /debug /machine:I386 /nodefaultlib /pdbtype:sept

!ELSEIF  "$(CFG)" == "kernel - Win32 XPOS Testing"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "kernel___Win32_XPOS_Testing"
# PROP BASE Intermediate_Dir "kernel___Win32_XPOS_Testing"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "XPOSTesting"
# PROP Intermediate_Dir "XPOSTesting"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /X /I "." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "KERNEL_EXPORTS" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /D "TESTING" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "KERNEL_EXPORTS" /FR /YX /FD /GZ /c
# SUBTRACT CPP /X
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x422 /d "_DEBUG"
# ADD RSC /l 0x422 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /base:"0x200000" /entry:"EntryPoint" /dll /debug /machine:I386 /nodefaultlib /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"XPOSTesting/testsuit.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "kernel - Win32 XPOS Testing Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "kernel___Win32_XPOS_Testing_Release"
# PROP BASE Intermediate_Dir "kernel___Win32_XPOS_Testing_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "XPOS_Testing_Release"
# PROP Intermediate_Dir "XPOS_Testing_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O2 /X /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "KERNEL_EXPORTS" /FR /YX /FD /c
# ADD CPP /nologo /MT /W3 /O2 /I "." /D "TESTING" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "KERNEL_EXPORTS" /FR /YX /FD /c
# SUBTRACT CPP /X
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x422 /d "NDEBUG"
# ADD RSC /l 0x422 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /base:"0x200000" /entry:"EntryPoint" /dll /machine:I386 /nodefaultlib
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"XPOS_Testing_Release/testsuit.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /incremental:yes /debug

!ENDIF 

# Begin Target

# Name "kernel - Win32 Release"
# Name "kernel - Win32 Debug"
# Name "kernel - Win32 XPOS Testing"
# Name "kernel - Win32 XPOS Testing Release"
# Begin Group "basic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\basic\character.h
# End Source File
# Begin Source File

SOURCE=.\basic\crt.cpp
# End Source File
# Begin Source File

SOURCE=.\basic\crt.h
# End Source File
# Begin Source File

SOURCE=.\basic\cstring.h
# End Source File
# Begin Source File

SOURCE=.\basic\formater.cpp
# End Source File
# Begin Source File

SOURCE=.\basic\formater.h
# End Source File
# Begin Source File

SOURCE=.\basic\memory.cpp
# End Source File
# Begin Source File

SOURCE=.\basic\memory.h
# End Source File
# Begin Source File

SOURCE=.\basic\simple_io.cpp
# End Source File
# Begin Source File

SOURCE=.\basic\simple_io.h
# End Source File
# Begin Source File

SOURCE=.\basic\types.h
# End Source File
# Begin Source File

SOURCE=.\basic\utility.h
# End Source File
# End Group
# Begin Group "xp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\xp\testing.cpp
# End Source File
# Begin Source File

SOURCE=.\xp\testing.h
# End Source File
# End Group
# Begin Group "main"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\main\bsod.cpp
# End Source File
# Begin Source File

SOURCE=.\main\bsod.h
# End Source File
# Begin Source File

SOURCE=.\main\kernel.cpp
# End Source File
# End Group
# Begin Group "algorithms"

# PROP Default_Filter ""
# Begin Group "utility"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\algorithms\utility\operators.h
# End Source File
# End Group
# Begin Group "memory"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\algorithms\memory\FixedPagedHeap.cpp
# End Source File
# Begin Source File

SOURCE=.\algorithms\memory\FixedPagedHeap.h
# End Source File
# Begin Source File

SOURCE=.\algorithms\memory\Heap.cpp
# End Source File
# Begin Source File

SOURCE=.\algorithms\memory\Heap.h
# End Source File
# End Group
# End Group
# Begin Group "structures"

# PROP Default_Filter ""
# Begin Group "trees"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\structures\trees\RedNBlackTree.cpp
# End Source File
# Begin Source File

SOURCE=.\structures\trees\RedNBlackTree.h
# End Source File
# End Group
# Begin Group "strings"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\structures\strings\String.cpp
# End Source File
# Begin Source File

SOURCE=.\structures\strings\String.h
# End Source File
# End Group
# Begin Group "containers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\structures\containers\List.cpp
# End Source File
# Begin Source File

SOURCE=.\structures\containers\List.h
# End Source File
# Begin Source File

SOURCE=.\structures\containers\Map.cpp
# End Source File
# Begin Source File

SOURCE=.\structures\containers\Map.h
# End Source File
# End Group
# End Group
# Begin Group "architectures"

# PROP Default_Filter ""
# Begin Group "x86"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\architectures\x86\idt.h
# End Source File
# Begin Source File

SOURCE=.\architectures\x86\InterruptManager.cpp
# End Source File
# Begin Source File

SOURCE=.\architectures\x86\InterruptManager.h
# End Source File
# Begin Source File

SOURCE=.\architectures\x86\interrupts.asm

!IF  "$(CFG)" == "kernel - Win32 Release"

# Begin Custom Build
InputPath=.\architectures\x86\interrupts.asm
InputName=interrupts

"$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw $(InputPath) -fwin32 -o $(InputName).obj

# End Custom Build

!ELSEIF  "$(CFG)" == "kernel - Win32 Debug"

!ELSEIF  "$(CFG)" == "kernel - Win32 XPOS Testing"

!ELSEIF  "$(CFG)" == "kernel - Win32 XPOS Testing Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\architectures\x86\io.cpp
# End Source File
# Begin Source File

SOURCE=.\architectures\x86\io.h
# End Source File
# Begin Source File

SOURCE=.\architectures\x86\x86.cpp
# End Source File
# Begin Source File

SOURCE=.\architectures\x86\x86.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\architectures\main.cpp
# End Source File
# Begin Source File

SOURCE=.\architectures\main.h
# End Source File
# End Group
# End Target
# End Project
