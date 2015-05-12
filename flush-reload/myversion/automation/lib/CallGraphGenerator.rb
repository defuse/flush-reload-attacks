require 'set'
require 'lib/Print.rb'
require 'lib/Instruction.rb'
require 'lib/Function.rb'
require 'lib/ObjdumpReader.rb'
require 'lib/ObjdumpLine.rb'

# NOTE: names are not unique, so we use address ranges to identify

class CallGraphGenerator

  attr_reader :elf_path, :functions

  BRANCH_MNEMONICS = [
  # TODO: add the other types of call instruction (are there any?)
    "call", 
    "jo", "jno", "js", "jns", "je", "jz", "jne", "jnz", "jb", "jnae", "jc",
    "jbe", "jna", "ja", "jnbe", "jl", "jnge", "jge", "jnl", "jle", "jng",
    "jg", "jnle", "jp", "jpe", "jnp", "jpo", "jcxz", "jecxz",
  ].to_set

  def initialize( path )
    @elf_path = path
    @functions = []
  end

  def generate
    extract_functions()
    add_edges()
    return @functions
  end

  # private FIXME (testing )

  def extract_functions
    output = ObjdumpReader.objdump_output(
      [
        "-M", "intel", "-D", 
        "--section=.text", "--section=.plt", "--section=.init", 
        "--demangle", @elf_path
      ]
    )
    lines = output.split("\n").map { |l| ObjdumpLine.new( l ) }

    @functions = Set.new
    last_label = nil
    last_instrs = nil

    lines.each do |l|
      if l.type == :label
        unless last_label.nil?
          f = Function.new(
            last_label.name,
            last_label.address,
            l.address,
            ObjdumpReader.lines_to_instrs( last_instrs )
          )
          @functions << f
        end
        last_label = l
        last_instrs = []
      elsif l.type == :instruction
        unless last_instrs.nil?
          last_instrs << l
        end
      end
    end
  end

  def add_edges
    @functions.each do |f|
      f.disassembly.each do |instr|
        
        if BRANCH_MNEMONICS.member?( instr.mnemonic ) && instr.args[0].type == :constant
          # FIXME: this will make inner loops look recursive. Maybe we should
          # stick with call? Or make J* instructions add a maybe_call to itself?
          called = find_function_at( instr.args[0].value )
          if called.nil?
            Print::error( "Function [#{instr.args[0].hint}] at [0x#{instr.args[0].value.to_s(16)}] doesn't exist!" )
            next
          end
          f.calls << called
          called.called_by << f
        elsif BRANCH_MNEMONICS.member?( instr.mnemonic ) && instr.args[0].type != :constant
          f.maybe_calls = @functions
          f.maybe_calls.each do |func|
            func.maybe_called_by << f
          end
        end
      end
    end
  end

  def find_function_at( address )
    @functions.each do |f|
      if f.start_addr <= address && address < f.end_addr # FIXME only exact?
        return f
      end
    end
    return nil
  end

end
