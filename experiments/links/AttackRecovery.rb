#!/usr/bin/env ruby

$LOAD_PATH << File.dirname( __FILE__ )

require 'optparse'
require 'levenshtein'
require 'parallel'

$options = {}
optparse = OptionParser.new do |opts|
  opts.banner = "Usage: #{__FILE__} [options]"

  $options[:recordingdir] = nil
  opts.on( '-r', '--recording-dir DIR', 'Directory of recordings.' ) do |dir|
    $options[:recordingdir] = dir
  end

  $options[:traindir] = nil
  opts.on( '-t', '--train-dir DIR', 'Training directory.') do |dir|
    $options[:traindir] = dir
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

if $options[:traindir].nil?
  exit_with_message(optparse, "Missing --train-dir")
end
unless Dir.exist?($options[:traindir])
  exit_with_message(optparse, "Training directory does not exist.")
end

if $options[:recordingdir].nil?
  exit_with_message(optparse, "Missing --recording-dir")
end
unless Dir.exist?($options[:recordingdir])
  exit_with_message(optparse, "Recording directory does not exist.")
end


metadata_path = File.join($options[:traindir], "METADATA")
metadata = File.readlines(metadata_path)

hash_to_url = {}

metadata.each do |line|
  line = line.chomp
  s = line.split(": ")
  hash_to_url[s[0]] = s[1]
end

Dir.foreach( $options[:recordingdir] ) do |filename|
  next if [".", ".."].include? filename

  rec_path = File.join($options[:recordingdir], filename)
  recording = File.read(rec_path)


  train_files = Dir.entries( $options[:traindir] ) - [".", ".."]

  distances = Parallel.map( train_files ) do |train_file|
    train_path = File.join($options[:traindir], train_file)
    training = File.read(train_path)
    {
      distance: Levenshtein.distance(recording, training),
      file: train_file
    }
  end

  closest_distance = 1_000_000_000
  closest_file = nil

  distances.each do |hash|
    if hash[:distance] < closest_distance
      closest_distance = hash[:distance]
      closest_file = hash[:file]
    end
  end

  url_hash = closest_file.split("_")[0]
  puts "#{filename}: #{hash_to_url[url_hash]}"
end
