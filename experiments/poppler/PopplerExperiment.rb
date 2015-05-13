#!/usr/bin/env ruby

if ARGV[0].nil?
  puts "Must pass output directory on command line!"
  exit(false)
end

URL_LIST_FILE = "pdf_lists/small-pdflist.txt"
SAMPLE_COUNT = 5
OUTPUT_DIR = ARGV[0]
RUN_BINARY = "/home/firexware/Desktop/buildroot/bin/pdftops"
SPY_BINARY = "/home/firexware/Desktop/buildroot/lib/libpoppler.so.51"
PROBES_PATH = "libpoppler.probes"
VICTIM_RUNS = 1
STRING_TRUNCATE_LENGTH = 1000
SLEEP_KILL = 7

require '../../flush-reload/myversion/ruby/RunExperiment.rb'
