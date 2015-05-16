#!/usr/bin/env ruby

$LOAD_PATH << File.dirname( __FILE__ )

require 'optparse'
require 'RubyInterface.rb'

$options = {}
optparse = OptionParser.new do |opts|
  opts.banner = "Usage: #{__FILE__} [options]"

  $options[:spy_binary] = nil
  opts.on( '-b', '--spy-binary FILE', 'Binary to spy on.') do |path|
    $options[:spy_binary] = path
  end

  $options[:outputdir] = nil
  opts.on( '-d', '--output-dir DIR', 'Output directory.' ) do |dir|
    $options[:outputdir] = dir
  end

  $options[:probefile] = nil
  opts.on( '-p', '--probe-file FILE', 'Probe configuration file.' ) do |path|
    $options[:probefile] = path
  end
end

def exit_with_message(optparse, msg)
  STDERR.puts "[!] #{msg}"
  STDERR.puts optparse
  exit(false)
end

begin
  optparse.parse!
rescue OptionParser::InvalidOption
  exit_with_message(optparse, "Invalid option.")
rescue OptionParser::MissingArgument
  exit_with_message(optparse, "Missing argument.")
end

if $options[:outputdir].nil?
  exit_with_message(optparse, "Missing --output-dir")
end
if Dir.exist?($options[:outputdir])
  exit_with_message(optparse, "Output directory already exists.")
end

if $options[:spy_binary].nil?
  exit_with_message(optparse, "Missing --spy-binary.")
end

if $options[:probefile].nil?
  exit_with_message(optparse, "Missing --probe-file.")
end

Dir.mkdir($options[:outputdir])

begin
  spy = Spy.new($options[:spy_binary])
  spy.loadProbes($options[:probefile])
  spy.start
  trap("SIGINT") do 
    spy.stop
    exit
  end
  spy.each_burst do |burst|
    # Ignore blips
    if burst.length > 5
      # NOTE: This code must match up with AttackTrainer.rb 
      # Join all of the lines.
      burst.gsub!("\n", "")
      # Remove pipe characters between slots.
      burst.gsub!("|", "")
      # We DON'T remove missed slots here, because we want them to be visible in
      # the saved experiment output, we DO do that just before computing the
      # Levenshtein distance.

      # Collapse repeated probes into just one occurance.
      spy.probe_names.each do |n|
        burst.gsub!(/#{n}+/, n)
      end

      save_path = File.join( $options[:outputdir], Time.now.to_i.to_s )
      File.open( save_path, "w" ) do |f|
        f.write(burst)
      end
    end
  end
rescue MonotonicityError
  puts "[!!] Monotonicity Error! Re-starting."
  retry
end
