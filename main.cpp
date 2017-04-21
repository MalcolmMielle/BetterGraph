#include <iostream>

#include "PseudoGraph.hpp"
#include "HypotheseComparable.hpp"
#include "MatchComparable.hpp"
#include "conversion.hpp"



class Node{
public:
	int i;
	std::string str;
	Node() : i(0), str("yo"){}
	Node(int ii) : i(ii), str("person"){}
	
};

std::istream& operator>>(std::istream& in, Node &p){
	
	in >> p.i ; in >> p.str; return in;
}

std::ostream& operator<<(std::ostream& in, const Node &p){
	
	return in << p.i << " " <<p.str;
}


std::istream& operator>>(std::istream& in, Node* p){
	
	in >> (*p).i ; in >> (*p).str; return in;
}

std::ostream& operator<<(std::ostream& in, const Node* p){
	
	std::cout << "Printing pointer" << std::endl;
	return in << (*p).i << " " <<(*p).str;
}


class EdgeAttr{
public:
	double bob;
	EdgeAttr() : bob(77.54){};
	EdgeAttr(const double i) : bob(i){};
};

std::istream& operator>>(std::istream& in, EdgeAttr &p){
	
	return in >> p.bob;
}

std::ostream& operator<<(std::ostream& in, const EdgeAttr &p){
	
	return in << p.bob ;
}


std::istream& operator>>(std::istream& in, EdgeAttr* p){
	
	return in >> p->bob;
}

std::ostream& operator<<(std::ostream& in, const EdgeAttr* p){
	std::cout << "Printing pointer edge" << std::endl;
	return in << p->bob ;
}


// namespace bettergraph{
// 	template<>
// 	class AttributeAdder<Node, Edge>{
// 	protected : 
// 		typedef boost::adjacency_list<
// 			boost::listS, boost::listS, boost::undirectedS, 
// 			Node,
// 			Edge, 
// 			boost::no_property > GraphType;
// 		typedef typename boost::graph_traits<GraphType>::vertex_iterator VertexIterator;
// 		typedef typename boost::graph_traits<GraphType>::vertex_descriptor Vertex;
// 		typedef typename boost::graph_traits<GraphType>::edge_descriptor Edge_type;
// 		typedef typename boost::graph_traits<GraphType>::out_edge_iterator EdgeIterator;
// 		
// 	public :
// 		AttributeAdder(){};
// 		virtual void add(GraphType& arg1, Vertex& vertex, const Node& vertexAttribute){
// 			arg1[vertex].i = vertexAttribute.i;
// 			arg1[vertex].str = vertexAttribute.str;
// 		};
// 		virtual void add(GraphType& arg1, Edge_type& edge, const Edge& edgeAttribute){
// 			arg1[edge].bob = edgeAttribute.bob;
// 		};
// 		
// 	};
// }

int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;
    
	bettergraph::PseudoGraph<Node, EdgeAttr> graph;
	
	typedef boost::adjacency_list<
		boost::listS, boost::listS, boost::undirectedS, 
		Node,
		EdgeAttr, 
		boost::no_property > GraphType;
// 	typedef typename boost::graph_traits<GraphType>::vertex_iterator VertexIterator;
	typedef typename boost::graph_traits<GraphType>::vertex_descriptor Vertex;
	typedef typename boost::graph_traits<GraphType>::edge_descriptor Edge;
// 	typedef typename boost::graph_traits<GraphType>::out_edge_iterator EdgeIterator;
	
	Vertex dad;
	Vertex son;
	EdgeAttr edd(55);
	graph.addVertex(dad, Node());
	graph.addVertex(son, dad, Node(1), edd);
	Edge eddgee;
	graph.getEdge(dad, son, eddgee);
	std::cout << "Edge value " << graph[eddgee] << std::endl;
	graph.addVertex(son, dad, Node(2));
	
	std::cout << "3 Node : " << graph.getNumVertices() << std::endl;
	if(graph.getNumVertices() != 3){
		std::cout << "Not the good number of vertices" << std::endl;
	}
	std::cout << "2 Edges : " << graph.getNumEdges() << std::endl;
	if(graph.getNumEdges() != 2){
		std::cout << "Not the good number of edges" << std::endl;
	}
	
	std::ofstream out("bob.txt");
	graph.write(out);
	
	graph.clear();
	
	std::cout << "0 Node : " << graph.getNumVertices() << std::endl;
	std::cout << "0 Edges : " << graph.getNumEdges() << std::endl;
	if(graph.getNumVertices() != 0){
		std::cout << "Not the good number of vertices" << std::endl;
	}
	if(graph.getNumEdges() != 0){
		std::cout << "Not the good number of edges" << std::endl;
	}
	
	std::ifstream in("bob.txt");
	graph.read(in);
	
	std::cout << "3 Node : " << graph.getNumVertices() << std::endl;
	std::cout << "2 Edges : " << graph.getNumEdges() << std::endl;
	if(graph.getNumVertices() != 3){
		std::cout << "Not the good number of vertices" << std::endl;
	}
	std::cout << "2 Edges : " << graph.getNumEdges() << std::endl;
	if(graph.getNumEdges() != 2){
		std::cout << "Not the good number of edges" << std::endl;
	}
	
	std::ofstream outt("bob2.txt");
	graph.write(outt);
	
	graph.clear();
	
	char** matrix;
	matrix = (char**)malloc(sizeof(char*) * 3);
	for(int y = 0 ; y < 3 ;y++){
		//malloc the 'x' dimension
		matrix[y] = (char*)malloc(sizeof(char) * 3);
		//iterate over the 'x' dimension
		for( int x = 0 ; x < 3 ; x++){
			//malloc the string in the data structure
			matrix[y][x] = 0;

		}
	}
	matrix[0][1] = 1;
	matrix[0][2] = 1;
	matrix[1][0] = 1;
	matrix[2][0] = 1;
	
	graph.read(matrix, 3);
	
	std::cout << "3 Node : " << graph.getNumVertices() << std::endl;
	std::cout << "2 Edges : " << graph.getNumEdges() << std::endl;
	if(graph.getNumVertices() != 3){
		std::cout << "Not the good number of vertices" << std::endl;
	}
	std::cout << "4 Edges : " << graph.getNumEdges() << std::endl;
	if(graph.getNumEdges() != 4){
		std::cout << "Not the good number of edges" << std::endl;
	}
	
	for(int y = 0 ; y < 3 ;y++){
		//malloc the 'x' dimension
		free(matrix[y]);
		//iterate over the 'x' dimension
		
	}
	free(matrix);
	
	
	bettergraph::HypotheseComparable<int> hyp;
	
	hyp.push_back(1);
	hyp.push_back(2);
	
	std::cout << "Size of hypothese shoudl be 2 : " << hyp.size() << std::endl;
	std::cout << "Value of hypothese should be 1 : " << hyp[0] << std::endl;
	
	std::cout << hyp << std::endl;
	
	bettergraph::MatchComparable<float> match(1, 5);
	match.setFirst(1.50);
	match.setSecond(1.880);
	
	bettergraph::MatchComparable<float> match2(1, 5);
	match2.setFirst(1.50);
	match2.setSecond(1.880);
	
	
	std::cout << match << std::endl;
	
	if(match == match2){
		std::cout << "GREAT" << std::endl;
	}
	else{
		std::cout << "TEST FAIL" <<std::endl;
	}
	
	/*** Trying pointers***/
	
	bettergraph::PseudoGraph<Node*, EdgeAttr*> graphP;
	
	typedef boost::adjacency_list<
		boost::listS, boost::listS, boost::undirectedS, 
		Node*,
		EdgeAttr*, 
		boost::no_property > GraphTypeP;
// 	typedef typename boost::graph_traits<GraphTypeP>::vertex_iterator VertexIteratorP;
	typedef typename boost::graph_traits<GraphTypeP>::vertex_descriptor VertexP;
// 	typedef typename boost::graph_traits<GraphTypeP>::edge_descriptor EdgeP;
// 	typedef typename boost::graph_traits<GraphTypeP>::out_edge_iterator EdgeIteratorP;
	
// 	bettergraph::VertexPseudo<Node, EdgeAttr> dadp;
	bettergraph::PseudoGraph<Node, EdgeAttr>::Vertex dadp;
	VertexP sonp;
	Node* n = new Node();
	Node* n1 = new Node(3);
	Node* n3 = new Node(5);
	graphP.addVertex(dadp, n);
	EdgeAttr* ed = new EdgeAttr();
	graphP.addVertex(sonp, dadp, n1, ed);
	graphP.addVertex(sonp, dadp, n3);
	
	std::ofstream outtt("bob3.txt");
	graphP.write(outtt);
	
	std::pair<bettergraph::PseudoGraph<Node, EdgeAttr>::VertexIterator, bettergraph::PseudoGraph<Node, EdgeAttr>::VertexIterator> vp;
	std::vector<bettergraph::PseudoGraph<Node, EdgeAttr>::Vertex> vec;
	//vertices access all the vertix
	//Classify them in order
	for (vp = boost::vertices(graphP); vp.first != vp.second; ++vp.first) {
		bettergraph::PseudoGraph<Node, EdgeAttr>::Vertex v = *vp.first;
		std::cout << graphP[v] << std::endl;
	}
	
	bettergraph::SimpleGraph<Node*, EdgeAttr*> graphS;
	bettergraph::toSimpleGraph<Node*, EdgeAttr*>(graphP, graphS);
	assert(graphP.getNumEdges() == graphS.getNumEdges());
	assert(graphP.getNumVertices() == graphS.getNumVertices());
	
    
    return 0;
	
}
