#!/bin/bash

function header {
    echo ""
    echo "-------------------------"
    echo "$1"
    echo "-------------------------"
    echo ""
}

header "Basic Information"

echo -n "DATE:    "
date
echo -n "UPTIME:  "
uptime
echo -n "KERNEL:  "
uname -a

header "Memory Usage"
free

header "Disk Usage"
df

header "Processor"
cat /proc/cpuinfo

header "Compiler"
gcc -v -v --version 2>&1
