#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>

#include "range.h"
#include "generate.h"


template <typename collection_t>
void dump_collection (const collection_t& c)
{
    for (auto n : c)
    {
        std::cout << n << std::endl;
    }   
}


int main ()
{
    dump_collection (range(0.0, 10.0, 1.1));

    
    std::list<double> x = range(200.0, 190.0, -0.9);

    dump_collection (x);
    
    auto r = range(10);
    
    std::vector<int> v (r.begin(), r.end());
    dump_collection (v);
    
/*
    std::vector<int> test = generate ([](int x){ return x * 2;}, range (10), [](int x){ return x & 1; });

    for (int n : test)
    {
        std::cout << n << std::endl;
    }
    */
}
