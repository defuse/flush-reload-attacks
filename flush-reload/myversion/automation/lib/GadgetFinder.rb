require 'lib/Instruction.rb'
require 'lib/ObjdumpReader.rb'
require 'lib/Print.rb'

# TODO: add different options for gadget finders

class GadgetPointer
  attr_reader :start_address, :instruction_count

  def initialize( start_address, instruction_count )
    @start_address = start_address
    @instruction_count = instruction_count
  end

  # Convert to array of Instruction
  def to_gadget( elf_path )
    stop_address = @start_address + 16*@instruction_count
    output = ObjdumpReader.objdump_output(
      [
        "-M", "intel", "-D",
        "--start-address=0x#{@start_address.to_s(16)}",
        "--stop-address=0x#{stop_address.to_s(16)}",
        elf_path
      ]
    )
    lines = output.split( "\n" ).map { |l| ObjdumpLine.new( l ) }
    lines.reject! { |l| l.type != :instruction }
    instrs = ObjdumpReader.lines_to_instrs( lines )
    if instrs.length == 0
      Print::error( "Gadget has zero length." )
    end
    return instrs.first( @instruction_count )
  end
end

# External gadget finders -- return array of GadgetPointer

class GadgetFinder

  def initialize( elf_path )
    @elf_path = elf_path
  end

  def findGadgets
    pointers = findGadgetPointers
    # We don't trust the gadget finder to be unique, so we uniq it ourselves.
    pointers.uniq! { |p| [p.start_address, p.instruction_count] }
    gadgets =  pointers.map { |g| g.to_gadget( @elf_path ) }
    gadgets.uniq! { |g| g.map { |i| i.binary }.join( "" ) }
    return gadgets.to_set
  end

  # In derived classes, this must return an array of GadgetPointer
  def findGadgetPointers
    raise "Incomplete class."
  end

end

class ROPgadgetGadgetFinder < GadgetFinder

  def findGadgetPointers
    output = nil
    IO.popen( ["ROPgadget", "-nocolor", "-nopayload", @elf_path, :err=>[:child, :out]] ) do |rop|
      output = rop.read
    end

    return output.split( "\n" ).reject { |l| !l.start_with? "0x" }.map do |line|
      line =~ /^0x([0-9a-fA-F]+):\s+(.*)$/
      address = $1.to_i(16)
      length = $2.split( ";" ).length
      GadgetPointer.new( address, length )
    end
  end

end

class MineGadgetFinder < GadgetFinder

  def findGadgetPointers
    output = nil
    IO.popen( ["../rop/gadget_finder", @elf_path] ) do |rop|
      output = rop.read
    end

    blocks = output.split( "-----------------------\n" )
    blocks.map! { |b| b.split( "\n" ).map { |l| l =~ /0x([0-9a-fA-F]+):/ ; $1.to_i(16) } }

    pointers = []
    blocks.each do |block|
      2.upto( block.length ) do |length|
        pointers << GadgetPointer.new( block[block.length - length], length )
      end
    end

    return pointers
  end

end
