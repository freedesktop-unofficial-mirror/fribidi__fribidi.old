# Microsoft Developer Studio Project File - Name="fribidi" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=fribidi - Win32 Debug Speed Optimized
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "fribidi.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "fribidi.mak" CFG="fribidi - Win32 Debug Speed Optimized"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "fribidi - Win32 Release Memory Optimized" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "fribidi - Win32 Debug Memory Optimized" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "fribidi - Win32 Release Speed Optimized" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "fribidi - Win32 Debug Speed Optimized" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "fribidi - Win32 Release Memory Optimized"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "fribidi___Win32_Release_Memory_Optimized"
# PROP BASE Intermediate_Dir "fribidi___Win32_Release_Memory_Optimized"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\mem\"
# PROP Intermediate_Dir "Release\mem\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FRIBIDI_EXPORTS" /D "HAS_FRIBIDI_TAB_CHAR_TYPE_9_I" /D "HAS_FRIBIDI_TAB_CHAR_TYPE_2_I" /D "MEM_OPTIMIZED" /D "FRIBIDI_NO_CHARSETS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "MEM_OPTIMIZED" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FRIBIDI_EXPORTS" /D "HAS_FRIBIDI_TAB_CHAR_TYPE_9_I" /D "HAS_FRIBIDI_TAB_CHAR_TYPE_2_I" /D "FRIBIDI_NO_CHARSETS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "fribidi - Win32 Debug Memory Optimized"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "fribidi___Win32_Debug_Memory_Optimized"
# PROP BASE Intermediate_Dir "fribidi___Win32_Debug_Memory_Optimized"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\mem\"
# PROP Intermediate_Dir "Debug\mem\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FRIBIDI_EXPORTS" /D "HAS_FRIBIDI_TAB_CHAR_TYPE_9_I" /D "HAS_FRIBIDI_TAB_CHAR_TYPE_2_I" /D "MEM_OPTIMIZED" /D "FRIBIDI_NO_CHARSETS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "MEM_OPTIMIZED" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FRIBIDI_EXPORTS" /D "HAS_FRIBIDI_TAB_CHAR_TYPE_9_I" /D "HAS_FRIBIDI_TAB_CHAR_TYPE_2_I" /D "FRIBIDI_NO_CHARSETS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "fribidi - Win32 Release Speed Optimized"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "fribidi___Win32_Release_Speed_Optimized"
# PROP BASE Intermediate_Dir "fribidi___Win32_Release_Speed_Optimized"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\speed\"
# PROP Intermediate_Dir "Release\speed\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FRIBIDI_EXPORTS" /D "HAS_FRIBIDI_TAB_CHAR_TYPE_9_I" /D "HAS_FRIBIDI_TAB_CHAR_TYPE_2_I" /D "MEM_OPTIMIZED" /D "FRIBIDI_NO_CHARSETS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FRIBIDI_EXPORTS" /D "HAS_FRIBIDI_TAB_CHAR_TYPE_9_I" /D "HAS_FRIBIDI_TAB_CHAR_TYPE_2_I" /D "FRIBIDI_NO_CHARSETS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "fribidi - Win32 Debug Speed Optimized"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "fribidi___Win32_Debug_Speed_Optimized"
# PROP BASE Intermediate_Dir "fribidi___Win32_Debug_Speed_Optimized"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\speed\"
# PROP Intermediate_Dir "Debug\speed\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FRIBIDI_EXPORTS" /D "HAS_FRIBIDI_TAB_CHAR_TYPE_9_I" /D "HAS_FRIBIDI_TAB_CHAR_TYPE_2_I" /D "MEM_OPTIMIZED" /D "FRIBIDI_NO_CHARSETS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FRIBIDI_EXPORTS" /D "HAS_FRIBIDI_TAB_CHAR_TYPE_9_I" /D "HAS_FRIBIDI_TAB_CHAR_TYPE_2_I" /D "FRIBIDI_NO_CHARSETS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "fribidi - Win32 Release Memory Optimized"
# Name "fribidi - Win32 Debug Memory Optimized"
# Name "fribidi - Win32 Release Speed Optimized"
# Name "fribidi - Win32 Debug Speed Optimized"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\fribidi.c
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\fribidi.cpp

!IF  "$(CFG)" == "fribidi - Win32 Release Memory Optimized"

# PROP BASE Intermediate_Dir "Release\main"
# PROP Intermediate_Dir "Release\main"
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "fribidi - Win32 Debug Memory Optimized"

# PROP BASE Intermediate_Dir "Debug\main"
# PROP Intermediate_Dir "Debug\main"
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "fribidi - Win32 Release Speed Optimized"

# PROP BASE Intermediate_Dir "Release\main"
# PROP Intermediate_Dir "Release\main"
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "fribidi - Win32 Debug Speed Optimized"

# PROP BASE Intermediate_Dir "Debug\main"
# PROP Intermediate_Dir "Debug\main"
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\fribidi_char_type.c
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\fribidi_env.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\fribidi_mem.c
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\fribidi_mirroring.c
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\fribidi_types.c
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\fribidi.h
# End Source File
# Begin Source File

SOURCE=..\fribidi_char_sets.h
# End Source File
# Begin Source File

SOURCE=..\fribidi_char_sets_cap_rtl.h
# End Source File
# Begin Source File

SOURCE=..\fribidi_char_sets_cp1255.h
# End Source File
# Begin Source File

SOURCE=..\fribidi_char_sets_cp1256.h
# End Source File
# Begin Source File

SOURCE=..\fribidi_char_sets_isiri_3342.h
# End Source File
# Begin Source File

SOURCE=..\fribidi_char_sets_iso8859_6.h
# End Source File
# Begin Source File

SOURCE=..\fribidi_char_sets_iso8859_8.h
# End Source File
# Begin Source File

SOURCE=..\fribidi_char_sets_utf8.h
# End Source File
# Begin Source File

SOURCE=..\fribidi_config.h
# End Source File
# Begin Source File

SOURCE=..\fribidi_env.h
# End Source File
# Begin Source File

SOURCE=..\fribidi_mem.h
# End Source File
# Begin Source File

SOURCE=..\fribidi_types.h
# End Source File
# Begin Source File

SOURCE=..\fribidi_unicode.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\version.rc
# End Source File
# End Group
# Begin Group "Char Sets"

# PROP Default_Filter "c"
# Begin Source File

SOURCE=..\fribidi_char_sets.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\fribidi_char_sets_cap_rtl.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\fribidi_char_sets_cp1255.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\fribidi_char_sets_cp1256.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\fribidi_char_sets_isiri_3342.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\fribidi_char_sets_iso8859_6.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\fribidi_char_sets_iso8859_8.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\fribidi_char_sets_utf8.c
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
