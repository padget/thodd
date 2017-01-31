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
        using map_iterator = typename set<entry>::set_iterator;
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
        ~map() = default;
        map() = default;
        map(map&&) = default;
        map& operator=(map&&) = default;


    public:
        template<
            typename iterator_t>
        map(
            detail::range<iterator_t> const& __range)
        {
            using namespace contdsl;

            go<query>(copy, __range, *this);
        } 


        template<
            typename iterator_t>
        map(
            iterator_t __begin,
            iterator_t __end) :
            map{ range(__begin, __end) } {}


        template<
            typename container_t>
        map(
            container_t& __container) : 
            map{ range(__container.begin(), 
                       __container.end()) } {}

        map(
            map const& __container) : 
            map{ range(__container.begin(), 
                       __container.end()) } {}


        map(
            std::initializer_list<entry>&& __init) :
            map{ range(__init.begin(), 
                       __init.end()) } {}


        template<
            typename container_t>
        map(
            container_t&& __container)
        {
            auto&& __end = end();

            for(auto&& __item : __container)
                this->push_at(rvalue(__item), __end);
        }

    public:
        template<
            typename iterator_t>
        map&
        operator= (
            detail::range<iterator_t> const& __range)
        {
            using namespace contdsl;

            this->clear();
            go<query>(copy, __range, *this);
            
            return *this;
        }
        

        map&
        operator= (
            map const& __other)
        {
            return &__other != this ? 
                        (*this) = range(this->begin(), 
                                        this->end()) :
                        *this;
        }

        
        template<
            typename container_t>
        map&
        operator=(
            container_t& __container)
        {
            return (*this) = range(__container.begin(), 
                                   __container.end());
        }


        map&
        operator=(
            std::initializer_list<entry> __range)
        {
            return (*this) = range(__range.begin(), __range.end());
        }


        template<
            typename container_t>
        map&
        operator=(
            container_t&& __container)
        {
            this->clear();
            auto&& __end = this->end();

            for(auto&& __item : __container)
                this->push_at(rvalue(__item), __end);

            return *this;
        }


    public:
        inline iterator_type
        push_at(
            entry const& _entry)
        {
            using namespace contdsl; 

            auto __iter = m_content.push_at(_entry);
            go<query>(with($0) > sort(asc), m_content);

            return __iter;
        }


        inline iterator_type
        push_at(
            key_t&& _key,
            value_t const& _value)
        {
            return push_at(entry{_key, _value});
        }


        inline iterator_type
        push_at(
            key_t const& _key,
            value_t&& _value)
        {
            return push_at(entry{_key, _value});
        }


        inline iterator_type
        push_at(
            key_t&& _key,
            value_t&& _value)
        {
            return push_at(entry{_key, _value});
        }


        inline iterator_type
        push_at(
            key_t const& _key,
            value_t const& _value)
        {
            return push_at(entry{_key, _value});
        }


        inline iterator_type
        pop_at(
            key_t const& _key)
        {
            using namespace contdsl;

            auto __pos = this->end();

            go<query>(
                with(ref(*this)) 
                > first(ref(__pos)) 
                > where([&_key](entry const& _item){return _item.key == _key;}));

            return m_content.pop_at(__pos);
        }


        inline iterator_type
        pop_at(
            key_t&& _key)
        {
            using namespace contdsl;

            auto __pos = this->end();

            go<query>(
                with(ref(*this)) 
                > first(ref(__pos)) 
                > where([&_key](entry const& _item){return _item.key == _key;}));

            return m_content.pop_at(__pos);
        }
    };
}

#endif