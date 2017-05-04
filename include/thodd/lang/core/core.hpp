#ifndef __THODD_LANG_CORE_HPP__
#  define __THODD_LANG_CORE_HPP__

#  include <thodd/core/rvalue.hpp>
#  include <thodd/core/perfect.hpp>
#  include <thodd/core/destroy.hpp>
#  include <thodd/core/begin.hpp>
#  include <thodd/core/end.hpp>

#  include <thodd/meta/traits/decay.hpp>

#  include <thodd/container/range.hpp>
#  include <thodd/container/list.hpp>

#  include <thodd/functional/functional.hpp>

namespace 
thodd::lang
{
    template<
        typename iterator_t>
    class token;

    template<
        typename iterator_t>
    class token_data
    {
        using range_t = thodd::detail::range<iterator_t>;
        using subranges_t = thodd::list<token*>;

        range_t range;
        subranges_t subranges;

    public:
        constexpr 
        token_data() = default;
        
        constexpr 
        token_data(token_data const&) = default;
        
        constexpr 
        token_data(token_data&&) = default;
        
        virtual ~token()  
        {
            for(auto* __range : subranges)
                thodd::destroy(__range);
        }
    
    public:
        constexpr token_data& 
        operator = (token_data const&) = default;
        
        constexpr token_data& 
        operator = (token_data&&) = default;

    public:
        constexpr 
        token_data(
            range_t const& __range) :
            range(__range) {}

        constexpr 
        token_data(
            range_t&& __range) :
            range(rvalue(__range)) {}

    public:
        constexpr 
        token_data(
            range_t const& __range, 
            subranges_t const& __subranges) :
            range(__range), 
            subranges(__subranges) {}

        constexpr 
        token_data(
            range_t&& __range, 
            subranges_t&& __subranges) :
            range(rvalue(__range)), 
            subranges(rvalue(__subranges)) {}

        constexpr 
        token_data(
            range_t const& __range, 
            subranges_t&& __subranges) :
            range(__range), 
            subranges(rvalue(__subranges)) {}

        constexpr 
        token_data(
            range_t&& __range,
            subranges_t const& __subranges) :
            range(rvalue(__range)), 
            subranges(__subranges) {}
    };


    /// Basic token with
    /// no special information
    template<
        typename iterator_t>
    class token
    {
        token_data* data;

    public:
        constexpr 
        token() = default;
        
        constexpr 
        token(token const&) = default;
        
        constexpr 
        token(token&&) = default;
        
        virtual ~token()  
        {
            thodd::destroy(data);
        }
    
    public:
        constexpr token& 
        operator = (token const&) = default;
        
        constexpr token& 
        operator = (token&&) = default;

    public:
        constexpr 
        token(
            range_t const& __range) :
            range(__range) {}

        constexpr 
        token(
            range_t&& __range) :
            range(rvalue(__range)) {}

    public:
        constexpr 
        token(
            range_t const& __range, 
            subranges_t const& __subranges) :
            range(__range), 
            subranges(__subranges) {}

        constexpr 
        token(
            range_t&& __range, 
            subranges_t&& __subranges) :
            range(rvalue(__range)), 
            subranges(rvalue(__subranges)) {}

        constexpr 
        token(
            range_t const& __range, 
            subranges_t&& __subranges) :
            range(__range), 
            subranges(rvalue(__subranges)) {}

        constexpr 
        token(
            range_t&& __range,
            subranges_t const& __subranges) :
            range(rvalue(__range)), 
            subranges(__subranges) {}

    public:
        virtual 
        operator bool() const
        {
            return 
            range.begin() != range.end();
        }

        inline auto const
        begin() const
        {
            return 
            range.begin();
        }

        inline auto
        begin()
        {
            return 
            range.begin();
        }

        inline auto const
        end() const
        {
            return 
            range.end();
        }

        inline auto
        end()
        {
            return 
            range.end();
        }

        inline auto const
        subbegin() const
        {
            return 
            thodd::begin(subranges);
        }

        inline auto
        subbegin()
        {
            return
            thodd::begin(subranges);
        }

        inline auto const
        subend() const
        {
            return 
            thodd::end(subranges);
        }

        inline auto
        subend()
        {
            return  
            thodd::end(subranges);
        }

    public:
        constexpr auto
        subsize()
        {
            return
            subranges.size();
        }
    };


    /// Make a basic token
    constexpr auto
    make_token(
        auto&& __begin,
        auto&& __end)
    {
        using iterator_t = meta::decay_t<decltype(__begin)>;

        return
        token<iterator_t>
        { thodd::range(
            perfect<decltype(__begin)>(__begin),
            perfect<decltype(__end)>(__end)) };
    }


    // extern constexpr auto interpret_ = 
    //     [] (auto&& __case_getter, 
    //         auto&& __token_getter)
    //     {
    //         return 
    //         as_functor(
    //             [&] (auto&& ... __args)
    //             {
    //                 return 
    //                 interpret(
    //                     __case_getter(perfect<decltype(__args)>(__args)...), 
    //                     __token_getter(perfect<decltype(__args)>(__args)...));
    //             });
    //     };
}

#endif