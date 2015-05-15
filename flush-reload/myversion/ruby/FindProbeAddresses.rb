#!/usr/bin/env ruby

require 'optparse'

$options = {}
optparse = OptionParser.new do |opts|
  opts.banner = "Usage: #{__FILE__} [options]"

  $options[:probe_func_names] = []
  opts.on( '-n', '--probe-name NAME', 'Probe name as in objdump (demangled)' ) do |name|
    $options[:probe_func_names] << name
  end

  $options[:binary_path] = nil
  opts.on( '-b', '--binary FILE', 'Path to the binary (must not be stripped)' ) do |path|
    $options[:binary_path] = path
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

if $options[:binary_path].nil?
  exit_with_message(optparse, "Missing --binary")
end

if $options[:probe_func_names].empty?
  exit_with_message(optparse, "Please give some --probe-name's")
end

lines = `objdump -t --demangle #{$options[:binary_path]} | fgrep .text`.split("\n")
name_to_addr = {}
lines.each do |line|
  parts = line.split(/(  |\t)/)
  addr = parts[0].split(' ')[0].to_i(16)
  name = parts[-1]
  name_to_addr[name] = addr
end

probe_names = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz".split('')
$options[:probe_func_names].each do |name|
  if name_to_addr[name]
    puts "#{probe_names.shift}:0x#{name_to_addr[name].to_s(16)}"
  else
    exit_with_message(optparse, "Name [#{name}] not found.")
  end
end
