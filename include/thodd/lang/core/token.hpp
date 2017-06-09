#ifndef __THODD_LANG_CORE_TOKEN_HPP__
#  define __THODD_LANG_CORE_TOKEN_HPP__

#  include <thodd/container/range.hpp>
#  include <thodd/pointer/unique.hpp>
#  include <thodd/meta/traits/decay.hpp>
#  include <thodd/core/rvalue.hpp>

namespace 
thodd::lang 
{
    /// struct token : 
    ///     Un token est un élément transportant l'information du début et de la fin d'un morceau
    ///     d'un flux de données (une sous chaine du flux). Le token connait aussi sont suivant.
    ///     Enfin, un token possède un 'type' parmi un ensemble possible de types. Cela permet de
    ///     donner une information supplémentaire sur comment doit être traité le contenu du token.
    template<
        typename enum_t, 
        typename iterator_t>
    struct token
    {
        enum_t type;
        range<iterator_t> matched ;
        unique<token> next ;
    };


    /// function make_token :
    ///     Permet de construire un token à partir d'un type, d'un début et d'une fin. 
    constexpr auto 
    make_token (
        auto&& __type, 
        auto&& __begin, 
        auto&& __end)
    {
        using type_t = decltype(__type); 
        using begin_t = decltype(__begin);
        using end_t = decltype(__end);

        return 
        token<
            meta::decay_t<type_t>, 
            meta::decay_t<begin_t>>
        { perfect<type_t>(__type), 
          range<meta::decay_t<begin_t>>
          { perfect<begin_t>(__begin), 
            prefect<end_t>(__end) } } ;
    }


    /// function append :
    ///     Ajoute un token à la suite d'un autre token. Retourne le token ajouté.
    template<
        typename enum_t, 
        typename iterator_t>
    inline auto
    append (
        token<enum_t, iterator_t>& __token, 
        token<enum_t, iterator_t>&& __next)
    -> decltype(auto)
    {
        __token.next = make_unique(rvalue(__next)) ;

        return 
        (*__token.next) ; 
    }
}

#endif