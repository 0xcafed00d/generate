#ifndef SIMULATED_SIMIAN_RANGE_H_INCLUDED
#define SIMULATED_SIMIAN_RANGE_H_INCLUDED

#include <iterator>

template <typename value_t>
struct range_impl
{
    typedef value_t value_type;

    value_t m_begin;
    value_t m_end;
    value_t m_inc;

    range_impl (value_t begin, value_t end, value_t increment) 
        : m_begin (begin), m_end (end), m_inc (increment)
    {
    }

    struct iterator
    {
        typedef std::input_iterator_tag iterator_category;
        typedef value_t value_type;
        typedef value_t difference_type;
        typedef value_t* pointer;
        typedef value_t& reference;
    
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

        bool operator == (const iterator& that)
        {
            return !(*this += that);
        }
    };

    iterator begin () const 
    {
        return iterator{m_begin, m_inc};
    }

    iterator end () const
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
inline range_impl<value_t> range (value_t begin, value_t end, value_t increment)
{
    return range_impl<value_t> (begin, end, increment);
}

template <typename value_t>
inline range_impl<value_t> range (value_t begin, value_t end)
{
    if (end < begin)
        return range_impl<value_t> (begin, end, -value_t(1));
    else
        return range_impl<value_t> (begin, end, value_t(1));
}

template <typename value_t>
inline range_impl<value_t> range (value_t end)
{
    return range (value_t(0), end);    
}

#endif
