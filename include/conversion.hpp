#ifndef BETTERGRAPH_CONVERSION_20042017
#define BETTERGRAPH_CONVERSION_20042017

#include <iostream>
#include <stdio.h>
#include <fstream>
#include "SimpleGraph.hpp"
#include "PseudoGraph.hpp"

namespace bettergraph{
	
	template < typename VertexType, typename EdgeType>
	inline void toSimpleGraph(const PseudoGraph<VertexType, EdgeType>& input, SimpleGraph<VertexType, EdgeType>& output){
		
		output.clear();
		std::pair< typename PseudoGraph<VertexType, EdgeType>::VertexIterator, typename PseudoGraph<VertexType, EdgeType>::VertexIterator > vp;
		std::deque< typename SimpleGraph<VertexType, EdgeType>::Vertex> vec_deque;
		std::deque< typename PseudoGraph<VertexType, EdgeType>::Vertex> vec_deque_input;
				
		//Add all vertex
		for (vp = boost::vertices(input); vp.first != vp.second; ++vp.first) {
	// 		bettergraph::PseudoGraph<AASS::vodigrex::SimpleNode, AASS::vodigrex::SimpleEdge>::Vertex v = *vp.first;
			typename PseudoGraph<VertexType, EdgeType>::Vertex v = *vp.first;
			
			typename SimpleGraph<VertexType, EdgeType>::Vertex vertex_out;
			output.addVertex(vertex_out, input[v]);
			
			vec_deque.push_back(vertex_out);
			vec_deque_input.push_back(v);

		}
		
		//Simply add all edges
		for (vp = boost::vertices(input); vp.first != vp.second; ++vp.first) {
			typename PseudoGraph<VertexType, EdgeType>::Vertex v = *vp.first;
			typename PseudoGraph<VertexType, EdgeType>::EdgeIterator out_i, out_end;
			typename PseudoGraph<VertexType, EdgeType>::Edge e;
			
			typename SimpleGraph<VertexType, EdgeType>::Vertex output_src;
			for(int i = 0 ; i < vec_deque.size() ; ++i){
				if(vec_deque_input[i] == v){
					output_src = vec_deque[i];
				}
			}
			
			for (boost::tie(out_i, out_end) = boost::out_edges(v, (input)); 
				out_i != out_end; ++out_i) {
				e = *out_i;
				typename PseudoGraph<VertexType, EdgeType>::Vertex targ = boost::target(e, input);
// 				typename PseudoGraph<VertexType, EdgeType>::Vertex src = boost::source(e, input);
				typename SimpleGraph<VertexType, EdgeType>::Vertex output_targ;
				for(int i = 0 ; i < vec_deque.size() ; ++i){
					if(vec_deque_input[i] == targ){
						output_targ = vec_deque[i];
					}
					
				}
			
				try{
					typename SimpleGraph<VertexType, EdgeType>::Edge e_out_output;
					output.addEdge(e_out_output, output_src, output_targ, input[e]);
				}
				catch(std::exception& e){
					std::cout << e.what();
					std::cout << " -> Ignoring self loop" << std::endl;
				}
			
			}
		}

	}
	
}


#endif