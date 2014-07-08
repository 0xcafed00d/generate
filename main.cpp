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
    
    template <typename collection_t> 
    operator collection_t ()
    {
        collection_t c;
        for (auto n : *this)
        {
            c.push_back(n);
        }
        return c;        
    }
};

int main ()
{
    for (int n : range<int>(0, 10))
    {
        std::cout << n << std::endl;
    }
    std::vector<int> x = range<int>(100, 110);

    for (int n : x)
    {
        std::cout << n << std::endl;
    }

}
