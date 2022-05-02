#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib>
#include <iostream>

template<typename T>
class Vector {
public:
    // constructors and destructor
    explicit Vector(size_t sz = 0);                // vector of size = sz and capacity = defaultCapacity || = sz
                                                   // elements initialized to 0 or default constructor
    Vector(size_t sz, const T &t);                 // size = capacity = sz and all elements = t
    Vector(const Vector<T> & source);              // copy constructor
    virtual ~Vector();                             // destructor

    // operators
    Vector & operator =(const Vector & v);         // assignment operator
    T & operator [](size_t index);                 // bracket operator
    const T & operator [](size_t index) const;     // const version

    // additional methods
    bool SetSize(size_t newSize);
    bool SetCapacity(size_t newCapacity);
    size_t Size() const;
    size_t Capacity() const;

    void Clear();                                   // set size to 0

    // Display methods
    void Display(std::ostream & os = std::cout, char ofc = '\0') const;
    void Dump(std::ostream & os = std::cout) const;

protected:
    size_t size_;     // current size of the vector, number of elements it is holding
    size_t capacity_; // number of elements it can hold
    T *content_;      // primitive C array to hold array of elements

    static int const defaultCapacity = 10;

    // safe memory allocator
    static T *NewArray(size_t sz);  // safe memory allocator

};

// non-member operator overloads
template < typename T >
std::ostream& operator << (std::ostream& os, const Vector<T>& a);

template < typename T >
bool operator == (const Vector<T>&, const Vector<T>&);

template < typename T >
bool operator != (const Vector<T>&, const Vector<T>&);

#endif //VECTOR_H
