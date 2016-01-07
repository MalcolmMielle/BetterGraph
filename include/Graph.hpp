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
	
	
	template < typename GraphType>
	class Graph{
	protected : 
		int _marge;
		GraphType _graph;
		AttributeAdder _attribute_adder;
		
		typedef typename boost::graph_traits<GraphType>::vertex_iterator VertexIterator;
		typedef typename boost::graph_traits<GraphType>::vertex_descriptor Vertex;
		typedef typename boost::graph_traits<GraphType>::edge_descriptor Edge;
		typedef typename boost::graph_traits<GraphType>::out_edge_iterator EdgeIterator;
		
		
	public:
		Graph() : _marge(5){};
		
		
		virtual ~Graph(){/*std::cout << "Removing grah place with " <<getNumVertices() << " nodes " << std::endl;*/}
		virtual int getNumVertices() const {return boost::num_vertices(_graph);}
		virtual GraphType& getGraph(){return _graph;}
		virtual int getMarge(){return _marge;}
		virtual const GraphType& getGraph() const{return _graph;}
		virtual int getMarge() const {return _marge;}

// 			/** @brief Add a landmark into vertexPlace v */
// 			virtual void addCrossing(VertexPlace& v, const topologicalmap::Vertex& in, const topologicalmap::Intersection_Graph& inter);
// 			virtual int getNumEdges() const {return boost::num_edges(_graph);}
		/* Return the number of edge linked to v */
		virtual int getNumEdges(const Vertex& v) const {return boost::out_degree(v, _graph);}
		/** @brief Add edge between lopp index and index */
		bool addEdge(const Vertex& loop_index, const Vertex& index, void* edgeAttribute, Edge& out);
		/**
			* @brief add a new vertex and some attributes.
			* 
			* Attention, the keypoints attributes start non initialized !
			*/
		virtual void addVertex(Vertex& vertex_out, const Vertex& dad, void* nodeAttribute);
		/**
			* @brief add a new vertex and some attributes.
			* 
			* Attention, the keypoints attributes start non initialized !
			*/
		virtual void addVertex(Vertex& vertex_out, void* nodeAttribute);

		virtual void removeVertex(Vertex& v){
			boost::clear_vertex(v, _graph);
			boost::remove_vertex(v, _graph);
			
		}
		virtual void removeEdge(Edge& e){
			boost::remove_edge(e, _graph);
		}
// 			
		virtual void getAllVertexLinked(const Vertex& v, std::deque< Vertex >& all_vertex) const;
		virtual void getAllEdgeLinked(const Vertex& v, std::deque< std::pair< Edge, Vertex > >& all_edge) const;
// 			
		/**
			* @brief return the vertex targeted by edge */
		virtual void getTarget(const Edge& edge, Vertex& out) const;
// 			
		virtual void print() const ;
		virtual void print(const Vertex& v) const ;
		virtual void printHighLevel(const Vertex& v) const ;
		virtual void draw(cv::Mat& m) const;
		virtual void drawSpecial(cv::Mat& m) const;
		virtual void drawSpecial(cv::Mat& m, const std::deque< Vertex >& d_vp_const) const;
		virtual void clear(){/*deleteAllPlacePointer();*/ _graph.clear();}
// 			
		virtual void draw(cv::Mat& m, const Vertex& v, const cv::Scalar& color) const;
		virtual void drawSpecial(cv::Mat& m, const Vertex& v) const;

// 			
// 			/**
// 			 *@brief change the graph into a complete graph
// 			 *
// 			 * Add an edge between every vertex. If the edge existed before, the label is set to true.
// 			* It's set to false otherwise
// 			*/
// 			virtual void makeCompleteGraph(graphmatch::GraphPlace& gp) const;
// 			
// 			/**
// 			 * @brief Calculate the edit distance between the neigbhor of v compared to string other_graph_neighbor. 
// 			* 
// 			* Uses circular string matching.
// 			* 
// 			* @param[in] v : VertexPlace we are working on in this graph
// 			* @param[in] other_graph_neighbor : string representing the neighborhood of the other graph vertex
// 			* @param[in] all_edge_other_graph : deque of graphmatch::EdgePlace and VertexPlace of the other graph vertex' neighborhood
// 			* @param[in] operation_out : string representing the operation need to go from one neighborhood to the other
// 			* 
// 			* @return edit distance
// 			*/
// 			int editDistance(const VertexPlace& v, const std::string& other_graph_neighbor, const std::deque< std::pair< graphmatch::EdgePlace, VertexPlace > >& all_edge_other_graph, std::deque< graphmatch::Match >& out, std::string& operation_out) const;
// 			
// 			virtual Place& operator[](const VertexPlace& v);
// 			virtual const Place& operator[] (const VertexPlace& v) const;
// 			virtual Gateway_struct& operator[](const EdgePlace& v);
// 			virtual const Gateway_struct& operator[] (const EdgePlace& v) const;
// 			
// 			
// 			/**
// 			 * @brief Return all the graphmatch::EdgePlace and VertexPlace of a neighborhood counterclockwise
// 			 * 
// 			 * @param[in] v : VertexPlace we work on
// 			 * @param[in] all_edge : deque of graphmatch::EdgePlace and VertexPlace returned.
// 			 */
// 			virtual void getAllEdgeLinkedCounterClockWise(const VertexPlace& v, std::deque< std::pair< graphmatch::EdgePlace, VertexPlace > >& all_edge) const;
// 			
// 	// 		virtual void reduce(const std::deque< VertexPlace >& h);
// 			
// 			///@brief Put all vertex label to true 
// 			virtual void labelAll(const std::deque< VertexPlace >& h);
// 			///@brief Put all vertex label to false
// 			virtual void labelAll2False(const std::deque< VertexPlace >& h);
// 			///@brief Put all vertex label to false 
// 			virtual void resetLabel();
// 			///@brief Remove all vertex with label false of the graph
// 			virtual void removeAllFalseLabel();
// 			///@brief Scale center of mass of evey vertex by a certain factor
// 			virtual void scale(double scale);
// 			
// 			///@brief Calculate angle between v1 and v2 depending on center
// 			double angle(const VertexPlace& center, const VertexPlace& v1, const VertexPlace& v2) const;
// 			/**
// 			 * @brief create a string from a deque of VertexPlace
// 			 *
// 			 * @param[in] all_edge : deque of topologicalmapEdgePlace and topologicalmap::Vertex Place to transform into a string
// 			 * @return string
// 			 */ 
// 			std::string makeString(const std::deque< std::pair< graphmatch::EdgePlace, VertexPlace > >& all_edge) const;
// 			
// 			
// 			
// 						
// 			
// 		private:
// 			
// // 			virtual void deleteAllPlacePointer(){	
// // 				std::pair<VertexIteratorPlace, VertexIteratorPlace> vp;
// // 				//vertices access all the vertix
// // 				for (vp = boost::vertices(_graph); vp.first != vp.second; ++vp.first) {
// // 					VertexPlace v = *vp.first;
// // 					_graph[v].deleteKeypoint();
// // 				}
// // 			}
// 			
	};
// 
// 		
	inline void Graph::addVertex(Vertex& vertex_out, const Vertex& dad, void* nodeAttribute)
	{
		addVertex(vertex_out, nodeAttribute);
		Edge out;
		addEdge(vertex_out, dad, out);
	}
// 		
// 		inline void GraphPlace::addVertex(VertexPlace& vertex_out, const VertexPlace& dad, const Place& place)
// 		{
// 			addVertex(vertex_out, place.contour, place.moment, place.mass_center);
// 			
// 			//ATTENTION BULLSHIT GATEWAY
// 			Gateway g; 
// 			EdgePlace out;
// 			addEdge(vertex_out, dad, g, out);
// 		}
// 		
	inline void Graph::addVertex(Vertex& vertex_out, void* nodeAttribute)
	{
		vertex_out = boost::add_vertex(_graph);
		_attribute_adder.add(&_graph, &vertex_out, nodeAttribute);
	}
// 
// 		
// 		inline void GraphPlace::addVertex(VertexPlace& vertex_out, const std::vector<cv::Point>& contour, const cv::Moments& mom, const cv::Point& center_mass)
// 		{
// 			vertex_out = boost::add_vertex(_graph);
// 			_graph[vertex_out].contour = contour;
// 			_graph[vertex_out].moment = mom;
// 			_graph[vertex_out].mass_center = center_mass;
// 		}
// 
// 		
// 		inline void GraphPlace::print() const
// 		{
// 
// 			std::cout << "Printing the place graph here " << std::endl;
// 		
// 			//first is beginning, second is "past the end"
// 			std::pair<VertexIteratorPlace, VertexIteratorPlace> vp;
// 			//vertices access all the vertix
// 			for (vp = boost::vertices(_graph); vp.first != vp.second; ++vp.first) {
// 				VertexPlace v = *vp.first;
// 				print(v);
// 				
// 	// 			typename boost::property_map<Graph_boost, boost::vertex_index_t>::type 
// 	// 				index = get(boost::vertex_index, _graph);
// 
// 				std::cout << "The edges : ";
// 				EdgeIteratorPlace out_i, out_end;
// 				EdgePlace e;
// 				for (boost::tie(out_i, out_end) = boost::out_edges(v, _graph); 
// 					out_i != out_end; ++out_i) {
// 					e = *out_i;
// 					topologicalmap::Vertex src = boost::source(e, _graph), targ = boost::target(e, _graph);
// 						std::cout << "(" << _graph[src].mass_center << "," 
// 						<< _graph[targ].mass_center << " || " ;
// 				}
// 				
// 				std::cout << std::endl << std::endl;
// 			}
// 			std::cout << std::endl;
// 		}
// 		
// 		inline void GraphPlace::print(const VertexPlace& v) const{
// 			
// 			std::cout << "Vertex : ";
// 	// 		for(size_t i = 0 ; i < _graph[v].place.size() ; i++){
// 	// 			_graph[v].place[i].print(); 
// 	// 			std::cout << " " ;
// 	// 		}
// 			std::cout << std::endl;
// 	// 		for(size_t i = 0 ; i < _graph[v].landmarks.size() ; i++){
// 	// 			std::cout << " voro point at x : " << _graph[v].landmarks[i].first.point.x << " y : " << _graph[v].landmarks[i].first.point.y << std::endl;
// 	// 		}
// 			std::cout << "Center : " << _graph[v].mass_center << std::endl;
// 		}
// 		
// 		
// 		inline void GraphPlace::printHighLevel(const VertexPlace& v) const
// 		{
// 			std::cout << "Center : " << _graph[v].mass_center << std::endl;
// 			EdgeIteratorPlace out_i, out_end;
// 			EdgePlace e;
// 			for (boost::tie(out_i, out_end) = boost::out_edges(v, _graph); 
// 				out_i != out_end; ++out_i) {
// 				e = *out_i;
// 				VertexPlace targ = boost::target(e, _graph);
// 				std::cout << "Linked to : " << _graph[targ].mass_center << std::endl;
// 			}
// 		}
// 
// 
// 		
// 		inline void GraphPlace::draw(cv::Mat& m) const
// 		{
// 			
// 			cv::Scalar color;
// 			cv::RNG rng(12345);
// 			
// 			//first is beginning, second is "past the end"
// 			std::pair<VertexIteratorPlace, VertexIteratorPlace> vp;
// 			//vertices access all the vertix
// 			for (vp = boost::vertices(_graph); vp.first != vp.second; ++vp.first) {
// 				
// 				if(m.channels() == 1){
// 					color = rng.uniform(50, 255);
// 				}
// 				else if(m.channels() == 3){
// 					color[0] = rng.uniform(50, 255);
// 					color[1] = rng.uniform(50, 255);
// 					color[2] = rng.uniform(50, 255);
// 				}
// 				
// 				VertexPlace v = *vp.first;
// 				
// 				draw(m, v, color);
// 				
// 				EdgeIteratorPlace out_i, out_end;
// 				EdgePlace e;
// 				
// 				for (boost::tie(out_i, out_end) = boost::out_edges(v, _graph); 
// 					out_i != out_end; ++out_i) {
// 					e = *out_i;
// 					VertexPlace src = boost::source(e, _graph), targ = boost::target(e, _graph);
// 					cv::line(m, _graph[src].mass_center, _graph[targ].mass_center, color);
// 
// 				}
// 				
// 			}
// 		}
// 
// 		inline void GraphPlace::drawSpecial(cv::Mat& m) const
// 		{
// 			
// 			cv::Scalar color_link;
// 			if(m.channels() == 1){
// 				color_link = 190;
// 			}
// 			else if(m.channels() == 3){
// 				color_link[0] = 0;
// 				color_link[1] = 0;
// 				color_link[2] = 255;
// 			}
// 			
// 			//first is beginning, second is "past the end"
// 			std::pair<VertexIteratorPlace, VertexIteratorPlace> vp;
// 			//vertices access all the vertix
// 			for (vp = boost::vertices(_graph); vp.first != vp.second; ++vp.first) {
// 				
// 				VertexPlace v = *vp.first;
// 				drawSpecial(m, v);
// 				
// 				EdgeIteratorPlace out_i, out_end;
// 				EdgePlace e;
// 				
// 				for (boost::tie(out_i, out_end) = boost::out_edges(v, _graph); 
// 					out_i != out_end; ++out_i) {
// 					e = *out_i;
// 					VertexPlace src = boost::source(e, _graph), targ = boost::target(e, _graph);
// 					cv::line(m, _graph[src].mass_center, _graph[targ].mass_center, color_link, 5);
// 
// 				}
// 				
// 			}
// 		}
// 		
// 		
// 		inline void GraphPlace::drawSpecial(cv::Mat& m, const std::deque<VertexPlace>& d_vp_const) const
// 		{
// 			
// 			cv::Scalar color_link;
// 			if(m.channels() == 1){
// 				color_link = 190;
// 			}
// 			else if(m.channels() == 3){
// 				color_link[0] = 0;
// 				color_link[1] = 0;
// 				color_link[2] = 255;
// 			}
// 			
// 			//first is beginning, second is "past the end"
// 			std::pair<VertexIteratorPlace, VertexIteratorPlace> vp;
// 			//vertices access all the vertix
// 			
// 			for(size_t i = 0 ; i < d_vp_const.size() ; ++i){
// 				VertexPlace v = d_vp_const[i];
// 				drawSpecial(m, v);
// 				
// 				EdgeIteratorPlace out_i, out_end;
// 				EdgePlace e;
// 				
// 				for (boost::tie(out_i, out_end) = boost::out_edges(v, _graph); 
// 					out_i != out_end; ++out_i) {
// 					e = *out_i;
// 					VertexPlace src = boost::source(e, _graph), targ = boost::target(e, _graph);
// 				
// 					for(size_t j = 0 ; j < d_vp_const.size() ; ++j){
// 					
// 						if(targ == d_vp_const[j]){
// 							cv::line(m, _graph[src].mass_center, _graph[targ].mass_center, color_link, 5);
// 						}
// 						
// 					}
// 				
// 					
// 
// 				}
// 				
// 			}
// 		}
// 
// 		inline void GraphPlace::draw(cv::Mat& m, const VertexPlace& v, const cv::Scalar& color) const
// 		{
// 			
// 	// 		std::cout << "Drawing at " << _graph[v].mass_center << std::endl;
// 			for(size_t i = 0 ; i < _graph[v].place.size() ; i++){
// 	// 			_graph[v].place[i].print(); 
// 	// 			std::cout << " " ;
// 			}
// 	// 		std::cout << std::endl;
// 			for(size_t i = 0 ; i < _graph[v].landmarks.size() ; i++){
// 				cv::circle(m, _graph[v].landmarks[i].first.point, 10, color, 3);
// 			}
// 			cv::drawContours( m, std::vector<std::vector<cv::Point> >(1,_graph[v].contour), -1, color, 2, 8);
// 			cv::circle(m, _graph[v].mass_center, 10, color, -1);
// 		}
// 
// 		inline void GraphPlace::drawSpecial(cv::Mat& m, const VertexPlace& v) const
// 		{
// 			cv::circle(m, _graph[v].mass_center, 15, _graph[v].getColor(m.channels()), -1);
// 		}
// 		
// 		inline bool GraphPlace::addEdge(const AASS::graphmatch::VertexPlace& loop_index, const AASS::graphmatch::VertexPlace& index, const Gateway& g, AASS::graphmatch::EdgePlace& out)
// 		{
// 			
// 			bool exist = boost::edge(loop_index, index , _graph).second;
// 			if(exist == true){
// 				out = boost::edge(loop_index, index , _graph).first;
// 			}
// 			else if(loop_index == index){
// 				exist = true;
// 			}
// 			else{
// 				out = boost::add_edge(loop_index, index , _graph).first;
// 				_graph[out].gateways = g;
// 				_graph[out].label = true;
// 			}
// 			return exist;
// 			
// 		}
// 
// 		inline void GraphPlace::addCrossing(VertexPlace& v, const topologicalmap::Vertex& in, const topologicalmap::Intersection_Graph& inter)
// 		{
// 			_graph[v].landmarks.push_back( std::pair<topologicalmap::Intersection_Graph, topologicalmap::Vertex>(inter, in) );
// 			
// 		}
// 		
// 		inline void GraphPlace::getAllVertexLinked(const VertexPlace& v, std::deque< VertexPlace >& all_vertex) const
// 		{
// 			EdgeIteratorPlace out_i, out_end;
// 			EdgePlace e;
// 			
// 			for (boost::tie(out_i, out_end) = boost::out_edges(v, _graph); 
// 				out_i != out_end; ++out_i) {
// 				e = *out_i;
// 				VertexPlace targ = boost::target(e, _graph);
// 				all_vertex.push_back(targ);
// 			}
// 			
// 		}
// 		
// 		inline void GraphPlace::getAllEdgeLinked(const VertexPlace& v, std::deque< std::pair< graphmatch::EdgePlace, VertexPlace > >& all_edge) const
// 		{
// 	// 		std::cout << "GRAPH PLACE EDGE LINKED" << std::endl;
// 			EdgeIteratorPlace out_i, out_end;
// 			EdgePlace e;
// 			
// 			for (boost::tie(out_i, out_end) = boost::out_edges(v, _graph); 
// 				out_i != out_end; ++out_i) {
// 				e = *out_i;
// 				VertexPlace targ = boost::target(e, _graph);
// 				all_edge.push_back(std::pair<graphmatch::EdgePlace, VertexPlace> (e, targ) );
// 			}
// 		}
// 
// 		
// 		inline void GraphPlace::getTarget(const graphmatch::EdgePlace& edge, VertexPlace& out) const
// 		{
// 			out = boost::target(edge, _graph);
// 		}
// 
// 		
// // 		inline bool GraphPlace::isRoom(const VertexPlace& v) const
// // 		{
// // 			int junc = getNumEdges(v);
// // 			if(_graph[v].landmarks.size() == 1 && junc <= 2){
// // 				return false;
// // 			}
// // 			return true;
// // 		}
// 
// 		
// 		inline Place& GraphPlace::operator[](const VertexPlace& v)
// 		{
// 			return _graph[v];
// 		}
// 		
// 		inline const Place& GraphPlace::operator[](const VertexPlace& v) const
// 		{
// 			return _graph[v];
// 		}
// 		
// 		inline Gateway_struct& GraphPlace::operator[](const EdgePlace& v)
// 		{
// 			return _graph[v];
// 		}
// 		
// 		inline const Gateway_struct& GraphPlace::operator[](const EdgePlace& v) const
// 		{
// 			return _graph[v];
// 		}
// 		
// 		inline void GraphPlace::makeCompleteGraph(GraphPlace& gp) const 
// 		{
// 
// 			gp = *this;
// 			
// 			//first is beginning, second is "past the end"
// 			std::pair<VertexIteratorPlace, VertexIteratorPlace> vp;
// 			//vertices access all the vertix
// 			for (vp = boost::vertices(gp.getGraph()); vp.first != vp.second; ++vp.first) {
// 				VertexPlace v = *vp.first;
// 				
// 				std::cout << "The edges : ";
// 				EdgeIteratorPlace out_i, out_end;
// 				EdgePlace e;
// 				
// 				/*
// 				* std::pair<edge_descriptor, bool> edge(vertex_descriptor u, vertex_descriptor v, const adjacency_list& g) If an edge from vertex u to vertex v exists, return a pair containing one such edge and true. If there are no edges between u and v, return a pair with an arbitrary edge descriptor and false.
// 				* 
// 				* 
// 				*/
// 				
// 				std::pair<VertexIteratorPlace, VertexIteratorPlace> vp_other;
// 				//vertices access all the vertix
// 				for (vp_other = boost::vertices(gp.getGraph()); vp_other.first != vp_other.second; ++vp_other.first) {
// 					//If it's not the same vertex TODO : maybe we can consider it
// 					VertexPlace v_other = *vp_other.first;
// 					if(v != v_other){
// 						
// 						bool edge_exist = boost::edge(v, v_other, gp.getGraph() ).second;
// 						//if edge exist, put label to true.
// 						//else create an edge and put label at false
// 						if(edge_exist == true){
// 							EdgePlace edge = boost::edge(v, v_other, gp.getGraph() ).first;
// 							gp[edge].label = true;
// 						}
// 						else{
// 							EdgePlace edge = boost::add_edge(v, v_other, gp.getGraph() ).first;
// 							gp[edge].label = false;
// 						}
// 					}
// 					
// 				}
// 			}
// 			
// 		}
// 		
// 		inline std::string GraphPlace::makeString(const std::deque< std::pair< graphmatch::EdgePlace, VertexPlace > >& all_edge) const
// 		{
// 			//Make a string out of the order of vertex.	
// 			std::string string;
// // 			std::cout << "Making the string : " << std::endl;
// 
// 			std::deque< std::pair< graphmatch::EdgePlace, VertexPlace > >::const_iterator it;
// 			for(it = all_edge.begin() ; it != all_edge.end() ; it++){
// // 				print((*it).second);
// // 				std::cout << "Associate ID : " << _graph[(*it).second].getID() << std::endl;
// 				
// 				string = string + _graph[(*it).second].getID();
// 				
// // 				if(isRoom((*it).second) == true){
// // 					string = string + "r";
// // 				}
// // 				else{
// // 					string = string + "c";
// // 				}
// 			}
// 			
// // 			std::cout << "Making the room : " << string << std::endl;
// 			return string;
// 		}
// 
// 
// 		inline int GraphPlace::editDistance(const VertexPlace& v, const std::string& other_graph_neighbor, const std::deque< std::pair< graphmatch::EdgePlace, VertexPlace > >& all_edge_other_graph, std::deque< graphmatch::Match >& out, std::string& operation_out) const
// 		{
// 			
// 			std::deque< std::pair< graphmatch::EdgePlace, VertexPlace > > all_edge;
// 			int best_dist = -1;
// 			
// 			getAllEdgeLinkedCounterClockWise(v, all_edge);
// 
// 			//Make a string out of the order of vertex.	
// 			std::string string = makeString(all_edge);
// 			std::string operation;
// 			std::string original;
// 			int starting_point = -1;
// 			
// 			//compare every possibility.	
// 			for(size_t i = 0 ; i < string.size() ; i++){
// 				size_t y = i;
// 				std::deque<VertexPlace> list;
// 				
// 				std::string new_test;
// 				//Get all string combination
// 				for(size_t j = 0 ; j < string.size() ; j++){
// 					new_test = new_test + string.at(y);
// 					y++;
// 					list.push_back(all_edge[y].second);
// 					if(y == string.size()){
// 						y = 0;
// 					}
// 				}
// 				
// 				std::string out_string;
// 				double edistance = AASS::editdistance::normalizedEditDistance(new_test, other_graph_neighbor, out_string);
// 				
// // 				std::cout << "the out string " << out_string << " for " << new_test <<" and " <<other_graph_neighbor <<std::endl;
// 	// 			std::cout << "case : " << new_test;
// 	// 			std::cout << " distance : " << edistance << std::endl;
// 				if(best_dist == -1 || best_dist > edistance){
// 					best_dist = edistance;
// 					operation = out_string;
// 					//TODO Useless
// 					original = new_test;
// 					starting_point = y;
// 				
// 				}
// 				
// 			}
// 			
// 			size_t place_index = starting_point;
// 			int model_index = 0;
// 			
// 			/*
// 			* Interesting part is here
// 			* 
// 			* 
// 			*/
// 			
// 			for(size_t i = 0 ; i < operation.size(); i++){
// 				
// 				//Match
// 				if(operation.at(i) == 'n'){
// 					
// 					out.push_back(
// 						graphmatch::Match(
// 							all_edge[place_index].second, 
// 							all_edge_other_graph[model_index].second)
// 								);
// 					
// 					place_index++;
// 					model_index++;
// 				}
// 				//Substitution
// 				else if(operation.at(i) == 's'){
// 					
// 					out.push_back(
// 						graphmatch::Match(
// 							all_edge[place_index].second, 
// 							all_edge_other_graph[model_index].second)
// 								);
// 					
// 					place_index++;
// 					model_index++;
// 				}
// 				
// 				//TODO : find a good way to cope with deletion.
// 				//Deletion
// 				else if(operation.at(i) == 'd'){
// 					//needs to stay at the same place on the model but we move onto the other word
// 					place_index++;
// 				}
// 				//Insertion
// 				else if(operation.at(i) == 'i'){
// 					//does nothing
// 					model_index++;
// 				}
// 				
// 				
// 				if(place_index == all_edge.size()){
// 					place_index = 0 ;
// 				}
// 				
// 				
// 			}
// 			
// 	// 		std::deque< graphmatch::Match >::iterator it_test_editdistance;
// 
// 			//Keep the best one edit distance one
// 			return best_dist;
// 		}
// 		
// 
// 
// 
// 		
// 
// 		inline void GraphPlace::getAllEdgeLinkedCounterClockWise(const VertexPlace& v, std::deque< std::pair< graphmatch::EdgePlace, VertexPlace > >& all_edge) const
// 		{
// 
// 			getAllEdgeLinked(v, all_edge);
// 	// 		std::cout << "Size in function " << all_edge.size() << std::endl;
// 			if(all_edge.size() > 0){
// 				
// 				VertexPlace firstvertex = all_edge[0].second;
// 				
// 				//classify them in a clock wise manner
// 				std::deque< std::pair< graphmatch::EdgePlace, VertexPlace > >::iterator it;
// 				std::pair< graphmatch::EdgePlace, VertexPlace > copy;
// 				std::deque< std::pair< graphmatch::EdgePlace, VertexPlace > >::iterator it_2;
// 				for(it = all_edge.begin()+1 ; it != all_edge.end() ; it++){
// 					
// 					it_2 = it ;
// 					copy = *it;
// 					
// 					double angle_to_compare = angle(v, firstvertex, (*it).second);
// 					
// 	// 				std::cout << "FIRST VERTEX " << std::endl;
// 	// 				print(firstvertex);
// 	// 				std::cout << "SECOND VERTEX " << std::endl;
// 	// 				print((*it).second);
// 	// 				std::cout << "the angle : " << angle_to_compare << std::endl << std::endl;
// 	// 				std::cout << "First angle to compare to : " << angle(v, firstvertex, (*( it_2-1 )).second) << std::endl;
// 	// 				std::cout << "Center " << std::endl;
// 	// 				print(v);
// 	// 				std::cout << "NEXT " << std::endl;
// 
// 					
// 					while( it_2 != all_edge.begin() && angle(v, firstvertex, (*( it_2-1 )).second) > angle_to_compare){
// 	// 					std::cout << "Exchanging " << std::endl;
// 	// 					print((*it).second);
// 	// 					std::cout << "With " << std::endl;
// 	// 					print((*(it_2-1)).second);
// 	// 					std::cout << std::endl;
// 						
// 						*(it_2) = *(it_2-1);
// 						it_2 = it_2 - 1;
// 						
// 					}
// 					*(it_2) = copy;
// 					
// 				}
// 				
// 				for(size_t i = 0 ; i < all_edge.size() ; i++){
// 	// 				std::cout << "FIRST VERTEX " << std::endl;
// 	// 				print(firstvertex);
// 	// 				std::cout << "SECOND VERTEX " << std::endl;
// 	// 				print(all_edge[i].second);
// 	// 				double a = angle(v, firstvertex, all_edge[i].second);
// 	// 				if(a < 0){a = a + (2 * M_PI);}
// 	// 				std::cout << "the angle : " << a << std::endl << std::endl;
// 	// 				std::cout << "Center " << std::endl;
// 	// 				print(v);
// 	// 				std::cout << "NEXT " << std::endl;
// 				}
// 			}
// 			
// 		}
// 		
// 		inline double GraphPlace::angle(const VertexPlace& center, const VertexPlace& v1, const VertexPlace& v2) const
// 		{
// 			double x1 = _graph[v1].mass_center.x - _graph[center].mass_center.x;
// 			double y1 = _graph[v1].mass_center.y - _graph[center].mass_center.y;
// 			
// 			double x2 = _graph[v2].mass_center.x - _graph[center].mass_center.x;
// 			double y2 = _graph[v2].mass_center.y - _graph[center].mass_center.y;
// 			
// 	// 		std::cout << "values " <<x1 << " " << y1 << " and " << x2 << " " << y2 <<std::endl;
// 			
// 			double angle = atan2(y2, x2) - atan2(y1, x1);
// 			if(angle < 0){
// 				angle = angle + (2 * M_PI);
// 			}
// 			return angle;
// 		
// 		}
// 		
// 
// 
// 		inline void GraphPlace::labelAll(const std::deque< VertexPlace >& h)
// 		{	
// 			
// 	// 		std::cout << "SIZE " << h.size() << std::endl;
// 			for(size_t i = 0; i < h.size() ; i++){
// 	// 			std::cout << "LABELLED" << std::endl;
// 				_graph[h[i]].label = true;
// 			}
// 		}
// 		
// 		inline void GraphPlace::labelAll2False(const std::deque< VertexPlace >& h)
// 		{	
// 			
// 	// 		std::cout << "SIZE " << h.size() << std::endl;
// 			for(size_t i = 0; i < h.size() ; i++){
// 	// 			std::cout << "LABELLED" << std::endl;
// 				_graph[h[i]].label = false;
// 			}
// 		}
// 		
// 		inline void GraphPlace::resetLabel()
// 		{	
// 			
// 	// 		//first is beginning, second is "past the end"
// 			std::pair<VertexIteratorPlace, VertexIteratorPlace> vp;
// 			//vertices access all the vertix
// 			for (vp = boost::vertices(_graph); vp.first != vp.second; ++vp.first) {
// 				VertexPlace v = *vp.first;
// 				_graph[v].label = false;
// 			}
// 		}
// 		
// 		
// 		inline void GraphPlace::removeAllFalseLabel()
// 		{
// 			std::pair<VertexIteratorPlace, VertexIteratorPlace> vp_other;
// 			//vertices access all the vertix
// 			std::pair<VertexIteratorPlace, VertexIteratorPlace> vp;
// 			//vertices access all the vertix
// 			for (vp = boost::vertices(_graph); vp.first != vp.second; ) {
// 	// 			std::cout << "studying vertex " << std::endl;
// 				
// 				VertexPlace v = *vp.first;
// 				print(v);
// 				
// 				if(_graph[v].label == false){
// 					
// 	// 				std::cout << "removing vertex " << std::endl;
// 					std::deque< std::pair< graphmatch::EdgePlace, VertexPlace > > pair;
// 					getAllEdgeLinked(v, pair);
// 					
// 					for(size_t i = 0 ; i < pair.size() ; i++){
// 	// 					std::cout << "creating edges " << std::endl;
// 						for(size_t j = i+1 ; j < pair.size() ; j++){
// 							Gateway gg;
// 							graphmatch::EdgePlace ep;
// 							addEdge(pair[i].second, pair[j].second, gg, ep);
// 						}
// 					}
// 					
// 	// 				std::cout << "removing the vertex " << std::endl;
// 					++vp.first;
// 					removeVertex(v);
// 	// 				std::cout << "DONE " << std::endl;
// 				}
// 				else{
// 					++vp.first;
// 				}
// 				
// 			}
// 			
// 
// 		}
// 
// 
// 		inline void GraphPlace::scale(double scale)
// 		{
// 				
// // 			std::cout << "Scaling by " << scale << std::endl;
// 			//first is beginning, second is "past the end"
// 			std::pair<VertexIteratorPlace, VertexIteratorPlace> vp;
// 			//vertices access all the vertix
// 			for (vp = boost::vertices(_graph); vp.first != vp.second; ++vp.first) {
// 				VertexPlace v = *vp.first;
// 	// 			std::cout << "before " << _graph[v].point;
// 				_graph[v].mass_center = _graph[v].mass_center * scale;
// 	// 			std::cout << " after " << _graph[v].point << std::endl;
// 			}
// 		}
// 
// 
// 
// 		
// 

}
#endif
