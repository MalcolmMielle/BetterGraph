#include <iostream>

#include "Graph.hpp"

class Node{
public:
	int i;
	std::string str;
	Node() : i(0), str("yo"){}
	Node(int ii) : i(ii), str("meuf"){}
	
};

std::istream& operator>>(std::istream& in, Node &p){
	
	in >> p.i ; in >> p.str; std::cout << "pi" << p.i << " str " << p.str <<std::endl; return in;
}

std::ostream& operator<<(std::ostream& in, const Node &p){
	
	return in << p.i << " " <<p.str;
}


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
			arg1[vertex_out].i = nodeAttribute.i;
			arg1[vertex_out].str = nodeAttribute.str;
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
	graph.addVertex(son, dad, Node(1));
	graph.addVertex(son, dad, Node(2));
	
	std::cout << "3 Node : " << graph.getNumVertices() << std::endl;
	std::cout << "2 Edges : " << graph.getNumEdges() << std::endl;
	
	std::ofstream out("bob.txt");
	graph.write(out);
	
	graph.clear();
	
	std::cout << "0 Node : " << graph.getNumVertices() << std::endl;
	std::cout << "0 Edges : " << graph.getNumEdges() << std::endl;
	
	std::ifstream in("bob.txt");
	graph.read(in);
	
	std::cout << "3 Node : " << graph.getNumVertices() << std::endl;
	std::cout << "2 Edges : " << graph.getNumEdges() << std::endl;
	
	std::ofstream outt("bob2.txt");
	graph.write(outt);
	
	
	return 0;
	
}
