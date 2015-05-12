
require 'lib/CallGraphGenerator.rb'
require 'lib/Instruction.rb'
require 'lib/Function.rb'
require 'lib/FunctionGraphRenderer.rb'
require 'lib/InstructionFilter.rb'
require 'lib/ExploitPotentialEvaluator.rb'
require 'lib/GadgetFinder.rb'
require 'lib/ObjdumpReader.rb'
require 'lib/Cache.rb'
require 'lib/Results.rb'

class Results

  attr_accessor :executable_path, :executable_hash
  attr_accessor :start_time, :end_time
  attr_accessor :filter_class, :filter_classes
  attr_accessor :functions_all, :functions_used
  attr_accessor :gadgets
  attr_accessor :gadgets_per_func_avg, :gadgets_per_func_max
  attr_accessor :shellcodes_all_per_func_avg
  attr_accessor :shellcodes_all_per_func_max
  attr_accessor :shellcodes_all_cutoff_avg, :shellcodes_all_cutoff_max
  attr_accessor :shellcodes_reverse_per_func_avg
  attr_accessor :shellcodes_reverse_per_func_max
  attr_accessor :shellcodes_reverse_cutoff_avg, :shellcodes_reverse_cutoff_max
  attr_accessor :shellcodes_complete_per_func_avg
  attr_accessor :shellcodes_complete_per_func_max
  attr_accessor :shellcodes_complete_cutoff_avg, :shellcodes_complete_cutoff_max
  attr_accessor :gadget_samples
  attr_accessor :gadget_results

  def to_file( path )
    File.open( path, "w" ) do |f|
      f.print Marshal.dump( self )
    end
  end

  def self.from_file( path )
    File.open( path, "r" ) do |f|
      Marshal.load( f.read )
    end
  end

  def to_s
    unless [@start_time, @end_time].include? nil
      execution_seconds = (@end_time - @start_time).to_i
      minutes = "%02d" % [execution_seconds / 60]
      seconds = "%02d" % [execution_seconds % 60]
    else
      minutes = "??"
      seconds = "??"
    end

    output = ""

    output << "Executable:          #{@executable_path}\n"
    output << "SHA256:              #{@executable_hash[0, 32]}\n"
    output << "                     #{@executable_hash[32, 32]}\n"
    output << "Filter Class:        #{@filter_class}\n"
    if @filter_classes
    output << "Filter Class Count:  #{@filter_classes.length}\n"
    end
    output << "Execution Time:      #{minutes}:#{seconds}\n"
    output << "Function Count:      #{@functions_all.size}\n"
    output << "Used Functions:      #{@functions_used.size}\n"
    if @gadgets
    output << "Gadget Count:        #{@gadgets.length}\n"
    output << "Average gadgets/f:   #{@gadgets_per_func_avg}\n"
    output << "Maximum gadgets/f:   #{@gadgets_per_func_max}\n"
    end
    if @shellcodes_all_per_func_avg
    output << "Average sc/f (comp): #{@shellcodes_complete_per_func_avg}\n"
    output << "Max sc/f (comp):     #{@shellcodes_complete_per_func_max}\n" 
    output << "Average co (comp):   #{@shellcodes_complete_cutoff_avg}\n"
    output << "Max co (comp):       #{@shellcodes_complete_cutoff_max}\n"
    output << "Average sc/f (all):  #{@shellcodes_all_per_func_avg}\n"
    output << "Max sc/f (all):      #{@shellcodes_all_per_func_max}\n" 
    output << "Average co (all):    #{@shellcodes_all_cutoff_avg}\n"
    output << "Max co (all):        #{@shellcodes_all_cutoff_max}\n"
    output << "Average sc/f (rev):  #{@shellcodes_reverse_per_func_avg}\n"
    output << "Max sc/f (rev):      #{@shellcodes_reverse_per_func_max}\n" 
    output << "Average co (rev):    #{@shellcodes_reverse_cutoff_avg}\n"
    output << "Max co (rev):        #{@shellcodes_reverse_cutoff_max}\n"
    end
    if @gadget_results
      [1,3,5,7,9].each do |i|
        output << "Avg GS/f (c #{i}): #{@gadget_results[:complete][i].per_function_avg}\n"
        output << "Avg GS/f (a #{i}): #{@gadget_results[:all][i].per_function_avg}\n"
        output << "Avg GS/f (r #{i}): #{@gadget_results[:reverse][i].per_function_avg}\n"
      end
    end

    return output
  end

end
