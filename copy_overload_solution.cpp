// Write a function template Copy that takes two pointers p and q and
// a std::size_t n, and copies one n adjacent elements starting at p
// into the array starting at q
//
// Overload Copy with a function that copies ints by using std::memcpy
//
// Overload Copy with a function template that copies all pointers
// using std::memcpy
//
// Verify that the “right” function is called automatically

#include <cstddef>
#include <cstring>
#include <iostream>

template <class T>
void Copy(T* p, T* q, std::size_t n)
{
    std::cout << "Copy1" << std::endl;
    while (n--)
        *q++ = *p++;
}

void Copy(int* p, int* q, std::size_t n)
{
    std::cout << "Copy2" << std::endl;
    std::memcpy(q, p, n*sizeof(int));
}

template <class T>
void Copy(T** p, T** q, std::size_t n)
{
    std::cout << "Copy3" << std::endl;
    std::memcpy(q, p, n*sizeof(T*));
}


int main()
{
    std::string x1[20] = {}, x2[20] = {};
    int y1[20] = {}, y2[20] = {};
    int* z1[20] = {}, *z2[20] = {};
    
    Copy(x1, x2, 20);
    Copy(y1, y2, 20);
    Copy(z1, z2, 20);
}
