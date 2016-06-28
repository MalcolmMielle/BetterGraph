#ifndef BETTERGRAPH_INTERFACE_280616
#define BETTERGRAPH_INTERFACE_280616

#include <iostream>
#include <stdio.h>
#include <fstream>
#include "boost/graph/adjacency_list.hpp"

namespace bettergraph{
	
	//FOrward declaration

	template <typename OutEdgeListS = boost::listS, // a Sequence or an AssociativeContainer
            typename VertexListS = boost::listS, // a Sequence or a RandomAccessContainer
            typename DirectedS = boost::directedS,
            typename VertexProperty = boost::no_property,
            typename EdgeProperty = boost::no_property,
            typename GraphProperty = boost::no_property,
            typename EdgeListS = boost::listS>
	class BetterGraphInterface : public boost::adjacency_list<
			OutEdgeListS, 
			VertexListS, 
			DirectedS, 
			VertexProperty,
			EdgeProperty,
			GraphProperty, 
			EdgeListS >{	
	public :
		typedef typename boost::adjacency_list<
			OutEdgeListS, 
			VertexListS, 
			DirectedS, 
			VertexProperty,
			EdgeProperty,
			GraphProperty, 
			EdgeListS > GraphType;
		typedef typename boost::graph_traits<GraphType>::vertex_iterator 
VertexIterator;
		typedef typename boost::graph_traits<GraphType>::vertex_descriptor 
Vertex;
		typedef typename boost::graph_traits<GraphType>::edge_descriptor Edge;
		typedef typename boost::graph_traits<GraphType>::out_edge_iterator 
EdgeIterator;
		
		
	public:
		
		BetterGraphInterface(){};
		virtual ~BetterGraphInterface(){}
		
		int getNumVertices() const {return boost::num_vertices((*this));}
		//Kept for easy backward compatibility
		GraphType& getGraph(){return (*this);}
		const GraphType& getGraph() const{return (*this);}
		int getNumEdges() const {return boost::num_edges((*this));}
		/* Return the number of edge linked to v */
		int getNumEdges(const Vertex& v) const {return boost::out_degree(v, 
(*this));}
		
		/** @brief Add edge with an edge attribute between lopp index and index 
*/
		virtual bool addEdge(Edge& out, const Vertex& origin, const Vertex& destination, 
const EdgeProperty& edgeAttribute);
		/** @brief Add edge with default attribute between lopp index and index 
or no attribute if the attribute is a pointer*/
		virtual bool addEdge(Edge& out, const Vertex& origin, const Vertex& destination);

		///@brief Add vertex linked to the vertex dad to the graph
		virtual void addVertex(Vertex& vertex_out, const Vertex& dad, const VertexProperty& 
nodeAttribute);
		///@brief Add vertex linked to the vertex dad to the graph + the edge attribute
		virtual void addVertex(Vertex& vertex_out, const Vertex& dad, const VertexProperty& 
nodeAttribute, const EdgeProperty& edgeAttribute);
		///@brief Add vertex with a node attribute
		virtual void addVertex(Vertex& vertex_out, const VertexProperty& nodeAttribute);
		///@brief Add vertex with default vertex attribute or no attribute if the node is a pointer
		virtual void addVertex(Vertex& vertex_out);

		virtual void removeVertex(Vertex& v){
			boost::clear_vertex(v, (*this));
			boost::remove_vertex(v, (*this));
			
		}
		virtual void removeEdge(Edge& e){
			boost::remove_edge(e, (*this));
		}
		
		/**
		* @brief Get edge between v1 and v2
		*/
		bool getEdge(const Vertex& origin, const Vertex& destination, Edge& edge_out);
			
		/**
		* @brief Get all the vertex linked to one vertex
		*/
		void getAllVertexLinked(const Vertex& v, std::deque< Vertex >& 
all_vertex) const;
		/**
		* @brief Get all the edge and associated vertex out of a vertex
		*/
		void getAllEdgeLinked(const Vertex& v, std::deque< std::pair< Edge, 
Vertex > >& all_edge) const;
			
		/**
		* @brief return the vertex targeted by edge */
		void getTarget(const Edge& edge, Vertex& out) const;/**
		* @brief return the vertex source of edge */
		void getSource(const Edge& edge, Vertex& out) const;
		
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
		
		/**
		 * Print the value of all nodes
		 * 
		 */
		void print() const ;
		
	private:
		void write(std::ostream& out, int index, const VertexProperty& vertex){
			out << index <<" " << vertex << std::endl;
		};
		
			
	};
	
	/*****************************************************************
	* 							ADD VERTEX
	* ***************************************************************/
	
	template <typename OutEdgeListS, // a Sequence or an AssociativeContainer
            typename VertexListS, // a Sequence or a RandomAccessContainer
            typename DirectedS,
            typename VertexProperty,
            typename EdgeProperty,
            typename GraphProperty,
            typename EdgeListS>
	inline void BetterGraphInterface<
			OutEdgeListS, 
			VertexListS, 
			DirectedS, 
			VertexProperty,
			EdgeProperty,
			GraphProperty, 
			EdgeListS >::addVertex(Vertex& vertex_out)
	{
		vertex_out = boost::add_vertex((*this));
	}
	
	template <typename OutEdgeListS, // a Sequence or an AssociativeContainer
            typename VertexListS, // a Sequence or a RandomAccessContainer
            typename DirectedS,
            typename VertexProperty,
            typename EdgeProperty,
            typename GraphProperty,
            typename EdgeListS>
	inline void BetterGraphInterface<
			OutEdgeListS, 
			VertexListS, 
			DirectedS, 
			VertexProperty,
			EdgeProperty,
			GraphProperty, 
			EdgeListS >::addVertex(Vertex& 
vertex_out, const VertexProperty& nodeAttribute)
	{
		vertex_out = boost::add_vertex(nodeAttribute, (*this));
// 		_attribute_adder.add((*this), vertex_out, nodeAttribute);
// 		(*this)[vertex_out] = nodeAttribute;
	}

	template <typename OutEdgeListS, // a Sequence or an AssociativeContainer
            typename VertexListS, // a Sequence or a RandomAccessContainer
            typename DirectedS,
            typename VertexProperty,
            typename EdgeProperty,
            typename GraphProperty,
            typename EdgeListS>
	inline void BetterGraphInterface<
			OutEdgeListS, 
			VertexListS, 
			DirectedS, 
			VertexProperty,
			EdgeProperty,
			GraphProperty, 
			EdgeListS >::addVertex(Vertex& 
vertex_out, const Vertex& dad, const VertexProperty& nodeAttribute)
	{
		addVertex(vertex_out, nodeAttribute);
		Edge out;
		addEdge(out, vertex_out, dad);
	}
	
	template <typename OutEdgeListS, // a Sequence or an AssociativeContainer
            typename VertexListS, // a Sequence or a RandomAccessContainer
            typename DirectedS,
            typename VertexProperty,
            typename EdgeProperty,
            typename GraphProperty,
            typename EdgeListS>
	inline void BetterGraphInterface<
			OutEdgeListS, 
			VertexListS, 
			DirectedS, 
			VertexProperty,
			EdgeProperty,
			GraphProperty, 
			EdgeListS >::addVertex(Vertex& 
vertex_out, const Vertex& dad, const VertexProperty& nodeAttribute, const EdgeProperty& 
edgeAttribute)
	{
		addVertex(vertex_out, nodeAttribute);
		Edge out;
		addEdge(out, vertex_out, dad, edgeAttribute);
	}
	
	/*****************************************************************
	* 							ADD EDGE
	* ***************************************************************/
	
	template <typename OutEdgeListS, // a Sequence or an AssociativeContainer
            typename VertexListS, // a Sequence or a RandomAccessContainer
            typename DirectedS,
            typename VertexProperty,
            typename EdgeProperty,
            typename GraphProperty,
            typename EdgeListS>
	inline bool BetterGraphInterface<
			OutEdgeListS, 
			VertexListS, 
			DirectedS, 
			VertexProperty,
			EdgeProperty,
			GraphProperty, 
			EdgeListS >::addEdge(Edge& out, const 
Vertex& origin, const Vertex& destination, const EdgeProperty& edgeAttribute)
	{
		out = boost::add_edge(origin, destination , edgeAttribute, (*this)).first;
// 		(*this)[out] = edgeAttribute;
		return true;
	}
	
	template <typename OutEdgeListS, // a Sequence or an AssociativeContainer
            typename VertexListS, // a Sequence or a RandomAccessContainer
            typename DirectedS,
            typename VertexProperty,
            typename EdgeProperty,
            typename GraphProperty,
            typename EdgeListS>
	inline bool BetterGraphInterface<
			OutEdgeListS, 
			VertexListS, 
			DirectedS, 
			VertexProperty,
			EdgeProperty,
			GraphProperty, 
			EdgeListS >::addEdge(Edge& out, const 
Vertex& origin, const Vertex& destination)
	{
// 		std::cout << "PSEUDO GRAPH ADD" << std::endl;
		out = boost::add_edge(origin, destination , (*this)).first;
		return true;
		
	}
	
	/*****************************************************************
	* 							OTHER
	* ***************************************************************/
	
	template <typename OutEdgeListS, // a Sequence or an AssociativeContainer
            typename VertexListS, // a Sequence or a RandomAccessContainer
            typename DirectedS,
            typename VertexProperty,
            typename EdgeProperty,
            typename GraphProperty,
            typename EdgeListS>
	inline bool BetterGraphInterface<
			OutEdgeListS, 
			VertexListS, 
			DirectedS, 
			VertexProperty,
			EdgeProperty,
			GraphProperty, 
			EdgeListS >::getEdge(const Vertex& origin, 
const Vertex& destination, Edge& edge_out){
		edge_out = boost::edge(origin, destination, (*this)).first;
		
		if(boost::edge(origin, destination, (*this)).second == false){
			throw std::runtime_error("Edge does not exist");
		}
		
		return boost::edge(origin, destination, (*this)).second;
	}
		
	template <typename OutEdgeListS, // a Sequence or an AssociativeContainer
            typename VertexListS, // a Sequence or a RandomAccessContainer
            typename DirectedS,
            typename VertexProperty,
            typename EdgeProperty,
            typename GraphProperty,
            typename EdgeListS>
	inline void BetterGraphInterface<
			OutEdgeListS, 
			VertexListS, 
			DirectedS, 
			VertexProperty,
			EdgeProperty,
			GraphProperty, 
			EdgeListS >::getAllVertexLinked(const 
Vertex& v, std::deque< Vertex >& all_vertex) const
	{
		EdgeIterator out_i, out_end;
		Edge e;
		
		for (boost::tie(out_i, out_end) = boost::out_edges(v, (*this)); 
			out_i != out_end; ++out_i) {
			e = *out_i;
			Vertex targ = boost::target(e, (*this));
			all_vertex.push_back(targ);
		}
		
	}
		
	template <typename OutEdgeListS, // a Sequence or an AssociativeContainer
            typename VertexListS, // a Sequence or a RandomAccessContainer
            typename DirectedS,
            typename VertexProperty,
            typename EdgeProperty,
            typename GraphProperty,
            typename EdgeListS>
	inline void BetterGraphInterface<
			OutEdgeListS, 
			VertexListS, 
			DirectedS, 
			VertexProperty,
			EdgeProperty,
			GraphProperty, 
			EdgeListS >::getAllEdgeLinked(const 
Vertex& v, std::deque< std::pair< Edge, Vertex > >& all_edge) const
	{
// 		std::cout << "GRAPH PLACE EDGE LINKED" << std::endl;
		EdgeIterator out_i, out_end;
		Edge e;
		
		for (boost::tie(out_i, out_end) = boost::out_edges(v, (*this)); 
			out_i != out_end; ++out_i) {
			e = *out_i;
			Vertex targ = boost::target(e, (*this));
			all_edge.push_back(std::pair<Edge, Vertex> (e, targ) );
		}
	}

		
	template <typename OutEdgeListS, // a Sequence or an AssociativeContainer
            typename VertexListS, // a Sequence or a RandomAccessContainer
            typename DirectedS,
            typename VertexProperty,
            typename EdgeProperty,
            typename GraphProperty,
            typename EdgeListS>
	inline void BetterGraphInterface<
			OutEdgeListS, 
			VertexListS, 
			DirectedS, 
			VertexProperty,
			EdgeProperty,
			GraphProperty, 
			EdgeListS >::getTarget(const Edge& edge, Vertex& out) const
	{
		out = boost::target(edge, (*this));
	}
	
	template <typename OutEdgeListS, // a Sequence or an AssociativeContainer
            typename VertexListS, // a Sequence or a RandomAccessContainer
            typename DirectedS,
            typename VertexProperty,
            typename EdgeProperty,
            typename GraphProperty,
            typename EdgeListS>
	inline void BetterGraphInterface<
			OutEdgeListS, 
			VertexListS, 
			DirectedS, 
			VertexProperty,
			EdgeProperty,
			GraphProperty, 
			EdgeListS >::getSource(const Edge& edge, Vertex& out) const
	{
		out = boost::source(edge, (*this));
	}
	
	template <typename OutEdgeListS, // a Sequence or an AssociativeContainer
            typename VertexListS, // a Sequence or a RandomAccessContainer
            typename DirectedS,
            typename VertexProperty,
            typename EdgeProperty,
            typename GraphProperty,
            typename EdgeListS>
	inline void BetterGraphInterface<
			OutEdgeListS, 
			VertexListS, 
			DirectedS, 
			VertexProperty,
			EdgeProperty,
			GraphProperty, 
			EdgeListS >::print() const
	{
		std::pair<VertexIterator, VertexIterator> vp;
		std::vector<Vertex> vec;
		//vertices access all the vertix
		//Classify them in order
		int i = 0;
		std::cout << getNumVertices() << std::endl;
		for (vp = boost::vertices((*this)); vp.first != vp.second; ++vp.first) {
			Vertex v = *vp.first;
			vec.push_back(v);
			std::cout << i <<" " << (*this)[v] << std::endl;
			++i;
		}
		
		for(size_t i = 0 ; i < vec.size() ; ++i){
			std::cout << getNumEdges(vec[i]) << std::endl;
			for(size_t j = 0 ; j < vec.size() ; ++j){
				
				bool exist = boost::edge(vec[i], vec[j], (*this)).second;
				if(exist == true){
					std::cout << i << " " << j << " " << (*this)[boost::edge(vec[i], 
vec[j], (*this)).first] << std::endl;
				}
			}
		}
	}

	
	template <typename OutEdgeListS, // a Sequence or an AssociativeContainer
            typename VertexListS, // a Sequence or a RandomAccessContainer
            typename DirectedS,
            typename VertexProperty,
            typename EdgeProperty,
            typename GraphProperty,
            typename EdgeListS>
	inline void BetterGraphInterface<
			OutEdgeListS, 
			VertexListS, 
			DirectedS, 
			VertexProperty,
			EdgeProperty,
			GraphProperty, 
			EdgeListS >::write(std::ostream& out){
		std::pair<VertexIterator, VertexIterator> vp;
		std::vector<Vertex> vec;
		std::vector<Edge> edges;
		//vertices access all the vertix
		//Classify them in order
		int i = 0;
		out << getNumVertices() << std::endl;
		for (vp = boost::vertices((*this)); vp.first != vp.second; ++vp.first) {
			Vertex v = *vp.first;
			vec.push_back(v);
			write(out, i, (*this)[v]);
			++i;
			
			//Getting all edges
			EdgeIterator out_i, out_end;
			Edge e;
			for (boost::tie(out_i, out_end) = boost::out_edges(v, (*this)); 
				out_i != out_end; ++out_i) {
				e = *out_i;
				bool saved = false;
				for(size_t ju = 0 ; ju < edges.size() ; ++ju){
					if(e == edges[ju]){
						saved = true;
					}
				}
				if(saved == false){
					edges.push_back(e);
				}
			}
			
		}		
		for(size_t i = 0 ; i < vec.size() ; ++i){
			
			std::deque<std::pair<int, Edge> > edge_to_write;
			for(size_t j = 0 ; j < vec.size() ; ++j){
				
				bool exist = boost::edge(vec[i], vec[j], (*this)).second;
				if(exist == true){
					
					bool written = true;
					for(size_t ju = 0 ; ju < edges.size() ; ++ju){
						if(boost::edge(vec[i], vec[j], (*this)).first == edges[ju]){
							edges.erase(edges.begin() + ju);
							written = false;
						}
					}
					if(written == false){
						edge_to_write.push_back(std::pair<int, Edge>(j, boost::edge(vec[i], vec[j], (*this)).first));
					}
				}
			}
			out << edge_to_write.size() << std::endl;
			for(size_t c = 0 ; c < edge_to_write.size() ; ++c){
				out << i << " " << edge_to_write[c].first << " " << (*this)[edge_to_write[c].second] << std::endl;
			}
			
		}
		
	}
	
	template <typename OutEdgeListS, // a Sequence or an AssociativeContainer
            typename VertexListS, // a Sequence or a RandomAccessContainer
            typename DirectedS,
            typename VertexProperty,
            typename EdgeProperty,
            typename GraphProperty,
            typename EdgeListS>
	inline void BetterGraphInterface<
			OutEdgeListS, 
			VertexListS, 
			DirectedS, 
			VertexProperty,
			EdgeProperty,
			GraphProperty, 
			EdgeListS >::read(std::ifstream& in){
		this->clear();
		std::vector<Vertex> vec;
		std::vector<VertexProperty> vectyp;
		int garbage;
		
		size_t num_vertex = 0;
		in >> num_vertex;
		for(size_t i = 0 ; i < num_vertex ; ++i){
			Vertex v;
			vec.push_back(v);
			
			in >> garbage;
			VertexProperty vt;
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
				EdgeProperty et;
				in >> et;
				Edge e;
				addEdge(e, vec[index], vec[index2], et);
			}
		}

		
	}
	
	template <typename OutEdgeListS, // a Sequence or an AssociativeContainer
            typename VertexListS, // a Sequence or a RandomAccessContainer
            typename DirectedS,
            typename VertexProperty,
            typename EdgeProperty,
            typename GraphProperty,
            typename EdgeListS>
	inline void BetterGraphInterface<
			OutEdgeListS, 
			VertexListS, 
			DirectedS, 
			VertexProperty,
			EdgeProperty,
			GraphProperty, 
			EdgeListS >::read(char* matrix[], const 
size_t x_size){
		std::vector<Vertex> vec;
		
		for(size_t i = 0 ; i < x_size ; ++i){
			Vertex v;
			VertexProperty vt;
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
