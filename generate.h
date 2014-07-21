#ifndef SIMULATED_SIMIAN_GENERATE_H_INCLUDED
#define SIMULATED_SIMIAN_GENERATE_H_INCLUDED

#include <iterator>

template <typename output_expr_t, typename range_itr_t, typename predictate_t>
struct generate_impl
{
    output_expr_t m_output_expr;
    range_itr_t m_range_from;
    range_itr_t m_range_to;
    predictate_t m_predictate;

    typedef typename range_itr_t::value_type value_t;

    generate_impl (output_expr_t output_expr, range_itr_t range_from, range_itr_t range_to, predictate_t predictate) :
        m_output_expr(output_expr), m_range_from(range_from), m_range_to(range_to), m_predictate(predictate)
    {
    }

    struct iterator
    {
        typedef std::input_iterator_tag iterator_category;
        typedef value_t value_type;
        typedef value_t difference_type;
        typedef value_t* pointer;
        typedef value_t& reference;

        generate_impl& gen;
        range_itr_t itr;

        value_t operator *()
        {
            return gen.m_output_expr (*itr);
        }

        iterator& operator++()
        {
            while (++itr != gen.m_range_to && !gen.m_predictate(*itr))
                ;
            return *this;
        }

        bool operator != (const iterator& that)
        {
            return itr != that.itr;
        }

        bool operator == (const iterator& that)
        {
            return itr == that.itr;
        }
    };

    iterator begin ()
    {
        auto itr = m_range_from;
        while (itr != m_range_to && !m_predictate(*itr))
            ++itr;

        return iterator{*this, itr};
    }

    iterator end ()
    {
        return iterator{*this, m_range_to};
    }


    template <typename collection_t>
    operator collection_t ()
    {
        collection_t c;
        for (auto i = m_range_from; i != m_range_to; ++i)
        {
            if (m_predictate(*i))
                c.push_back(m_output_expr(*i));
        }
        return c;
    }
    
};

template <typename value_t>
bool true_predictate (const value_t&) 
{
    return true;
}

template <typename output_expr_t, typename range_t, typename predictate_t>
auto generate (output_expr_t expr, const range_t& r, predictate_t p) 
                   -> generate_impl<output_expr_t, decltype (r.begin()), predictate_t>
{
    typedef decltype (r.begin()) range_itr_t;
    return generate_impl<output_expr_t, range_itr_t, predictate_t> (expr, r.begin(), r.end(), p);
}

template <typename output_expr_t, typename range_t>
auto generate (output_expr_t expr, const range_t& r) 
                   -> generate_impl<output_expr_t, decltype (r.begin()), 
                      decltype (&true_predictate<typename range_t::value_type>)>
{
    return generate(expr, r, true_predictate<typename range_t::value_type>);
}

#endif
