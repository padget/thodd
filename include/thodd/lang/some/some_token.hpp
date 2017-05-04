#ifndef __THODD_LANG_SOME_SOME_TOKEN_HPP__
#  define __THODD_LANG_SOME_SOME_TOKEN_HPP__

#  include <thodd/container/range.hpp>
#  include <thodd/container/list.hpp>

#  include <thodd/core/infinity.hpp>
#  include <thodd/core/size_t.hpp>
#  include <thodd/core/perfect.hpp>
#  include <thodd/core/rvalue.hpp>
#  include <thodd/core/begin.hpp>
#  include <thodd/core/end.hpp>

#  include <thodd/meta/traits/decay.hpp>

#  include <thodd/lang/core/core.hpp>

namespace 
thodd::lang
{
    template<
        typename iterator_t>
    class some_token:
        public token<iterator_t>
    {
        using range_t = typename token<iterator_t>::range_t;
        using subranges_t = typename token<iterator_t>::subranges_t;
        
        size_t min{0u}; 
        size_t max{thodd::infinity};

    public:
        constexpr 
        some_token() = default;
        
        constexpr 
        some_token(some_token const&) = default;
        
        constexpr 
        some_token(some_token&&) = default;
        virtual ~some_token() = default;

    public:
        constexpr some_token& 
        operator = (some_token const&) = default;
        
        constexpr some_token& 
        operator = (some_token&&) = default;

    public:
        constexpr 
        some_token(
            range_t const& __range, 
            subranges_t const& __subranges) :
            token<iterator_t>(
                __range, 
                __subranges) {}

        constexpr 
        some_token(
            range_t&& __range, 
            subranges_t&& __subranges) :
            token<iterator_t>(
                rvalue(__range), 
                rvalue(__subranges)) {}
        
        constexpr 
        some_token(
            range_t const& __range, 
            subranges_t&& __subranges) :
            token<iterator_t>(
                __range, 
                rvalue(__subranges)) {}

        constexpr 
        some_token(
            range_t&& __range,
            subranges_t const& __subranges) :
            token<iterator_t>(
                rvalue(__range), 
                __subranges) {} 

    public:
        some_token& 
        operator () (
            size_t const& __min, 
            size_t const& __max) const
        {
            this->min = __min;
            this->max = __max;
            
            return *this;
        }     

    public:
        virtual
        operator bool () const
        {
            return 
            thodd::between(
                this->subsize(), 
                min, max);
        }
    };

    constexpr auto
    make_some_token(
        auto&& __begin, 
        auto&& __end, 
        auto&& __subranges, 
        size_t const& __min, 
        size_t const& __max)
    {
        using iterator_t = meta::decay_t<decltype(__begin)>;

        return  
        some_token<iterator_t>(
            thodd::range(
                perfect<decltype(__begin)>(__begin),
                perfect<decltype(__end)>(__end)),
            perfect<decltype(__subranges)>(__subranges))
        (__min, __max);
    }
}

#endif 