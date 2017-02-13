#ifndef __THODD_UUID_HPP__
#  define __THODD_UUID_HPP__

namespace thodd
{
    struct uuid
    {
        using uuid_t = size_t;

        static uuid_t id;

        static 
        inline auto 
        next_id()
        {
            return ++id;
        }
    };

    typename uuid::uuid_data_t uuid::id{0u};
}

#endif