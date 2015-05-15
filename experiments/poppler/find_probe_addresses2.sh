#!/bin/bash

ruby ../../flush-reload/myversion/ruby/FindProbeAddresses.rb \
    -n 'gmallocn' \
    -n 'PSOutputDev::writePSString(GooString*)' \
    -n 'PSOutputDev::drawString(GfxState*, GooString*)' \
    -n 'PSOutputDev::updateTextShift(GfxState*, double)' \
    -b /tmp/experiment_root/lib/libpoppler.so.51
