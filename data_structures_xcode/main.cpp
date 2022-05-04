//
//  main.cpp
//  data_structures_xcode
//
//  Created by Jason Ketterer on 4/30/22.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <map>
#include "vector.h"
#include "vector.cpp"

std::list<int> * foo(int x) {
    std::list<int> * l = new std::list<int>{};
    //l->push_back(x);
    return l;
}

std::list< std::list<int> * > foo2() {
    std::list< std::list<int> * > null;
    null.push_back(nullptr);
    return null;
}

std::list< std::list<int> * > findWays(int steps, std::vector<int> & hops) {
    if(steps < 0) {
        std::list< std::list<int> * > null;
        null.push_front(nullptr);
        return null;
    }
    if(steps == 0) {
        std::list< std::list<int> * > empty;
        empty.push_front(new std::list<int>{});
        return empty;
    }
    for(int i = 0; i < hops.size(); ++i) {
        std::list< std::list<int> * > result;
        result = findWays(steps - hops[i], hops);
        if(result.front()->empty()) {
            result.front()->push_back(hops[i]);
            return result;
        }
        if(result.front() != nullptr) {
            
        }
    }
    std::list< std::list<int> * > null;
    null.push_back(nullptr);
    return null;
}

void printPrimesBelow(int n) {
    std::vector<int> primes(n,1);
    
    int stop = sqrt(n);
    int start = 2;
    while(start <= stop) {
        for(int i = 2 * start; i <= n; i += start) {
            primes[i] = 0;
        }
        for(++start; start <= stop; ++start) {
            if(primes[start])
                break;
        }
    }
    for(int i = 2; i < n; ++i) {
        if(primes[i])
            std::cout << i << '\n';
    }
}

int fairArrays(std::vector<int> & nums) {
    int numFair = 0;
    size_t n = nums.size();
    
    // r[0] = even sum of nums[i+1 ... n]
    // r[1] = odd sum of nums[i+1 ... n]
    // l[0] = even sum of nums[0...i)
    // l[1] = odd sum of nums[0...i)
    std::vector<int> r(2);
    std::vector<int> l(2);
    
    // initialize r with even/odd sums of nums[0...n]
    for(int i = 0; i < n; ++i)
        r[i % 2] += nums[i];
    
    // whenever we remove an element, the oddsum of elements to the right of i become
    // part of the even sum and the evensum elements become part of the odd sum
    for(int i = 0; i < n; ++i) {
        r[i % 2] -= nums[i];
        if(l[0] + r[1] == l[1] + r[0]) ++numFair;
        l[i % 2] += nums[i];
    }
    return numFair;
}


int main(int argc, const char * argv[]) {
    std::vector<int> hops = {1,2,3};
    std::list< std::list<int> * > result;
    
    std::vector<int> nums = {1,2,3};
    std::cout << fairArrays(nums) << '\n';
}
