#!/bin/bash

ruby ../../flush-reload/myversion/ruby/FindProbeAddresses.rb \
    -n 'kill_html_stack_item' \
    -n 'html_stack_dup' \
    -n 'html_a' \
    -n 'parse_html' \
    -b binaries/links-debian
