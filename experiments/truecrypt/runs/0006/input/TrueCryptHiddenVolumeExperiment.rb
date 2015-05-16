#!/usr/bin/env ruby

require '../../flush-reload/myversion/ruby/RubyInterface.rb'

SAMPLES = 500
TC_PATH = "./binaries/truecrypt-arch"
PROBES_PATH = "./binaries/truecrypt-arch.probes"
VOLUME_BYTES = 1_000_000
HIDDEN_VOL = "./hidden.tc"
STANDARD_VOL = "./standard.tc"
MAJORITY_COUNT = 3

$right = 0
$wrong = 0
$hidden = 0
$standard = 0
$monotonicity = 0
$unknown = 0

def decide(output)
  puts "DECIDING..."
  puts "OUTPUT: [#{output}]"
  if output.length >= 4
    if output.end_with? "R|"
    #if output.scan("R|").length < 6
      return :standard
    else
      return :hidden
    end
    #if output.end_with? "G|"
    #  puts "DECISION: hidden"
    #  return :hidden
    #elsif output =~ /(G\|)+(R\|)+/
    #  puts "DECISION: standard"
    #  return :standard
    #else
    #  puts "DECISION: unknown"
    #  return :unknown
    #end
  else
    # Blip
      puts "DECISION: unknown (blip)"
    return :unknown
  end
end

# Create the standard volume.
IO.popen(
[
    TC_PATH,
    "-t",
    "--non-interactive",
    "-c",
    "-p",
    "1234",
    "--volume-type=normal",
    "--size=#{VOLUME_BYTES}",
    "--encryption=AES",
    "--hash=RIPEMD-160",
    "--filesystem=FAT",
    STANDARD_VOL
], "r") do |x|
end
if $?.exitstatus != 0
  puts "Error."
  exit
end

# Create the hidden volume.
IO.popen(
[
    TC_PATH,
    "-t",
    "--non-interactive",
    "-c",
    "-p",
    "asdf",
    "--volume-type=normal",
    "--size=#{VOLUME_BYTES}",
    "--encryption=AES",
    "--hash=RIPEMD-160",
    "--filesystem=FAT",
    HIDDEN_VOL
], "r") do |x|
end
if $?.exitstatus != 0
  puts "Error."
  exit
end

IO.popen(
[
    TC_PATH,
    "-t",
    "--non-interactive",
    "-c",
    "-p",
    "1234",
    "--volume-type=hidden",
    "--size=#{VOLUME_BYTES/2}",
    "--encryption=AES",
    "--hash=RIPEMD-160",
    "--filesystem=FAT",
    HIDDEN_VOL
], "r") do |x|
end
if $?.exitstatus != 0
  puts "Error."
  exit
end

def array_majority(array)
  freq = array.inject(Hash.new(0)) { |h,v| h[v] += 1; h }
  return array.max_by { |v| freq[v] }
end

SAMPLES.times do |i|
  print "\n\n"
  puts "Sample #{i} ----------------------------------------------------"
  begin

    # Randomly mount the hidden or the standard
    actual = :standard
    if rand() < 0.5
      puts "ACTUAL: standard"
      $standard += 1
    else
      actual = :hidden
      puts "ACTUAL: hidden"
      $hidden += 1
    end

    majority = []

    MAJORITY_COUNT.times do |k|
      # Dismount both hidden and standard.
      IO.popen( [TC_PATH, "-t", "--non-interactive", "-d", HIDDEN_VOL], "r") do |x|
      end
      IO.popen( [TC_PATH, "-t", "--non-interactive", "-d", STANDARD_VOL], "r") do |x|
      end

      # Start spying
      spy = Spy.new(TC_PATH)
      spy.loadProbes(PROBES_PATH)
      spy.slot = 20480
      spy.start

      sleep 1

      if actual == :standard
        IO.popen( [TC_PATH, "-t", "--non-interactive", "-p", "1234", STANDARD_VOL], "r") do |x|
        end
      else
        IO.popen( [TC_PATH, "-t", "--non-interactive", "-p", "1234", HIDDEN_VOL], "r") do |x|
        end
      end

      # Stop the spy, getting the output.
      result = spy.stop

      # Decide whether we think it was a hidden or standard.
      majority << decide(result)
    end

    p majority
    decision = array_majority(majority)
    puts "DECISION: #{decision}"
    if decision == actual
      puts "right"
      $right += 1
    elsif decision == :unknown
      puts "UNKNOWN##########"
      $unknown += 1
    else
      puts "WRONG########################"
      $wrong += 1
    end

  rescue MonotonicityError
    $monotonicity += 1
  end
end

puts "TOTALS:"
puts "    SMPLS: #{SAMPLES}"
puts "    WRONG: #{$wrong}"
puts "    RIGHT: #{$right}"
puts "    MONO:  #{$monotonicity}"
puts "    UNK:   #{$unknown}"
puts "    STD:   #{$standard}"
puts "    HDN:   #{$hidden}"

