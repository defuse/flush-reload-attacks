#!/bin/bash

# The calling script is responsible for running the experiment and saving the
# output to $OUTPUT_DIR. Additional input can be put in $EXTRA_INPUT.

# The directory *this* script is in (where library scripts are kept).
OUR_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

source $OUR_DIR/funcs.sh

# Make sure the ./runs and ./testrun directories exist.
mkdir -p ./runs
mkdir -p ./testrun

# By default, the run is saved to ./testrun.
THIS_RUN=./testrun

# Otherwise, we create a new directory in ./runs
if [ "$1" = "--keep" ]; then
    # Find this run's number.
    NNNN=$(find ./runs/ -maxdepth 1 -type d | grep '[0-9]\{4\}' | wc -l)
    let NNNN=NNNN+1
    NNNN=$(printf "%04d" $NNNN)

    # Create the run directory.
    THIS_RUN=./runs/$NNNN
    mkdir $THIS_RUN
fi

echo "[*] Experiment run will be saved to $THIS_RUN"
rm -rf $THIS_RUN/*

# Record pre-run state for better reproducibility.
status "Saving system information."
$OUR_DIR/systeminfo.sh > $THIS_RUN/SystemInfo.txt


status "Copying input."
mkdir $THIS_RUN/input
rsync -a ./ $THIS_RUN/input --exclude runs --exclude testrun

# Save the helper scripts, so that it's possible to know exactly what happened.
mkdir $THIS_RUN/helpers
cp $OUR_DIR/*.sh $THIS_RUN/helpers/

# Give the experiment script a place to put its own additional input.
mkdir $THIS_RUN/extra_input
EXTRA_INPUT=$THIS_RUN/extra_input

# Create an experimenter's notes file.
echo "Experiment Notes" > $THIS_RUN/NOTES.txt
echo "-----------------" >> $THIS_RUN/NOTES.txt
echo "Date: $(date)" >> $THIS_RUN/NOTES.txt

# Create output directory.
mkdir $THIS_RUN/output
OUTPUT_DIR=$THIS_RUN/output

status "Running experiment."
