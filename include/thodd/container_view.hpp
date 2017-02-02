#ifndef __THODD_CONTAINER_VIEW_HPP__
#  define __THODD_CONTAINER_VIEW_HPP__

#  include <thodd/law.hpp>
#  include <thodd/meta.hpp>
#  include <thodd/functional.hpp>
#  include <thodd/require.hpp>

#  include <thodd/container_iterator_traits.hpp>
#  include <thodd/container_range.hpp>
#  include <thodd/container_dsl.hpp>
#  include <thodd/container_func.hpp>

#  include <thodd/container_list.hpp>

namespace thodd
{
    template<
        typename item_t, 
        template<typename> 
        typename container_t = list>
    struct view_iterator
    {
        using value_type = item_t;
        using iterator_t = typename container_t<item_t*>::iterator_type;

        iterator_t iter;
    };


    template<
        typename item_t, 
        template<typename> 
        typename container_t = list>
    inline auto&
    operator*(
        view_iterator<item_t, container_t>& __iter)
    {
        return **__iter.iter;
    }


    template<
        typename item_t, 
        template<typename> 
        typename container_t = list>
    inline auto const&
    operator*(
        view_iterator<item_t, container_t> const& __iter)
    {
        return **__iter.iter;
    }

    template<
        typename item_t, 
        template<typename> 
        typename container_t = list>
    inline auto&
    operator++(
        view_iterator<item_t, container_t>& __iter)
    {
        ++__iter.iter;
        return __iter;
    }

    template<
        typename item_t, 
        template<typename> 
        typename container_t = list>
    inline auto const&
    operator++(
        view_iterator<item_t, container_t> const& __iter)
    {
        ++__iter.iter;
        return __iter;
    }

    template<
        typename item_t, 
        template<typename> 
        typename container_t = list>
    inline auto&
    operator--(
        view_iterator<item_t, container_t>& __iter)
    {	
        --__iter.iter;
        return __iter;
    }

    template<
        typename item_t, 
        template<typename> 
        typename container_t = list>
    inline auto const&    
    operator--(
        view_iterator<item_t, container_t> const& __iter)
    {	
        --__iter.iter;
        return __iter;
    }


    template<
        typename item_t, 
        template<typename> 
        typename container_t = list>
    inline auto const
    operator == (
        view_iterator<item_t, container_t> const& __liter,
        view_iterator<item_t, container_t> const& __riter)
    {
        return __liter.iter == __riter.iter;
    }


    template<
        typename item_t, 
        template<typename> 
        typename container_t = list>
    inline auto const
    operator!=(
        view_iterator<item_t, container_t> const& __liter,
        view_iterator<item_t, container_t> const& __riter)
    {
        return !(__liter == __riter);
    }    


    namespace detail
    {
        template<
            typename item_t, 
            template<typename> 
            typename container_t = list>
        class view final 
        {
            container_t<item_t*> m_content;
            using iterator_type = view_iterator<item_t, container_t>;

        public:
            inline auto
            begin()
            {
                return iterator_type(m_content.begin());
            }

            inline auto const
            begin() const
            {
                return iterator_type(m_content.begin());
            }

            inline auto
            end()
            {
                return iterator_type(m_content.end());
            }

            inline auto const
            end() const
            {
                return iterator_type(m_content.end());
            }

        public:
            
            inline size_t const
            size() const
            {
                return m_content.size();
            }

            inline void
            clear()
            {
                m_content.clear();
            }

        public:
            ~view() = default;
            view() = default;
           

        public:
            view(
                view const& __other) :
                m_content(__other.m_content) {}


            view(
                view&& __other) : 
                m_content(thodd::rvalue(__other.m_content)) {}


        public:
            template<
                typename iterator_t>
            view(
                detail::range<iterator_t> const& __range)
            {
                for(auto&& __item : __range)
                    thodd::push_back(*this, __item);   
            }

            
            view(
                auto __begin, 
                auto __end) :
                view(thodd::range(__begin, __end)) {}
        
        
        public:
            inline view& 
            operator = (
                view const& __other) 
            {
                if(this != &__other)
                    m_content = __other.m_content;

                return *this;
            }

            
            inline view& 
            operator = (
                view&& __other) 
            {
                if(this != &__other)
                    m_content = thodd::rvalue(__other.m_content);

                return *this;
            }


            template<
                typename iterator_t>
            inline view&
            operator = (
                detail::range<iterator_t> const& __range) 
            {
                this->clear();
                
                for(auto&& __item : __range)
                    thodd::push_back(*this, __item);

                return *this;
            }

    
        public:
            inline auto
            push_at(
                item_t& __item,
                iterator_type __pos)
            {
                return m_content.push_at(&__item, __pos.iter());
            }

            inline auto
            push_at(
                item_t&& __item,
                iterator_type __pos)
            {
                return m_content.push_at(&__item, __pos.iter());
            }


            inline auto
            pop_at(
                iterator_type __pos)
            {
                return m_content.pop_at(__pos.iter());
            }
        };
    }

    inline auto
    view(
        auto&& __container)
    {
        using item_t = typename meta::decay<decltype(__container)>::value_type;

        auto __begin = perfect<decltype(__container)>(__container).begin();
        auto __end   = perfect<decltype(__container)>(__container).end();

        return detail::view<item_t>(__begin, __end);
    }
}

#endif