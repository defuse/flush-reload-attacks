class IndividualProbe
  attr_reader :address, :extra

  # Variance on same input and different input.
  attr_accessor :si_var, :di_var, :base, :same, :diff, :metric, :rank
  def initialize(address, extra = "")
    @address = address
    @extra = extra
    @si_var = -1
    @di_var = -1
    @base = -1
    @same = -1
    @diff = -1
    @metric = -1
  end

  def to_s
    "0x%08x%-60s (Quality: %7d %7d %7d %7d %7d %7d)" % [@address, @extra, @si_var, @di_var, @metric, @base, @same, @diff]
  end
end

def exit_with_message(optparse, msg)
  STDERR.puts "[!] #{msg}"
  STDERR.puts optparse
  exit(false)
end

def load_probe_file(optparse, path)
  probe_file_lines = File.readlines(path)
  probe_candidates = []
  probe_file_lines.each do |line|
    line.strip!
    if /\A0x([0-9a-fA-F]+)(\s.*)?\z/ =~ line
      probe_candidates << IndividualProbe.new($1.to_i(16), $2)
    else
      exit_with_message(optparse, "Invalid probe line [#{line}]")
    end
  end
  return probe_candidates
end
