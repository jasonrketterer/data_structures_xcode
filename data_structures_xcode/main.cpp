//
//  main.cpp
//  data_structures_xcode
//
//  Created by Jason Ketterer on 4/30/22.
//

#include <iostream>
#include "vector.h"
#include "vector.cpp"

int main(int argc, const char * argv[]) {
    Vector<int> v;
    
    v.PushBack(1);
    v.PushBack(2); v.PushBack(3); v.PushBack(4); v.PushBack(5); v.PushBack(6); v.PushBack(7);
    std::cout << v;
    std::cout << "Size: " << v.Size() << "  Capacity: " << v.Capacity() << "\n\n";
    std::cout << "Front: " << v.Front() << "  Back: " << v.Back() << '\n';
    v.Clear();
    v.Front();
}
