#!/usr/bin/env ruby

if ARGV[0].nil?
  puts "Must pass output directory on command line!"
  exit(false)
end

URL_LIST_FILE = "pdf_lists/pdflist.txt"
SAMPLE_COUNT = 5
OUTPUT_DIR = ARGV[0]
RUN_BINARY = "/tmp/experiment_root/bin/pdftops"
SPY_BINARY = "/tmp/experiment_root/lib/libpoppler.so.51"
PROBES_PATH = "libpoppler-debian.probes"
VICTIM_RUNS = 10
STRING_TRUNCATE_LENGTH = 1000
SLEEP_KILL = false

require '../../flush-reload/myversion/ruby/RunExperiment.rb'
