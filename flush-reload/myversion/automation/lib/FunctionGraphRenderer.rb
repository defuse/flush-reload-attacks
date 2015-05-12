require 'graphviz'

class FunctionGraphRenderer

  def FunctionGraphRenderer.make_image( functions, type, output_path )
    g = GraphViz.new( :G, :type => :digraph )

    # Create a node for every function.
    nodes = {}
    functions.each do |f|
      if f.gadgets.nil?
        gadget_info = ""
      else
        gadget_info = "(Gadgets: #{f.gadgets.length})"
      end
      node = g.add_nodes( "#{f.name} at 0x#{f.start_addr.to_s(16)} #{gadget_info}" )
      nodes[f] = node
    end

    # Add the edges between functions.
    edges_added = []
    functions.each do |f|
      f.calls.each do |called|
        edge = [nodes[f], nodes[called]]
        next if edges_added.include? edge
        g.add_edges( nodes[f], nodes[called], "color" => "black" )
        edges_added << edge
      end
      f.maybe_calls.each do |called|
        edge = [nodes[f], nodes[called]]
        next if edges_added.include? edge
        g.add_edges( nodes[f], nodes[called], "color" => "gray" )
        edges_added << edge
      end
    end
    
    begin
      g.output( type => output_path )
    rescue RuntimeError => e
      if e.message.include? "too large for cairo-renderer"
        Print::error "The graph was too big so it has been scaled down."
      else
        raise e
      end
    end
  end

end
