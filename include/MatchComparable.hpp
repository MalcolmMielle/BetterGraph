#ifndef BETTERGRAPH_MATCH_COMPARABLE_15FEB2016
#define BETTERGRAPH_MATCH_COMPARABLE_15FEB2016

#include <iostream>
#include <stdio.h>
#include "MatchBase.hpp"


namespace bettergraph{
	///@brief Two Element linked.
	template<typename Element>
	class MatchComparable : public MatchBase<Element>{
		
	protected :
		
	public :
		MatchComparable(){};
		MatchComparable(const Element& v, const Element& vv) : MatchBase<Element>(v, vv){};
		
		//THIS CANNOT BE COMPLETELY OVERRIDED AFTER :( see : http://stackoverflow.com/questions/35414595/overriding-template-function-in-specialized-daughter-class
		
		///@brief return true if one of the vertex correspond
		virtual bool oneCommonElement(const MatchBase<Element>& m) const{
// 				std::cout << "Comparing " <<this->_v1 << " with " << m.getFirst() << std::endl;
// 				std::cout << " And Comparing " <<this->_v2 << " with " << m.getSecond() << std::endl;
			if(this->_v1 == m.getFirst() || this->_v2 == m.getSecond()){
				return true;
			}
			return false;
		}
		
		
		///@brief compare all attributes. return true if they are the same.
		virtual bool operator ==(const MatchBase<Element>& m) const{
			if(this->_v1 == m.getFirst() && this->_v2 == m.getSecond()){
				return true;
			}
			return false;
		}
		
		///@brief compare all attributes. return true if they are different.
		virtual bool operator !=(const MatchBase<Element>& m) const {
			if(*this == m){
				return false;
			}
			return true;
		}
		
		virtual void print(){
			std::cout << "Element : " << this->_v1 << " " << this->_v2 << std::endl;
		}
			
			
	};
	
	template <typename Element>
	inline std::ostream& operator<<(std::ostream& os, const bettergraph::MatchComparable<Element>& dt){
		os << "Vertex : " << dt.getFirst() << " " << dt.getSecond() << std::endl;
		return os;
	}
	
}






#endif