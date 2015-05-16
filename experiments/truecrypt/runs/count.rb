
total_standard = 0
total_hidden = 0
right_standard = 0
right_hidden = 0

File.open( ARGV[0], "r") do |f|
  file = f.read()
  samples = file.split("Sample")
  samples.reject! { |s| s.empty? }
  samples.each do |sample|
    if sample.include?("ACTUAL: hidden")
      total_hidden += 1
      if sample.include? "right"
        right_hidden += 1
      end
    elsif sample.include?("ACTUAL: standard")
      total_standard += 1
      if sample.include? "right"
        right_standard += 1
      end
    else
      p sample
      raise "Ahh!!"
    end
  end
end

puts "Normal: #{right_standard}/#{total_standard}"
puts "Hidden: #{right_hidden}/#{total_hidden}"
