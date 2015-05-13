#!/usr/bin/env ruby

require 'gnuplot'
require 'yaml'

# The YAML produced by AttackRecovery.rb
input_path = ARGV[0]
output_path = ARGV[1]

data = YAML.load(File.read(input_path))
if data.keys.length != 1
  puts "There are more than one key, using the 'first'."
end

files_to_distances = Hash.new { |h,k| h[k] = Array.new }
array = data[data.keys[0]]
array.each do |entry|
  file = entry[:file].split('_')[0]
  dist = entry[:distance]
  files_to_distances[file] << dist
end

data = []
i = 0
files_to_distances.each do |file, distance_array|
  print "#{i} "
  distance_array.each do |d|
    data << [i, d]
    print "#{d} "
  end
  print "\n"
  i += 1
end

exit

Gnuplot.open do |gp|
  Gnuplot::Plot.new( gp ) do |plot|

    plot.title File.basename(input_path)
    # FIXME
    plot.xrange "[0:10]"
    plot.yrange "[0:2000]"

    plot.terminal "png"
    plot.output File.expand_path(output_path, __FILE__)

    plot.ylabel "Distance"
    plot.xlabel "Page (x Sample)"

    plot.data << Gnuplot::DataSet.new( "sin(x)" ) do |ds|
      ds.with = "points"
      ds.title = "Distances"
    end
  end
end

