#!/usr/bin/env ruby

$LOAD_PATH << File.dirname( __FILE__ )

require 'optparse'
require '../../flush-reload/myversion/RubyInterface.rb'

$options = {}
optparse = OptionParser.new do |opts|
  opts.banner = "Usage: #{__FILE__} [options]"

  $options[:links] = nil
  opts.on( '-l', '--links-path PATH', 'Path to the links web browser.' ) do |path|
    $options[:links] = path
  end

  $options[:outputdir] = nil
  opts.on( '-d', '--output-dir DIR', 'Output directory.' ) do |dir|
    $options[:outputdir] = dir
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

if $options[:links].nil?
  exit_with_message(optparse, "Missing --links-path (path to links binary)")
end

Dir.mkdir($options[:outputdir])

begin
  spy = Spy.new($options[:links])
  spy.addProbe("R", 0x422460)
  spy.addProbe("D", 0x41f8b0)
  spy.addProbe("H", 0x41e480)
  spy.addProbe("S", 0x41eab0)
  spy.start
  spy.each_burst do |burst|
    # Ignore blips
    if burst.length > 5
      # Collapse
      burst.gsub!("\n", "")
      burst.gsub!("|", "")
      burst.gsub!(/D+/, "D")
      burst.gsub!(/R+/, "R")
      burst.gsub!(/H+/, "H")
      burst.gsub!(/S+/, "S")

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
