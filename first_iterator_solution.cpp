/*
    g++ map_bfs.cpp -o g
    echo "2

    4 5 1
    0
    3 1
    3 0" | ./g 2 0
    . . * . . .
    . . . . . .
    . * . . * *
    * . . . . .
    . * . * . .
    * . . * . .
    common neighbors of vertices 2 and 0:
    vertex 0 is reachable from vertex 2

 */
#define _GLIBCXX_DEBUG
#define _GLIBCXX_FULLY_DYNAMIC_STRING
#include <istream>
#include <ostream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>
#include <deque>
#include <iterator>
#include <algorithm>
#include <map>

#include <boost/iterator/iterator_adaptor.hpp>

template <class PairIter>
struct first_iterator : boost::iterator_adaptor<
  first_iterator<PairIter>, PairIter,
  typename std::iterator_traits<PairIter>::value_type::first_type
  >
{
  first_iterator() {}
  first_iterator(PairIter p) : first_iterator::iterator_adaptor_(p) {}
private:
  friend class boost::iterator_core_access;

  typename first_iterator::reference dereference() const
  {
    return this->base()->first;
  }
};

template <class PairIter>
first_iterator<PairIter> make_first_iterator(PairIter p)
{
  return first_iterator<PairIter>(p);
}

// Adjacency list graph representation
typedef unsigned vertex_id;
typedef float edge_weight;
typedef std::map<vertex_id, edge_weight> neighbors_t;
typedef std::vector<neighbors_t> graph;

// True iff there is an edge in g from u to v
// Complexity: O( log(|V|) )
inline bool has_edge(graph const& g, int u, int v)
{
    return g[u].find(v) != g[u].end();
}

// Add a vertex to g and return its id
// Complexity: O( 1 )
inline vertex_id add_vertex( graph& g )
{
    vertex_id v = g.size();
    g.resize( v + 1 );
    return v;
}

// Return the number of vertices in g
inline std::size_t count_vertices( graph const& g )
{
    return g.size();
}

// Return the number of outgoing edges from u in g
inline std::size_t count_adj( graph const& g, vertex_id u )
{
    return g[u].size();
}

// Add an edge in g from u to v with weight w
// Complexity: O( log(|V|) )
// Requires: u is a vertex in g, i.e. u < count_vertices( g )
inline void add_edge( graph& g, vertex_id u, vertex_id v, edge_weight w )
{
    assert( u < count_vertices( g ) );
    g[u].insert( std::make_pair( v, w ) );
}

// A lightweight function object that compares the "first" members of
// any two pairs having the same type.
struct compare1st
{
    // Complexity: O( 1 )
    template <class Pair>
    bool operator()( Pair const& p1, Pair const& p2 )
    {
        return p1.first < p2.first;
    }
};

// A lightweight function object that projects from a pair onto its
// "first" member
struct project1st
{
    // Complexity: O( 1 )
    template <class Pair>
    typename Pair::first_type operator()( Pair const& p )
    {
        return p.first;
    }
};

// Find all vertices reachable in one step from both u and v, and
// write their ids into results.  Return the past-the-end position in
// the sequence of written result values.
//
// Complexity: O(|V|)
template <class OutputIterator>
OutputIterator
common_neighbors(
    graph const& g, vertex_id u, vertex_id v, OutputIterator results )
{
    return std::set_intersection(
        make_first_iterator(g[u].begin()), make_first_iterator(g[u].end()),
        make_first_iterator(g[v].begin()), make_first_iterator(g[v].end()),
        results
        );
}

// A simple breadth-first search starting from u for vertex v.
// Returns true iff v is reachable from u.  Complexity: O(|V|+|E|)
bool bfs(graph const& g, vertex_id u, vertex_id v)
{
    std::vector<bool> visited( count_vertices( g ) );
    std::deque<vertex_id> q;
    q.push_back( u );

    while ( !q.empty() )
    {
        vertex_id const next = q.front();
        q.pop_front();
        if ( next == v )
            return true;
        if ( !visited[next] )
        {
            visited[next] = true;
            
            std::transform( g[next].begin(), g[next].end(),
                            std::back_inserter( q ),
                            project1st()
                );
        }
    }
    return false;
}

// Read a graph from input in adjacency list form.
void read_adjacency_list( std::istream& input, graph& g )
{
  for (std::string line ; std::getline(input, line); )
    {
        vertex_id src = add_vertex( g );
        
        std::stringstream s(line);
        for ( int dst; s >> dst; )
        {
            // Make up an arbitrary weight
            edge_weight w = (1 + count_adj(g, src)) * 1.0 / count_vertices(g);
            add_edge( g, src, dst, w );
        }
    }
}

// Write a g to output in adjacency matrix form.
void write_adjacency_matrix( std::ostream& output, graph const& g )
{
    for ( vertex_id u = 0; u < count_vertices( g ); ++u )
    {
        for ( vertex_id v = 0; v < count_vertices( g ); ++v )
            output << (has_edge( g, u, v ) ? "* " : ". ");
        output << std::endl;
    }
}

#include <iostream>
int main( int argc, char *argv[] )
{
    graph g;

    read_adjacency_list( std::cin, g );
    write_adjacency_matrix( std::cout, g );
    
    if ( argc == 3 )
    {
        vertex_id u, v;
        std::stringstream(argv[1]) >> u;
        std::stringstream(argv[2]) >> v;

        std::vector<vertex_id> neighbors;
        
        std::cout << "common neighbors of vertices " << u << " and " << v << ": ";
        common_neighbors( g, u, v, std::ostream_iterator<vertex_id>( std::cout, " " ) );

        std::cout << std::endl;
        
        std::cout << "vertex " << v << " is " << (bfs( g, u, v ) ? "" : "not ")
                  << "reachable from vertex" << u << std::endl;
    }
}

