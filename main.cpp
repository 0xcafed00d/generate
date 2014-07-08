#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

template <typename value_t> 
struct range 
{
    value_t m_begin;
    value_t m_end;
    bool m_reverse;

    range (value_t begin, value_t end) : m_begin (begin), m_end (end)
    {
        m_reverse = m_end < m_begin;
    }

    range (value_t end) : m_begin (value_t()), m_end (end)
    {
        m_reverse = m_end < m_begin;
    }
    
    struct iterator 
    {
        value_t value;
        bool reverse;
        const value_t& operator *()
        {
            return value;
        } 
        
        iterator& operator++()
        {
            if (reverse)
                --value;
            else
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
        return iterator{m_begin, m_reverse};
    } 
    
    iterator end ()
    {
        return iterator{m_end, m_reverse};
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
    for (int n : range<int>(10))
    {
        std::cout << n << std::endl;
    }
    std::vector<int> x = range<int>(200, 190);

    for (int n : x)
    {
        std::cout << n << std::endl;
    }

}
