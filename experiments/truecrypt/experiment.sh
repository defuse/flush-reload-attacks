#!/bin/bash

source ../funcs.sh
trap 'exp_failed' ERR

# Puts the ouput directory in $OUTPUT_DIR.
source ../experiment.sh

# Get sudo working (it's cached)
sudo echo Thanks

cp ../../flush-reload/myversion/spy $EXTRA_INPUT/
cp ../../flush-reload/myversion/RubyInterface.rb $EXTRA_INPUT/

status "Running the experiment script..."
ruby TrueCryptHiddenVolumeExperiment.rb 2>$OUTPUT_DIR/stderr | tee $OUTPUT_DIR/stdout

mv ./hidden.tc $OUTPUT_DIR/
mv ./standard.tc $OUTPUT_DIR/

exp_completed
