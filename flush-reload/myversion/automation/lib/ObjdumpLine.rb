class ObjdumpLine

  attr_reader :raw, :type

  def initialize(line)
    @raw = line

    if @raw =~ /^\s*([0-9a-f]+) \<(.*)\>:\s*$/
      @type = :label
      @address = $1.to_i(16)
      @name = $2
    elsif @raw =~ /^\s*([0-9a-f]+):\s*((?:[0-9a-f]{2}\s)+)\s*(.*)$/
      @type = :instruction
      @address = $1.to_i(16)
      @opcode = $2.strip
      @instruction = $3
    elsif @raw =~ /^(.*):\s+file format\s(\S+)$/
      @type = :format
      @filename = $1
      @format = $2
    elsif @raw =~ /^Disassembly of section (.*):$/
      @type = :section
      @section = $1
    elsif @raw =~ /^\s*$/
      @type = :empty
    else
      @type = :unknown
    end

  end

  def name
    require_type :label
    return @name
  end

  def address
    require_type [:label, :instruction]
    return @address
  end

  def instruction
    require_type :instruction
    return @instruction
  end

  def opcode
    require_type :instruction
    return @opcode
  end

  def filename
    require_type :format
    return @filename
  end

  def format
    require_type :format
    return @format
  end

  def section
    require_type :section
    return @section
  end

  def to_s
    @raw
  end

  private

  def require_type( list )
    list = [list].flatten
    unless list.include? @type
      throw ArgumentError.new( "Property not supported by this line type." )
    end
  end

end
