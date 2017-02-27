#ifndef __THODD_DSL_HPP__
#  define __THODD_DSL_HPP__

#  include <thodd/meta.hpp>
#  include <thodd/tuple.hpp>

namespace thodd
{
    /// #(struct) dsl_expression
    /// #(params)
    ///     nodes_t... types des noeuds présents dans l'expression. 
    ///
    /// #(members)
    ///     nodes : tuple<nodes_t...> 
    ///         stockage des noeuds de l'expressions
    ///         sous forme d'un tuple.
    ///
    /// Une dsl_expression permet d'aggréger des noeuds 
    /// de différents types.
    template<
        typename ... nodes_t>
    struct dsl_expression
    {
        tuple<nodes_t...> nodes;    
    };

    /// #(struct) dsl_node
    /// #(params)
    ///     node_t type du noeud encapsulé. 
    ///
    /// #(members)
    ///     node : node_t 
    ///         stockage du noeud
    ///
    /// Une dsl_node permet le stockage unitaire d'un 
    /// noeud d'un type_t donné.
    template<
        typename node_t>
    struct dsl_node
    {
        node_t node;
    };

    /// #(struct) dsl_expressions
    /// #(params)
    ///     expressions_t... types des expressions_t 
    ///                      regroupées dans la liste. 
    ///
    /// #(members)
    ///     expressions : tuple<expressions_t...> 
    ///         stockage des expressions au sein d'un tuple.
    ///
    /// Une dsl_expressions permet d'aggréger un ensemble 
    /// d'expressions.
    template<
        typename ... expressions_t>
    struct dsl_expressions
    {
        tuple<expressions_t...> expressions;
    };

    /// #(function) get
    /// #(params) 
    ///     index_c : size_t index du noeud à 
    ///                      extraire de la dsl_expression.
    ///     nodes_t... ensemble des types des noeuds 
    ///                présents dans la dsl_expression.
    /// 
    /// #(arguments)
    ///     __cdsl : dsl_expression<nodes_t...>
    ///         expression de laquelle un noeud va être extrait.
    ///
    /// Extrait un noeud d'une expression en 
    /// fonction de son index dans celle-ci. 
    template<
        size_t index_c,
        typename ... nodes_t>
    constexpr auto
    get(
        dsl_expression<nodes_t...> const& __cdsl)
    {
        return get<index_c>(__cdsl.nodes);
    }

    /// #(function) get
    /// #(params) 
    ///     index_c : size_t index de l'expression à 
    ///                      extraire de la dsl_expression.
    ///     expressions_t... ensemble des types des expressions 
    ///                      présentes dans la dsl_expressions.
    /// 
    /// #(arguments)
    ///     __cdsl : dsl_expressions<expressions_t...>
    ///         expressions de laquelle une expression va être extraite.
    ///
    /// Extrait un noeud d'une expression en 
    /// fonction de son index dans celle-ci. 
    template<
        size_t index_c,
        typename ... expressions_t>
    constexpr auto
    get(
        dsl_expressions<expressions_t...> const& __cdsl)
    {
        return get<index_c>(__cdsl.expressions);
    }

    /// #(operator) >
    /// #(params) 
    ///     nodes_t... type des noeuds déjà présents 
    ///                dans la dsl_expression. 
    ///     node_t type du noeud à rajouter dans
    ///            la dsl_expression.
    /// 
    /// #(arguments)
    ///     __cdsl : dsl_expression<nodes_t...>
    ///         expression dans laquelle un nouveau noeud
    ///         va être inséré entrainant ainsi la 
    ///         création d'une nouvelle dsl_expression.
    ///     __node : noeud à ajouter dans la dsl_expression.
    ///
    /// Ajoute un noeud dans une dsl_expression.
    template<
        typename ... nodes_t,
        typename node_t>
    constexpr auto
    operator > (
        dsl_expression<nodes_t...> const& __cdsl,
        dsl_node<node_t> const& __node)
    {
        return dsl_expression<nodes_t..., meta::decay<node_t>>{__cdsl.nodes + make_tuple(__node.node)};
    }

    /// #(operator) >
    /// #(params) 
    ///     nodes_t... type des noeuds déjà présents 
    ///                dans la dsl_expression. 
    ///     node_t type du noeud à rajouter dans
    ///            la dsl_expression.
    /// 
    /// #(arguments)
    ///     __cdsl : dsl_expression<nodes_t...>
    ///         expression dans laquelle un nouveau noeud
    ///         va être inséré entrainant ainsi la 
    ///         création d'une nouvelle dsl_expression.
    ///     __node : noeud à ajouter dans la dsl_expression.   
    ///
    /// Ajoute un noeud dans une dsl_expression.
    template<
        typename ... nodes_t,
        typename node_t>
    constexpr auto
    operator > (
        dsl_node<node_t> const& __node, 
        dsl_expression<nodes_t...> const& __cdsl)
    {
        return dsl_expression<meta::decay<node_t>, nodes_t...>{make_tuple(__node.node) + __cdsl.nodes};
    }

    /// #(operator) >
    /// #(params) 
    ///     func1_t type du foncteur présent dans le premier noeud. 
    ///     func2_t type du foncteur présent dans le second noeud.
    /// 
    /// #(arguments)
    ///     __node1 :dsl_node<func1_t>
    ///         premier noeud d'une nouvelle dsl_expression.
    ///     __node2 :dsl_node<func1_t>
    ///         second noeud d'une nouvelle dsl_expression.
    /// 
    /// Créer une dsl_expression à partir de deux noeuds.
    template<
        typename func1_t, 
        typename func2_t>
    constexpr auto
    operator > (
        dsl_node<func1_t> const& __node1,
        dsl_node<func2_t> const& __node2)
    {
        return dsl_expression<func1_t, func2_t>{make_tuple(__node1.node, __node2.node)};
    }

    /// #(operator) ,
    /// #(params) 
    ///     lnodes_t... types des noeuds de la dsl_expression de gauche.
    ///     rnodes_t... types des noeuds de la dsl_expression de droite.
    ///      
    /// #(args)
    ///     __lexpression : dsl_expression<lnodes_t...>
    ///         dsl_expression de gauche.
    ///     __rexpression : dsl_expression<rnodes_t...>
    ///         dsl_expression droite. 
    ///
    /// Construit une dsl_expressions à partir de
    /// deux dsl_expression.
    template<
        typename ... lnodes_t, 
        typename ... rnodes_t>
    constexpr auto 
    operator , (
        dsl_expression<lnodes_t...> const& __lexpression,
        dsl_expression<rnodes_t...> const& __rexpression)
    {
        using left_t = dsl_expression<lnodes_t...>;
        using right_t = dsl_expression<rnodes_t...>;

        return dsl_expressions<left_t, right_t>{
                    make_tuple(__lexpression, 
                               __rexpression)};
    }

    /// #(operator) ,
    /// #(params) 
    ///     expressions_t... types des expressions déjà présentes
    ///                      dans la dsl_expressions.
    ///     nodes_t... types des noeuds de la dsl_expression à
    ///                ajouter à la dsl_expressions
    ///
    /// #(args)
    ///     __expressions : dsl_expressions<expressions_t...>
    ///         dsl_expressions dans laquelle on 
    ///         va ajouter une expression.
    ///     __expression : dsl_expression<nodes_t...>
    ///         dsl_expression qui va être ajoutée à la 
    ///         dsl_expressions entrainant la création
    ///         d'une nouvelle dsl_expressions.
    ///
    /// Ajoute une dsl_expression dans une dsl_expressions.
    template<
        typename ... expressions_t,
        typename ... nodes_t>
    constexpr auto
    operator , (
        dsl_expressions<expressions_t...> const& __expressions,
        dsl_expression<nodes_t...> const __expression)
    {
        using right_t = dsl_expression<nodes_t...>;

        return dsl_expressions<expressions_t..., right_t>
                {__expressions.expressions + __expression};
    }


    namespace detail
    {
        template<
            template<typename> 
            typename dsl_t>
        struct go_launcher
        {
             template<
                typename ... nodes_t, 
                typename ... args_t>
            constexpr auto 
            operator()(
                dsl_expression<nodes_t...> const& __dsl, 
                args_t&&... __args) const
            {
                constexpr dsl_t<dsl_expression<nodes_t...>> __lang{};
                return __lang(__dsl, perfect<args_t>(__args)...);
            }


            template<
                typename ... expressions_t, 
                typename ... args_t,
                size_t ... indexes_c>
            constexpr void 
            operator()(
                indexes<indexes_c...> const&, 
                dsl_expressions<expressions_t...> const& __dsls,
                args_t&&... __args) const
            {
                repeat{(go_launcher<dsl_t>{}(get<indexes_c>(__dsls), 
                        perfect<args_t>(__args)...), 0)...};
            }


            template<
                typename ... expressions_t, 
                typename ... args_t>
            constexpr void 
            operator()(
                dsl_expressions<expressions_t...> const& __dsls,
                args_t&&... __args) const
            {
                go_launcher<dsl_t>{}(make_indexes<sizeof...(expressions_t)>{}, __dsls, perfect<args_t>(__args)...);
            }
        };
    }

    template<
        template<typename>
        typename dsl_t>
    extern constexpr auto go = detail::go_launcher<dsl_t>{};

   
   
    template<
        template<typename...> typename node_t, 
        typename ... funcs_t>
    constexpr auto
    make_node(
        funcs_t&&... __funcs)
    {
        return dsl_node<node_t<meta::decay<funcs_t>...>>
                {{perfect<funcs_t>(__funcs)...}};
    }

}

#endif