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

// Adjacency list graph representation
typedef unsigned vertex_id;
typedef float edge_weight;
typedef std::vector<vertex_id> neighbors_t;
typedef std::vector<neighbors_t> graph;

// True iff there is an edge in g from u to v
// Complexity: O( log(|V|) )
inline bool has_edge(graph const& g, int u, int v)
{
    return std::find(g[u].begin(), g[u].end(), v) != g[u].end();
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
void read_adjacency_list( graph& g )
{
    for ( std::string line("x"); std::getline(std::cin, line); )
    {
        g.push_back( neighbors_t() );

        std::stringstream s(line);
        for ( vertex_id dst; s >> dst; )
            g.back()
             .push_back( dst );
    }
}

// Write a g to output in adjacency matrix form.
void write_adjacency_matrix( graph const& g )
{
    for ( vertex_id u = 0; u < g.size(); ++u )
    {
        for ( vertex_id v = 0; v < g.size(); ++v )
            std::cout << ( has_edge( g, u, v ) ? "* " : ". " );
        std::cout << std::endl;
    }
}

int main( int argc, char *argv[] )
{
    graph g;

    read_adjacency_list( g );
    write_adjacency_matrix( g );
}

