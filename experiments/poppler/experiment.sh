#!/bin/bash

source ../funcs.sh
trap 'exp_failed' ERR

# Puts the ouput directory in $OUTPUT_DIR.
source ../experiment.sh

cp ../../flush-reload/myversion/spy $EXTRA_INPUT/
cp -R ../../flush-reload/myversion/ruby $EXTRA_INPUT/
cp /tmp/experiment_root/lib/libpoppler.so.51.0.0 $EXTRA_INPUT/
cp /tmp/experiment_root/bin/pdftops $EXTRA_INPUT/

status "Running the experiment script..."
ruby PopplerExperiment.rb "$OUTPUT_DIR" 2>$OUTPUT_DIR/stderr | tee $OUTPUT_DIR/stdout

exp_completed
