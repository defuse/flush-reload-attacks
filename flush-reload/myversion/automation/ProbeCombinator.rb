#!/usr/bin/env ruby

$LOAD_PATH << File.dirname( __FILE__ )

require 'optparse'
require 'Common.rb'

$options = {}
optparse = OptionParser.new do |opts|
  opts.banner = "Usage: #{__FILE__} [OPTIONS]"

  $options[:probe_file] = nil
  opts.on( '-p', '--probe-list FILE', 'Probe list in best->worst order.' ) do |path|
    $options[:probe_file] = path
  end

  $options[:probe_set_size] = nil
  opts.on( '-s', '--set-size COUNT', 'Size of the probe set.' ) do |count|
    $options[:probe_set_size] = count.to_i
  end

  $options[:output_file] = nil
  opts.on( '-o', '--output-file FILE', 'Output file.' ) do |path|
    $options[:output_file] = path
  end
end

begin
  optparse.parse!
rescue OptionParser::InvalidOption
  exit_with_message(optparse, "Invalid option.")
rescue OptionParser::MissingArgument
  exit_with_message(optparse, "Missing argument")
end

if $options[:probe_file].nil?
  exit_with_message(optparse, "Please provide an --probe-list")
end

if $options[:output_file].nil?
  exit_with_message(optparse, "Please provide an --output-file")
end

if $options[:probe_set_size].nil? || $options[:probe_set_size] < 2
  exit_with_message(optparse, "Please provide an --set-size >= 2")
end

probe_candidates = load_probe_file(optparse, $options[:probe_file])

# FIXME: this is pretty ugly
probe_candidates.each_with_index do |probe, i|
  probe.rank = i
end

probe_sets = probe_candidates.combination($options[:probe_set_size]).to_a

# Reject if there is a pair within 3-ish cache lines of each other (either direction).
probe_sets.reject! do |probe_set|
  reject = false
  probe_set.combination(2) do |pair|
    if (pair[0].address - pair[1].address).abs <= 3*64
      reject = true
      break
    end
  end
  reject
end

# Sort by lowest total rank first.
probe_sets.sort! do |a,b|
  a_total_rank = a.inject(0) { |sum, probe| sum + probe.rank }
  b_total_rank = b.inject(0) { |sum, probe| sum + probe.rank }
  # FIXME: should we do something special when the ranks are the same?
  a_total_rank <=> b_total_rank
end

File.open($options[:output_file], "w") do |f|
  probe_sets.each do |probe_set|
    f.write("-" * 80 + "\n")
    probe_set.each do |probe|
      f.write(probe.to_s + "\n")
    end
  end
end
