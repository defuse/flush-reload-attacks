#!/usr/bin/env ruby

$LOAD_PATH << File.dirname( __FILE__ )

require 'optparse'
require 'digest'
require '../../flush-reload/myversion/RubyInterface.rb'

$options = {}
optparse = OptionParser.new do |opts|
  opts.banner = "Usage: #{__FILE__} [options]"

  $options[:urls] = nil
  opts.on( '-u', '--url-list FILE', 'List of URLs to train on.' ) do |path|
    $options[:urls] = path
  end

  $options[:traindir] = nil
  opts.on( '-t', '--train-dir DIR', 'Directory to save training in (must be empty).' ) do |dir|
    $options[:traindir] = dir
  end

  $options[:links] = nil
  opts.on( '-l', '--links-path PATH', 'Path to the links web browser.' ) do |path|
    $options[:links] = path
  end

  $options[:samples] = 1
  opts.on( '-s', '--samples N', 'Number of samples to capture' ) do |n|
    $options[:samples] = n.to_i
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

if $options[:urls].nil?
  exit_with_message(optparse, "Missing --url-list")
end
unless File.exists?($options[:urls])
  exit_with_message(optparse, "URL file does not exist.")
end

if $options[:traindir].nil?
  exit_with_message(optparse, "Missing --train-dir")
end
if Dir.exist?($options[:traindir])
  exit_with_message(optparse, "Training directory already exists.")
end

if $options[:links].nil?
  exit_with_message(optparse, "Missing --links-path (path to links binary).")
end

if $options[:samples] <= 0
  exit_with_message(optparse, "Bad --samples value.")
end

Dir.mkdir($options[:traindir])

urls = File.readlines($options[:urls]).uniq.map { |line| line.chomp }

metadata_path = File.join($options[:traindir], "METADATA")
metadata = File.open(metadata_path, "w")

urls.each_with_index do |train_url, index|
  url_hash = Digest::SHA256.hexdigest(train_url)
  metadata.puts "#{url_hash}: #{train_url}"

  puts "Sampling[%03d/%03d]: %s" % [index+1, urls.length, train_url]
  1.upto($options[:samples]) do |sample_n|
    begin
      puts "    #{sample_n}..."
      spy = Spy.new($options[:links])
      spy.addProbe("R", 0x422460)
      spy.addProbe("D", 0x41f8b0)
      spy.addProbe("H", 0x41e480)
      spy.addProbe("S", 0x41eab0)
      spy.start

      links = IO.popen([$options[:links], train_url, :err=>[:child, :out]])
      sleep 3
      # Use SIGINT. SIGKILL leaves the terminal broken.
      Process.kill("INT", links.pid)

      output = spy.stop.gsub("\n", "")

      # Collapse repeated probes into just one.
      output.gsub!("|", "")
      output.gsub!(/D+/, "D")
      output.gsub!(/R+/, "R")
      output.gsub!(/H+/, "H")
      output.gsub!(/S+/, "S")

      output_path = File.join($options[:traindir], url_hash + "_" + sample_n.to_s)
      File.open( output_path, "w" ) do |f|
        f.write(output)
      end
    rescue MonotonicityError
      puts "[!!] Monotonicity Error! Re-doing sample."
      retry
    end
  end

end

metadata.close
