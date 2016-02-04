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
		
		GraphType _graph;
		AttributeAdder<VertexType, EdgeType> _attribute_adder;
		
		
	public:
		Graph(){};
		
		
		virtual ~Graph(){}
		
		int getNumVertices() const {return boost::num_vertices(_graph);}
		GraphType& getGraph(){return _graph;}
		const GraphType& getGraph() const{return _graph;}
		int getNumEdges() const {return boost::num_edges(_graph);}
		/* Return the number of edge linked to v */
		int getNumEdges(const Vertex& v) const {return boost::out_degree(v, _graph);}
		/** @brief Add edge between lopp index and index */
		bool addEdge(const Vertex& loop_index, const Vertex& index, Edge& out, const EdgeType& edgeAttribute);
		bool addEdge(const Vertex& loop_index, const Vertex& index, Edge& out);

		void addVertex(Vertex& vertex_out, const Vertex& dad, const VertexType& nodeAttribute);
		void addVertex(Vertex& vertex_out, const VertexType& nodeAttribute);

		void removeVertex(Vertex& v){
			boost::clear_vertex(v, _graph);
			boost::remove_vertex(v, _graph);
			
		}
		void removeEdge(Edge& e){
			boost::remove_edge(e, _graph);
		}
			
		/**
		 * @brief Get all the vertex linked to one vertex
		 */
		void getAllVertexLinked(const Vertex& v, std::deque< Vertex >& all_vertex) const;
		/**
		 * @brief Get all the edge and associated vertex out of a vertex
		 */
		void getAllEdgeLinked(const Vertex& v, std::deque< std::pair< Edge, Vertex > >& all_edge) const;
			
		/**
		* @brief return the vertex targeted by edge */
		void getTarget(const Edge& edge, Vertex& out) const;
		/**
		 * @brief get element of Vertex v in graph*/
		VertexType& operator[](const Vertex& v);
		const VertexType& operator[] (const Vertex& v) const;
		EdgeType& operator[](const Edge& v);
		const EdgeType& operator[] (const Edge& v) const;
		
		/**
		 * @brief erase graph*/
		void clear(){_graph.clear();}
		
		///@brief write graph to a file
		void write(std::ostream& out);
		///@brief read graph from a file
		void read(std::ifstream& in);
		
		/**
		 * @brief Reading an adjancy matrix
		 * @param[in] matrix : adjancy matrix
		 * @param[in] x_size : size of matrix
		 * */
		void read(char* matrix[], size_t x_size);
		
	private:
		void write(std::ostream& out, int index, const VertexType& vertex){
			out << index <<" " << vertex << std::endl;
		};
		
			
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
		
		bool exist = boost::edge(loop_index, index, _graph).second;
		if(exist == true){
			out = boost::edge(loop_index, index, _graph).first;
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
	
	template<typename VertexType, typename EdgeType>
	inline void Graph<VertexType, EdgeType>::write(std::ostream& out){
		std::pair<VertexIterator, VertexIterator> vp;
		std::vector<Vertex> vec;
		//vertices access all the vertix
		//Classify them in order
		int i = 0;
		out << getNumVertices() << std::endl;
		for (vp = boost::vertices(_graph); vp.first != vp.second; ++vp.first) {
			Vertex v = *vp.first;
			vec.push_back(v);
			write(out, i, _graph[v]);
			++i;
		}
		
		for(size_t i = 0 ; i < vec.size() ; ++i){
			out << getNumVertices() << std::endl;
			for(size_t j = 0 ; j < vec.size() ; ++j){
				
				bool exist = boost::edge(vec[i], vec[j], _graph).second;
				if(exist == true){
					out << i << " " << j << " " << _graph[boost::edge(vec[i], vec[j], _graph).first] << std::endl;
				}
			}
		}
		
	}
	
	template<typename VertexType, typename EdgeType>
	inline void Graph<VertexType, EdgeType>::read(std::ifstream& in){
		clear();
		std::vector<Vertex> vec;
		std::vector<VertexType> vectyp;
		int garbage;
		
		size_t num_vertex = 0;
		in >> num_vertex;
		for(size_t i = 0 ; i < num_vertex ; ++i){
			Vertex v;
			vec.push_back(v);
			
			in >> garbage;
			VertexType vt;
			in >> vt;
			vectyp.push_back(vt);
		}
		
		for(size_t i = 0 ; i < vec.size() ; ++i){
			addVertex(vec[i], vectyp[i]);
		}
		
		while(!in.eof()){
			int index;
			int index2;
			in >> index;
			if(index == num_vertex){
				in >> index;
			}
			in >> index2;
			
			EdgeType et;
			in >> et;
			Edge e;
			addEdge(vec[index], vec[index2], e);
		}

		
	}
	
	template<typename VertexType, typename EdgeType>
	inline void Graph<VertexType, EdgeType>::read(char* matrix[], size_t x_size){
		std::vector<Vertex> vec;
		
		for(size_t i = 0 ; i < x_size ; ++i){
			Vertex v;
			VertexType vt;
			addVertex(v, vt);
			vec.push_back(v);
		}
		
		for(size_t i = 0 ; i < x_size ; ++i){
			for(size_t j = 0 ; j < x_size ; ++j){
				if(matrix[i][j] == 1){
					Edge o;
					addEdge(vec[i], vec[j], o);
				}
				
			}
		}
		
	}

}
#endif
