#include <iostream>

#include "Graph.hpp"

class Node{
	
};

class Edge{
	
};

namespace betterGraph{
	template<>
	class AttributeAdder<Node, Edge>{
	protected : 
		typedef boost::adjacency_list<
			boost::listS, boost::listS, boost::undirectedS, 
			Node,
			Edge, 
			boost::no_property > GraphType;
		typedef typename boost::graph_traits<GraphType>::vertex_iterator VertexIterator;
		typedef typename boost::graph_traits<GraphType>::vertex_descriptor Vertex;
		typedef typename boost::graph_traits<GraphType>::edge_descriptor Edge_type;
		typedef typename boost::graph_traits<GraphType>::out_edge_iterator EdgeIterator;
		
	public :
		AttributeAdder(){};
		virtual void add(GraphType& arg1, Vertex& vertex_out, const Node& nodeAttribute){
			std::cout << "BOUWA Node" << std::endl;
		};
		virtual void add(GraphType& arg1, Edge_type& out, const Edge& nodeAttribute){
			std::cout << "BOUWA Edge" << std::endl;
		};
		
	};
}

int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;
    
	betterGraph::Graph<Node, Edge> graph;
	
	typedef boost::adjacency_list<
		boost::listS, boost::listS, boost::undirectedS, 
		Node,
		Edge, 
		boost::no_property > GraphType;
	typedef typename boost::graph_traits<GraphType>::vertex_iterator VertexIterator;
	typedef typename boost::graph_traits<GraphType>::vertex_descriptor Vertex;
	typedef typename boost::graph_traits<GraphType>::edge_descriptor Edge;
	typedef typename boost::graph_traits<GraphType>::out_edge_iterator EdgeIterator;
	
	Vertex dad;
	Vertex son;
	graph.addVertex(dad, Node());
	graph.addVertex(son, dad, Node());
	graph.addVertex(son, dad, Node());
	
	std::cout << "3 Node : " << graph.getNumVertices() << std::endl;
	std::cout << "2 Edges : " << graph.getNumEdges() << std::endl;
	graph.clear();
	
	std::cout << "0 Node : " << graph.getNumVertices() << std::endl;
	std::cout << "0 Edges : " << graph.getNumEdges() << std::endl;
	
	
	return 0;
	
}
