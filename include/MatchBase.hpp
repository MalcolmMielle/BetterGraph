#ifndef BETTERGRAPH_MATCH_BASE_15FEB2016
#define BETTERGRAPH_MATCH_BASE_15FEB2016

#include <iostream>
#include <stdio.h>



namespace bettergraph{
	///@brief Two Element linked.
	template<typename Element>
	class MatchBase{
		
	protected :
		
		Element _v1;
		Element _v2;
		
	public :
		MatchBase(){};
		MatchBase(const Element& v, const Element& vv) : _v1(v), _v2(vv){};
		
		const Element& getFirst() const {return _v1;}
		const Element& getSecond() const {return _v2;}
		
		Element& getFirst() {return _v1;}
		Element& getSecond() {return _v2;}
		
		void setFirst(const Element& v){_v1 = v;}
		void setSecond(const Element& v){_v2 = v;}

		
		virtual void print(){
			std::cout << "Element : " << _v1 << " " << _v2 << std::endl;
		}
			
			
	};
	
// 	template <typename Element>
// 	inline std::ostream& operator<<(std::ostream& os, const betterGraph::MatchBase<Element>& dt){
// 		os << "Vertex : " << dt.getFirst() << " " << dt.getSecond() << std::endl;
// 		return os;
// 	}
	
}






#endif