#!/bin/bash
clear
date

make clean
CT_BuildConfigTool -force -verbose  .
make
CT_GeanyProject -r .

