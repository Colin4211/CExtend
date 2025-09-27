#!/bin/bash
clear
date

###############################################################

LOG_DEBUG="../../Output/BuildLogs/CExtend_Libraries_CExThreading.LinuxI64.Debug.log"
LOG_RELEASE="../../Output/BuildLogs/CExtend_Libraries_CExThreading.LinuxI64.Release.log"

TARGET_DEBUG="../../Output/Libs/LinuxI64_Debug/CExThreading_LinuxI64_d.lib"
TARGET_RELEASE="../../Output/Libs/LinuxI64_Release/CExThreading_LinuxI64.lib"

rm -rf "$LOG_DEBUG" "$LOG_RELEASE"
touch  "$LOG_DEBUG" "$LOG_RELEASE"
rm -rf "$TARGET_DEBUG" "$TARGET_RELEASE"

###############################################################

DO_DEBUG="true"
DO_RELEASE="true"
DO_CLEAN="false"

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
    else
        echo "### ERROR: Invalid ARG -->$CUR_ARG<-- "
        exit
    fi
done

###############################################################

if [ "$DO_CLEAN" == "true" ] ; then
    make clean
fi

if [ "$DO_DEBUG" == "true" ] ; then
    make build_Debug
    CT_BuildLog -reformat "$LOG_DEBUG"
fi

if [ "$DO_RELEASE" == "true" ] ; then
    make build_Release
    CT_BuildLog -reformat "$LOG_RELEASE"
fi

###############################################################

date

