# Better Graphs

Inspired by [VFL](http://mivia.unisa.it/datasets/graph-database/vflib/) and made with boost graph, here is the better Graph library.

Made to use in an intuitive way the boost graph and using iostream way to read and write graph to file.

## Create the graph 

```
betterGraph::Graph<Node, Edge> graph;
```

Node and Edge are custom class created by the user. They need to have a default constructor with no argument (because of the read function). 

The better graph can be update real time by adding edges, vertex and changing attributes. This is the main advantage compared to [VFL](http://mivia.unisa.it/datasets/graph-database/vflib/).

for a PseudoGraph with a Node attribute `Node` and a Edge attribute `EdgeAttr` :

* Vertex of the graph : `bettergraph::PseudoGraph<Node, EdgeAttr>::Vertex}` 
* Edge of the graph : `bettergraph::PseudoGraph<Node, EdgeAttr>::Edge}` 
* Vertex iterator of the graph : `bettergraph::PseudoGraph<Node, EdgeAttr>::VertexIterator}` 
* Edge iterator of the graph : `bettergraph::PseudoGraph<Node, EdgeAttr>::EdgeIterator}` 

To access the attribute of an edge or a vertex : `graph[vertex]` and then use the class for the attribute as you would normally do.

# Read and write

To read and write a graph to/from a file, the Node and Edge class need to have the operator `>>` and `<<` overloaded. For example :

```
std::istream& operator>>(std::istream& in, Node &p){
	
	in >> p.i ; in >> p.str; return in;
}

std::ostream& operator<<(std::ostream& in, const Node &p){
	
	return in << p.i << " " <<p.str;
}
```

## Write a graph to a file

```
std::ofstream out("bob.txt");
graph.write(out);
```

## Read a graph from a file 

```
std::ifstream in("bob.txt");
graph.read(in);
```

## Writing convention

```
total number of vertices
number of vertex + node attributes
total number of vertices
index index2 edge attributes
index index3 edge attributes
total number of vertices
index2 index1 edge attributes
index2 index3 edge attributes
...
```

# Element of graph matching

Two base class HypotheseBase and MatchBase are provided. 

MatchBase is an match between two element and HypotheseBase is a deque of Match providing a possible match between two graph.

MatchComparable and HypotheseComparable are daughter class with some comparaison function already implemented. Thus their element class needs to have an `operator==` and `operator<<`.

# Example

See main.cpp