#ifndef BETTERGRAPH_HYPOTHESE_BASE_15FEB2016
#define BETTERGRAPH_HYPOTHESE_BASE_15FEB2016

#include "boost/bind.hpp"

namespace bettergraph{	
	
	/**
		* @brief Object defining a possible matching between two graphmatch::GraphPlace
		*
		* As a deque of Match, an Hypothese define a possible matching between an input graph and a model graph 
		* 
		*/
	template<typename Element>
	class HypotheseBase{
		
	protected :
		
		std::deque< Element > _hypothesis;		
			
	public :
		
		HypotheseBase(){};
		HypotheseBase(const std::deque< Element >& h) : _hypothesis(h) {};
		
		size_t size() const {return _hypothesis.size();}
		void push_back(const Element& pair){_hypothesis.push_back(pair);}
		void push_front(const Element& pair){_hypothesis.push_front(pair);}
		void pop_back(){_hypothesis.pop_back();}
		void pop_front(){_hypothesis.pop_front();}
		void clear(){_hypothesis.clear();}
		bool empty(){return _hypothesis.empty();}
		Element& at(int i){return _hypothesis.at(i);}
		typename std::deque< Element>::iterator begin(){return _hypothesis.begin();}
		typename std::deque< Element>::iterator erase(const typename std::deque< Element>::iterator& it){return _hypothesis.erase(it);};
		
		
		std::deque< Element >& getAllElements(){return _hypothesis;}
		const std::deque< Element >& getAllElements() const {return _hypothesis;}
		
		Element& operator[](int i);
		const Element& operator[](const int i) const;
		
		
	};
	
	template<typename Element>
	inline Element& HypotheseBase<Element>::operator[](int i)
	{
		return _hypothesis[i];
	}
	
	template<typename Element>
	inline const Element& HypotheseBase<Element>::operator[](const int i) const
	{
		return _hypothesis[i];
	}
	
	
	
	
	/* STD::COUT function*/
// 	template<typename Element>
// 	inline std::ostream& operator<<(std::ostream& os, const betterGraph::HypotheseBase<Element>& dt){
// 		os << "Hypothese" << std::endl;
// 		for(size_t i = 0 ; i < dt.size() ; ++i){
// 			os << "element " << i << " " << dt[i] << std::endl;
// 		}
// 		return os;
// 	}
	
}

#endif