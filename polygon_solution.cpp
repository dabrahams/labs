// Copyright David Abrahams 2010. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <cstddef>
#include <cassert>
#include <iostream>

// Write a function template circumference that computes the
// circumference of a polygon
namespace unoptimized
{
  template <class Polygon>
  float circumference(Polygon const& p)
  {
      std::cout << "slow" << std::endl;
      float ret = 0.0;

      for (std::size_t i = 0, n = size(p); i < n; ++i)
          ret += length(p,i);

      return ret;
  }
}

// Write another function template regular_circumference that
// computes the circumference of an regular polygon
template <class RegularPolygon>
float regular_circumference(RegularPolygon const& p)
{
    std::cout << "fast" << std::endl;
    return size(p) * side_length(p);
}


// From your two function implementations derive and define a Polygon
// concept, and its refinement RegularPolygon
//
//    Polygon Requirements
//
//    P: model of Polygon, x: object of type P, n: object of type size_t
//    +-------------------+---------------+-----------------------+ 
//    |Valid Expression   |Type           |Semantics / Pre / Post |
//    +===================+===============+=======================+
//    |size( x )          |std::size_t    |                       |
//    +-------------------+---------------+-----------------------+
//    |length( x, n )     |float          |Pre: n < size( x )     |
//    +-------------------+---------------+-----------------------+
//
//  
//    RegularPolygon Requirements (in addition to Polygon)
//
//    P: model of RegularPolygon, x: object of type P, n: object of type size_t
//    +-------------------+---------------+-----------------------+ 
//    |Valid Expression   |Type           |Semantics / Pre / Post |
//    +===================+===============+=======================+
//    |side_length( x )   | float         |length(x, n) ==        |
//    |                   |               |side_length( x ) for   |
//    |                   |               |all n < size( x )      |
//    +-------------------+---------------+-----------------------+
//  

// Extra Credit (hard): overload circumference so it uses
// regular_circumference on regular polygons

//
// Rectangle
//
struct rect
{
    rect(float top, float left, float bottom, float right)
        : top(top), left(left), bottom(bottom), right(right)
    {}

    float top, left, bottom, right;
};

inline float size(rect const& r)
{ return 4; }

inline float length(rect const& r, std::size_t side)
{ return side % 2 ? r.right - r.left : r.bottom - r.top; }


//
// Square
//
struct square
{
    square(float top, float left, float dim)
        : top(top), left(left), dim(dim)
    {}

    float top, left, dim;
};

inline float size(square const& r)
{ return 4; }

inline float side_length( square const& r )
{
    return r.dim;
}
    
inline float length(square const& r, std::size_t side)
{
    return side_length(r);
}

// Default implementation
template <class Polygon>
inline void* side_length( Polygon const& r )
{
    return 0;
}

// Extra Credit (hard): overload circumference so it uses
// regular_circumference on regular polygons
namespace optimized
{
  template <class Polygon>
  float circumference_impl(Polygon const& p, void*)
  {
      return unoptimized::circumference( p );
  }

  template <class RegularPolygon>
  float circumference_impl(RegularPolygon const& p, std::size_t)
  {
      return regular_circumference(p);
  }

  template <class Polygon>
  float circumference(Polygon const& p)
  {
      return circumference_impl(p, side_length(p));
  }
}

int main()
{
    using optimized::circumference;
    
    std::cout << "rect: ";
    rect r(3, 4, 5, 9);
    assert( circumference(r) == 14 );

    std::cout << "square: ";
    square s(0, 0, 5);
    assert( circumference(s) == 20 );

    std::cout << "explicit square: ";
    assert( regular_circumference(s) == 20 );
}
