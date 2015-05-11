#!/usr/bin/env ruby

$LOAD_PATH << File.dirname( __FILE__ )

require 'optparse'

$options = {}
optparse = OptionParser.new do |opts|
  opts.banner = "Usage: #{__FILE__} -p <probe file> [-o <output file>] COMMAND"

  $options[:probe_file] = nil
  opts.on( '-p', '--probe-file FILE', 'File with list of addresses to probe.' ) do |path|
    $options[:probe_file] = path
  end

  $options[:output_file] = nil
  opts.on( '-o', '--output-file FILE', 'Write output to this file (stdout otherwise)' ) do |path|
    $options[:output_file] = path
  end

  $options[:kill_time] = nil
  opts.on( '-k', '--kill-time SECONDS', 'Kill process this many seconds after starting' ) do |seconds|
    $options[:kill_time] = seconds.to_i
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

if $options[:output_file].nil?
  output_io = STDOUT
else
  begin
    output_io = File.open($options[:output_file], "w")
  rescue
    exit_with_message(optparse, "Error opening the output file.")
  end
end

if $options[:probe_file].nil?
  exit_with_message(optparse, "Missing --probe-file argument.")
else
  begin
    probe_lines = File.readlines($options[:probe_file])
  rescue
    exit_with_message(optparse, "Error opening probe file.")
  end
end

if ARGV.empty?
  exit_with_message(optparse, "Missing command to run.")
end

breakpoints = []
probe_lines.each do |line|
  line.strip!
  next if line.empty?
  if /\A0x([0-9a-fA-F])+\z/ =~ line
    breakpoints << line.to_i(16)
  else
    exit_with_message(optparse, "Probe file contains bad address #{line}")
  end
end

gdb_script = ""
gdb_script << "set logging file .run_gdboutput\n"
gdb_script << "set logging on\n"
# TODO: Forking (but do we really need to?)
# gdb_script << "set detach-on-fork off"
# https://sourceware.org/gdb/onlinedocs/gdb/Forks.html
breakpoints.each do |addr|
  gdb_script << "break *0x#{addr.to_s(16)}\n"
end
gdb_script << "commands 1-#{breakpoints.length}\n"
gdb_script << "    cont\n"
gdb_script << "end\n"

gdb_script << "r"
ARGV.each_with_index do |arg, i|
  # Skip the executable path.
  next if i == 0

  # FIXME: This isn't correct...
  gdb_script << " #{arg}"
end
gdb_script << " > /dev/null 2>&1 \n"

File.open( ".run_gdbcommands", "w" ) do |f|
  f.write(gdb_script)
end

gdb_pid = Process.spawn(
  *[
    "gdb",
    "-x", ".run_gdbcommands",
    "-batch",
    ARGV[0]
  ]
)
if $options[:kill_time]
  sleep $options[:kill_time]
  Process.kill("INT", gdb_pid)
else
  Process.wait(gdb_pid)
end

results = []
gdb_lines = File.readlines(".run_gdboutput")
gdb_lines.each do |line|
  line.strip!
  if /\ABreakpoint (\d)+, (0x[0-9a-fA-F]+) in/ =~ line
    results << $2.to_i(16)
  end
end

File.unlink(".run_gdbcommands")
File.unlink(".run_gdboutput")

results.each do |addr|
  output_io.write("0x#{addr.to_s(16)}\n")
end
output_io.close
