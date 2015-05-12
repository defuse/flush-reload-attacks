require 'set'
require 'lib/Instruction.rb'
require 'lib/Print.rb'

class Shellcode
  include Enumerable

  attr_reader :gadgets

  def initialize( gadgets = Array.new )
    @gadgets = gadgets
  end

  def add_sequence( instr_sequence )
    if instr_sequence.class != Array
      raise ArgumentError.new( "You must provide an ARRAY of instructions." )
    end
    @gadgets << instr_sequence
  end

  def each
    @gadgets.each do |gadget|
      yield gadget
    end
  end

  def self.load_from_dir( dir )
    shellcodes = Set.new
    Dir.foreach( dir ) do |file|
      next if ["..", "."].include? file
      next unless file.end_with? ".sc"

      begin
        path = File.join( dir, file )
        serialized = File.open( path, "r" ) { |f| f.read }
        shellcodes << Marshal.load( serialized )
      rescue
        Print::error "Failed to load shellcode #{path}"
      end
    end
    return shellcodes
  end

end
