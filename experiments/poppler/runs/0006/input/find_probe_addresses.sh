#!/bin/bash

ruby ../../flush-reload/myversion/ruby/FindProbeAddresses.rb \
    -n 'Gfx::opShowSpaceText(Object*, int)' \
    -n 'Gfx::opTextMoveSet(Object*, int)' \
    -n 'Gfx::opSetFont(Object*, int)' \
    -n 'Gfx::opTextNextLine(Object*, int)' \
    -b /tmp/experiment_root/lib/libpoppler.so.51
