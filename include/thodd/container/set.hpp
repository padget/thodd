#ifndef __THODD_CONTAINER_SET_HPP__
#  define __THODD_CONTAINER_SET_HPP__

#  include <thodd/container/list.hpp>
#  include <thodd/container/dsl.hpp>

namespace thodd
{
      template<
        typename item_t>
    class set final
    {
        list<item_t> m_content;


    public:
        using set_iterator = typename list<item_t>::iterator_type;
        using iterator_type = set_iterator;


    public:
        inline auto const
        begin() const
        {
            return m_content.begin();
        }


        inline auto
        begin()
        {
            return m_content.begin();
        }


        inline auto const
        end() const
        {
            return m_content.end();
        }


        inline auto
        end()
        {
            return m_content.end();
        }
    
    public:
        inline auto const
        size() const
        {
            return m_content.size();
        }


    public:
        inline void
        clear()
        {
            m_content.clear();
        }


    public:
        ~set() { this->clear(); }
        set() = default;

    public:
        set(
            set const& __other) :
            m_content(__other.m_content) {}


        set(
            set&& __other) : 
            m_content(thodd::rvalue(__other.m_content)) {}


        set(
            std::initializer_list<item_t>&& __init)
        {
            for(auto&& __item : __init)
                thodd::push_back(*this, thodd::rvalue(__item));
        }


    public:
        template<
            typename iterator_t>
        set(
            detail::range<iterator_t> const& __range)
        {
            for(auto&& __item : __range)
                thodd::push_back(*this, __item);   
        }

        
        set(
            auto __begin, 
            auto __end) :
            set(thodd::range(__begin, __end)) {}
    
    
    public:
        inline set& 
        operator = (
            set const& __other) 
        {
            if(this != &__other)
                m_content = __other.m_content;

            return *this;
        }

        
        inline set& 
        operator = (
            set&& __other) 
        {
            if(this != &__other)
                m_content = thodd::rvalue(__other.m_content);

            return *this;
        }


        inline set& 
        operator = (
            std::initializer_list<item_t>&& __init)
        {
            this->clear();

            for(auto&& __item : __init)
                thodd::push_back(*this, thodd::rvalue(__item));
        
            return *this;
        }


        template<
            typename iterator_t>
        inline set&
        operator = (
            detail::range<iterator_t> const& __range) 
        {
            this->clear();
            
            for(auto&& __item : __range)
                thodd::push_back(*this, __item);

            return *this;
        }
       


    public:
        inline void
        push_at(
            auto&& __item)
        {
            using namespace contdsl; 
            
            auto __pos = this->end();

            go<query>(
                with($0) 
                > first($1) 
                > where($0 == cref(perfect<decltype(__item)>(__item))), 
                *this, __pos);

            if(__pos != end())
                *__pos = perfect<decltype(__item)>(__item);
            else
                m_content.push_at(perfect<decltype(__item)>(__item), __pos);
        }


        inline void
        push_at(
            auto&& __item,
            set_iterator)
        {
            this->push_at(perfect<decltype(__item)>(__item));
        }


        inline set_iterator
        pop_at(
            set_iterator _pos)
        {
            return m_content.pop_at(_pos);
        }
    };
}

#endif