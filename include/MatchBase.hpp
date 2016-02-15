#ifndef BETTERGRAPH_MATCH_BASE_15FEB2016
#define BETTERGRAPH_MATCH_BASE_15FEB2016

#include <iostream>
#include <stdio.h>

namespace betterGraph{
	///@brief Two Element linked.
	template<typename Element>
	class MatchBase{
		
	protected :
		
		Element _v1;
		Element _v2;
		
	public :
		MatchBase(const Element& v, const Element& vv) : _v1(v), _v2(vv){};
		
		const Element& getFirst() const {return _v1;}
		const Element& getSecond() const {return _v2;}
		
		Element& getFirst() {return _v1;}
		Element& getSecond() {return _v2;}
		
		void setFirst(const Element& v){_v1 = v;}
		void setSecond(const Element& v){_v2 = v;}

		
		//THIS CANNOT BE OVERRIDED AFTER :(
		
// 		///@brief return true if one of the vertex correspond
// 		virtual bool oneCommonElement(const MatchBase<Element>& m) const{
// // 				std::cout << "Comparing " <<_v1 << " with " << m.getFirst() << std::endl;
// // 				std::cout << " And Comparing " <<_v2 << " with " << m.getSecond() << std::endl;
// 			if(_v1 == m.getFirst() || _v2 == m.getSecond()){
// 				return true;
// 			}
// 			return false;
// 		}
		
		
// 		///@brief compare all attributes. return true if they are the same.
// 		virtual bool operator ==(const MatchBase<Element>& m) const{
// 			if(_v1 == m.getFirst() && _v2 == m.getSecond()){
// 				return true;
// 			}
// 			return false;
// 		}
// 		
// 		///@brief compare all attributes. return true if they are different.
// 		virtual bool operator !=(const MatchBase<Element>& m) const {
// 			if(*this == m){
// 				return false;
// 			}
// 			return true;
// 		}
		
		virtual void print(){
			std::cout << "Element : " << _v1 << " " << _v2 << std::endl;
		}
			
			
	};
	
	template <typename Element>
	inline std::ostream& operator<<(std::ostream& os, const betterGraph::MatchBase<Element>& dt){
		os << "Vertex : " << dt.getFirst() << " " << dt.getSecond() << std::endl;
		return os;
	}
	
}






#endif