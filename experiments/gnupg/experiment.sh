#!/bin/bash

# Prerequisites:
# 1. The Flush+Reload spy tool exists at ../../flush-reload/spy.
# 2. GnuPG binary at ../../source/gnupg-1.4.13/g10/gpg

source ../funcs.sh
trap 'exp_failed' ERR

GPG_DIR="../../source/gnupg-1.4.13"

# Leaves the ouput directory in $OUTPUT_DIR.
source ../experiment.sh

cp ../../flush-reload/spy $EXTRA_INPUT/spy
cp $GPG_DIR/g10/gpg $EXTRA_INPUT/gpg

status "Starting the spy process."
../../flush-reload/spy mygpg.conf > $OUTPUT_DIR/spy.output &
SPY_PID=$!

# Wait for the spy to get started.
sleep 2

GNUPGHOME=./dot-gnupg

status "Running a GnuPG decryption"
$GPG_DIR/g10/gpg -d ./testfiles/hello.txt.gpg 2>$OUTPUT_DIR/gpg.err 1>$OUTPUT_DIR/gpg.out

# Stop the spy process.
status "Killing the spy process"
kill -9 "$SPY_PID"

exp_completed
