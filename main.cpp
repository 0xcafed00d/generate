
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
#include <cctype>


#include "range.h"
#include "generate.h"


template <typename collection_t>
void dump_collection (const collection_t& c)
{
    for (auto n : c)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}


int main ()
{
    dump_collection (range(0.0, 10.0, 1.1));


    std::list<double> x = range(200.0, 190.0, -0.9);

    dump_collection (x);

    auto r = range(10);

    std::vector<int> v (r.begin(), r.end());
    dump_collection (v);

    std::vector<int> test = generate ([](int x){ return x * x;}, range (10), [](int x){ return x & 1; });

    dump_collection (test);

    for (auto n : generate ([](int x){ return x * x;}, test))
    {
        std::cout << n << " ";
    }
    
    std::string s = generate ([](char c){return std::toupper(c);}, std::string("hello world"), 
                              [](char c){return c != ' ';});    

    std::cout << std::endl << s << std::endl;
    
}
