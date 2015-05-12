require 'set'
require 'lib/Function.rb'
require 'lib/Shellcode.rb'
require 'lib/Print.rb'

class FunctionSequence < Array

  def initialize( start )
    start = [*start]
    start.each do |s|
      self << s
    end
  end

  def advance( next_f )
    next_f = [*next_f]
    return FunctionSequence.new( self + next_f )
  end

end

class PathFinder

  attr_accessor :allow_calls, :allow_maybe_calls
  attr_accessor :allow_called_by, :allow_maybe_called_by
  attr_accessor :complete

  def initialize( all_functions )
    @functions = all_functions
    @paths = Hash.new { |h,k| h[k] = Hash.new }
    @allow_calls = false
    @allow_maybe_calls = false
    @allow_called_by = false
    @allow_maybe_called_by = false
    @complete = false
  end

  def process
    return if @complete

    @functions.each do |start|
      # All nodes have the 0-length path to themselves
      @paths[start][start] = [start]

      # 'seen' is the set of all nodes that we've visited, or in other words,
      # for which we know a path from 'start' to.
      seen = [start].to_set
      # 'seen_unprocessed' is the subset of 'seen' for which we haven't
      # added their neighbours.
      seen_unprocessed = seen

      # Keep adding neighbour nodes until there are no more neighbours to add.
      loop do
        # Loop over all nodes we have seen but not yet added neighbours.
        # A list of new nodes (not 'seen') that we discover in this iteration.
        seen_thistime = Set.new
        seen_unprocessed.each do |s|

          # List their neighbours
          if @allow_calls
            s.calls.each do |n|
              # If we haven't seen it before...
              unless seen.member?( n ) || seen_thistime.member?( n )
                # Add the new-found path, and remember that we've seen it.
                @paths[start][n] = @paths[start][s] + [n]
                seen_thistime << n
              end
            end
          end

          if @allow_maybe_calls
            s.maybe_calls.each do |n|
              # If we haven't seen it before...
              unless seen.member?( n ) || seen_thistime.member?( n )
                # Add the new-found path, and remember that we've seen it.
                @paths[start][n] = @paths[start][s] + [n]
                seen_thistime << n
              end
            end
          end

          if @allow_called_by
            s.called_by.each do |n|
              # If we haven't seen it before...
              unless seen.member?( n ) || seen_thistime.member?( n )
                # Add the new-found path, and remember that we've seen it.
                @paths[start][n] = @paths[start][s] + [n]
                seen_thistime << n
              end
            end
          end

          if @allow_maybe_called_by
            s.maybe_called_by.each do |n|
              # If we haven't seen it before...
              unless seen.member?( n ) || seen_thistime.member?( n )
                # Add the new-found path, and remember that we've seen it.
                @paths[start][n] = @paths[start][s] + [n]
                seen_thistime << n
              end
            end
          end

        end # seen_unprocessed.each

        # Everything in the old seen_unprocessed is now processed, but none of
        # the nodes we added in this iteration are processed, so process them
        # next time.
        seen_unprocessed = seen_thistime
        seen.merge( seen_thistime )

        # If we didn't encounter any new nodes, we're done for this function.
        break if seen_thistime.empty?
      end # loop
    end # @functions.each
  end

  def set_allows( calls, maybe_calls, called_by, maybe_called_by )
    @allow_calls = calls
    @allow_maybe_calls = maybe_calls
    @allow_called_by = called_by
    @allow_maybe_called_by = maybe_called_by
  end

  def get_path( from, to )
    if @complete
      return [to]
    else
      return @paths[from][to]
    end
  end

end

class GraphSearchResults
  attr_accessor :per_function_avg, :per_function_max
  attr_accessor :cutoff_avg, :cutoff_max

  def initialize
    @per_function_avg = 0.0
    @per_function_max = 0
    @cutoff_avg = 0.0
    @cutoff_max = 0
  end
end

class GraphSearch

  attr_reader :start, :all, :paths

  def initialize( start_function, all_functions, path_finder )
    @start = start_function
    @all = all_functions
    @paths = path_finder
  end

  def executable_prefix_length( sc_goals )
    state = [FunctionSequence.new( @start )].to_set
    length = 0
    nextState = Set.new
    sc_goals.each do |goals|
      nextState.clear
      # FIXME: this probably doesn't have to be n^2
      goals.each do |to|
        state.each do |from_fs|
          path = @paths.get_path( from_fs.last, to )
          unless path.nil?
            # FIXME: is this making it n^3? would it be better if nextState was
            # an array?
            nextState << from_fs.advance( path[1..-1] )
            break
          end
        end
      end

      if nextState.empty?
        break
      end
      state = nextState.clone
      length += 1
    end

    return length
  end

  def self.get_shellcode_goals( shellcodes, all_functions )
    @@cache ||= Hash.new { |h,k| h[k] = Hash.new } 
    if @@cache[shellcodes] && @@cache[shellcodes][all_functions]
      return @@cache[shellcodes][all_functions]
    end
    sc_goals = shellcodes.map do |shellcode|
      shellcode.gadgets.map do |gadget|
        all_functions.reject{ |f| !f.filter.allows?( gadget ) }
      end
    end
    @@cache[shellcodes][all_functions] = sc_goals
    return sc_goals
  end

  def self.run( eval_functions, functions, shellcodes, path_finder )
    results = GraphSearchResults.new
    sc_goals = self.get_shellcode_goals( shellcodes, functions )
    eval_functions.each do |f|
      Print::status "Evaluating shellcodes from function #{f.name}"
      count = 0
      searcher = GraphSearch.new( f, functions, path_finder )
      sc_goals.each do |s|
        length = searcher.executable_prefix_length( s )
        if length == s.length
          count += 1
        else
          results.cutoff_avg += length
          results.cutoff_max = [length, results.cutoff_max].max
        end
      end
      results.per_function_avg += count
      results.per_function_max = [count, results.per_function_max].max
    end
    results.per_function_avg /= eval_functions.length
    results.cutoff_avg /= (eval_functions.length * shellcodes.length)

    return results
  end

end
