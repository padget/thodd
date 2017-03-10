#ifndef __THODD_CONTAINER_VECTOR_HPP__
#  define __THODD_CONTAINER_VECTOR_HPP__

namespace thodd
{
    namespace arrays
    {
        THODD_EXCEPTION(zero_sized_array_exception, 
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
                __new[__index] = rvalue(__array[__index]);

            return __new;
        }
    }

    THODD_EXCEPTION(vector_out_of_bound_exception, 
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
                m_first[__i] = rvalue(m_first[__i - 1]);

            m_first[__index] = __item;
            ++m_size;

            return {this, m_first + __index};
        }
        
        
        inline iterator_type
        push_at(
            item_t&& __item,
            iterator_type __pos)
        {
            std::cout << "rvalue elt" << std::endl;
            go<contract>(
                require(cref(__pos.origin()) == cref(this))
                > throw_<bad_iterator_origin>());

            auto __index = __pos.item() == nullptr ?  
                                m_size : 
                                __pos.item() - m_first;

            if(m_size == m_capacity)
                resize(m_capacity + 10);

            for(auto __i = m_size; __i > __index; --__i)
                m_first[__i] = rvalue(m_first[__i - 1]);

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
                    m_first[__i] = rvalue(m_first[__i + 1]);

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

}

 #endif