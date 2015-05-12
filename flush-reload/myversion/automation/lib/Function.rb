require 'set'

class Function
  attr_reader :start_addr, :end_addr
  attr_accessor :name, :disassembly, :calls, :called_by, :maybe_calls, :maybe_called_by, :filter, :gadgets

  def initialize(name, start_addr, end_addr, disassembly)
    @name = name
    @start_addr = start_addr
    @end_addr = end_addr
    @disassembly = disassembly
    @calls = Set.new
    @called_by = Set.new
    @maybe_calls = Set.new
    @maybe_called_by = Set.new
    @filter = nil
    @gadgets = nil

    if @start_addr > @end_addr
      raise ArgumentError.new( "start_addr > end_addr" )
    end
  end

  def applyFilter( filter_class )
    @filter = filter_class.new
    @filter.setMostRestrictive( @disassembly )
  end

  def to_s
    return @name # FIXME
    "#{@name} (0x#{@start_addr.to_s(16)} - 0x#{@end_addr.to_s(16)}):\n" +
      @disassembly.map { |x| x.to_s }.join("\n")
  end

end
