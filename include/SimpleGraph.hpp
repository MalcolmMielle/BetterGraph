#ifndef SIMPLEGRAPH_GRAPHGRAPH
#define SIMPLEGRAPH_GRAPHGRAPH

#include "PseudoGraph.hpp"

namespace bettergraph{
	
	
	/**
	 * @brief A simple graph, also called a strict graph (Tutte 1998, p. 2), is an unweighted, undirected graph containing no graph loops or multiple edges (Gibbons 1985, p. 2; West 2000, p. 2; Bronshtein and Semendyayev 2004, p. 346). A simple graph may be either connected or disconnected.

	Unless stated otherwise, the unqualified term "graph" usually refers to a simple graph. A simple graph with multiple edges is sometimes called a multigraph (Skiena 1990, p. 89).
	*/
	template < typename VertexType, typename EdgeType>
	class SimpleGraph : public PseudoGraph<VertexType, EdgeType>{
	public:
		
		typedef boost::adjacency_list<
			boost::listS, boost::listS, boost::undirectedS, 
			VertexType,
			EdgeType, 
			boost::no_property > GraphType;
		typedef typename boost::graph_traits<GraphType>::vertex_iterator VertexIterator;
		typedef typename boost::graph_traits<GraphType>::vertex_descriptor Vertex;
		typedef typename boost::graph_traits<GraphType>::edge_descriptor Edge;
		typedef typename boost::graph_traits<GraphType>::out_edge_iterator EdgeIterator;		
		
	public:
		SimpleGraph(){};
		
		
		virtual ~SimpleGraph(){}
		
		/** @brief Add edge with an edge attribute between lopp index and index
		 * If the edge already exist, no Edge is created and we return the Edge that was already there. 
		 * The Edge type is changed
		 */
		bool addEdge(Edge& out, const Vertex& loop_index, const Vertex& index, const EdgeType& edgeAttribute);
		/** @brief Add edge with default attribute between lopp index and index or no attribute if the attribute is a pointer
		 * If the edge already exist, no Edge is created and we return the Edge that was already there. 
		 * The Edge type is changed
		 */
		bool addEdge(Edge& out, const Vertex& loop_index, const Vertex& index);


		
			
	};

	/*****************************************************************
	 * 							ADD EDGE
	 * ***************************************************************/
	
	/**@brief always modify the edge */
	template<typename VertexType, typename EdgeType>
	inline bool SimpleGraph<VertexType, EdgeType>::addEdge(Edge& out, const Vertex& loop_index, const Vertex& index, const EdgeType& edgeAttribute)
	{
		
		bool self_loop = addEdge(out, loop_index, index);
		//Add the attribute only if the edge is new and the node are not the same
		if(self_loop == false){
			(*this)[out] = edgeAttribute;
		}
		return self_loop;
		
	}
	
	template<typename VertexType, typename EdgeType>
	inline bool SimpleGraph<VertexType, EdgeType>::addEdge(Edge& out, const Vertex& loop_index, const Vertex& index)
	{
// 		std::cout << "SIMPLE GRAPH ADD" << std::endl;
		bool self_loop = false;
		bool exist = boost::edge(loop_index, index, (*this)).second;
		//No multiple edges from one node to the same node
		if(exist == true){
			out = boost::edge(loop_index, index, (*this)).first;
#ifdef VERBOSE
			std::cout << "Edge already existed, modifying the old edge" << std::endl;
#endif
		}
// 		No self loop
		else if(loop_index == index){
			self_loop = true;
			throw std::runtime_error("No self-loops are possible in Simple Graphs");
		}
		else{
			out = boost::add_edge(loop_index, index , (*this)).first;
		}
		return self_loop;
		
	}

}
#endif
