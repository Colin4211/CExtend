/////////////////////////////////////////////////////////////////////////////
//
//  Filename: PlatformInfoVersion.h
//
//  Auto Generated:
//      Tool: CT_VersionTool
//      Version: CToolsDev-v4.1.1.74
//      Timestamp: 2025\09\26-23:54:04 utc
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __PlatformInfoVersion_h__
#define __PlatformInfoVersion_h__

/////////////////////////////////////////////////////////////////////////////

extern CExBase_VersionNumber    PlatformInfoVersion_FileVersionNumber;
extern CExBase_VersionNumber    PlatformInfoVersion_ProductVersionNumber;
extern CExBase_VersionInfo      PlatformInfoVersion_VersionInfo;

#define PlatformInfoVersion_InitializeVersion( utilVersionInfo ) \
    { if ( utilVersionInfo.initialize() == false ) { \
            utilVersionInfo.initialize( PlatformInfoVersion_VersionInfo ); \
    } }


/////////////////////////////////////////////////////////////////////////////

#endif /* __PlatformInfoVersion_h__ */


