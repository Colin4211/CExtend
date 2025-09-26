#!/bin/bash

###############################################################

TOOL_NAME_LINUXI64_DBG="PlatformInfo_LinuxI64_d"
TOOL_NAME_LINUXI64_REL="PlatformInfo_LinuxI64"

WORK_DIR_LINUXI64_DBG="../../Output/Distrib/LinuxI64_Debug"
WORK_DIR_LINUXI64_REL="../../Output/Distrib/LinuxI64_Release"


###############################################################

TOOL_NAME_LINUXI32_DBG="PlatformInfo_LinuxI32_d"
TOOL_NAME_LINUXI32_REL="PlatformInfo_LinuxI32"

WORK_DIR_LINUXI32_DBG="../../Output/Distrib/LinuxI32_Debug"
WORK_DIR_LINUXI32_REL="../../Output/Distrib/LinuxI32_Release"

###############################################################

TOOL_NAME_GENERIC_DBG="PlatformInfo_Generic_d"
TOOL_NAME_GENERIC_REL="PlatformInfo_Generic"

WORK_DIR_GENERIC_DBG="../../Output/Distrib/Generic_Debug"
WORK_DIR_GENERIC_REL="../../Output/Distrib/Generic_Release"

###############################################################

TOOL_NAME_LINUXARM_DBG="PlatformInfo_LinuxARM_d"
TOOL_NAME_LINUXARM_REL="PlatformInfo_LinuxARM"

WORK_DIR_LINUXARM_DBG="../../Output/Distrib/LinuxARM_Debug"
WORK_DIR_LINUXARM_REL="../../Output/Distrib/LinuxARM_Release"

###############################################################

TOOL_NAME_DBG="$TOOL_NAME_LINUXI64_DBG"
TOOL_NAME_REL="$TOOL_NAME_LINUXI64_REL"
WORK_DIR_DBG="$WORK_DIR_LINUXI64_DBG"
WORK_DIR_REL="$WORK_DIR_LINUXI64_REL"

###############################################################

DO_DEBUG="true"
DO_RELEASE="true"

for CUR_ARG in "${@}" ; do
    if [ "$CUR_ARG" == "DEBUG" ] ; then
        DO_DEBUG="true"
        DO_RELEASE="false"
    elif [ "$CUR_ARG" == "RELEASE" ] ; then
        DO_DEBUG="false"
        DO_RELEASE="true"
    elif [ "$CUR_ARG" == "ALL" ] ; then
        DO_DEBUG="true"
        DO_RELEASE="true"
    elif [ "$CUR_ARG" == "LINUXI64" ] ; then
        TOOL_NAME_DBG="$TOOL_NAME_LINUXI64_DBG"
        TOOL_NAME_REL="$TOOL_NAME_LINUXI64_REL"
        WORK_DIR_DBG="$WORK_DIR_LINUXI64_DBG"
        WORK_DIR_REL="$WORK_DIR_LINUXI64_REL"
    elif [ "$CUR_ARG" == "LINUXI32" ] ; then
        TOOL_NAME_DBG="$TOOL_NAME_LINUXI32_DBG"
        TOOL_NAME_REL="$TOOL_NAME_LINUXI32_REL"
        WORK_DIR_DBG="$WORK_DIR_LINUXI32_DBG"
        WORK_DIR_REL="$WORK_DIR_LINUXI32_REL"
    elif [ "$CUR_ARG" == "GENERIC" ] ; then
        TOOL_NAME_DBG="$TOOL_NAME_GENERIC_DBG"
        TOOL_NAME_REL="$TOOL_NAME_GENERIC_REL"
        WORK_DIR_DBG="$WORK_DIR_GENERIC_DBG"
        WORK_DIR_REL="$WORK_DIR_GENERIC_REL"
    elif [ "$CUR_ARG" == "LINUXARM" ] ; then
        TOOL_NAME_DBG="$TOOL_NAME_LINUXARM_DBG"
        TOOL_NAME_REL="$TOOL_NAME_LINUXARM_REL"
        WORK_DIR_DBG="$WORK_DIR_LINUXARM_DBG"
        WORK_DIR_REL="$WORK_DIR_LINUXARM_REL"
    else
        echo "### ERROR: Invalid ARG -->$CUR_ARG<-- "
        exit
    fi
done

###############################################################

TOOL_NAME="$TOOL_NAME_DEBUG"
WORK_DIR="$WORK_DIR_DEBUG"

###############################################################

TEST_ARGS=" Float=1.234    Float=-5.678  "
TEST_ARGS=" Float32=42.0 Float80=432.2994234"

###############################################################

clear
echo "==================================================================="
echo "==             date = $(date) "
echo "==    TOOL_NAME_DBG = $TOOL_NAME_DBG "
echo "==     WORK_DIR_DBG = $WORK_DIR_DBG  "
echo "==    TOOL_NAME_REL = $TOOL_NAME_REL "
echo "==     WORK_DIR_REL = $WORK_DIR_REL  "
echo "==        TEST_ARGS = $TEST_ARGS  "
echo "==         DO_DEBUG = $DO_DEBUG  "
echo "==       DO_RELEASE = $DO_RELEASE  "
echo "==================================================================="

if [ "$DO_DEBUG" == "true" ] ; then
    cd $WORK_DIR_DBG
    $TOOL_NAME_DBG  $TEST_ARGS
elif [ "$DO_RELEASE" == "true" ] ; then
    cd $WORK_DIR_REL
    $TOOL_NAME_REL  $TEST_ARGS
fi

echo "==================================================================="


