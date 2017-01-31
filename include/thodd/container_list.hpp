#ifndef __THODD_CONTAINER_LIST_HPP__
#  define __THODD_CONTAINER_LIST_HPP__

#  include <thodd/law.hpp>
#  include <thodd/meta.hpp>
#  include <thodd/functional.hpp>
#  include <thodd/require.hpp>

#  include <thodd/container_iterator_traits.hpp>
#  include <thodd/container_range.hpp>
#  include <thodd/container_dsl.hpp>
#  include <thodd/container_func.hpp>

namespace thodd
{
    template<
        typename item_t>
    class list;


    template<
        typename item_t>
    struct node
    {
        item_t item;
        node* next{nullptr};
        node* pred{nullptr};
    };


    template<
        typename item_t>
    struct list_iterator
    {
        list<item_t> const* origin{nullptr};
        mutable node<item_t>* node{nullptr};

        using value_type = item_t;
    };


    inline auto 
    operator * (
        list_iterator<auto> const& __it)
    -> decltype(auto)
    {
        return (__it.node->item);
    }

    
    inline auto
    operator * (
        list_iterator<auto>& __it)
    -> decltype(auto)
    {
        return (__it.node->item);
    }


    inline auto
    operator ++ (
        list_iterator<auto> const& __it)
    -> decltype(auto)
    {
        if(__it.node != nullptr)
            __it.node = __it.node->next;

        return __it;
    }


    inline auto
    operator ++ (
        list_iterator<auto>& __it)
    -> decltype(auto)
    {
        if(__it.node != nullptr)
            __it.node = __it.node->next;

        return __it;
    }


    inline auto 
    operator -- (
        list_iterator<auto> const& __it)
    -> decltype(auto)
    {
        __it.node = __it.node != nullptr ?
                        __it.node->pred :
                        __it.origin->m_last;
        
        return __it;
    }


    inline auto 
    operator -- (
        list_iterator<auto>& __it)
    -> decltype(auto)
    {
        __it.node = __it.node != nullptr ?
                        __it.node->pred :
                        __it.origin->m_last;
        
        return __it;
    }


    inline auto const
    operator == (
        list_iterator<auto> const& __lit,
        list_iterator<auto> const& __rit)
    {
        return __lit.origin == __rit.origin
            && __lit.node   == __rit.node;
    }


    inline auto const
    operator!=(
        list_iterator<auto> const& __lit,
        list_iterator<auto> const& __rit)
    {
        return !(__lit == __rit);
    }
}


namespace thodd
{
    THODD_EXCEPTION(
        bad_iterator_origin, 
        "bad_iterator_origin :" 
        "the origin of the iterator is"
        "not the same than expected !")

    template<
        typename item_t>
    class list final
    {
        node<item_t>* m_first{nullptr};
        node<item_t>* m_last{nullptr};

        size_t m_size{0};

    public:
        
        using iterator_type = list_iterator<item_t>;
        using value_type = item_t;

    public:
        inline auto const
        begin() const
        {
            return iterator_type{this, m_first};
        }


        inline auto
        begin()
        {
            return iterator_type{this, m_first};
        }


        inline auto const
        end() const
        {
            return iterator_type{this};
        }


        inline auto
        end()
        {
            return iterator_type{this};
        }

     public:
        
        inline size_t const
        size() const
        {
            return m_size;
        }


        inline void
        clear()
        {
            node<item_t>* __current{m_first};

            while(__current != nullptr)
            {
                node<item_t>* __tmp {__current};
                __current = __current->next;
                delete __tmp;
            }

            m_first = nullptr;
            m_last = nullptr;
        }


    public:
        ~list() { this->clear(); }
        list() = default;

    public:
        list(
            list const& __other) 
        {
            for(auto&& __item : __other)
                thodd::push_back(*this, __item);
        }

        list(
            list&& __other) : 
            m_first(thodd::rvalue(__other.m_first)),
            m_last(thodd::rvalue(__other.m_last)),
            m_size(thodd::rvalue(__other.m_size)) 
        {
            __other.m_first = nullptr;
            __other.m_last = nullptr;
            __other.m_size = 0u;
        }


        list(
            std::initializer_list<item_t>&& __init)
        {
            for(auto&& __item : __init)
                thodd::push_back(*this, thodd::rvalue(__item));
        }


    public:
    
        template<
            typename iterator_t>
        list(
            detail::range<iterator_t> const& __range) 
        {
            for(auto&& __item : __range)
                thodd::push_back(*this, __item);
        }


        list(
            auto __begin, 
            auto __end) : 
            list(thodd::range(__begin, __end)) {}
    
    public:
        inline list& 
        operator = (
            list const& __other) 
        {
            
            if(this != &__other)
            {    
                this->clear();
            
                for(auto&& __item : __other)
                    thodd::push_back(*this, __other);
            }

            return *this;
        }

        
        inline list& 
        operator = (
            list&& __other) 
        {
            if(this != &__other)
            {   
                this->m_first = thodd::rvalue(__other.m_first);
                this->m_last = thodd::rvalue(__other.m_last);
                this->m_size = thodd::rvalue(__other.m_size);

                __other.m_first = nullptr;
                __other.m_last = nullptr;
                __other.m_size = 0u;
            }

            return *this;
        }


        inline list& 
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
        inline list&
        operator = (
            detail::range<iterator_t> const& __range) 
        {
            this->clear();

            for(auto&& __item : __range)
                thodd::push_back(*this, __item);

            return *this;
        }
       


    public:
        inline iterator_type
        push_at(
            auto&& __item,
            iterator_type __pos)
        {
            node<item_t>* __to_push{new node<item_t>{perfect<decltype(__item)>(__item), nullptr, nullptr}};
            node<item_t>* __at{__pos.node};

            if(__at != nullptr)
            {
                node<item_t>*& __pred{__at->pred};

                __to_push->pred = __pred;
                __at->pred      = __to_push;
                __to_push->next = __at;

                if(__pred != nullptr)
                    __pred->next = __to_push;
            }
            else if (m_last != nullptr)
            {
                __at = m_last;
                __at->next = __to_push;
                __to_push->pred = __at;
            }

            if(__to_push->pred == nullptr)
                m_first = __to_push;

            if(__to_push->next == nullptr)
                m_last  = __to_push;

            m_size++;
            return {this, __to_push};
        }


        inline iterator_type
        pop_at(
            iterator_type __pos)
        {
            go<contract>(
                require(ref(__pos.origin) == ref(this)) 
                > throw_<bad_iterator_origin>());

            node<item_t>* __to_pop = __pos.node;
            node<item_t>* __next{nullptr};

            if(__to_pop != nullptr)
            {
                node<item_t>* __pred = __to_pop->pred;
                      __next = __to_pop->next;

                if(__pred != nullptr)
                    __pred->next = __next;
                else
                    m_first = __next;

                if(__next != nullptr)
                    __next->pred = __pred;
                else
                    m_last = __pred;

                delete  __to_pop;

                --m_size;
            }

            return {this, __next};
        }
    };
}

#endif