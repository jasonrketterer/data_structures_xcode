// Vector class implementation/definition
//
// Created by Jason Ketterer on 1/11/22.
//

#include "vector.h"
#include <iostream>

template <typename T>
Vector<T>::Vector(size_t sz) : size_(sz), capacity_(0), content_(0) {
    capacity_ = (size_ == 0) ? defaultCapacity : size_;
    content_ = NewArray(capacity_);
}

template <typename T>
Vector<T>::Vector(size_t sz, const T &t) : size_(sz), capacity_(sz), content_(0) {
    content_ = NewArray(capacity_);
    for(size_t i = 0; i < size_; ++i) {
        content_[i] = t;
    }
}

// copy constructor
template <typename T>
Vector<T>::Vector(const Vector<T> & source) : size_(source.size_), capacity_(source.capacity_) {
    content_ = NewArray(capacity_);
    for(size_t i = 0; i < capacity_; ++i)
        content_[i] = source.content_[i];
}

// for assignment operator, we need to delete what is already there
// before reallocating and copying any data
template <typename T>
Vector<T> & Vector<T>::operator =(const Vector & source) {
    if( this != &source ) {

        if(source.capacity_ == 0) {
            // assigning an empty vector
            if(capacity_ > 0)
                delete [] content_;
            size_ = capacity_ = 0;
            content_ = 0;
            return *this;
        }

        // next, we want to set the capacity

        // this check could save us from having to allocate new storage
        if (capacity_ != source.capacity_) {
            if(capacity_ > 0)
                delete [] content_;
            capacity_ = source.capacity_;
            content_ = NewArray(capacity_);
        }

        // set size
        size_ = source.size_;

        // copy data
        for(size_t i = 0; i < size_; ++i)
            content_[i] = source.content_[i];
    }
    return *this;
}

template <typename T>
T & Vector<T>::operator [](size_t index) {
    // size_t is an unsigned type so we don't need to check if it's less than 0
    if( index >= size_) {
        std::cerr << "**  Error: Index Out of Bounds\n";
        if( index >= capacity_)
            // critical error and security risk; trying to index beyond the end of allocated memory
            exit(EXIT_FAILURE);
    }
    return content_[index];
}

template <typename T>
const T & Vector<T>::operator [](size_t index) const {
    // size_t is an unsigned type so we don't need to check if it's less than 0
    if( index >= size_) {
        std::cerr << "**  Error: Index Out of Bounds\n";
        if( index >= capacity_)
            // critical error and security risk; trying to index beyond the end of allocated memory
            exit(EXIT_FAILURE);
    }
    return content_[index];
}

template <typename T>
Vector<T>::~Vector() {
    delete [] content_;
    content_ = nullptr;
    size_ = capacity_ = 0;
}

// safe memory allocation for our vector
template <typename T>
T* Vector<T>::NewArray(size_t capacity) {
    T * newDataPtr;
    if(capacity > 0) {
        newDataPtr = new(std::nothrow) T[capacity];
        // std::nothrow prevents throwing an exception allowing us to handle the problem in the code below
        if (newDataPtr == 0) {
            std::cerr << "** Memory allocation for vector failed\n";
            exit(EXIT_FAILURE);
        }
    }
    else
        newDataPtr = 0;
    return newDataPtr;
}

template <typename T>
bool Vector<T>::SetSize(size_t newSize) {
    if( newSize > capacity_)
        if(!SetCapacity(newSize))
            return false;
    size_ = newSize;
    return true;
}

template <typename T>
bool Vector<T>::SetCapacity(size_t newCapacity) {
    if(newCapacity == 0) {
        delete [] content_;
        size_ = capacity_ = 0;
        content_ = nullptr;
        return true;
    }
    if(newCapacity != capacity_) {
        T *newContent = NewArray(newCapacity);
        if (newContent == 0)
            return false;
        if (size_ > newCapacity)
            size_ = newCapacity;
        for (size_t i = 0; i < size_; ++i)
            newContent[i] = content_[i];
        delete[] content_;
        content_ = newContent;
        capacity_ = newCapacity;
    }
    return true;
}

template <typename T>
size_t Vector<T>::Size() const {
    return size_;
}

template <typename T>
size_t Vector<T>::Capacity() const {
    return capacity_;
}

template <typename T>
void Vector<T>::Clear() {
    SetSize(0);
}

template <typename T>
void Vector<T>::Display(std::ostream & os, char ofc) const {
    for(size_t i = 0; i < size_; ++i)
        os << content_[i] << ofc;
    os << '\n';
}

template <typename T>
void Vector<T>::Dump(std::ostream & os) const {
    if( size_ == 0)
        std::cout << "[]\n";
    for(size_t i = 0; i < size_; ++i) {
        std::cout << '[' << i << "] = " << content_[i] << '\n';
    }
}

template < typename T >
std::ostream& operator << (std::ostream& os, const Vector<T>& v) {
    v.Display(os, ' ');
    return os;
}

template < typename T >
bool operator == (const Vector<T>& v1, const Vector<T>& v2) {
    if( v1.Size() != v2.Size())
        return false;

    for(size_t i = 0; i < v1.Size(); ++i) {
        if( v1[i] != v2[i])
            return false;
    }
    return true;
}

template < typename T >
bool operator != (const Vector<T>& v1, const Vector<T>& v2) {
    return !(v1 == v2);
}

