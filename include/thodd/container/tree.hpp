#ifndef __THODD_CONTAINER_TREE_HPP__
#  define __THODD_CONTAINER_TREE_HPP__

#  include <thodd/container/list.hpp>

namespace 
thodd
{
    template<
        typename type_t>
    struct tree_node
    {
        type_t data;
        list<tree_node<type_t>> subnodes;
    };


    template<
        typename type_t>
    struct tree_dive_iterator 
    {
        mutable tree_node* parent{nullptr};
        mutable tree_node* current{nullptr};
    };

    template<
        typename type_t>
    tree_dive_iterator& 
    operator ++ (
        tree_dive_iterator& __it)
    {
        if(__it.current != nullptr)


        return __it;
    }
    
    
    
    
    
    template<
        typename type_t>
    struct tree_lateral_iterator
    {
        mutable tree_node* parent{nullptr};
        mutable tree_node* current{nullptr};
    };


    


    tree_iterator& 
    operator ++ (
        tree_iterator<auto>& __it) 
    {
        if(__it.current != nullptr)
        {

        } 


        return 
        __it;
    }


    template<
        typename type_t>
    class tree
    {
        list<tree_node<type_t>> m_roots;

        size_t m_size{0u};

    public:
        using iterator_type = tree_iterator<type_t>;

    public:
        tree() = default;
        tree(tree const&) = default;
        tree(tree&&) = default;
        ~tree() = default;
    
    public:
        tree& operator = (tree const&) = default;
        tree& operator = (tree&&) = default;

    public:
        constexpr auto
        size() const
        {
            return m_size;
        }

        constexpr auto
        is_final()
        {
            return 
            m_subtree.size() == 0;
        }

    public: 

        inline iterator_type
        push_at(
            auto&& __item,
            iterator_type __pos)
        {
            
        }
    };
}

#endif