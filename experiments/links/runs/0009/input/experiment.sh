#!/bin/bash

source ../funcs.sh
trap 'exp_failed' ERR

# Puts the ouput directory in $OUTPUT_DIR.
source ../experiment.sh

cp ../../flush-reload/myversion/spy $EXTRA_INPUT/
cp ../../flush-reload/myversion/RubyInterface.rb $EXTRA_INPUT/

status "Running the experiment script..."
ruby LinksExperiment.rb "$OUTPUT_DIR" 2>$OUTPUT_DIR/stderr | tee $OUTPUT_DIR/stdout

exp_completed
