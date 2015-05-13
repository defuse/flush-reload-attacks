#!/usr/bin/env ruby

$LOAD_PATH << File.dirname( __FILE__ )

require 'optparse'
require 'Common.rb'

$options = {}
optparse = OptionParser.new do |opts|
  opts.banner = "Usage: #{__FILE__} [OPTIONS]"

  $options[:probe_file] = nil
  opts.on( '-p', '--probe-list FILE', 'Probe list.' ) do |path|
    $options[:probe_file] = path
  end

  $options[:input_pool_file] = nil
  opts.on( '-i', '--input-pool FILE', 'Input pool (one set of command-line args per line)' ) do |path|
    $options[:input_pool_file] = path
  end

  $options[:elf_file] = nil
  opts.on( '-e', '--elf-path FILE', 'ELF binary.' ) do |path|
    $options[:elf_file] = path
  end

  $options[:output_file] = nil
  opts.on( '-o', '--output-file FILE', 'Output file.' ) do |path|
    $options[:output_file] = path
  end

  $options[:kill_time] = nil
  opts.on( '-k', '--kill-time SECONDS', 'Kill process this many seconds after starting.' ) do |seconds|
    $options[:kill_time] = seconds.to_i
  end

  $options[:solib_cont_times] = nil
  opts.on( '-l', '--shared-library TIMES', 'Times to cont in GDB to pass solib loading.' ) do |times|
    $options[:solib_cont_times] = times.to_i
  end

  $options[:address_offset] = 0
  opts.on( '-a', '--address-offset OFFSET', 'Address offset.' ) do |offset|
    if /\A0x([0-9a-fA-F]+)\z/ =~ offset
      $options[:address_offset] = $1.to_i(16)
    else
      # FIXME
      raise "FIXME!!!"
    end
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

if $options[:input_pool_file].nil?
  exit_with_message(optparse, "Please provide an --input-pool")
end

if $options[:elf_file].nil?
  exit_with_message(optparse, "Please provide an --elf-path")
end

if $options[:output_file].nil?
  output_file = STDOUT
else
  output_file = File.open($options[:output_file], "w")
  # FIXME: error handling
end

probe_candidates = load_probe_file(optparse, $options[:probe_file])

File.open($options[:input_pool_file], "r") do |f|
  INPUTS = f.readlines.map do |line|
    line.strip!
    parts = line.split(';')
    if parts.length == 1
      setup = parts[0]
      teardown = nil
    elsif parts.length == 2
      setup = parts[0]
      teardown = parts[1]
    else
      exit_with_message(optparse, "Bad input line [#{line}].")
    end
    {
      setup: setup,
      teardown: teardown
    }
  end
end

if INPUTS.length < 2
  exit_with_message(optparse, "Not enough distinct inputs in the pool.")
end

def count_probe_hits(probe, arguments)
  File.open(".run_probefile", "w") do |f|
    f.write("0x#{probe.address.to_s(16)}\n")
  end
  if File.exist?(".run_hits")
    File.unlink(".run_hits")
  end
  args = [
    "ruby",
    "HitRecorder.rb",
    "-p", ".run_probefile",
    "-o", ".run_hits",
    "-a", "0x#{$options[:address_offset].to_s(16)}"
  ]
  if $options[:kill_time]
    args << "-k"
    args << $options[:kill_time].to_s
  end
  if $options[:solib_cont_times]
    args << "-l"
    args << $options[:solib_cont_times].to_s
  end
  args << $options[:elf_file]
  args << arguments[:setup]
  ruby_pid = Process.spawn(*args)
  Process.wait(ruby_pid)
  count = `wc -l .run_hits`.split(' ')[0].to_i

  if arguments[:teardown]
      `#{$options[:elf_file]} #{arguments[:teardown]}`
  end

  return count
end

probe_candidates.each do |probe|
  # FIXME: these results don't seem to correspond well with manual runs,
  # sometimes seems to double? Hmm... I guess it was just a sporadic issue,
  # since I am no longer seeing the problem. I'll leave this comment here in
  # case I get bored and want to investigate later.
  probe.base = count_probe_hits(probe, INPUTS[0])
  probe.same = count_probe_hits(probe, INPUTS[0])
  probe.diff = count_probe_hits(probe, INPUTS[1])

  probe.si_var = (probe.same - probe.base).abs
  probe.di_var = (probe.diff - probe.base).abs

  probe.metric = probe.di_var - probe.si_var
end

probe_candidates.sort! do |a,b|
  b.metric <=> a.metric
end

probe_candidates.each do |probe|
  output_file.write(probe.to_s + "\n")
end
output_file.close
