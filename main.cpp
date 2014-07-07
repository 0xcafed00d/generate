#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

template <value_t> 
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
        const& value_t operator *()
        {
            return value;
        } 
        
        iterator& operator++()
        {
            ++value;
        }
    }
    
    iterator cbegin ()
    {
        return iterator{m_begin};
    } 
    
    iterator cend ()
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
}
