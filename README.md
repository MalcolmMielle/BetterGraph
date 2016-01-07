# Better Graphs

Inspired by [VFL](http://mivia.unisa.it/datasets/graph-database/vflib/) and made with boost graph, here is the better Graph library.

Made to use in an intuitive way the boost graph and using iostream way to read and write graph to file.

## Create the graph 

```
betterGraph::Graph<Node, Edge> graph;
```

Node and Edge are custom class created by the user. They need to have a default constructor with no argument. The Graph are always undirected.
Since it uses boost it may be useful to declare those typedef

```
typedef boost::adjacency_list<
boost::listS, boost::listS, boost::undirectedS, 
Node,
Edge, 
boost::no_property > GraphType;
typedef typename boost::graph_traits<GraphType>::vertex_iterator VertexIterator;
typedef typename boost::graph_traits<GraphType>::vertex_descriptor Vertex;
typedef typename boost::graph_traits<GraphType>::edge_descriptor Edge;
typedef typename boost::graph_traits<GraphType>::out_edge_iterator EdgeIterator;
```

Those are the long complicated name of the vertices and edges of the graph and the iterators associated.

The better graph can be update real time by adding edges, vertex and changing attributes. This is the main advantage compared to [VFL](http://mivia.unisa.it/datasets/graph-database/vflib/).

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

# Example

See main.cpp