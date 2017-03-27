#ifndef __THODD_CONTAINER_RANGE_HPP__
#  define __THODD_CONTAINER_RANGE_HPP__

#  include <thodd/container/iterator_traits.hpp>
#  include <thodd/meta/value.hpp>

#  include <thodd/core/rvalue.hpp>
#  include <thodd/core/perfect.hpp>
#  include <thodd/meta/traits/decay.hpp>

#  include <initializer_list>

namespace thodd
{
    namespace detail
    {
          template<
            typename iterator_t>
        class range
        {            
            iterator_t m_begin;
            iterator_t m_end;

            using iterator_type = iterator_t;
            using value_type = meta::__value_type<iterator_traits<iterator_t>>;

        public:
            inline auto const
            size()
            {
                size_t __size{0u};
                auto __cursor = m_begin;

                while(__cursor != m_end)
                {
                    ++__cursor;
                    ++__size;
                }

                return __size;
            }

        public:
            inline auto 
            begin() 
            {
                return m_begin;
            }

            inline auto const
            begin() const
            {
                return m_begin;
            }

            inline auto 
            end() 
            {
                return m_end;
            }

            inline auto const
            end() const
            {
                return m_end;
            }

        public:
            range() = default;
            range(range const&) = default;
            range(range&&) = default;
            ~range() = default;
            range& operator=(range const&) = default;
            range& operator=(range&&) = default;
        
        public: 
            range(
                iterator_type __begin, 
                iterator_type __end) :
                m_begin{rvalue(__begin)},
                m_end{rvalue(__end)} {}

            template<
                typename container_t>
            range(
                container_t&& __c) :
                range(perfect<container_t>(__c).begin(), 
                      perfect<container_t>(__c).end()) {}
        };
    }

    inline auto
    range(
        auto __begin, 
        auto __end)
    {
        return detail::range<
                meta::decay_t<decltype(__begin)>>
                {__begin, __end};
    }

    template<
        typename container_t>
    inline auto
    range(
        container_t&& __c)
    {
        return range(perfect<container_t>(__c).begin(), 
                     perfect<container_t>(__c).end());
    }

    template<
        typename item_t>
    inline auto
    range(
        std::initializer_list<item_t> const& __init)
    {
        return range(__init.begin(), 
                     __init.end());
    }

}

#endif