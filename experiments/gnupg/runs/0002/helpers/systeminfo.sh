#!/bin/bash

echo -n "DATE:    "
date
echo -n "UPTIME:  "
uptime
echo -n "KERNEL:  "
uname -a

echo "MEMORY:"
free

echo "PROCESSOR:"
cat /proc/cpuinfo
