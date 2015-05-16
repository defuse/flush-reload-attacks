#!/usr/bin/env ruby

if ARGV[0].nil?
  puts "Must pass output directory on command line!"
  exit(false)
end

URL_LIST_FILE = "url_sets/wiki-top-100-of-2013-HTTPS.txt"
#URL_LIST_FILE = "url_sets/small-test.txt"
SAMPLE_COUNT = 10
OUTPUT_DIR = ARGV[0]
RUN_BINARY = "binaries/links-debian"
SPY_BINARY = RUN_BINARY
PROBES_PATH = "binaries/links-debian-discovered.probes"
VICTIM_RUNS = 10
STRING_TRUNCATE_LENGTH = 1000
SLEEP_KILL = 7

require '../../flush-reload/myversion/ruby/RunExperiment.rb'
