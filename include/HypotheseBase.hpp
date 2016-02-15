#ifndef BETTERGRAPH_HYPOTHESE_BASE_15FEB2016
#define BETTERGRAPH_HYPOTHESE_BASE_15FEB2016

#include "boost/bind.hpp"

namespace betterGraph{	
	
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
		
		//TODO : in isSeen no need for the double comparison because it's supposed to be consistent.
		
		/**
			* @brief Tell if the input match is part of the Hypothese
			* 
			* @param[in] pair : Element that we want to test
			* @return true if seen, false otherwise
			* 
			*/
		bool isSeen(const Element& pair) const;
		
		/**
			* @brief Tell if the input match is part of the Hypothese and return the index
			* 
			* @param[in] pair : Element that we want to test
			* @param[in] index : index of the Match in Hypothese
			* @return true if seen, false otherwise
			*/
		bool isSeen(const Element& pair, int& index) const;
		
		/**
			* @brief Test if two hypothese don't have overlaping points.
			* 
			* @param[in] h : Hypothese to test
			* @return true if compatible, false otherwise. 
			*/
		bool isCompatible(const HypotheseBase<Element> h) const;
		
		Element& operator[](int i);
		const Element& operator[](const int i) const;
		
		
	};
	
	template<typename Element>
	inline bool HypotheseBase<Element>::isSeen(const Element& pair) const
	{
		
		for(size_t i = 0 ; i < _hypothesis.size() ; i++){
			if(_hypothesis[i].getFirst() == pair.getFirst() || _hypothesis[i].getSecond() == pair.getSecond()){
				return true;
			}
			else if(_hypothesis[i].getSecond() == pair.getFirst() || _hypothesis[i].getFirst() == pair.getSecond()){
				return true;
			}
		}
		return false;
	}
	
	template<typename Element>
	inline bool HypotheseBase<Element>::isSeen(const Element& pair, int& index) const
	{
		
		for(size_t i = 0 ; i < _hypothesis.size() ; i++){
			if(_hypothesis[i].getFirst() == pair.getFirst() && _hypothesis[i].getSecond() == pair.getSecond()){
				index = i ;
				return true;
			}
			else if(_hypothesis[i].getSecond() == pair.getFirst() && _hypothesis[i].getFirst() == pair.getSecond()){
				index = i;
				return true;
			}
		}
		index = -1;
		return false;
	}
	
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
	
	template<typename Element>
	inline bool HypotheseBase<Element>::isCompatible(const HypotheseBase<Element> h) const
	{
		
		bool compatible = true;
		std::deque< Element > match_h;
		match_h = h.getMatches();
		
		typename std::deque< Element >::iterator it;
		
		for(it = match_h.begin() ; it != match_h.end() ; it++){
			if(isSeen(*it) == true){
				compatible = false;
			}
		}
		
		return compatible;
		

	}
	
	/* STD::COUT function*/
	template<typename Element>
	inline std::ostream& operator<<(std::ostream& os, const betterGraph::HypotheseBase<Element>& dt){
		os << "Hypothese" << std::endl;
		for(size_t i = 0 ; i < dt.size() ; ++i){
			os << "element " << i << " " << dt[i] << std::endl;
		}
		return os;
	}
	
	
	
	
	
}

#endif