#ifndef BETTERGRAPH_GRAPHGRAPH
#define BETTERGRAPH_GRAPHGRAPH

#include <iostream>
#include <stdio.h>
#include <fstream>
#include "BetterGraphInterface.hpp"

namespace bettergraph{

	template < typename VertexType, typename EdgeType>
	class PseudoGraph : public BetterGraphInterface<boost::listS, 
			boost::listS, 
			boost::undirectedS, 
			VertexType,
			EdgeType, 
			boost::no_property>{
				
	public :
		
		typedef typename bettergraph::BetterGraphInterface<boost::listS, boost::listS, boost::undirectedS, VertexType, EdgeType, boost::no_property>::GraphType GraphType;
		
		typedef typename boost::graph_traits<GraphType>::vertex_iterator 
VertexIterator;
		typedef typename boost::graph_traits<GraphType>::vertex_descriptor 
Vertex;
		typedef typename boost::graph_traits<GraphType>::edge_descriptor Edge;
		typedef typename boost::graph_traits<GraphType>::out_edge_iterator 
EdgeIterator;
		
// 	protected:
// 		
// 		GraphType (*this);
		
		
	public:
		PseudoGraph(){};
		
		
		virtual ~PseudoGraph(){}
		
// 		int getNumVertices() const {return boost::num_vertices((*this));}
// 		//Kept for easy backward compatibility
// 		GraphType& getGraph(){return (*this);}
// 		const GraphType& getGraph() const{return (*this);}
// 		int getNumEdges() const {return boost::num_edges((*this));}
// 		/* Return the number of edge linked to v */
// 		int getNumEdges(const Vertex& v) const {return boost::out_degree(v, 
// (*this));}
// 		
// 		/** @brief Add edge with an edge attribute between lopp index and index 
// */
// 		virtual bool addEdge(Edge& out, const Vertex& loop_index, const Vertex& index, 
// const EdgeType& edgeAttribute);
// 		/** @brief Add edge with default attribute between lopp index and index 
// or no attribute if the attribute is a pointer*/
// 		virtual bool addEdge(Edge& out, const Vertex& loop_index, const Vertex& index);
// 
// 		///@brief Add vertex linked to the vertex dad to the graph
// 		virtual void addVertex(Vertex& vertex_out, const Vertex& dad, const VertexType& 
// nodeAttribute);
// 		///@brief Add vertex linked to the vertex dad to the graph + the edge attribute
// 		virtual void addVertex(Vertex& vertex_out, const Vertex& dad, const VertexType& 
// nodeAttribute, const EdgeType& edgeAttribute);
// 		///@brief Add vertex with a node attribute
// 		virtual void addVertex(Vertex& vertex_out, const VertexType& nodeAttribute);
// 		///@brief Add vertex with default vertex attribute or no attribute if the node is a pointer
// 		virtual void addVertex(Vertex& vertex_out);
// 
// 		virtual void removeVertex(Vertex& v){
// 			boost::clear_vertex(v, (*this));
// 			boost::remove_vertex(v, (*this));
// 			
// 		}
// 		virtual void removeEdge(Edge& e){
// 			boost::remove_edge(e, (*this));
// 		}
// 		
// 		/**
// 		* @brief Get edge between v1 and v2
// 		*/
// 		bool getEdge(const Vertex& v1, const Vertex& v2, Edge& edge_out);
// 			
// 		/**
// 		* @brief Get all the vertex linked to one vertex
// 		*/
// 		void getAllVertexLinked(const Vertex& v, std::deque< Vertex >& 
// all_vertex) const;
// 		/**
// 		* @brief Get all the edge and associated vertex out of a vertex
// 		*/
// 		void getAllEdgeLinked(const Vertex& v, std::deque< std::pair< Edge, 
// Vertex > >& all_edge) const;
// 			
// 		/**
// 		* @brief return the vertex targeted by edge */
// 		void getTarget(const Edge& edge, Vertex& out) const;/**
// 		* @brief return the vertex source of edge */
// 		void getSource(const Edge& edge, Vertex& out) const;
// 		
// 		///@brief write graph to a file
// 		void write(std::ostream& out);
// 		///@brief read graph from a file
// 		void read(std::ifstream& in);
// 		
// 		/**
// 		* @brief Reading an adjancy matrix
// 		* @param[in] matrix : adjancy matrix
// 		* @param[in] x_size : size of matrix
// 		* */
// 		void read(char* matrix[], const size_t x_size);
// 		
// 		/**
// 		 * Print the value of all nodes
// 		 * 
// 		 */
// 		void print() const ;
// 		
// 	private:
// 		void write(std::ostream& out, int index, const VertexType& vertex){
// 			out << index <<" " << vertex << std::endl;
// 		};
		
			
	};
	
	/*****************************************************************
	* 							ADD VERTEX
	* ***************************************************************/
	
// 	template<typename VertexType, typename EdgeType>
// 	inline void PseudoGraph<VertexType, EdgeType>::addVertex(Vertex& vertex_out)
// 	{
// 		vertex_out = boost::add_vertex((*this));
// 	}
// 	
// 	template<typename VertexType, typename EdgeType>
// 	inline void PseudoGraph<VertexType, EdgeType>::addVertex(Vertex& 
// vertex_out, const VertexType& nodeAttribute)
// 	{
// 		vertex_out = boost::add_vertex(nodeAttribute, (*this));
// // 		_attribute_adder.add((*this), vertex_out, nodeAttribute);
// // 		(*this)[vertex_out] = nodeAttribute;
// 	}
// 
// 	template<typename VertexType, typename EdgeType>
// 	inline void PseudoGraph<VertexType, EdgeType>::addVertex(Vertex& 
// vertex_out, const Vertex& dad, const VertexType& nodeAttribute)
// 	{
// 		addVertex(vertex_out, nodeAttribute);
// 		Edge out;
// 		addEdge(out, vertex_out, dad);
// 	}
// 	
// 	template<typename VertexType, typename EdgeType>
// 	inline void PseudoGraph<VertexType, EdgeType>::addVertex(Vertex& 
// vertex_out, const Vertex& dad, const VertexType& nodeAttribute, const EdgeType& 
// edgeAttribute)
// 	{
// 		addVertex(vertex_out, nodeAttribute);
// 		Edge out;
// 		addEdge(out, vertex_out, dad, edgeAttribute);
// 	}
// 	
	/*****************************************************************
	* 							ADD EDGE
	* ***************************************************************/
	
// 	template<typename VertexType, typename EdgeType>
// 	inline bool PseudoGraph<VertexType, EdgeType>::addEdge(Edge& out, const 
// Vertex& loop_index, const Vertex& index, const EdgeType& edgeAttribute)
// 	{
// 		out = boost::add_edge(loop_index, index , edgeAttribute, (*this)).first;
// // 		(*this)[out] = edgeAttribute;
// 		return true;
// 	}
// 	
// 	template<typename VertexType, typename EdgeType>
// 	inline bool PseudoGraph<VertexType, EdgeType>::addEdge(Edge& out, const 
// Vertex& loop_index, const Vertex& index)
// 	{
// // 		std::cout << "PSEUDO GRAPH ADD" << std::endl;
// 		out = boost::add_edge(loop_index, index , (*this)).first;
// 		return true;
// 		
// 	}
// 	
// 	/*****************************************************************
// 	* 							OTHER
// 	* ***************************************************************/
// 	
// 	template<typename VertexType, typename EdgeType>
// 	inline bool PseudoGraph<VertexType, EdgeType>::getEdge(const Vertex& v1, 
// const Vertex& v2, Edge& edge_out){
// 		edge_out = boost::edge(v1, v2, (*this)).first;
// 		return boost::edge(v1, v2, (*this)).second;
// 	}
// 		
// 	template<typename VertexType, typename EdgeType>
// 	inline void PseudoGraph<VertexType, EdgeType>::getAllVertexLinked(const 
// Vertex& v, std::deque< Vertex >& all_vertex) const
// 	{
// 		EdgeIterator out_i, out_end;
// 		Edge e;
// 		
// 		for (boost::tie(out_i, out_end) = boost::out_edges(v, (*this)); 
// 			out_i != out_end; ++out_i) {
// 			e = *out_i;
// 			Vertex targ = boost::target(e, (*this));
// 			all_vertex.push_back(targ);
// 		}
// 		
// 	}
// 		
// 	template<typename VertexType, typename EdgeType>
// 	inline void PseudoGraph<VertexType, EdgeType>::getAllEdgeLinked(const 
// Vertex& v, std::deque< std::pair< Edge, Vertex > >& all_edge) const
// 	{
// // 		std::cout << "GRAPH PLACE EDGE LINKED" << std::endl;
// 		EdgeIterator out_i, out_end;
// 		Edge e;
// 		
// 		for (boost::tie(out_i, out_end) = boost::out_edges(v, (*this)); 
// 			out_i != out_end; ++out_i) {
// 			e = *out_i;
// 			Vertex targ = boost::target(e, (*this));
// 			all_edge.push_back(std::pair<Edge, Vertex> (e, targ) );
// 		}
// 	}
// 
// 		
// 	template<typename VertexType, typename EdgeType>
// 	inline void PseudoGraph<VertexType, EdgeType>::getTarget(const Edge& edge, Vertex& out) const
// 	{
// 		out = boost::target(edge, (*this));
// 	}
// 	
// 	template<typename VertexType, typename EdgeType>
// 	inline void PseudoGraph<VertexType, EdgeType>::getSource(const Edge& edge, Vertex& out) const
// 	{
// 		out = boost::source(edge, (*this));
// 	}
// 	
// 	template<typename VertexType, typename EdgeType>
// 	inline void PseudoGraph<VertexType, EdgeType>::print() const
// 	{
// 		std::pair<VertexIterator, VertexIterator> vp;
// 		std::vector<Vertex> vec;
// 		//vertices access all the vertix
// 		//Classify them in order
// 		int i = 0;
// 		std::cout << getNumVertices() << std::endl;
// 		for (vp = boost::vertices((*this)); vp.first != vp.second; ++vp.first) {
// 			Vertex v = *vp.first;
// 			vec.push_back(v);
// 			std::cout << i <<" " << (*this)[v] << std::endl;
// 			++i;
// 		}
// 		
// 		for(size_t i = 0 ; i < vec.size() ; ++i){
// 			std::cout << getNumEdges(vec[i]) << std::endl;
// 			for(size_t j = 0 ; j < vec.size() ; ++j){
// 				
// 				bool exist = boost::edge(vec[i], vec[j], (*this)).second;
// 				if(exist == true){
// 					std::cout << i << " " << j << " " << (*this)[boost::edge(vec[i], 
// vec[j], (*this)).first] << std::endl;
// 				}
// 			}
// 		}
// 	}

	
// 	template<typename VertexType, typename EdgeType>
// 	inline void PseudoGraph<VertexType, EdgeType>::write(std::ostream& out){
// 		std::pair<VertexIterator, VertexIterator> vp;
// 		std::vector<Vertex> vec;
// 		//vertices access all the vertix
// 		//Classify them in order
// 		int i = 0;
// 		out << getNumVertices() << std::endl;
// 		for (vp = boost::vertices((*this)); vp.first != vp.second; ++vp.first) {
// 			Vertex v = *vp.first;
// 			vec.push_back(v);
// 			write(out, i, (*this)[v]);
// 			++i;
// 		}
// 		
// 		for(size_t i = 0 ; i < vec.size() ; ++i){
// 			out << getNumEdges(vec[i]) << std::endl;
// 			for(size_t j = 0 ; j < vec.size() ; ++j){
// 				
// 				bool exist = boost::edge(vec[i], vec[j], (*this)).second;
// 				if(exist == true){
// 					out << i << " " << j << " " << (*this)[boost::edge(vec[i], 
// vec[j], (*this)).first] << std::endl;
// 				}
// 			}
// 		}
// 		
// 	}
	
// 	template<typename VertexType, typename EdgeType>
// 	inline void PseudoGraph<VertexType, EdgeType>::read(std::ifstream& in){
// 		this->clear();
// 		std::vector<Vertex> vec;
// 		std::vector<VertexType> vectyp;
// 		int garbage;
// 		
// 		size_t num_vertex = 0;
// 		in >> num_vertex;
// 		for(size_t i = 0 ; i < num_vertex ; ++i){
// 			Vertex v;
// 			vec.push_back(v);
// 			
// 			in >> garbage;
// 			VertexType vt;
// 			in >> vt;
// 			vectyp.push_back(vt);
// 		}
// 		
// 		for(size_t i = 0 ; i < vec.size() ; ++i){
// 			addVertex(vec[i], vectyp[i]);
// 		}
// 		
// 		while(!in.eof()){
// 			int count_edge = 0 ;
// 			in >> count_edge;
// 			for(int p = 0 ; p < count_edge ; ++p){
// 				int index;
// 				int index2;
// 				in >> index;
// 				in >> index2;
// 				EdgeType et;
// 				in >> et;
// 				Edge e;
// 				addEdge(e, vec[index], vec[index2]);
// 			}
// 		}
// 
// 		
// 	}
	
// 	template<typename VertexType, typename EdgeType>
// 	inline void PseudoGraph<VertexType, EdgeType>::read(char* matrix[], const 
// size_t x_size){
// 		std::vector<Vertex> vec;
// 		
// 		for(size_t i = 0 ; i < x_size ; ++i){
// 			Vertex v;
// 			VertexType vt;
// 			addVertex(v, vt);
// 			vec.push_back(v);
// 		}
// 		
// 		for(size_t i = 0 ; i < x_size ; ++i){
// 			for(size_t j = 0 ; j < x_size ; ++j){
// 				if(matrix[i][j] == 1){
// 					Edge o;
// 					addEdge(o, vec[i], vec[j]);
// 				}
// 				
// 			}
// 		}
// 		
// 	}

}

#endif
