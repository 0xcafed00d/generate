#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

template <typename value_t> 
struct range 
{
    value_t m_begin;
    value_t m_end;

    range (value_t begin, value_t end) : m_begin (begin), m_end (end)
    {
    }
    
    struct iterator 
    {
        value_t value;
        const value_t& operator *()
        {
            return value;
        } 
        
        iterator& operator++()
        {
            ++value;
            return *this;
        }
        
        bool operator != (const iterator& that)
        {
            return value != that.value;
        }
    };
    
    iterator begin ()
    {
        return iterator{m_begin};
    } 
    
    iterator end ()
    {
        return iterator{m_end};
    }
};

int main ()
{
    for (int n : range<int>(0, 10))
    {
        std::cout << n << std::endl;
    }
    auto r = range<int>(0, 8);
 //   std::vector<int> x(r.begin(), r.end());  
}
