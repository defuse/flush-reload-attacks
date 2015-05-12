require 'lib/ObjdumpLine.rb'
require 'lib/Instruction.rb'

class ObjdumpReader

  def self.objdump_output( args )
    output = nil
    args.unshift( "objdump" )
    IO.popen( args ) do |obj|
      output = obj.read
    end
    return output
  end

  def self.lines_to_instrs( lines )
    all_instructions = []

    i = 0
    while i < lines.length
      instr = [lines[i]]
      i += 1
      # Sometimes objdump breaks an instruction into two or more lines.
      while i < lines.length && lines[i].instruction.empty?
        instr << lines[i]
        i += 1
      end
      
      address = instr[0].address
      code = instr[0].instruction
      opcode = instr.map { |x| x.opcode }.join("").gsub(/\s/, "")
      binary = Instruction.hex2bin( opcode )
      
      all_instructions << Instruction.new( address, binary, code )
    end

    return all_instructions
  end

  def self.x86ELF?( elf_path )
    output = self.objdump_output( ["--file-headers", elf_path] )
    return output.include? "file format elf32-i386"
  end

end
