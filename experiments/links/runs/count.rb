
lines = File.readlines(ARGV[0])
lines.reject! { |l| !(l.start_with? "https://") }
freq = {}
mean = 0
lines.each do |line|
  split = line.split(' ')
  p split
  good = 0
  1.upto(10) do |result|
    if split[result] == "P"
      good += 1
    end
  end
  puts good
  if freq[good].nil?
    freq[good] = 0
  end
  freq[good] += 1
  mean += good
end
mean /= 100.0
puts mean
p freq
