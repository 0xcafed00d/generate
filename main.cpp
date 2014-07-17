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
    value_t m_inc;

    range_itr (value_t begin, value_t end, value_t increment) : m_begin (begin), m_end (end), m_inc (increment)
    {
    }

    struct iterator
    {
        value_t value;
        value_t increment;

        const value_t& operator *()
        {
            return value;
        }

        iterator& operator++()
        {
            value += increment;
            return *this;
        }

        bool operator != (const iterator& that)
        {
            if (increment < value_t())
                return that.value < value;
            else 
                return value < that.value;
        }
    };

    iterator begin ()
    {
        return iterator{m_begin, m_inc};
    }

    iterator end ()
    {
        return iterator{m_end, m_inc};
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
inline range_itr<value_t> range (value_t begin, value_t end, value_t increment)
{
    return range_itr<value_t> (begin, end, increment);
}

template <typename value_t>
inline range_itr<value_t> range (value_t begin, value_t end)
{
    if (end < begin)
        return range_itr<value_t> (begin, end, -value_t(1));
    else
        return range_itr<value_t> (begin, end, value_t(1));
}

template <typename value_t>
inline range_itr<value_t> range (value_t end)
{
    return range (value_t(0), end);    
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
            return *this;
        }

        bool operator != (const iterator& that)
        {
            return value != that.value;
        }
    };

    iterator begin ()
    {
        return iterator{};
    }

    iterator end ()
    {
        return iterator{};
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
    for (auto n : range(0.0, 10.0, 1.1))
    {
        std::cout << n << std::endl;
    }
    
    std::list<double> x = range(200.0, 190.0, -0.9);

    for (auto n : x)
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
