#!/bin/bash

CT_VERSION_PREFIX=CExtendDev


if [ "$1" == "REPORT" ] ; then
	CT_VersionTool -Report .
elif [ "$1" == "" ] ; then
	echo   "CExtendDev -- Incrementing Version"
	CT_VersionTool  ./  -Increment build
	echo   "CExtendDev -- Marking Version"
	CT_VersionTool  ./
else
	echo "CExtendDev -- Marking Version "
	CT_VersionTool  ./  -SetVersionFile "$1" -SetVersionProduct "$CT_VERSION_PREFIX-$1"
	echo   "CExtendDev -- Marking Version"
	CT_VersionTool  ./
fi




