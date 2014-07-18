#ifndef SIMULATED_SIMIAN_GENERATE_H_INCLUDED
#define SIMULATED_SIMIAN_GENERATE_H_INCLUDED

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


#endif