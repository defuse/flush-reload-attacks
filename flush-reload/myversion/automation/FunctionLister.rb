#!/usr/bin/env ruby

$LOAD_PATH << File.dirname( __FILE__ )

require 'optparse'
require 'lib/CallGraphGenerator.rb'

$options = {}
optparse = OptionParser.new do |opts|
  opts.banner = "Usage: #{__FILE__} -e <elf path> -o <output file>"

  $options[:elf_file] = nil
  opts.on( '-e', '--elf-path FILE', 'ELF binary.') do |path|
    $options[:elf_file] = path
  end

  $options[:output_file] = nil
  opts.on( '-o', '--output-file FILE', 'Output file.') do |path|
    $options[:output_file] = path
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
  exit_with_message(optparse, "Missing argument")
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

callgraph = CallGraphGenerator.new($options[:elf_file])
functions = callgraph.generate()

functions.each do |function|
  output_file.write("0x#{function.start_addr.to_s(16)} #{function.name}\n")
end
output_file.close

