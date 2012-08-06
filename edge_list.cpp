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
typedef std::pair<vertex_id, vertex_id> edge;
typedef std::vector<edge> graph;

// True iff there is an edge in g from u to v
// Complexity: O( log(|V|) )
inline bool has_edge(graph const& g, int u, int v)
{
    $writeme$
}

// Add an edge in g from u to v with weight w
// Complexity: O( log(|V|) )
// Requires: u is a vertex in g, i.e. u < count_vertices( g )
inline void add_edge( graph& g, vertex_id u, vertex_id v )
{
    $writeme$
}

// Background: to remove an element from a vector<T> v, invoke
// v.erase(x) where x is a vector<T>::iterator to the element

// Write a function delete_edge( g, u, v ) that uses v.erase with
// std::find to delete an edge from the graph
inline void delete_edge( graph& g, vertex_id u, vertex_id v )
{
    $writeme$
}

// Write another function delete_self_loops( g ) that uses del_edge to
// delete all self-loops from the graph
inline void delete_self_loops( graph& g )
{
     $writeme$
}

// Read a graph from input in adjacency list form.
void read_edge_list( graph& g )
{
     $writeme$
}

// Write a g to output in adjacency matrix form.
void write_adjacency_matrix( graph const& g )
{
    $fixme$
    for ( vertex_id u = 0; u < count_vertices( g ); ++u )
    {
        for ( vertex_id v = 0; v < count_vertices( g ); ++v )
            std::cout << (has_edge( g, u, v ) ? "* " : ". ");
        std::cout << std::endl;
    }
}

int main( int argc, char *argv[] )
{
    graph g;

    read_edge_list( g );
    write_adjacency_matrix( g );
}

