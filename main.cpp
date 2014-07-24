
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

template <typename collection_t>
struct as_ref_impl
{
    const collection_t& col;
    
    as_ref_impl (const collection_t& c) : col(c) {}
    
    typedef typename collection_t::value_type value_type;
    typedef decltype (col.begin()) iterator;
    
    iterator begin() 
    {
        return col.begin();
    }
    
    iterator end()
    {
        return col.end();
    } 
};

template <typename collection_t>
as_ref_impl<collection_t> as_ref (const collection_t& v)
{
    return as_ref_impl<collection_t>{v};
}

void reftest ()
{
/*
    std::cout << "----------------" << std::endl;
    
    auto t1 = range(10);
    auto t2 = as_ref(range(10));
    
    std::cout << typeid(t1).name() << std::endl;   
    std::cout << typeid(t2).name() << std::endl;
    
    for (auto n : t2)
    {
        std::cout << n << " ";
    }
    
 */    
    std::cout << std::endl << "----------------" << std::endl;
 
    {       
        range_impl<int> r = range(5);
    
        for (auto n : generate ([](int x){ return x * x;}, as_ref(r)))
        {
            std::cout << n << std::endl;
        }
    }

    std::cout << std::endl << "----------------" << std::endl;

    {       
        range_impl<int> r = range(5);
    
        for (auto n : generate ([](int x){ return x * x;}, r))
        {
            std::cout << n << std::endl;
        }
    }

    std::cout << std::endl << "----------------" << std::endl;

}

int main ()
{
    reftest();

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
    
    auto gs = generate ([](char c){return std::toupper(c);}, std::string("hello world"), 
                        [](char c){return c != ' ';});    

    std::string s = gs;

    std::cout << std::endl << s << std::endl;
    
}
