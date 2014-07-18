#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>

#include "range.h"
#include "generate.h"


int main ()
{
    for (auto n : range(0.0, 10.0, 1.1))
    {
        std::cout << n << std::endl;
    }
    
    std::list<double> x = range(200.0, 190.0, -0.9);

    for (auto n : x)
    {
        std::cout << n << std::endl;
    }


    auto r = range(10);
    
    std::vector<int> v (r.begin(), r.end());
    for (auto n : v)
    {
        std::cout << n << std::endl;
    }


/*
    std::vector<int> test = generate ([](int x){ return x * 2;}, range (10), [](int x){ return x & 1; });

    for (int n : test)
    {
        std::cout << n << std::endl;
    }
    */
}
