#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>

template <typename value_t> 
struct range_itr 
{
    typedef value_t value_type;

    value_t m_begin;
    value_t m_end;
    bool m_reverse;

    range_itr (value_t begin, value_t end) : m_begin (begin), m_end (end)
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


template <typename value_t>
inline range_itr<value_t> range (value_t begin, value_t end)
{
    return range_itr<value_t> (begin, end);
} 

template <typename value_t>
inline range_itr<value_t> range (value_t end)
{
    return range_itr<value_t> (0, end);
} 

template <typename output_expr_t, typename range_t, typename predictate_t>
struct generate_itr
{
    output_expr_t m_output_expr; 
    range_t m_range;
    predictate_t m_predictate; 
    
    typedef typename range_t::value_type value_t;

    generate_itr (output_expr_t output_expr, range_t range, predictate_t predictate) :
        m_output_expr(output_expr), m_range(range), m_predictate(predictate)
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
        for (auto n : m_range)
        {
            if (m_predictate(n)) 
                c.push_back(m_output_expr(n));
        }
        return c;        
    } 
};

template <typename output_expr_t, typename range_t, typename predictate_t>
generate_itr<output_expr_t, range_t, predictate_t> generate (output_expr_t expr, range_t r, predictate_t p)
{
    return generate_itr<output_expr_t, range_t, predictate_t> (expr, r, p);
}                                                     

int main ()
{
    for (int n : range(10))
    {
        std::cout << n << std::endl;
    }
    std::list<int> x = range(200, 190);

    for (int n : x)
    {
        std::cout << n << std::endl;
    }
    
    std::vector<int> test = generate ([](int x){ return x * 2;}, range (10), [](int x){ return x & 1; });

    for (int n : test)
    {
        std::cout << n << std::endl;
    }
}
    