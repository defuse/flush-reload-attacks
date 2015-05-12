
class InstructionArgument
  # Types:
  #   :memory_computed - A computed address, e.g. [ecx+4]
  #   :memory_constant - A constant used as an address, e.g. ds:0xdeadbeef
  #   :constant        - A constant, e.g. 0xdeadbeef
  #   :register        - A register, e.g. eax
  attr_reader :raw, :type

  def initialize( argument_code )
    @raw = argument_code.strip

    # TODO: extensive testing of this

    # FIXME: this is information-lossy

    # Computed memory address, e.g. [ecx+4]
    if @raw =~ /\[(.*)\]/
      #FIXME: the type of PTR is lost here
      @type = :memory_computed
      @address = $1.downcase
    # Constant memory address, e.g. DWORD PTR 0xdeadbeef
    elsif @raw =~ /PTR\s+(.*)$/
      @type = :memory_constant
      @address = $1
    # Constant memory address, e.g. ds:0xdeadbeef (usually LHS argument)
    elsif @raw =~ /(cs|ds|es|fs|gs|ss):0x[0-9a-fA-F]+/
      @type = :memory_constant
      @address = @raw
    # Numeric constant.
    elsif @raw =~ /^(?:0x)?([0-9a-fA-F]+)(?:\s*\<(.*)\>)?$/
      @type = :constant
      @value = $1.to_i(16)
      @hint = $2
    # Otherwise, assume it's a register.
    else
      @type = :register
      @register = @raw.downcase
    end
  end

  # Memory
  def address
    unless [:memory_computed, :memory_constant].include? @type
      throw ArgumentError.new( "Not a memory type." )
    end
    return @address
  end

  # Constant
  def value
    unless @type == :constant
      throw ArgumentError.new( "Not a constant type." )
    end
    return @value
  end

  def hint
    unless @type == :constant
      throw ArgumentError.new( "Not a constant type." )
    end
    return @hint
  end

  # Register
  def register
    unless @type == :register
      throw ArgumentError.new( "Not a register type." )
    end
    return @register
  end

  def to_s
    case @type
      when :memory_computed
        "[" + @address + "]"
      when :memory_constant
        @address
      when :constant
        "0x#{@value.to_s(16)} <#{@hint}>"
      when :register
        @register
    end
  end

end
