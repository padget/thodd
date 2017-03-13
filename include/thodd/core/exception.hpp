#ifndef __THODD_EXCEPTION_HPP__
#  define __THODD_EXCEPTION_HPP__

#  include <exception>

#  define THODD_EXCEPTION(name, message)                            \
    class name :                                                    \
        public std::exception                                       \
    {                                                               \
    public:                                                         \
        virtual char const* what() const noexcept{ return message; }\
    };                                                              \
    
#endif 