#ifndef __ATOM_STRING_HPP__
#  define __ATOM_STRING_HPP__

#  include <thodd/container_dsl.hpp>
#  include <thodd/containers.hpp>

namespace thodd
{
    namespace cstr
    {
        template<
            typename char_t>
        inline size_t 
        size(
            char_t const* __cs)
        {
            char_t const* __first = __cs;
            
            while(*__cs != '\0')
                ++__cs;

            return __cs - __first;
        }
    }


    template<
        typename char_t>
    class const_basic_string 
    {
        char_t const* data;
        std::size_t size;
    
    public:
        template<
            std::size_t length_c>
        constexpr 
        const_basic_string(
            char_t const (&__data) [length_c]):
            data(__data), 
            size(length_c - 1) {}
    };


    using const_string   = const_basic_string<char>;
    using const_wstring  = const_basic_string<wchar_t>;
    using const_string16 = const_basic_string<char16_t>;
    using const_string32 = const_basic_string<char32_t>;


    template<
        typename char_t>
    class basic_string final
    {
        vector<char_t> m_data;
        using string_iterator = typename vector<char_t>::vector_iterator;


    public:
        inline char_t const*
        c_str() const
        {
            return m_data.data();
        }


        inline size_t
        size() const
        {
            return m_data.size() - 1;
        }


    public:
        basic_string(basic_string const&) = default;
        basic_string(basic_string&&) = default;
        ~basic_string() = default;
        basic_string& operator=(basic_string const&) = default;
        basic_string& operator=(basic_string&&) = default;


    public:
        basic_string(
            size_t const __capacity = 10u) :
            m_data(__capacity) 
        {
            m_data.push_at('\0', m_data.end());   
        }


        basic_string(
            char_t const* __data) :
            basic_string(cstr::size(__data) + 1)
        {
            while(*__data != '\0')
            {
                m_data.push_at(*__data, --m_data.end());
                ++__data;
            }
        }


        basic_string
        operator +(
            basic_string const& __other) const
        {
            using namespace contdsl;
            constexpr auto __cat_query = with($0) > select($2) > limit($2);
            
            basic_string __result(size() + __other.size());
                
            go<query>(__cat_query, *this, __result, size() - 1);
            go<query>(__cat_query, __other, __result,  __other.size() - 1);
            
            return __result;
        }


        basic_string&
        operator += (
            basic_string const& __other)
        {
            using namespace contdsl;
            constexpr auto __cat_query = with($0) > select($2) > limit($2);
            
            m_data.resize(size() + __other.size());

            go<query>(__cat_query, __other, *this, __other.size() - 1);

            return *this;
        }


    public:
        inline string_iterator const
        begin() const
        {
            return m_data.begin();
        }


        inline string_iterator
        begin()
        {
            return m_data.begin();
        }


        inline string_iterator const
        end() const
        {
            return --m_data.end(); 
        }


        inline string_iterator
        end()
        {
            return --m_data.end();
        }


    public:
        inline string_iterator
        push_at(
            char_t const& __item,
            string_iterator __pos)
        {
            return m_data.push_at(__item, __pos);
        }


        inline string_iterator
        push_at(
            char_t&& __item,
            string_iterator __pos)
        {
            return m_data.push_at(perfect<char_t>(__item), __pos);
        }


        inline string_iterator
        pop_at(
            string_iterator __pos)
        {
            return m_data.pop_at(__pos);
        }

    public:
        inline char_t& 
        operator[] (
            size_t const& __index)
        {
            return m_data[__index];
        } 

        
        inline char_t const& 
        operator[] (
            size_t const& __index) const
        {
            return m_data[__index];
        } 
    };


    template<
        typename char_t>
    inline std::ostream& 
    operator << (
        std::ostream& __out, 
        basic_string<char_t> const& __str)
    {
        __out << __str.c_str();

        return __out;
    }


    using string = basic_string<char>;   
    using wstring = basic_string<wchar_t>;   
    using string16 = basic_string<char16_t>;   
    using string32 = basic_string<char32_t>; 


    template<
        typename char_t>
    class basic_string_builder
    {
        list<basic_string<char_t>> m_strings;


    public:
        inline basic_string_builder&
        append(
            basic_string<char_t> const& __str)
        {
            m_strings.push_at(__str, m_strings.end());
            return *this;
        }

        inline basic_string_builder&
        append(
            basic_string<char_t>&& __str)
        {
            m_strings.push_at(__str, m_strings.end());
            return *this;
        }

        inline basic_string_builder&
        operator << (
            basic_string<char_t> const& __str)
        {
            return append(__str);
        } 

        inline basic_string_builder&
        operator << (
            basic_string<char_t>&& __str)
        {
            return append(__str);
        } 

        inline basic_string<char_t>
        str() const
        {
            using namespace contdsl;

            size_t __final_size{0u};

            constexpr auto __sizeof =
                [](auto const& __plh)
                {
                    return [&__plh] (auto&&... __args) 
                           { return __plh(perfect<decltype(__args)>(__args)...).size(); };
                };

            go<query>(
                with($0) 
                > foreach(ref(__final_size) += as_functor(__sizeof($0))), 
                m_strings);
           
            basic_string<char_t> __result(__final_size);
            
            // go<query>(
            //     with($0) 
            //     > foreach(bind(go<query>, with($0) > select($2) > limit(__sizeof($0)), $0, $1)), 
            //     m_strings); 
         

            return __result;
        }
    };

    template<
        typename char_t>
    inline std::ostream& 
    operator << (
        std::ostream& __out, 
        basic_string_builder<char_t> const& __str)
    {
        __out << __str.str();

        return __out;
    }

    using string_builder = basic_string_builder<char>;
    using wstring_builder = basic_string_builder<wchar_t>;
    using string16_builder = basic_string_builder<char16_t>;
    using string32_builder = basic_string_builder<char32_t>;
}

#endif