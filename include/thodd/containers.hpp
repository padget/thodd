/*
 * containers.hpp
 *
 *  Created on: 23 sept. 2016
 *      Author: padget
 */

#ifndef ATOM_CONTAINERS_HPP_
#  define ATOM_CONTAINERS_HPP_

#  include <thodd/meta.hpp>
#  include <thodd/require.hpp>
#  include <thodd/law.hpp>
#  include <thodd/tuple.hpp>
#  include <thodd/functional.hpp>
#  include <thodd/container_func.hpp>
#  include <thodd/container_dsl.hpp>

#  include <initializer_list>


namespace thodd
{
    ATOM_EXCEPTION(
            bad_iterator_origin,
            "bad_iterator_origin : "
            "the used iterator must "
            "have the same origin "
            "that the container where "
            "it is used")

    namespace detail
    {
        template<
            typename begin_t, 
            typename end_t = begin_t>
        class range
        {            
            begin_t m_begin;
            end_t m_end;

            using iterator_type = begin_t;

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
            range(
                begin_t __begin, 
                end_t __end) :
                m_begin{move(__begin)},
                m_end{move(__end)} {}

            template<
                typename container_t>
            range(
                container_t&& __c) :
                range(perfect<container_t>(__c).begin(), 
                      perfect<container_t>(__c).end()) {}
        };
    }
  
  
    template<
        typename begin_t, 
        typename end_t>
    inline auto
    range(
        begin_t __begin, 
        end_t __end)
    {
        return detail::range<
                meta::decay<begin_t>, 
                meta::decay<end_t>>
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



    template<
        typename item_t>
    class list final
    {
        struct node
        {
            item_t item;
            node* next{nullptr};
            node* pred{nullptr};

            node(
                item_t&& _item,
                node* _next,
                node* _pred):
                item{_item},
                next{_next},
                pred{_pred} {}

            node(
                item_t const& _item,
                node* _next,
                node* _pred):
                item{_item},
                next{_next},
                pred{_pred} {}

            ~node(){}
        };

        node* m_first{nullptr};
        node* m_last{nullptr};

        size_t m_size{0};

    public:
        class list_iterator
        {
            list const* m_origin{nullptr};
            mutable list::node* m_node{nullptr};
            

        public:
            using value_type = item_t;
            
            inline list const*
            origin() const
            {
                return m_origin;
            }

            inline list::node*
            node()
            {
                return m_node;
            }

            inline list::node const*
            node() const
            {
                return m_node;
            }

        public:
            list_iterator(
                list const* _origin,
                list::node* _node = nullptr):
                m_origin{_origin},
                m_node{_node} {}


            inline item_t&
            operator*()
            {
                return m_node->item;
            }


            inline item_t const&
            operator*() const
            {
                return m_node->item;
            }


            inline list_iterator&
            operator++()
            {
                if(m_node != nullptr)
                    m_node = m_node->next;

                return *this;
            }

            inline list_iterator&
            operator--()
            {
                m_node = m_node != nullptr ?
                            m_node->pred :
                            m_origin->m_last;

                return *this;
            }

            inline list_iterator const&
            operator++() const
            {
                if(m_node != nullptr)
                    m_node = m_node->next;

                return *this;
            }

            inline list_iterator const&
            operator--() const
            {
                m_node = m_node != nullptr ?
                            m_node->pred :
                            m_origin->m_last;

                return *this;
            }


            inline bool const
            operator == (
                list_iterator const& _other) const
            {
                return m_origin == _other.m_origin
                    && m_node   == _other.m_node;
            }


            inline bool const
            operator!=(
                list_iterator const& _other) const
            {
                return !this->operator ==(_other);
            }
        };


        using iterator_type = list_iterator;
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
            node* __current{m_first};

            while(__current != nullptr)
            {
                node* __tmp {__current};
                __current = __current->next;
                delete __tmp;
            }

            m_first = nullptr;
            m_last = nullptr;
        }


    public:
        ~list() { this->clear(); }
        list() = default;
        list(list&&) = default;
        list& operator= (list&&) = default;

    public:
        template<
            typename iterator_t>
        list(
            detail::range<iterator_t> const& __range)
        {
            using namespace contdsl;

            go<query>(copy, __range, *this);
        } 


        template<
            typename iterator_t>
        list(
            iterator_t __begin,
            iterator_t __end) :
            list{range(__begin, __end)} {}


        template<
            typename container_t>
        list(
            container_t& __container) : 
            list{ range(__container.begin(), 
                        __container.end()) } {}


        list(
            std::initializer_list<item_t>&& __init) :
            list{ range(__init.begin(), 
                        __init.end()) } {}


        template<
            typename container_t>
        list(
            container_t&& __container)
        {
            auto&& __end = end();

            for(auto&& __item : __container)
                this->push_at(move(__item), __end);
        }


    public:
        template<
            typename iterator_t>
        list&
        operator= (
            detail::range<iterator_t> const& __range)
        {
            using namespace contdsl;
            
            this->clear();
            go<query>(copy, __range, *this);
            
            return *this;
        }
        

        list&
        operator= (
            list const& __other)
        {
            return &__other != this ? 
                        (*this) = range(this->begin(), 
                                        this->end()) :
                        *this;
        }

        
        template<
            typename container_t>
        list&
        operator=(
            container_t& __container)
        {
            return (*this) = range(__container.begin(), 
                                   __container.end());
        }


        list&
        operator=(
            std::initializer_list<item_t> __range)
        {
            return (*this) = range(__range.begin(), __range.end());
        }


        template<
            typename container_t>
        list&
        operator=(
            container_t&& __container)
        {
            this->clear();
            auto&& __end = this->end();

            for(auto&& __item : __container)
                this->push_at(move(__item), __end);

            return *this;
        }


    public:
        inline iterator_type
        push_at(
            item_t const& _item,
            iterator_type _pos)
        {
            node* __to_push{new node{_item, nullptr, nullptr}};
            node* __at{_pos.node()};

            if(__at != nullptr)
            {
                node*& __pred{__at->pred};

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
        push_at(
            item_t&& _item,
            iterator_type _pos)
        {
            node* __to_push{new node{_item, nullptr, nullptr}};
            node* __at{_pos.node()};

            if(__at != nullptr)
            {
                node*& __pred{__at->pred};

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
            iterator_type _pos)
        {
            go<contract>(
                require(ref(_pos.origin()) == ref(this)) 
                > throw_<bad_iterator_origin>());

            node* __to_pop = _pos.node();
            node* __next{nullptr};

            if(__to_pop != nullptr)
            {
                node* __pred = __to_pop->pred;
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



    /// /// ///
    /// Set ///
    /// /// ///
    template<
        typename item_t>
    class set final
    {
        list<item_t> m_content;


    public:
        using set_iterator = typename list<item_t>::list_iterator;
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
        ~set() = default;
        set() = default;
        set(set&&) = default;
        set& operator=(set&&) = default;


    public:
        template<
            typename iterator_t>
        set(
            detail::range<iterator_t> const& __range)
        {
            using namespace contdsl;

            go<query>(copy, __range, *this); 
        } 


        template<
            typename iterator_t>
        set(
            iterator_t __begin,
            iterator_t __end) :
            set{range(__begin, __end)} {}


        template<
            typename container_t>
        set(
            container_t& __container) : 
            set{ range(__container.begin(), 
                       __container.end()) } {}


        set(
            std::initializer_list<item_t>&& __init) :
            set{ range(__init.begin(), 
                       __init.end()) } {}


        template<
            typename container_t>
        set(
            container_t&& __container)
        {
            auto&& __end = end();

            for(auto&& __item : __container)
                this->push_at(move(__item), __end);
        }

        
    public:
        template<
            typename iterator_t>
        set&
        operator= (
            detail::range<iterator_t> const& __range)
        {
            using namespace contdsl;
         
            this->clear();
            go<query>(copy, __range, *this); 
            
            return *this;
        }
        

        set&
        operator= (
            set const& __other)
        {
            return &__other != this ? 
                        (*this) = range(this->begin(), 
                                        this->end()) :
                        *this;
        }

        
        template<
            typename container_t>
        set&
        operator=(
            container_t& __container)
        {
            return (*this) = range(__container.begin(), 
                                   __container.end());
        }


        set&
        operator=(
            std::initializer_list<item_t> __range)
        {
            return (*this) = range(__range.begin(), __range.end());
        }


        template<
            typename container_t>
        set&
        operator=(
            container_t&& __container)
        {
            this->clear();
            auto&& __end = this->end();

            for(auto&& __item : __container)
                this->push_at(move(__item), __end);

            return *this;
        }


    public:
        inline void
        push_at(
            item_t const& _item)
        {
            using namespace contdsl;

            auto __pos = this->end();

            go<query>(
                with($0) 
                > first($1) 
                > where($0 == cref(_item)), 
                *this, __pos);

            if(__pos != end())
                *__pos = _item;
            else
                m_content.push_at(_item, __pos);
        }


        inline void
        push_at(
            item_t&& _item)
        {
            using namespace contdsl; 
            
            auto __pos = this->end();

            go<query>(
                with($0) 
                > first($1) 
                > where($0 == cref(_item)), 
                *this, __pos);

            if(__pos != end())
                *__pos = _item;
            else
                m_content.push_at(_item, __pos);
        }

        inline void
        push_at(
            item_t const& _item,
            set_iterator)
        {
            push_at(_item);
        }

        inline void
        push_at(
            item_t&& _item,
            set_iterator)
        {
            push_at(perfect<item_t>(_item));
        }


        inline set_iterator
        pop_at(
            set_iterator _pos)
        {
            return m_content.pop_at(_pos);
        }
    };





    template<
        typename key_t,
        typename value_t>
    class map final
    {
        struct entry
        {
            key_t key;
            value_t value;

            inline bool const
            operator ==(
                entry const& _other) const
            {
                return key == _other.key;
            }

            inline bool const
            operator !=(
                entry const& _other) const
            {
                return ! (*this == _other);
            }

            inline bool const
            operator < (
                entry const& _other) const
            {
                return key < _other.key;
            }
        };

        set<entry> m_content;


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
                this->push_at(move(__item), __end);
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
                this->push_at(move(__item), __end);

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



    namespace arrays
    {
        ATOM_EXCEPTION(zero_sized_array_exception, 
                       "zero_sized_array_exception : "
                       "an array can't have a zero size !!!")

        /// Clone the __array with the new size
        /// and return the clone. The old array 
        /// is not destroyed !!!
        template<
            typename type_t>
        inline auto
        resize(
            type_t* __array, 
            size_t __old_size, 
            size_t __new_size)
        -> type_t*
        {
            go<contract>(
                require(ref(__new_size) > val(0u)) 
                > throw_<zero_sized_array_exception>());

            auto __new = new type_t[__new_size];
            auto __bound = __old_size > __new_size ? __new_size : __old_size;
        
            for(auto __index = 0u; __index < __bound; ++__index)
                __new[__index] = move(__array[__index]);

            return __new;
        }
    }

    ATOM_EXCEPTION(vector_out_of_bound_exception, 
                   "vector_out_of_bound_exception : "
                   "tryed to access to an out of bound memory")

    template<
        typename item_t>
    class vector final
    {
        using value_type = item_t;
        
    
        size_t m_capacity{10u};
        size_t m_size{0u};
        
        value_type* m_first{nullptr};

    public:
        inline value_type const*
        data() const
        {
            return m_first;
        }

        inline size_t const& 
        capacity() const
        {
            return m_capacity;
        }

        inline size_t const&
        size() const
        {
            return m_size;
        }

    public:

        struct vector_iterator
        {
            using value_type = item_t;
        private:
            vector const* m_origin{nullptr};
            mutable item_t* m_item{nullptr};

        public:
            inline vector const*
            origin() const
            {
                return m_origin;
            }

            inline item_t const* 
            item() const
            {
                return m_item;
            }

            inline item_t* 
            item()
            {
                return m_item;
            }
            
        public:
            vector_iterator(
                vector const* __origin,
                item_t* __item = nullptr) :
                m_origin{__origin},
                m_item{__item} {}

            inline item_t&
            operator*()
            {
                return *m_item;
            }


            inline item_t const&
            operator*() const
            {
                return *m_item;
            }


            inline vector_iterator&
            operator++()
            {
                if(m_origin->m_first != nullptr && m_item != nullptr)
                {
                    if(m_item != m_origin->m_first + m_origin->m_size - 1u)
                        ++m_item;
                    else 
                        m_item = nullptr;
                }
            
                return *this;
            }

            inline vector_iterator const&
            operator++() const
            {
                if(m_origin->m_first != nullptr && m_item != nullptr)
                {
                    if(m_item != m_origin->m_first + m_origin->m_size - 1u)
                        ++m_item;
                    else 
                        m_item = nullptr;
                }
            
                return *this;
            }

            inline vector_iterator&
            operator--()
            {	
                if(m_origin->m_first != nullptr)
                {
                    if(m_item != nullptr)
                    {	
                        if(m_item != m_origin->m_first)
                            --m_item;
                    }
                    else
                        m_item = m_origin->m_first + m_origin->m_size - 1;	
                }

                return *this;
            }

            inline vector_iterator const&
            operator--() const
            {	
                if(m_origin->m_first != nullptr)
                {
                    if(m_item != nullptr)
                    {	
                        if(m_item != m_origin->m_first)
                            --m_item;
                    }
                    else
                        m_item = m_origin->m_first + m_origin->m_size - 1;	
                }

                return *this;
            }


            inline bool const
            operator == (
                vector_iterator const& __other) const
            {
                return m_origin == __other.m_origin
                    && m_item   == __other.m_item;
            }


            inline bool const
            operator!=(
                vector_iterator const& __other) const
            {
                return !this->operator ==(__other);
            }
        };


        using iterator_type = vector_iterator;

    public:
        vector(vector&&) = default;
        vector& operator=(vector&&) = default;

    public:
        ~vector()
        {
            delete[] m_first;
        }
        
        vector(
             size_t __capacity = 10u) :
             m_capacity{__capacity},
             m_first{new item_t[m_capacity]} {}

        template<
            typename container_t>
        vector(
            container_t& __container) :
            vector(__container.size())
        {
            //go<query>(copy, __container, *this);
        }

         template<
            typename container_t>
        vector(
            container_t&& __container) :
            vector(__container.size())
        {
            
            //constexpr auto __transfer = with($0) > transfer($2);
            //go<query>(__transfer, __container, *this);
        }

        vector(
            std::initializer_list<item_t> __init) :
            vector(__init.begin(), __init.end(), __init.size()) {}
    

        template<
            typename iterator_t>
        vector(
            iterator_t __begin, 
            iterator_t __end, 
            size_t const& __capacity = 10u) :
            vector{__capacity}
        {
            auto&& __this_end = this->end();

            while(__begin != __end)
            {
                push_at(*__begin, __this_end);
                ++__begin;
            }	
        }
    

    /*	template<
            typename container_t>
        explicit vector(
            container_t&& __container) :
            vector(__container.begin(), __container.end(), __container.size()) {}
*/

        
        template<
            typename iterator_t>
        vector&
        operator=(
            tuple<iterator_t, iterator_t>&& _range)
        {
            auto&& __current = get<0>(_range),
                   __end     = get<1>(_range);

            if(__current.origin() != this)
            {
                this->clear();
                auto&& __this_end = this->end();

                while(__current != __end)
                {
                    push_at(*__current, __this_end);
                    ++__current;
                }
            }

            return *this;
        }


        vector&
        operator=(
            vector const& _other)
        {
            if(this != &_other)
                this->operator =(make_tuple(this->begin(), this->end()));

            return *this;
        }


        vector&
        operator=(
            std::initializer_list<item_t> _range)
        {
            return this->operator =(make_tuple(_range.begin(), _range.end()));
        }


      /*  template<
            typename container_t>
        vector&
        operator=(
            container_t&& _container)
        {
            return this->operator =(make_tuple(_container.begin(), _container.end()));
        }
*/
     public:
        inline iterator_type const
        begin() const
        {
            return iterator_type{this, m_first};
        }


        inline iterator_type
        begin()
        {
            return iterator_type{this, m_first};
        }


        inline iterator_type const
        end() const
        {
            return iterator_type{this};
        }


        inline iterator_type
        end()
        {
            return iterator_type{this};
        }


    public:
        inline void 
        clear()
        {
            if(m_size != 0u)
            {
                delete[] m_first;
                m_first = nullptr;
                m_size = 0u;
                m_capacity = 10u;
                m_first = new item_t[m_capacity];
            }
        }

        inline void 
        resize(
            size_t __new_capacity)
        {
            auto* __old_first = m_first;

            m_capacity = __new_capacity;
            m_first = arrays::resize(__old_first, m_size, m_capacity);
            m_size = m_capacity > m_size ? m_size : m_capacity;

            delete[] __old_first;
        }

    public:
        inline vector_iterator
        push_at(
            item_t const& __item,
            iterator_type __pos)
        {
            std::cout << "copy elt" << std::endl;
            go<contract>(
                require(cref(__pos.origin()) == cref(this))
                > throw_<bad_iterator_origin>());

            auto __index = __pos.item() == nullptr ?  
                                m_size : 
                                __pos.item() - m_first;

            if(__index == m_capacity)
                resize(m_capacity + 10);

            for(auto __i = m_size; __i > __index; --__i)
                m_first[__i] = move(m_first[__i - 1]);

            m_first[__index] = __item;
            ++m_size;

            return {this, m_first + __index};
        }
        
        
        inline iterator_type
        push_at(
            item_t&& __item,
            iterator_type __pos)
        {
            std::cout << "move elt" << std::endl;
            go<contract>(
                require(cref(__pos.origin()) == cref(this))
                > throw_<bad_iterator_origin>());

            auto __index = __pos.item() == nullptr ?  
                                m_size : 
                                __pos.item() - m_first;

            if(m_size == m_capacity)
                resize(m_capacity + 10);

            for(auto __i = m_size; __i > __index; --__i)
                m_first[__i] = move(m_first[__i - 1]);

            m_first[__index] = perfect<item_t>(__item);
            ++m_size;

            return {this, m_first + __index};
        }

        
        inline iterator_type
        pop_at(
            iterator_type __pos)
        {
            go<contract>(
                require(ref(__pos.origin()) == ref(this))
                > throw_<bad_iterator_origin>());
            
            if(__pos.item() != nullptr)
            {
                size_t __index = __pos.item() - m_first;
                
                for(auto __i = __index; __i < m_size - 1; ++__i)
                    m_first[__i] = move(m_first[__i + 1]);

                --m_size;
            }

            return __pos;
        }


        inline item_t& 
        operator[] (
            size_t __index)
        {
            go<contract>(
                require(ref(__index) < ref(m_size)) 
                > throw_<vector_out_of_bound_exception>());
           
            return *(m_first + __index);
        }

        inline item_t const& 
        operator[] (
            size_t __index) const
        {
            go<contract>(
                require(ref(__index) < ref(m_size)) 
                > throw_<vector_out_of_bound_exception>());

            return *(m_first + __index);
        }
    };


   


  


    namespace detail
    {
        template<
            typename item_t, 
            template<typename> typename container_t = list>
        class view final 
        {
            container_t<item_t*> m_data;

            struct view_iterator
            {
                using iterator_t = typename container_t<item_t*>::iterator_type;

            private:
                iterator_t m_iter;

            public:
                using value_type = item_t;
                
                iterator_t&
                iter()
                {
                    return m_iter;
                }

                iterator_t const&
                iter() const
                {
                    return m_iter;
                }

            public:
                view_iterator(
                    iterator_t const& __iter) :
                    m_iter{__iter} {}

                inline item_t&
                operator*()
                {
                    return **m_iter;
                }


                inline item_t const&
                operator*() const
                {
                    return **m_iter;
                }


                inline view_iterator&
                operator++()
                {
                    ++m_iter;
                    return *this;
                }

                inline view_iterator const&
                operator++() const
                {
                    ++m_iter;
                    return *this;
                }

                inline view_iterator&
                operator--()
                {	
                    --m_iter;
                    return *this;
                }

                inline view_iterator const&
                operator--() const
                {	
                    --m_iter;
                    return *this;
                }


                inline bool const
                operator == (
                    view_iterator const& __other) const
                {
                    return m_iter == __other.iter();
                }


                inline bool const
                operator!=(
                    view_iterator const& __other) const
                {
                    return !this->operator ==(__other);
                }
            };

            using iterator_type = view_iterator;

        public:
            inline auto
            begin()
            {
                return view_iterator(m_data.begin());
            }

            inline auto const
            begin() const
            {
                return view_iterator(m_data.begin());
            }

            inline auto
            end()
            {
                return view_iterator(m_data.end());
            }

            inline auto const
            end() const
            {
                return view_iterator(m_data.end());
            }

        public:
            
            inline size_t const
            size() const
            {
                return m_data.size();
            }

            inline void
            clear()
            {
                m_data.clear();
            }

        public:
            ~view() = default;
            view() = default;
            view(view const&) = default;
            view(view&&) = default;
            view& operator=(view const&) = default;
            view& operator=(view&&) = default;
        
        public:
            template<
                typename iterator_t>
            view(
                detail::range<iterator_t>&& __range)
            {
                using namespace contdsl;

                go<query>(copy, __range, *this);
            }

            template<
                typename iterator_t>
            view(
                detail::range<iterator_t> const& __range)
            {
                using namespace contdsl;

                go<query>(copy, __range, *this);
            }


            template<
                typename iterator_t>
            view(
                iterator_t __begin,
                iterator_t __end) :
                view{ thodd::range(__begin, __end) } {}


            view(
                std::initializer_list<item_t> __init):
                view{ thodd::range(__init) } {}


            template<
                typename other_t>
            view(
                other_t&& __container) :
                view{ thodd::range(__container) } {}


        public:
            template<
                typename iterator_t>
            view&
            operator= (
                detail::range<iterator_t> const& __range)
            {
                using namespace contdsl;
                
                this->clear();
                go<query>(copy, __range, *this);

                return *this;
            }

            template<
                typename iterator_t>
            view&
            operator= (
                detail::range<iterator_t>&& __range)
            {
                using namespace contdsl;
                
                this->clear();
                go<query>(copy, __range, *this);

                return *this;
            }


            view&
            operator=(
                std::initializer_list<item_t> const& __init)
            {
                return (*this) = thodd::range(__init.begin(), 
                                             __init.end());
            }


            template<
                typename other_t>
            view&
            operator=(
                other_t&& __container)
            {
                return (*this) = thodd::range(__container.begin(), 
                                             __container.end());
            }
    
        public:
            inline iterator_type
            push_at(
                item_t& __item,
                iterator_type __pos)
            {
                return m_data.push_at(&__item, __pos.iter());
            }

            inline iterator_type
            push_at(
                item_t&& __item,
                iterator_type __pos)
            {
                return m_data.push_at(&__item, __pos.iter());
            }


            inline iterator_type
            pop_at(
                iterator_type __pos)
            {
            return m_data.pop_at(__pos.iter());
            }
        };
    }

    template<
        typename container_t>
    inline auto
    view(
        container_t&& __container)
    {
        using item_t = typename meta::decay<container_t>::value_type;

        return detail::view<item_t>
                { perfect<container_t>(__container) };
    }

    template<
        typename iterator_t>
    inline auto
    view(
        iterator_t __begin, 
        iterator_t __end)
    {
        return view(thodd::range(__begin, __end));
    }

    

    template<
        typename item_t>
    inline auto
    view(
        std::initializer_list<item_t> const& __init)
    {
        return detail::view<item_t>{ thodd::range(__init) };
    }



//	template<
//		typename colname_t,
//		typename item_t>
//	struct column
//	{
//		item_t m_item;
//
//
//	public:
//		item_t&
//		get()
//		{
//			return m_item;
//		}
//
//
//		item_t const&
//		get() const
//		{
//			return m_item;
//		}
//
//
//	public:
//		column() = default;
//		column(column const&) = default;
//		column(column&&) = default;
//		virtual ~column() = default;
//		column& operator=(column const&) = default;
//		column& operator=(column&&) = default;
//
//
//	public:
//		column(
//			item_t const& _item):
//			m_item{_item} {}
//
//
//		template<
//			typename uitem_t>
//		column(
//			uitem_t&& _uitem):
//			m_item{perfect<uitem_t>(_uitem)} {}
//	};
//
//
//	template<
//		typename ... columns_t>
//	class record;
//
//
//	template<
//		typename ... colnames_t,
//		typename ... items_t>
//	class record<column<colnames_t, items_t>...>:
//		public column<colnames_t, items_t>...
//	{
//		template<
//			typename colname_t>
//		using at_ = model::value_of_<
//						model::map<model::pair<colnames_t, items_t>...>,
//						colname_t>;
//
//	public:
//		template<
//			typename colname_t>
//		inline at_<colname_t>&
//		get()
//		{
//			return column<colname_t, at_<colname_t>>::get();
//		}
//
//		template<
//			typename colname_t>
//		inline at_<colname_t> const&
//		get() const
//		{
//			return column<colname_t, at_<colname_t>>::get();
//		}
//
//
//	public:
//		record() = default;
//		record(record const&) = default;
//		record(record&&) = default;
//		virtual ~record() = default;
//		record& operator=(record const&) = default;
//		record& operator=(record&&) = default;
//
//		record(
//			items_t const&... _items):
//			column<colnames_t, items_t>(_items)... {}
//
//		template<
//			typename ... uitems_t>
//		record(
//			uitems_t&&... _uitems):
//			column<colnames_t, items_t>(perfect<uitems_t>(_uitems))... {}
//
//		template<
//			typename ... uitems_t>
//		record(
//			record<uitems_t..., colnames_t...>&& _urecord):
//			column<colnames_t, items_t>(_urecord.template get<uitems_t, colnames_t>())... {}
//
//		template<
//			typename ... uitems_t>
//		record(
//			record<uitems_t..., colnames_t...> const& _urecord):
//			column<colnames_t, items_t>(_urecord.template get<uitems_t, colnames_t>())... {}
//	};
//
//
//	template<
//		typename record_t>
//	class table;
//
//	template<
//		typename ... colnames_t,
//		typename ... items_t>
//	class table<record<column<colnames_t, items_t>...>>
//	{
//		using record_t = record<column<colnames_t, items_t>...>;
//		using table_iterator = typename list<record_t>::list_iterator;
//
//		list<record_t> m_content;
//
//	public:
//		table() = default;
//		table(table const&) = default;
//		table(table&&) = default;
//		~table() = default;
//		table& operator=(table const&) = default;
//		table& operator=(table&&) = default;
//
//
//		template<
//			typename iterator_t>
//		explicit table(
//			iterator_t _begin,
//			iterator_t _end):
//			m_content{_begin, _end} {}
//
//
//		explicit table(
//			std::initializer_list<record_t> _init):
//			table<record<column<colnames_t, items_t>...>>{_init.begin(), _init.end()} {}
//
//
//		template<
//			typename container_t>
//		explicit table(
//			container_t&& _container):
//			table<record<column<colnames_t, items_t>...>>{_container.begin(), _container.end()} {}
//
//
//		template<
//			typename iterator_t>
//		table&
//		operator=(
//			tuple<iterator_t, iterator_t>&& _range)
//		{
//			m_content = _range;
//			return *this;
//		}
//
//
//		table&
//		operator=(
//			std::initializer_list<record_t> _range)
//		{
//			return this->operator =(make_tuple(_range.begin(), _range.end()));
//		}
//
//
//		template<
//			typename container_t>
//		table&
//		operator=(
//			container_t&& _container)
//		{
//			return this->operator =(make_tuple(_container.begin(), _container.end()));
//		}
//
//
//
//	public:
//		inline table_iterator const
//		begin() const
//		{
//			return m_content.begin();
//		}
//
//
//		inline table_iterator
//		begin()
//		{
//			return m_content.begin();
//		}
//
//
//		inline table_iterator const
//		end() const
//		{
//			return m_content.end();
//		}
//
//
//		inline table_iterator
//		end()
//		{
//			return m_content.end();
//		}
//
//		inline void
//		clear()
//		{
//			m_content.clear();
//		}
//
//		inline size_t const
//		size() const
//		{
//			return m_content.size();
//		}
//
//	public:
//		inline void
//		push_at(
//			record_t const& _record,
//			table_iterator _pos)
//		{
//			m_content.push_at(_record, _pos);
//		}
//
//		inline void
//		push_at(
//			record_t&& _record,
//			table_iterator _pos)
//		{
//			m_content.push_at(_record, _pos);
//		}
//
//		inline table_iterator
//		pop_at(
//			table_iterator _pos)
//		{
//			return m_content.pop_at(_pos);
//		}
//	};

}

#endif /* ATOM_CONTAINERS_HPP_ */
