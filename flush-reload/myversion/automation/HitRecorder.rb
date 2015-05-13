#!/usr/bin/env ruby

$LOAD_PATH << File.dirname( __FILE__ )

require 'optparse'

$options = {}
optparse = OptionParser.new do |opts|
  opts.banner = "Usage: #{__FILE__} -p <probe file> [OPTIONS] COMMAND"

  $options[:probe_file] = nil
  opts.on( '-p', '--probe-file FILE', 'File with list of addresses to probe.' ) do |path|
    $options[:probe_file] = path
  end

  $options[:output_file] = nil
  opts.on( '-o', '--output-file FILE', 'Write output to this file (stdout otherwise).' ) do |path|
    $options[:output_file] = path
  end

  $options[:kill_time] = nil
  opts.on( '-k', '--kill-time SECONDS', 'Kill process this many seconds after starting.' ) do |seconds|
    $options[:kill_time] = seconds.to_i
  end

  # For links we breakpoint close_socket(), the third hit (skipping two)
  # so 0x412c30:2 -- actually this isn't quite reliable when probes change

  $options[:stop_breakpoints] = []
  opts.on( '-s', '--stop-breakpoint ADDRESS', 'Stop when this breakpoint gets hit.' ) do |addr|
    if /\A0x([0-9a-fA-F]+)(:(\d+))?\z/ =~ addr
      count = 0
      if $2
        count = $2.split(':')[1].to_i
      end
      $options[:stop_breakpoints] << [$1.to_i(16), count]
    else
      # TODO
    end
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


def set_breakpoints(last_breakpoint_number, breakpoints)
  result = ""
  breakpoints.each do |addr|
    result << "break *0x#{(addr + $options[:address_offset]).to_s(16)}\n"
  end
  result << "commands #{last_breakpoint_number + 1}-#{last_breakpoint_number + breakpoints.length}\n"
  result << "    silent\n"
  result << "    info reg $pc\n"
  result << "    cont\n"
  result << "end\n"
  # Max out at at 100K in the case of a really common function.
  # FIXME: parameterize this max-out value so the other script can detect it,
  # and discard ones that are this common (they actually should be way down on
  # the list anyway, but for correctness' sake)
  result << "enable count 100000 #{last_breakpoint_number + 1}-#{last_breakpoint_number + breakpoints.length}\n"
  return result
end


last_breakpoint_number = 0
gdb_script = ""
# This may have been necessary for Links, I'm not sure.
#gdb_script << "tty /dev/pts/38\n" #FIXME
gdb_script << "set logging file .run_gdboutput\n"
gdb_script << "set logging on\n"
# TODO: Forking (but do we really need to?)
# gdb_script << "set detach-on-fork off"
# https://sourceware.org/gdb/onlinedocs/gdb/Forks.html

if $options[:solib_cont_times]
  # If it's a shared library, we have to wait for it to load.
  gdb_script << "set stop-on-solib-events 1\n"
else
  # If it's not a shared library, we can set breakpoints before running.
  gdb_script << set_breakpoints(last_breakpoint_number, breakpoints)
  last_breakpoint_number += breakpoints.length
end

$options[:stop_breakpoints].each do |addr_and_count|
  addr = addr_and_count[0]
  count = addr_and_count[1]

  gdb_script << "break *0x#{addr.to_s(16)}\n"
  last_breakpoint_number += 1
  gdb_script << "ignore #{last_breakpoint_number} #{count}\n"
  gdb_script << "commands\n"
  gdb_script << "    quit\n"
  gdb_script << "end\n"
end

gdb_script << "r"
ARGV.each_with_index do |arg, i|
  # Skip the executable path.
  next if i == 0

  # FIXME: This isn't correct (cross-check with usage in
  # IndividualProbeTester.rb)...
  # FIXME: HACK: this padding lets us pass switches that optparse won't see
  gdb_script << " #{arg.gsub("PADDING", "")}"
end
gdb_script << " > /dev/null 2>&1 \n"

if $options[:solib_cont_times]
  # Continue to the last shared library load.
  ($options[:solib_cont_times] - 1).times do |i|
    gdb_script << "cont\n"
  end
  # Now we can set the breakpoints.
  gdb_script << set_breakpoints(last_breakpoint_number, breakpoints)
  last_breakpoint_number += breakpoints.length
  # Continue after the last shared library load (allow execution to proceed).
  gdb_script << "cont\n"
end

File.open( ".run_gdbcommands", "w" ) do |f|
  f.write(gdb_script)
end

if File.exist?(".run_gdboutput")
  File.unlink(".run_gdboutput")
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
  # FIXME: We might kill an innocent process here if it's already exited!
  Process.kill("INT", gdb_pid)
  Process.wait(gdb_pid)
else
  Process.wait(gdb_pid)
end

results = []
gdb_lines = File.readlines(".run_gdboutput")
gdb_lines.each do |line|
  line.strip!
  if /\Apc\s+(0x[0-9a-fA-F]+)\s/ =~ line
    results << $1.to_i(16)
  end
end

File.unlink(".run_gdbcommands")
File.unlink(".run_gdboutput")

results.each do |addr|
  output_io.write("0x#{addr.to_s(16)}\n")
end
output_io.close
