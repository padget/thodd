#ifndef __THODD_CONTAINER_TREE_HPP__
#  define __THODD_CONTAINER_TREE_HPP__

#  include <thodd/container/list.hpp>
#  include <thodd/core/destroy.hpp>

namespace 
thodd
{
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


    template<
        typename type_t>
    constexpr auto 
    has_childs(
        tree_node<type_t> const& __node)
    {
        return 
        __node.childs.size() > 0u;
    }


    template<
        typename type_t>
    constexpr auto 
    has_parent(
        tree_node<type_t> const& __node)
    {
        return 
        __node.parent != nullptr;
    }

    template<
        typename type_t>
    constexpr auto 
    has_little_brother(
        tree_node<type_t> const& __node)
    {
        return 
        __node.little_brother != nullptr;
    }
  

    template<
        typename type_t>
    constexpr auto 
    has_great_brother(
        tree_node<type_t> const& __node)
    {
        return 
        __node.great_brother != nullptr;
    }


    template<
        typename type_t>
    struct rlg_tree_iterator 
    {
        mutable tree_node<type_t>* current{nullptr};
    };

    template<
        typename type_t>
    rlg_tree_iterator<type_t>& 
    dive(
        rlg_tree_iterator<type_t>& __it)
    {
        __it.current = &*__it.current->childs.begin();
        
        return 
        __it;
    }

    
    template<
        typename type_t>
    rlg_tree_iterator<type_t> const& 
    dive(
        rlg_tree_iterator<type_t> const& __it)
    {
        dive(const_cast<rlg_tree_iterator<type_t>&>(__it));

        return 
        __it;
    }


    template<
        typename type_t>
    rlg_tree_iterator<type_t>& 
    rise(
        rlg_tree_iterator<type_t>& __it)
    {
        __it.current = __it.current->parent;
        
        return 
        __it;
    }

    
    template<
        typename type_t>
    rlg_tree_iterator<type_t> const& 
    rise(
        rlg_tree_iterator<type_t> const& __it)
    {
        rise(const_cast<rlg_tree_iterator<type_t>&>(__it));
        
        return 
        __it;
    }

    template<
        typename type_t>
    rlg_tree_iterator<type_t>& 
    go_great(
        rlg_tree_iterator<type_t>& __it)
    {
        __it.current = __it.current->great_brother;
        
        return 
        __it;
    }

    
    template<
        typename type_t>
    rlg_tree_iterator<type_t> const& 
    go_great(
        rlg_tree_iterator<type_t> const& __it)
    {
        go_great(const_cast<rlg_tree_iterator<type_t>&>(__it));
        
        return 
        __it;
    }


    template<
        typename type_t>
    rlg_tree_iterator<type_t>& 
    go_little(
        rlg_tree_iterator<type_t>& __it)
    {
        __it.current = __it.current->little_brother;
        
        return 
        __it;
    }

    
    template<
        typename type_t>
    rlg_tree_iterator<type_t> const& 
    go_little(
        rlg_tree_iterator<type_t> const& __it)
    {
        go_little(const_cast<rlg_tree_iterator<type_t>&>(__it));
        
        return 
        __it;
    }


    template<
        typename type_t>
    rlg_tree_iterator<type_t>& 
    operator ++ (
        rlg_tree_iterator<type_t>& __it)
    {
        if (__it.current != nullptr)
        {
            if (has_childs(*__it.current)) 
                dive(__it);
            
            else if (has_great_brother(*__it.current))
                go_great(__it);

            else 
            {
                while (has_parent(*__it.current) 
                    && !has_great_brother(*__it.current))
                    rise(__it);
                
                go_great(__it);
            }
        }

        return 
        __it;
    }


    template<
        typename type_t>
    rlg_tree_iterator<type_t> const& 
    operator ++ (
        rlg_tree_iterator<type_t> const& __it)
    {
        ++const_cast<rlg_tree_iterator<type_t>&>(__it);

        return 
        __it;
    }


    template<
        typename type_t>
    type_t& 
    operator * (
        rlg_tree_iterator<type_t>& __it) 
    {
        return 
        __it.current->data;
    }


    template<
        typename type_t>
    type_t const& 
    operator * (
        rlg_tree_iterator<type_t> const& __it) 
    {
        return 
        __it.current->data;
    }





    template<
        typename type_t>
    using default_tree_iterator = rlg_tree_iterator<type_t>;


    template<
        typename type_t>
    class tree
    {
        using root_t = tree_node<type_t>;

        root_t* m_root{nullptr};
        size_t m_size{0u};

    public:
        using iterator_type = default_tree_iterator<type_t>;

    public:
        tree() = default;
        tree(tree&&) = default;
        ~tree() 
        {
            thodd::destroy(m_root);
        }

        tree(tree const&) = default;
    
    public:
        tree& operator = (tree const&) = default;
        tree& operator = (tree&&) = default;

    public:
        constexpr auto
        size() const
        {
            return m_size;
        }

    private:
        constexpr void
        realign() 
        {

        }

    public: 

        inline iterator_type
        push_at(
            auto&& __item,
            iterator_type __pos)
        {
            if (__pos.current != nullptr)
                __pos.current->childs.push_at(
                    perfect<decltype(__item)>(__item), 
                    __pos.current->childs.end());

            ++m_size;
        }
    };
}

#endif