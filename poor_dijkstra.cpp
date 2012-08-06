/*
    g++ poor_dijkstra.cpp -o g
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
    reverse shortest path: 0 3 4 has length: 0.783333

 */

#include <vector>
#include <string>
#include <sstream>
#include <cassert>
#include <queue>
#include <iterator>
#include <algorithm>
#include <map>
#include <istream>
#include <ostream>

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
        g[u].begin(), g[u].end(), g[v].begin(), g[v].end(),
        results, compare1st()
        );
}

// Compute the shortest path from s to dst, writing the ids of
// vertices on the path (excluding s), in reverse order, into
// out_path.  Return a pair consisting of the total path cost and the
// resulting value of out_path.
//
// Pseudocode:
//
// POOR-DIJKSTRA(G, s, w)
//   for each vertex u in V 
//     d[u] := infinity 
//     p[u] := u 
//   end for 
//   INSERT(Q, (s,s,0)) 
//   while (Q != Ø) 
//     t,u,x := EXTRACT-MIN(Q) 
//     if u not in S 
//       d[u] = x                           // Record minimum distance from s to u
//       p[u] = t                           // Record predecessor of u in shortest path from s
//       S := S U { u } 
//       for each vertex v in Adj[u] 
//         if v not in S                    // First path found to v is always shortest 
//           INSERT(Q, (u, v, x + w(u,v)))  // put the path in the queue 
//       end for 
//   end while
//
template <class OutputIterator>
std::pair<edge_weight,OutputIterator>
poor_dijkstra( graph const& g, vertex_id s, vertex_id dst, OutputIterator out_path )
{
    // This is "S" from the pseudocode
    std::vector<bool> visited( count_vertices( g ) );
    
    // shortest distance to each vertex starts at infinity
    std::vector<edge_weight> d(
        count_vertices( g ), std::numeric_limits<edge_weight>::infinity() );
    
    // Here's where you complete the implementation
    $$ writeme $$
        
    // Get the total cost of the shortest path
    edge_weight w = d[ dst ];

    // Walk backwards from dst until we find a self-loop, writing out
    // vertices along the way.
    while ( p[dst] != dst )
    {
        *out_path++ = dst;
        dst = p[dst];
    }

    // Return total cost plus new iterator
    return std::make_pair( w, out_path );
}

// Read a graph from input in adjacency list form.
void read_adjacency_list( std::istream& input, graph& g )
{
    for ( std::string line; std::getline(input, line); )
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

        std::vector<std::pair<vertex_id, edge_weight> > neighbors;
        
        std::cout << "common neighbors of vertices " << u << " and " << v << ": ";
        common_neighbors( g, u, v, std::back_inserter( neighbors ) );
        std::transform( neighbors.begin(), neighbors.end(),
                        std::ostream_iterator<vertex_id>( std::cout, " " ),
                        project1st()
            );
        std::cout << std::endl;
        
        std::cout << "reverse shortest path: ";
        edge_weight w;
        w = poor_dijkstra(
            g, u, v,
            std::ostream_iterator<vertex_id>( std::cout, " " ) ).first;
        std::cout << "has length: " << w << std::endl;
    }
}

