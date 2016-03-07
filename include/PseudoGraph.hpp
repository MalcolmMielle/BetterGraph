#ifndef BETTERGRAPH_GRAPHGRAPH
#define BETTERGRAPH_GRAPHGRAPH

#include <iostream>
#include <stdio.h>
#include <fstream>
#include "boost/graph/adjacency_list.hpp"

namespace bettergraph{


	
	
	template < typename VertexType, typename EdgeType>
	class PseudoGraph{
	public :
		
		typedef boost::adjacency_list<
			boost::listS, boost::listS, boost::undirectedS, 
			VertexType,
			EdgeType, 
			boost::no_property > GraphType;
		typedef typename boost::graph_traits<GraphType>::vertex_iterator VertexIterator;
		typedef typename boost::graph_traits<GraphType>::vertex_descriptor Vertex;
		typedef typename boost::graph_traits<GraphType>::edge_descriptor Edge;
		typedef typename boost::graph_traits<GraphType>::out_edge_iterator EdgeIterator;
		
	protected:
		
		GraphType _graph;
		
		
	public:
		PseudoGraph(){};
		
		
		virtual ~PseudoGraph(){}
		
		int getNumVertices() const {return boost::num_vertices(_graph);}
		GraphType& getGraph(){return _graph;}
		const GraphType& getGraph() const{return _graph;}
		int getNumEdges() const {return boost::num_edges(_graph);}
		/* Return the number of edge linked to v */
		int getNumEdges(const Vertex& v) const {return boost::out_degree(v, _graph);}
		
		/** @brief Add edge with an edge attribute between lopp index and index */
		bool addEdge(Edge& out, const Vertex& loop_index, const Vertex& index, const EdgeType& edgeAttribute);
		/** @brief Add edge with default attribute between lopp index and index or no attribute if the attribute is a pointer*/
		bool addEdge(Edge& out, const Vertex& loop_index, const Vertex& index);

		///@brief Add vertex linked to the vertex dad to the graph
		void addVertex(Vertex& vertex_out, const Vertex& dad, const VertexType& nodeAttribute);
		///@brief Add vertex linked to the vertex dad to the graph + the edge attribute
		void addVertex(Vertex& vertex_out, const Vertex& dad, const VertexType& nodeAttribute, const EdgeType& edgeAttribute);
		///@brief Add vertex with a node attribute
		void addVertex(Vertex& vertex_out, const VertexType& nodeAttribute);
		///@brief Add vertex with default vertex attribute or no attribute if the node is a pointer
		void addVertex(Vertex& vertex_out);

		void removeVertex(Vertex& v){
			boost::clear_vertex(v, _graph);
			boost::remove_vertex(v, _graph);
			
		}
		void removeEdge(Edge& e){
			boost::remove_edge(e, _graph);
		}
		
		/**
		* @brief Get edge between v1 and v2
		*/
		bool getEdge(const Vertex& v1, const Vertex& v2, Edge& edge_out);
			
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
		void getTarget(const Edge& edge, Vertex& out) const;/**
		* @brief return the vertex source of edge */
		void getSource(const Edge& edge, Vertex& out) const;
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
		void read(char* matrix[], const size_t x_size);
		
	private:
		void write(std::ostream& out, int index, const VertexType& vertex){
			out << index <<" " << vertex << std::endl;
		};
		
			
	};
	
	/*****************************************************************
	* 							ADD VERTEX
	* ***************************************************************/
	
	template<typename VertexType, typename EdgeType>
	inline void PseudoGraph<VertexType, EdgeType>::addVertex(Vertex& vertex_out)
	{
		vertex_out = boost::add_vertex(_graph);
	}
	
	template<typename VertexType, typename EdgeType>
	inline void PseudoGraph<VertexType, EdgeType>::addVertex(Vertex& vertex_out, const VertexType& nodeAttribute)
	{
		vertex_out = boost::add_vertex(_graph);
// 		_attribute_adder.add(_graph, vertex_out, nodeAttribute);
		_graph[vertex_out] = nodeAttribute;
	}

	template<typename VertexType, typename EdgeType>
	inline void PseudoGraph<VertexType, EdgeType>::addVertex(Vertex& vertex_out, const Vertex& dad, const VertexType& nodeAttribute)
	{
		addVertex(vertex_out, nodeAttribute);
		Edge out;
		addEdge(out, vertex_out, dad);
	}
	
	template<typename VertexType, typename EdgeType>
	inline void PseudoGraph<VertexType, EdgeType>::addVertex(Vertex& vertex_out, const Vertex& dad, const VertexType& nodeAttribute, const EdgeType& edgeAttribute)
	{
		addVertex(vertex_out, nodeAttribute);
		Edge out;
		addEdge(out, vertex_out, dad, edgeAttribute);
	}
	
	/*****************************************************************
	* 							ADD EDGE
	* ***************************************************************/
	
	template<typename VertexType, typename EdgeType>
	inline bool PseudoGraph<VertexType, EdgeType>::addEdge(Edge& out, const Vertex& loop_index, const Vertex& index, const EdgeType& edgeAttribute)
	{
		bool res = addEdge(out, loop_index, index);
		_graph[out] = edgeAttribute;
		return res;
	}
	
	template<typename VertexType, typename EdgeType>
	inline bool PseudoGraph<VertexType, EdgeType>::addEdge(Edge& out, const Vertex& loop_index, const Vertex& index)
	{
		out = boost::add_edge(loop_index, index , _graph).first;
		return true;
		
	}
	
	/*****************************************************************
	* 							OTHER
	* ***************************************************************/
	
	template<typename VertexType, typename EdgeType>
	inline bool PseudoGraph<VertexType, EdgeType>::getEdge(const Vertex& v1, const Vertex& v2, Edge& edge_out){
		edge_out = boost::edge(v1, v2, _graph).first;
		return boost::edge(v1, v2, _graph).second;
	}
		
	template<typename VertexType, typename EdgeType>
	inline void PseudoGraph<VertexType, EdgeType>::getAllVertexLinked(const Vertex& v, std::deque< Vertex >& all_vertex) const
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
	inline void PseudoGraph<VertexType, EdgeType>::getAllEdgeLinked(const Vertex& v, std::deque< std::pair< Edge, Vertex > >& all_edge) const
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
	inline void PseudoGraph<VertexType, EdgeType>::getTarget(const Edge& edge, Vertex& out) const
	{
		out = boost::target(edge, _graph);
	}
	
	template<typename VertexType, typename EdgeType>
	inline void PseudoGraph<VertexType, EdgeType>::getSource(const Edge& edge, Vertex& out) const
	{
		out = boost::source(edge, _graph);
	}


	template<typename VertexType, typename EdgeType>
	inline VertexType& PseudoGraph<VertexType, EdgeType>::operator[](const Vertex& v)
	{
		return _graph[v];
	}
	
	template<typename VertexType, typename EdgeType>
	inline const VertexType& PseudoGraph<VertexType, EdgeType>::operator[](const Vertex& v) const
	{
		return _graph[v];
	}
	
	template<typename VertexType, typename EdgeType>
	inline EdgeType& PseudoGraph<VertexType, EdgeType>::operator[](const Edge& v)
	{
		return _graph[v];
	}
	
	template<typename VertexType, typename EdgeType>
	inline const EdgeType& PseudoGraph<VertexType, EdgeType>::operator[](const Edge& v) const
	{
		return _graph[v];
	}
	
	template<typename VertexType, typename EdgeType>
	inline void PseudoGraph<VertexType, EdgeType>::write(std::ostream& out){
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
			out << getNumEdges(vec[i]) << std::endl;
			for(size_t j = 0 ; j < vec.size() ; ++j){
				
				bool exist = boost::edge(vec[i], vec[j], _graph).second;
				if(exist == true){
					out << i << " " << j << " " << _graph[boost::edge(vec[i], vec[j], _graph).first] << std::endl;
				}
			}
		}
		
	}
	
	template<typename VertexType, typename EdgeType>
	inline void PseudoGraph<VertexType, EdgeType>::read(std::ifstream& in){
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
			int count_edge = 0 ;
			in >> count_edge;
			for(int p = 0 ; p < count_edge ; ++p){
				int index;
				int index2;
				in >> index;
				in >> index2;
				EdgeType et;
				in >> et;
				Edge e;
				addEdge(e, vec[index], vec[index2]);
			}
		}

		
	}
	
	template<typename VertexType, typename EdgeType>
	inline void PseudoGraph<VertexType, EdgeType>::read(char* matrix[], const size_t x_size){
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
					addEdge(o, vec[i], vec[j]);
				}
				
			}
		}
		
	}

}

#endif
