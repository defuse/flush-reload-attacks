#!/bin/bash

# Prerequisites:
# 1. The Flush+Reload spy tool exists at ../../flush-reload/spy.

source ../funcs.sh
trap 'exp_failed' ERR

ensure_spy_not_running

# Leaves the ouput directory in $OUTPUT_DIR.
source ../experiment.sh

cp ../../flush-reload/spy $EXTRA_INPUT/spy

status "Starting the spy process."
../../flush-reload/spy hello.probe > $OUTPUT_DIR/spy.output &
SPY_PID=$!

# Wait for the spy to get started.
sleep 2

status "Running ./hello"
# Run the vulnerable target program.
(
    echo "H";
    echo "H";
    sleep 1;
    echo "E";
    echo "E";
    sleep 1;
    echo "L";
    echo "L";
    sleep 1;
    echo "L";
    echo "L";
    sleep 1;
    echo "O";
    echo "O";
    sleep 1;
    echo "Q";
    sleep 5;
) | ./hello > $OUTPUT_DIR/hello.output

# Stop the spy process.
status "Killing the spy process"
kill -9 "$SPY_PID"

exp_completed
