#ifndef __THODD_CONTAINER_MAP_HPP__
#  define __THODD_CONTAINER_MAP_HPP__


#  include <thodd/law.hpp>
#  include <thodd/meta.hpp>
#  include <thodd/functional.hpp>
#  include <thodd/require.hpp>

#  include <thodd/container_set.hpp>

namespace thodd
{
    template<
        typename key_t,
        typename value_t>
    struct entry
    {
        key_t key;
        value_t value;
    };
    
    template<
        typename key_t, 
        typename value_t>
    inline bool const
    operator == (
        entry<key_t, value_t> const& __le,
        entry<key_t, value_t> const& __re)
    {
        return __le.key == __re.key;
    }


    template<
        typename key_t, 
        typename value_t>
    inline bool const
    operator != (
        entry<key_t, value_t> const& __le,
        entry<key_t, value_t> const& __re)
    {
        return !(__le.key == __re.key);
    }


    template<
        typename key_t, 
        typename value_t>
    inline bool const
    operator < (
        entry<key_t, value_t> const& __le,
        entry<key_t, value_t> const& __re)
    {
        return __le.key < __re.key;
    }



    template<
        typename key_t,
        typename value_t>
    class map final
    {
       
        set<entry<key_t, value_t>> m_content;


    public:
        using map_iterator = typename set<entry<key_t, value_t>>::iterator_type;
        using iterator_type = map_iterator;

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
        inline size_t const
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
        ~map() { this->clear(); }
        map() = default;

    public:
        map(
            map const& __other) :
            m_content(__other.m_content) {}


        map(
            map&& __other) : 
            m_content(thodd::rvalue(__other.m_content)) {}


        map(
            std::initializer_list<entry<key_t, value_t>>&& __init)
        {
            for(auto&& __item : __init)
                thodd::push_back(*this, thodd::rvalue(__item));
        }


    public:
        template<
            typename iterator_t>
        map(
            detail::range<iterator_t> const& __range)
        {
            for(auto&& __item : __range)
                thodd::push_back(*this, __item);   
        }

        
        map(
            auto __begin, 
            auto __end) :
            map(thodd::range(__begin, __end)) {}
    
    
    public:
        inline map& 
        operator = (
            map const& __other) 
        {
            if(this != &__other)
                m_content = __other.m_content;

            return *this;
        }

        
        inline map& 
        operator = (
            map&& __other) 
        {
            if(this != &__other)
                m_content = thodd::rvalue(__other.m_content);

            return *this;
        }


        inline map& 
        operator = (
            std::initializer_list<entry<key_t, value_t>>&& __init)
        {
            this->clear();

            for(auto&& __item : __init)
                thodd::push_back(*this, thodd::rvalue(__item));
        
            return *this;
        }


        template<
            typename iterator_t>
        inline map&
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
            entry<key_t, value_t> const& __entry)
        {
            using namespace contdsl; 

            m_content.push_at(__entry);

            go<query>(with($0) > sort(asc), m_content);
        }

        inline void 
        push_at(
            entry<key_t, value_t> const& __entry, 
            iterator_type __pos)
        {
            this->push_at(__entry);
        }

        inline void
        pop_at(
            iterator_type __pos)
        {
            m_content.pop_at(__pos);
        }


        inline void
        pop_at(
            key_t const& __key)
        {
            using namespace contdsl;

            auto __pos = this->end();

            go<query>(
                with(ref(*this)) 
                > first(ref(__pos)) 
                > where([&__key](entry<key_t, value_t> const& __item){return __item.key == __key;}));

            this->pop_at(__pos);
        }
    };
}

#endif