#ifndef BETTERGRAPH_HYPOTHESE_COMPARABLE_15FEB2016
#define BETTERGRAPH_HYPOTHESE_COMPARABLE_15FEB2016

#include "boost/bind.hpp"
#include "HypotheseBase.hpp"

namespace bettergraph{
	
	/**
		* @brief Object defining a possible matching between two graphmatch::GraphPlace
		*
		* As a deque of Match, an Hypothese define a possible matching between an input graph and a model graph 
		* 
		*/
	template<typename Element>
	class HypotheseComparable : public HypotheseBase<Element>{
		
	protected :
		
			
	public :
		
		HypotheseComparable(){};
		HypotheseComparable(const typename std::deque< Element >& h) : HypotheseBase<Element>(h) {};
		
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
		

		
	};
	
	template<typename Element>
	inline bool HypotheseComparable<Element>::isSeen(const Element& pair) const
	{
		
		for(size_t i = 0 ; i < this->_hypothesis.size() ; i++){
			if(this->_hypothesis[i].getFirst() == pair.getFirst() || this->_hypothesis[i].getSecond() == pair.getSecond()){
				return true;
			}
			else if(this->_hypothesis[i].getSecond() == pair.getFirst() || this->_hypothesis[i].getFirst() == pair.getSecond()){
				return true;
			}
		}
		return false;
	}
	
	template<typename Element>
	inline bool HypotheseComparable<Element>::isSeen(const Element& pair, int& index) const
	{
		
		for(size_t i = 0 ; i < this->_hypothesis.size() ; i++){
			if(this->_hypothesis[i].getFirst() == pair.getFirst() && this->_hypothesis[i].getSecond() == pair.getSecond()){
				index = i ;
				return true;
			}
			else if(this->_hypothesis[i].getSecond() == pair.getFirst() && this->_hypothesis[i].getFirst() == pair.getSecond()){
				index = i;
				return true;
			}
		}
		index = -1;
		return false;
	}

	
	template<typename Element>
	inline bool HypotheseComparable<Element>::isCompatible(const HypotheseBase<Element> h) const
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
	inline std::ostream& operator<<(std::ostream& os, const bettergraph::HypotheseComparable<Element>& dt){
		os << "Hypothese" << std::endl;
		for(size_t i = 0 ; i < dt.size() ; ++i){
			os << "element " << i << " " << dt[i] << std::endl;
		}
		return os;
	}
	
	
	
	
	
}

#endif