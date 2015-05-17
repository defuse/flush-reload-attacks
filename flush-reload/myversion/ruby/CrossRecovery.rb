#!/usr/bin/env ruby

require 'optparse'

$options = {}
optparse = OptionParser.new do |opts|
  opts.banner = "Usage: #{__FILE__} [options]"

  $options[:recordingdir] = nil
  opts.on( '-r', '--recording-dir DIR', 'Directory of recording directories' ) do |dir|
    $options[:recordingdir] = dir
  end

  $options[:traindir] = nil
  opts.on( '-t', '--train-dir DIR', 'Training directory.' ) do |dir|
    $options[:traindir] = dir
  end

  $options[:truncate] = 1_000_000
  opts.on( '-m', '--max-length LEN', 'Truncate strings to this length before computing distance.' ) do |len|
    $options[:truncate] = len.to_i
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

total = 0
correct = 0
Dir.foreach( $options[:recordingdir] ) do |dirname|
  next if [".", ".."].include? dirname

  dir_path = File.join($options[:recordingdir], dirname)
  hash = File.basename(dir_path).split('_')[0]
  url = hash_to_url[hash]
  print "#{url}: "

  recovery = IO.popen(
    [
      "ruby",
      File.join(File.dirname(__FILE__), "AttackRecovery.rb"),
      "--recording-dir", dir_path,
      "--train-dir", $options[:traindir],
      "--max-length", $options[:truncate].to_s,
    ]
  )
  Process.wait(recovery.pid)
  recovered_url = recovery.readlines[0].chomp.split(": ")[1]
  if recovered_url == url
    correct += 1
    print "P "
  else
    print "U "
  end
  print "\n"
  total += 1
end

puts "#{correct}/#{total} = #{correct/total.to_f}"
