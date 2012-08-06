/*
    g++ self_loops.cpp -o g
    echo "2
1
4 5 1
0 3
3 1 4
3 0" | ./g
    . . * . . .
    . . . . . .
    . * . . * *
    * . . . . .
    . * . * . .
    * . . * . .

Notes:
pair comparison
range delete
erase returns new iterator

 */
#define _GLIBCXX_DEBUG

#include <vector>
#include <string>
#include <cassert>
#include <iterator>
#include <algorithm>
#include <istream>
#include <ostream>
#include <sstream>
#include <iostream>
#include <utility>
#include <numeric>

// Adjacency list graph representation
typedef unsigned vertex_id;
typedef float edge_weight;
typedef std::vector<vertex_id> neighbors_t;
typedef std::vector<neighbors_t> adjacency_list;

// Edge list graph representation
typedef std::pair<vertex_id, vertex_id> edge;
typedef std::vector<edge> edge_list;

// True iff there is an edge in g from u to v
// Complexity: O( log(|E|) )
inline bool has_edge(edge_list const& g, int u, int v)
{
    return std::binary_search( g.begin(), g.end(), edge(u,v) );
}

// Add a vertex to g and return its id
// Complexity: O( 1 )
inline vertex_id add_vertex( adjacency_list& g )
{
    vertex_id v = g.size();
    g.resize( v + 1 );
    return v;
}

// Return the number of vertices in g
inline std::size_t count_vertices( adjacency_list const& g )
{
    return g.size();
}

// True iff there is an edge in g from u to v
// Complexity: O( log(|V|) )
inline bool has_edge(adjacency_list const& g, int u, int v)
{
    return std::binary_search( g[u].begin(), g[u].end(), v );
}

// Add an edge in g from u to v with weight w
// Complexity: O( log(|V|) )
// Requires: u is a vertex in g, i.e. u < count_vertices( g )
inline void add_edge( edge_list& g, vertex_id u, vertex_id v )
{
    edge e(u,v);
    g.insert( std::lower_bound( g.begin(), g.end(), e ), e );
}

inline void add_edge( adjacency_list& g, vertex_id u, vertex_id v )
{
    assert( u < count_vertices( g ) );
    g[u].insert( std::lower_bound( g[u].begin(), g[u].end(), v ), v );
}

// Background: to remove an element from a vector<T> v, invoke
// v.erase(x) where x is a vector<T>::iterator to the element

// Write a function delete_edge( g, u, v ) that uses v.erase with
// std::find to delete an edge from the edge_list
inline void delete_edge( edge_list& g, vertex_id u, vertex_id v )
{
    edge e(u,v);
    std::pair<edge_list::iterator,edge_list::iterator> p
        = std::equal_range( g.begin(), g.end(), e );
    g.erase( p.first, p.second );
}

inline void delete_edge( adjacency_list& g, vertex_id u, vertex_id v )
{
    assert( u < count_vertices( g ) );
    neighbors_t::iterator e = g[u].end(), p = std::find( g[u].begin(), e, v );
    if ( p != e )
        g[u].erase( p );
}

// Write another function delete_self_loops( g ) that uses del_edge to
// delete all self-loops from the edge_list
inline void delete_self_loops( adjacency_list& g )
{
    for ( vertex_id u = 0, n = count_vertices( g ); u != n; ++u )
        delete_edge(g, u, u);
}

inline void delete_self_loops( edge_list& g )
{
    for ( edge_list::iterator p = g.begin(), e = g.end(); p != e; ++p )
        if ( p->first == p->second )
            p = g.erase(p);
}

// Read a adjacency_list from input in adjacency list form.
void read_adjacency_list( adjacency_list& g )
{
    for ( std::string line("x"); std::getline(std::cin, line); )
    {
        vertex_id src = add_vertex( g );
        
        std::stringstream s(line);
        for ( vertex_id dst; s >> dst; )
        {
            add_edge( g, src, dst );
        }
    }
}

// Read a edge_list from input in adjacency list form.
void read_edge_list( edge_list& g )
{
    vertex_id src = 0;
    for ( std::string line("x"); std::getline(std::cin, line); ++src)
    {
        std::stringstream s(line);
        for ( vertex_id dst; s >> dst; )
        {
            add_edge( g, src, dst );
        }
    }
}

// Write a g to output in adjacency matrix form.
void write_adjacency_matrix( adjacency_list const& g )
{
    for ( vertex_id u = 0; u < count_vertices( g ); ++u )
    {
        for ( vertex_id v = 0; v < count_vertices( g ); ++v )
            std::cout << (has_edge( g, u, v ) ? "* " : ". ");
        std::cout << std::endl;
    }
}

void write_adjacency_matrix( edge_list const& g )
{
    std::size_t vcnt = 0;
    for ( edge_list::const_iterator p = g.begin(), e = g.end(); p != e; ++p )
        vcnt = std::max((vertex_id)vcnt, std::max(p->first,p->second)+1);
    
    for ( vertex_id u = 0; u < vcnt; ++u )
    {
        for ( vertex_id v = 0; v < vcnt; ++v )
            std::cout << (has_edge( g, u, v ) ? "* " : ". ");
        std::cout << std::endl;
    }
}

inline bool cmp(edge e1, edge e2)
{
    if (e1.second < e2.second) return true;
    else if (e1.second > e2.second) return false;
    else return (e1.first < e2.first);
}

adjacency_list transposed_adjacency_list( edge_list eg )
{
    std::sort(eg.begin(), eg.end(), cmp);
    adjacency_list ag;
    
    for ( edge_list::iterator p = eg.begin(), e = eg.end(); p != e; ++p )
    {
        while ( p->second >= count_vertices(ag) || p->first >= count_vertices(ag) )
            add_vertex(ag);
        add_edge(ag, p->second, p->first);
    }
    return ag;
}

int main( int argc, char *argv[] )
{
    edge_list g;

    read_edge_list( g );
    write_adjacency_matrix( g );
    std::cout << "------- transposed --------" << std::endl;
    write_adjacency_matrix( transposed_adjacency_list( g ) );
}

