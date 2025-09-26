#!/bin/bash
clear
date

###############################################################

LOG_DBG_LINUXI64="../../Output/BuildLogs/CExtend_Libraries_CExBase.LinuxI64.Debug.log"
LOG_REL_LINUXI64="../../Output/BuildLogs/CExtend_Libraries_CExBase.LinuxI64.Release.log"
TARGET_DBG_LINUXI64="../../Output/Libs/LinuxI64_Debug/CExBase_LinuxI64_d.lib"
TARGET_REL_LINUXI64="../../Output/Libs/LinuxI64_Release/CExBase_LinuxI64.lib"
MAKETARGET_DBG_LINUXI64="build_LinuxI64_Debug"
MAKETARGET_REL_LINUXI64="build_LinuxI64_Release"

###############################################################

LOG_DBG_LINUXI32="../../Output/BuildLogs/CExtend_Libraries_CExBase.LinuxI32.Debug.log"
LOG_REL_LINUXI32="../../Output/BuildLogs/CExtend_Libraries_CExBase.LinuxI32.Release.log"
TARGET_DBG_LINUXI32="../../Output/Libs/LinuxI32_Debug/CExBase_LinuxI32_d.lib"
TARGET_REL_LINUXI32="../../Output/Libs/LinuxI32_Release/CExBase_LinuxI32.lib"
MAKETARGET_DBG_LINUXI32="build_LinuxI32_Debug"
MAKETARGET_REL_LINUXI32="build_LinuxI32_Release"

###############################################################

LOG_DBG_GENERIC="../../Output/BuildLogs/CExtend_Libraries_CExBase.Generic.Debug.log"
LOG_REL_GENERIC="../../Output/BuildLogs/CExtend_Libraries_CExBase.Generic.Release.log"
TARGET_DBG_GENERIC="../../Output/Libs/Generic_Debug/CExBase_Generic_d.lib"
TARGET_REL_GENERIC="../../Output/Libs/Generic_Release/CExBase_Generic.lib"
MAKETARGET_DBG_GENERIC="build_Generic_Debug"
MAKETARGET_REL_GENERIC="build_Generic_Release"

###############################################################

LOG_DBG="$LOG_DBG_LINUXI64"
LOG_REL="$LOG_REL_LINUXI64"
TARGET_DBG="$TARGET_DBG_LINUXI64"
TARGET_REL="$TARGET_REL_LINUXI64"
MAKETARGET_DBG="$MAKETARGET_DBG_LINUXI64"
MAKETARGET_REL="$MAKETARGET_REL_LINUXI64"

###############################################################

DO_DEBUG="true"
DO_RELEASE="true"
DO_CLEAN="false"

###############################################################

for CUR_ARG in "${@}" ; do
    if [ "$CUR_ARG" == "CLEAN" ] ; then
        DO_CLEAN="true"
    elif [ "$CUR_ARG" == "DEBUG" ] ; then
        DO_DEBUG="true"
        DO_RELEASE="false"
    elif [ "$CUR_ARG" == "RELEASE" ] ; then
        DO_DEBUG="false"
        DO_RELEASE="true"
    elif [ "$CUR_ARG" == "ALL" ] ; then
        DO_DEBUG="true"
        DO_RELEASE="true"
    elif [ "$CUR_ARG" == "LINUXI64" ] ; then
        LOG_DBG="$LOG_DBG_LINUXI64"
        LOG_REL="$LOG_REL_LINUXI64"
        TARGET_DBG="$TARGET_DBG_LINUXI64"
        TARGET_REL="$TARGET_REL_LINUXI64"
        MAKETARGET_DBG="$MAKETARGET_DBG_LINUXI64"
        MAKETARGET_REL="$MAKETARGET_REL_LINUXI64"
    elif [ "$CUR_ARG" == "LINUXI32" ] ; then
        LOG_DBG="$LOG_DBG_LINUXI32"
        LOG_REL="$LOG_REL_LINUXI32"
        TARGET_DBG="$TARGET_DBG_LINUXI32"
        TARGET_REL="$TARGET_REL_LINUXI32"
        MAKETARGET_DBG="$MAKETARGET_DBG_LINUXI32"
        MAKETARGET_REL="$MAKETARGET_REL_LINUXI32"
    elif [ "$CUR_ARG" == "GENERIC" ] ; then
        LOG_DBG="$LOG_DBG_GENERIC"
        LOG_REL="$LOG_REL_GENERIC"
        TARGET_DBG="$TARGET_DBG_GENERIC"
        TARGET_REL="$TARGET_REL_GENERIC"
        MAKETARGET_DBG="$MAKETARGET_DBG_GENERIC"
        MAKETARGET_REL="$MAKETARGET_REL_GENERIC"
    else
        echo "### ERROR: Invalid ARG -->$CUR_ARG<-- "
        exit
    fi
done

###############################################################

rm -rf "$LOG_DBG" "$LOG_REL"
touch  "$LOG_DBG" "$LOG_REL"
rm -rf "$TARGET_DBG" "$TARGET_REL"

###############################################################

if [ "$DO_CLEAN" == "true" ] ; then
    make clean
fi

if [ "$DO_DEBUG" == "true" ] ; then
    make "$MAKETARGET_DBG"
    CT_BuildLog -reformat "$LOG_DBG"
fi

if [ "$DO_RELEASE" == "true" ] ; then
    make "$MAKETARGET_REL"
    CT_BuildLog -reformat "$LOG_REL"
fi

###############################################################

date

