class MonotonicityError < StandardError
end

class ArgumentError < StandardError
end

class Spy

  EXIT_BAD_ARGUMENTS = 2
  EXIT_MONOTONICITY = 3

  SPY_PATH = File.join( File.dirname( __FILE__ ), "..", "spy" )

  attr_accessor :elf_path, :threshold, :slot
  attr_reader :probe_names

  def initialize(elf_path = nil)
    @elf_path = elf_path
    @threshold = 120
    @slot = 2048
    @probes = []
    @probe_names = []
    @spy_io = nil
    @whole_output = nil
  end

  def addProbe(name, address)
    if name =~ /\A[A-Za-z]\Z/
      @probe_names << name
      @probes << name + ':0x' + address.to_s(16)
    else
      raise ArgumentError.new("Name must be exactly one alphabet character.")
    end
  end

  def loadProbes(file)
    lines = File.readlines(file)
    lines.each do |line|
      # Strip comments
      line.gsub!(/#.*$/, '')
      # Strip whitespace
      line.gsub!(/\s/, '')
      if /\A([a-zA-Z]):0x([0-9A-Fa-f]+)\Z/ =~ line
        addProbe($1, $2.to_i(16))
      elsif !line.empty?
        puts "Invalid probe file!"
        exit
      end
    end
  end

  def start
    if @elf_path.nil?
      raise ArgumentError.new("The elf_path is not set.")
    end

    unless @spy_io.nil?
      raise ArgumentError.new("Already started.")
    end

    if @probes.empty?
      raise ArgumentError.new("There are no probes.")
    end

    command = [
        SPY_PATH,
        "-e", @elf_path,
        "-s", @slot.to_s,
        "-t", @threshold.to_s
      ]
    @probes.each do |probe|
      command << "-p"
      command << probe
    end

    @spy_io = IO.popen(command, "r")
    @whole_output = ""
    # TODO: check error exits
  end

  def stop
    Process.kill("KILL", @spy_io.pid)
    # Read any remaining output.
    # FIXME: this might block if there was no output
    @whole_output += parse_output(@spy_io.read)
    @spy_io.close
    @spy_io = nil
    return @whole_output
  end

  def each_burst(wait = 1)
    # Holds the output from the current burst.
    burst_output = ""

    loop do
      begin
        # Attempt to read output.
        output = ""
        @spy_io.read_nonblock(1_000_000, output)
        output = parse_output(output)
        # If we get output, add it to the burst buffer.
        # We only want to yield the buffer after 'wait' seconds of silence.
        # Or, equvalently, after we've waited and read nothing.
        burst_output += output
      rescue Errno::EWOULDBLOCK
        # When nothing gets read, we end up here.
          unless burst_output.empty?
            # If the current burst is not empty, yield the buffer and empty.
            yield burst_output
            @whole_output += burst_output
            burst_output = ""
          end
      rescue IO::WaitReadable
        # It's one of the other reasons read() fails.
        # In this case, immediately retry reading without delay.
        retry
      rescue EOFError
        @spy_io.close
        if $?.exitstatus == EXIT_BAD_ARGUMENTS
          raise ArgumentError.new("Spy program says bad arguments.")
        elsif $?.exitstatus == EXIT_MONOTONICITY
          raise MonotonicityError.new("RDTSC behaved non-monotonically.")
        else
          raise ArgumentError.new("Unknown error.")
        end
      end
      sleep wait
    end
  end

  def parse_output(raw_output)

    if raw_output.include? "Monotonicity failure"
      raise MonotonicityError.new("RDTSC behaved non-monotonically.")
    end

    lines = raw_output.split("\n")
    lines.reject! { |l| l.include?("WARNING") || l.include?("Detected ELF type") }

    return lines.join("\n")
  end

end
