#ifndef __THODD_CONTAINER_TREE_HPP__
#  define __THODD_CONTAINER_TREE_HPP__

#  include <thodd/container/list.hpp>

namespace 
thodd
{
    /// #struct tree_node
    /// #param type_t:
    ///     item type contained in tree_node
    ///
    /// tree_node is a node in tree container
    template<
        typename type_t>
    struct tree_node
    {
        type_t data;
    
        list<tree_node<type_t>> childs;

        tree_node<type_t>* little_brother{nullptr}; 
        tree_node<type_t>* great_brother{nullptr};
        tree_node<type_t>* parent{nullptr}; 
    };


  

    /// #struct tree_dive_iterator
    /// #param type_t:
    ///     item type contained in current tree_node
    ///
    /// Iterator enables to explore tree by diving in 
    template<
        typename type_t>
    struct tree_dive_iterator 
    {
        mutable tree_node<type_t>* current{nullptr};
    };


    /// #operator ++ 
    /// #param type_t:
    ///     item type contained in tree_dive_iterator
    /// #arg __it[tree_dive_iterator<type_t>&]:
    ///     iterator to increment
    ///
    /// Increments the tree dive iterator    
    template<
        typename type_t>
    tree_dive_iterator<type_t>& 
    operator ++ (
        tree_dive_iterator<type_t>& __it)
    {
        if(__it.current != nullptr)
        {

        }

        return 
        __it;
    }


    /// #operator -- 
    /// #param type_t:
    ///     item type contained in tree_dive_iterator
    /// #arg __it[tree_dive_iterator<type_t>&]:
    ///     iterator to decrement
    ///
    /// Decrements the tree dive iterator 
    template<
        typename type_t>
    tree_dive_iterator<type_t>& 
    operator -- (
        tree_dive_iterator<type_t>& __it)
    {
        if(__it.parent != nullptr)
        {

        }

        return 
        __it;
    }
    
    
    
    
    
    template<
        typename type_t>
    struct tree_lateral_iterator
    {
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

    tree_iterator& 
    operator -- (
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