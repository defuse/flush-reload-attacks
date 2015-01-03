MAX = 200
MIN = 150
p File.readlines("values.dat").map { |s| s.to_i }.reject { |v| v < MIN || v > MAX }
