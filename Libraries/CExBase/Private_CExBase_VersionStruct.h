/////////////////////////////////////////////////////////////////////////////
//
//  Filename: Private_CExBase_VersionStruct.h
//
//  Auto Generated:
//      Tool: CT_VersionTool
//      Version: CToolsDev-v4.1.1.74
//      Timestamp: 2025\09\26-23:54:04 utc
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __Private_CExBase_VersionStruct_h__
#define __Private_CExBase_VersionStruct_h__

/////////////////////////////////////////////////////////////////////////////

extern CExBase_VersionNumber    Private_CExBaseVersion_FileVersionNumber;
extern CExBase_VersionNumber    Private_CExBaseVersion_ProductVersionNumber;
extern CExBase_VersionInfo      Private_CExBaseVersion_VersionInfo;

#define Private_CExBaseVersion_InitializeVersion( utilVersionInfo ) \
    { if ( utilVersionInfo.initialize() == false ) { \
            utilVersionInfo.initialize( Private_CExBaseVersion_VersionInfo ); \
    } }


/////////////////////////////////////////////////////////////////////////////

#endif /* __Private_CExBase_VersionStruct_h__ */


