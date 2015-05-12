require 'lib/InstructionArgument.rb'

class Instruction

  attr_reader :address, :binary, :code, :mnemonic, :args

  def initialize(address, binary, code)
    @address = address
    @binary = binary
    @code = code

    parts = @code.split(/\s+/)

    # FIXME: we need to look for prefixes, right now prefixes are being treated
    # as the mnemonic. We have to look for the prefix byte, then remove any
    # textual prefix there may be.

    @mnemonic = parts[0].downcase
    rest = parts[1..-1].join(" ")

    # We want to ignore commas inside angle brackets, so replace everything
    # inside angle brackets with a numeric "pointer" to the old contents.
    # FIXME: This doesn't work if there is more than one group of brackets!
    #        That's OK, though, since it will never happen in x86.
    id = 0
    map = {}
    if rest =~ /\<(.*)\>/
      map[id] = $1
      rest.gsub!( /\<.*\>/, "<" + id.to_s + ">" )
      id += 1
    end

    # Now that the commas that don't separate arguments are gone, we can just
    # split on comma.
    args = rest.split(",")

    # Go through each argument and replace the angle bracket content identifier
    # with the previous content.
    args.each do |a|
      if a. =~ /\<(.*)\>/
        id = $1.to_i
        a.gsub!( /\<.*\>/, "<" + map[id] + ">" )
      end
    end

    # Finally, turn them into InstructionArguments.
    @args = args.map { |x| InstructionArgument.new( x ) }

    if @args.length > 3
      raise ArgumentError.new( "Instruction [#{code}] has 3 operands." )
    end
  end

  def hex_opcode
    Instruction.bin2hex( @binary )
  end

  def to_s
    "0x#{@address.to_s(16)}: {#{hex_opcode}} #{@code}"
  end

  def Instruction.bin2hex( bin_opcode )
    bin_opcode.unpack('H*')[0].upcase
  end

  def Instruction.hex2bin( hex_opcode )
    [hex_opcode].pack('H*')
  end

end
