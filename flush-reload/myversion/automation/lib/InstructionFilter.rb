require 'set'
require 'digest'

class InstructionFilter

  def initialize
    @allowed = Set.new
    $filter_classes ||= Set.new
  end

  def setMostRestrictive( required_instrs )
    required_instrs.each do |i|
      @allowed << instr_class( i )
    end
    $filter_classes.merge( @allowed )
  end

  def allows?( instrs )
    instrs = [instrs].flatten
    return instrs.inject( true ) { |res,i| res && @allowed.include?( instr_class( i ) ) }
  end

  def instr_class( instr )
    raise "Incomplete class!"
  end

end

class NullInstructionFilter < InstructionFilter

  def instr_class( instr )
    ""
  end

  def allows?( instrs )
    true
  end

end

class ExactInstructionFilter < InstructionFilter

  def instr_class( instr )
    instr.binary
  end

end

class MnemonicInstructionFilter < InstructionFilter

  def instr_class( instr )
    instr.mnemonic
  end

end

class MnemonicArgTypeInstructionFilter < InstructionFilter

  def instr_class( instr )
    instr.mnemonic + "::" + instr.args.map { |a| a.type.to_s }.join( "::" )
  end

end

class MnemonicArgTypeRegisterInstructionFilter < InstructionFilter

  def instr_class( instr )
    instr.mnemonic + "::" + instr.args.map do |a|
      if a.type == :register
        a.register
      else
        a.type.to_s
      end
    end.join( "::" )
  end

end

class DJB512InstructionFilter < InstructionFilter

  def instr_class( instr )
    hash = 5381
    instr.binary.each_byte do |b|
      hash = ((hash << 5) + hash) + b
    end
    return hash % 512
  end

end

class DJB1024InstructionFilter < InstructionFilter

  def instr_class( instr )
    hash = 5381
    instr.binary.each_byte do |b|
      hash = ((hash << 5) + hash) + b
    end
    return hash % 1024
  end

end

class DJB4096InstructionFilter < InstructionFilter

  def instr_class( instr )
    hash = 5381
    instr.binary.each_byte do |b|
      hash = ((hash << 5) + hash) + b
    end
    return hash % 4096
  end

end

