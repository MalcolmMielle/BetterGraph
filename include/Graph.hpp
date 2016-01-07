#ifndef BETTERGRAPH_GRAPHGRAPH
#define BETTERGRAPH_GRAPHGRAPH

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <assert.h>
#include <stdexcept>
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/topological_sort.hpp"
#include <boost/graph/copy.hpp>
#include <math.h>
	
#include "AttributeAdder.hpp"
		
namespace betterGraph{
	
	
	template < typename VertexType, typename EdgeType>
	class Graph{
	protected :
		
		typedef boost::adjacency_list<
			boost::listS, boost::listS, boost::undirectedS, 
			VertexType,
			EdgeType, 
			boost::no_property > GraphType;
		typedef typename boost::graph_traits<GraphType>::vertex_iterator VertexIterator;
		typedef typename boost::graph_traits<GraphType>::vertex_descriptor Vertex;
		typedef typename boost::graph_traits<GraphType>::edge_descriptor Edge;
		typedef typename boost::graph_traits<GraphType>::out_edge_iterator EdgeIterator;
		
		int _marge;
		GraphType _graph;
		AttributeAdder<VertexType, EdgeType> _attribute_adder;
		
		
	public:
		Graph() : _marge(5){};
		
		
		virtual ~Graph(){/*std::cout << "Removing grah place with " <<getNumVertices() << " nodes " << std::endl;*/}
		virtual int getNumVertices() const {return boost::num_vertices(_graph);}
		virtual GraphType& getGraph(){return _graph;}
		virtual int getMarge(){return _marge;}
		virtual const GraphType& getGraph() const{return _graph;}
		virtual int getMarge() const {return _marge;}
		virtual int getNumEdges() const {return boost::num_edges(_graph);}
		/* Return the number of edge linked to v */
		virtual int getNumEdges(const Vertex& v) const {return boost::out_degree(v, _graph);}
		/** @brief Add edge between lopp index and index */
		bool addEdge(const Vertex& loop_index, const Vertex& index, Edge& out, const EdgeType& edgeAttribute);
		bool addEdge(const Vertex& loop_index, const Vertex& index, Edge& out);

		virtual void addVertex(Vertex& vertex_out, const Vertex& dad, const VertexType& nodeAttribute);
		virtual void addVertex(Vertex& vertex_out, const VertexType& nodeAttribute);

		virtual void removeVertex(Vertex& v){
			boost::clear_vertex(v, _graph);
			boost::remove_vertex(v, _graph);
			
		}
		virtual void removeEdge(Edge& e){
			boost::remove_edge(e, _graph);
		}
			
		virtual void getAllVertexLinked(const Vertex& v, std::deque< Vertex >& all_vertex) const;
		virtual void getAllEdgeLinked(const Vertex& v, std::deque< std::pair< Edge, Vertex > >& all_edge) const;
			
		/**
		* @brief return the vertex targeted by edge */
		virtual void getTarget(const Edge& edge, Vertex& out) const;
		virtual VertexType& operator[](const Vertex& v);
		virtual const VertexType& operator[] (const Vertex& v) const;
		virtual EdgeType& operator[](const Edge& v);
		virtual const EdgeType& operator[] (const Edge& v) const;
		
		virtual void clear(){_graph.clear();}
			
	};

	template<typename VertexType, typename EdgeType>
	inline void Graph<VertexType, EdgeType>::addVertex(Vertex& vertex_out, const Vertex& dad, const VertexType& nodeAttribute)
	{
		addVertex(vertex_out, nodeAttribute);
		Edge out;
		addEdge(vertex_out, dad, out);
	}

	template<typename VertexType, typename EdgeType>
	inline void Graph<VertexType, EdgeType>::addVertex(Vertex& vertex_out, const VertexType& nodeAttribute)
	{
		vertex_out = boost::add_vertex(_graph);
		_attribute_adder.add(_graph, vertex_out, nodeAttribute);
	}
	
	template<typename VertexType, typename EdgeType>
	inline bool Graph<VertexType, EdgeType>::addEdge(const Vertex& loop_index, const Vertex& index, Edge& out, const EdgeType& edgeAttribute)
	{
		
		bool res = addEdge(loop_index, index, out);
		//Add the attribute only if the edge is new and the node are note the same
		if(res == true && loop_index != index){
			_attribute_adder.add(_graph, out, edgeAttribute);
		}
		return res;
		
	}
	
	template<typename VertexType, typename EdgeType>
	inline bool Graph<VertexType, EdgeType>::addEdge(const Vertex& loop_index, const Vertex& index, Edge& out)
	{
		
		bool exist = boost::edge(loop_index, index , _graph).second;
		if(exist == true){
			out = boost::edge(loop_index, index , _graph).first;
		}
		else if(loop_index == index){
			exist = true;
		}
		else{
			out = boost::add_edge(loop_index, index , _graph).first;
		}
		return exist;
		
	}

		
	template<typename VertexType, typename EdgeType>
	inline void Graph<VertexType, EdgeType>::getAllVertexLinked(const Vertex& v, std::deque< Vertex >& all_vertex) const
	{
		EdgeIterator out_i, out_end;
		Edge e;
		
		for (boost::tie(out_i, out_end) = boost::out_edges(v, _graph); 
			out_i != out_end; ++out_i) {
			e = *out_i;
			Vertex targ = boost::target(e, _graph);
			all_vertex.push_back(targ);
		}
		
	}
		
	template<typename VertexType, typename EdgeType>
	inline void Graph<VertexType, EdgeType>::getAllEdgeLinked(const Vertex& v, std::deque< std::pair< Edge, Vertex > >& all_edge) const
	{
// 		std::cout << "GRAPH PLACE EDGE LINKED" << std::endl;
		EdgeIterator out_i, out_end;
		Edge e;
		
		for (boost::tie(out_i, out_end) = boost::out_edges(v, _graph); 
			out_i != out_end; ++out_i) {
			e = *out_i;
			Vertex targ = boost::target(e, _graph);
			all_edge.push_back(std::pair<Edge, Vertex> (e, targ) );
		}
	}

		
	template<typename VertexType, typename EdgeType>
	inline void Graph<VertexType, EdgeType>::getTarget(const Edge& edge, Vertex& out) const
	{
		out = boost::target(edge, _graph);
	}


	template<typename VertexType, typename EdgeType>
	inline VertexType& Graph<VertexType, EdgeType>::operator[](const Vertex& v)
	{
		return _graph[v];
	}
	
	template<typename VertexType, typename EdgeType>
	inline const VertexType& Graph<VertexType, EdgeType>::operator[](const Vertex& v) const
	{
		return _graph[v];
	}
	
	template<typename VertexType, typename EdgeType>
	inline EdgeType& Graph<VertexType, EdgeType>::operator[](const Edge& v)
	{
		return _graph[v];
	}
	
	template<typename VertexType, typename EdgeType>
	inline const EdgeType& Graph<VertexType, EdgeType>::operator[](const Edge& v) const
	{
		return _graph[v];
	}

}
#endif
