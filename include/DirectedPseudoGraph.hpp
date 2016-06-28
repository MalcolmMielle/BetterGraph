#ifndef BETTERGRAPH_DIRECTEDGRAPHGRAPH_280616
#define BETTERGRAPH_DIRECTEDGRAPHGRAPH_280616

#include <iostream>
#include <stdio.h>
#include <fstream>
#include "BetterGraphInterface.hpp"

namespace bettergraph{

	template < typename VertexType, typename EdgeType>
	class DirectedPseudoGraph : public BetterGraphInterface<boost::listS, 
			boost::listS, 
			boost::directedS, 
			VertexType,
			EdgeType, 
			boost::no_property>{
				
	public :
		
		typedef typename bettergraph::BetterGraphInterface<boost::listS, boost::listS, boost::directedS, VertexType, EdgeType, boost::no_property>::GraphType GraphType;
		
		typedef typename boost::graph_traits<GraphType>::vertex_iterator 
VertexIterator;
		typedef typename boost::graph_traits<GraphType>::vertex_descriptor 
Vertex;
		typedef typename boost::graph_traits<GraphType>::edge_descriptor Edge;
		typedef typename boost::graph_traits<GraphType>::out_edge_iterator 
EdgeIterator;		
		
	public:
		DirectedPseudoGraph(){};
		virtual ~DirectedPseudoGraph(){}	
			
	};


}

#endif
