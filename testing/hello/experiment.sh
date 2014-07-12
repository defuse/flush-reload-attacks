#!/bin/bash

# Copy state for better reproducibility.
# TODO: Move this code into a global script to be included in all experiments.
rm -rf data
mkdir data
mkdir data/state
cp * data/state/
cp ../../flush-reload/spy data/state/
uname -a > data/uname.output
date > data/date.output
uptime > data/uptime.output

# Start the spy process.
# (You must have built the spy tool.)
../../flush-reload/spy hello.probe > data/spy.output &
SPY_PID=$!

# Wait for the spy to get started.
sleep 2

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
) | ./hello > data/hello.output 

# Stop the spy process.
kill -9 "$SPY_PID"
