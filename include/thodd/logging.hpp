#ifndef THODD_LOGGING_HPP__
#define THODD_LOGGING_HPP__

#  include <iostream>
#  include <typeinfo>
#  include <string>
#  include <chrono>
#  include <thodd/law.hpp>

namespace thodd
{
    struct root {};

    enum class log_level
    {
        trace,
        debug,
        info,
        warn,
        error,
        fatal,
        all
    };

    template <
        log_level lvl_c>
    constexpr auto 
    lvl_name()
    { 
        switch(lvl_c)
        {
            case log_level::trace : return "TRACE";
            case log_level::debug : return "DEBUG";
            case log_level::info  : return "INFO";
            case log_level::warn  : return "WARN";
            case log_level::error : return "ERROR";
            case log_level::fatal : return "FATAL";
            default               : return "UNDEFINED";
        }
    }

    

    
    struct time
    {
        static std::string 
        now() noexcept
        {
            auto __time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            auto&& __now = std::string{ctime(&__time)};
            __now.pop_back();
            return __now;
        }
    };
    

    template<
        typename type_t>
    struct logger
    {   
        template<
            log_level level_c>
        struct log
        {
            template< 
                typename ... messages_t>
            inline void 
            operator() (
                messages_t&&... __messages) const
            {
                std::cout << "--" << lvl_name<level_c>() << "--" << "  ["<< time::now() << "] : " << "[" << typeid(type_t).name() << "] : ";
                repeat{(std::cout << perfect<messages_t>(__messages), 0)...};
                std::cout << std::endl;
            }
        };

        static constexpr log<log_level::trace> trace{};
        static constexpr log<log_level::debug> debug{};
        static constexpr log<log_level::info>  info {};
        static constexpr log<log_level::warn>  warn {};
        static constexpr log<log_level::error> error{};
        static constexpr log<log_level::fatal> fatal{};
    };


    template<
        typename type_t>    
    constexpr logger<type_t>::log<log_level::trace> logger<type_t>::trace;

     template<
        typename type_t>    
    constexpr logger<type_t>::log<log_level::debug> logger<type_t>::debug;
     
    template<
        typename type_t>    
    constexpr logger<type_t>::log<log_level::info>  logger<type_t>::info; 
    
    template<
        typename type_t>    
    constexpr logger<type_t>::log<log_level::warn>  logger<type_t>::warn;
    
    template<
        typename type_t>    
    constexpr logger<type_t>::log<log_level::error> logger<type_t>::error;
    
    template<
        typename type_t>    
    constexpr logger<type_t>::log<log_level::fatal> logger<type_t>::fatal;
}

#endif // !THODD_LOGGING_HPP__