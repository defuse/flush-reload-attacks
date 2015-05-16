#!/usr/bin/env ruby

$LOAD_PATH << File.dirname( __FILE__ )

require 'optparse'
require 'digest'
require 'RubyInterface.rb'

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

  $options[:run_binary] = nil
  opts.on( '-l', '--run-binary PATH', 'Path to the binary to run.' ) do |path|
    $options[:run_binary] = path
  end

  $options[:samples] = 1
  opts.on( '-s', '--samples N', 'Number of samples to capture' ) do |n|
    $options[:samples] = n.to_i
  end

  $options[:probefile] = nil
  opts.on( '-p', '--probe-file FILE', 'Probe configuration file.' ) do |path|
    $options[:probefile] = path
  end

  $options[:sleep_kill] = nil
  opts.on( '-k', '--sleep-kill SECONDS', 'Kill process after this many seconds.') do |seconds|
    $options[:sleep_kill] = seconds.to_i
  end

  $options[:spy_binary] = nil
  opts.on( '-b', '--spy-binary FILE', 'Binary to spy (default same as --run-binary).') do |path|
    $options[:spy_binary] = path
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

if $options[:run_binary].nil?
  exit_with_message(optparse, "Missing --run-binary.")
end

if $options[:probefile].nil?
  exit_with_message(optparse, "Missing --probe-file (path to probe config)")
end

if $options[:samples] <= 0
  exit_with_message(optparse, "Bad --samples value.")
end

if $options[:spy_binary].nil?
  $options[:spy_binary] = $options[:run_binary]
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
      spy = Spy.new($options[:spy_binary])
      spy.loadProbes($options[:probefile])
      spy.start

      run_proc = IO.popen([$options[:run_binary], train_url, :err=>[:child, :out]])
      if $options[:sleep_kill]
        sleep 7
        # Use SIGINT. SIGKILL leaves the terminal broken.
        Process.kill("INT", run_proc.pid)
      else
        Process.wait(run_proc.pid)
      end

      # NOTE: This code must match up with AttackRecorder.rb
      output = spy.stop.gsub("\n", "")
      # Remove pipe characters between slots.
      output.gsub!("|", "")

      # Collapse repeated probes into just one occurance.
      spy.probe_names.each do |n|
        output.gsub!(/#{n}+/, n)
      end

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
