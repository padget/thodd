# Valeur, Référence faible(#), Référence forte([#]), Alias (##)

## Valeur 

Une valeur est une variable qui a été initialisé dans la pile. 

## Alias

Un alias n'est qu'un simple renommage d'une variable (quelque soit sa nature).

## Référence faible vs Référence forte

Toutes deux sont nullables. Ce qui diffère vraiment est la durée de vie de chacune. Une référence faible n'a, à proprement parler, pas  de cycle de vie étant donnée qu'au moment de l'invalidation du scope parent, la variable pointée par la référence ne sera pas invalidé elle aussi. Alors que dans le cas d'une référence forte, la variable pointée sera invalidée juste avant l'invalidation du scope parent.


## Quelque chose vers une Référence forte

Affecter une variable dans une référence forte va modifier le scope parent de la valeur portée par la variable. Ainsi on évite les copies de données, on va juste déplacer celle-ci dans un nouveau scope. 

Par exemple, on crée le noeud d'une liste chainée indépendemment de celle-ci, puis on l'ajoute dans la liste chainée. Au lieu de faire des copies en profondeur de cette donnée dans une instance clone de la liste chainée, on va simplement déplacer la donnée dans le scope de la liste chainée.

Bien entendu, ce déplacement va rendre invalide l'utilisation de la variable dont la valeur a ainsi été déplacée. Toute utilisation ultérieure de cette variable provoquera une erreur d'exécution (à voir si l'erreur peut être détectée à la compilation).

De plus, si jamais la référence forte contenait au préalable une valeur alors, celle-ci sera détruite juste avant la prochaine affectation. Affecter une valeur null à une référence forte est donc un moyen de détruire des valeurs dont on ne veut plus.  


## Quelque chose vers une Référence faible

Une référence faible ne modifiant pas le cycle de vie de la variable pointée, il n'y a pas de problème d'invalidité de cette dernière après son référencement faible. 


## Quelque chose vers une valeur

Quand on affecte quelque chose à une variable de type valeur, alors il y a copie de la première dans la seconde. Lorsque le quelque chose qui est affecté à une valeur est null il y a alors erreur d'exécution. 


## Quelque chose vers un alias

Un alias est, rappellons le, non nullable, et ne peut donc faire allusion qu'à une variable de type valeur. Le fait de passer par un alias au lieu d'une référence faible, garantit qu'en dessous nous avons à faire à une valeur forcément non null (pb de compilation autrement). A partir du moment où il y a utilisation de référence faible, il faudra continuer à utiliser les références faibles/fortes.


## Référence forte vs Valeur

La différence fondamentale pour entre une référence forte et une valeur est la nullabilité de la première contrairement à la seconde. 

## Symbolismes

Référence forte : 

    i : [#]int = 12;

Référence faible :

    i2 : #int = i;

Valeur :

    i3 : int = 12;

Alias :

    i4 : @int = i3;


# Ensemble et POD (Plain of data)

## Plain of Data

Les POD permettent la composition de type au sein d'une même structure :


    pod name_age: /// déclaration d'un pod
    { 
        name : string; /// string sera développé ultérieurement
        age  : uint;
    };


## Ensemble

La notion d'ensemble permet de définir une ou plusieurs restriction sur un type donné :


    age : {a : uint | 0 < a && a < 150}; /// age est l'ensemble des objets a de type uint tel que a est compris entre 0 et 150.
                                        /// On définit donc ainsi un ensemble d'objet par restriction conditionnelle sur un ensemble plus vaste.


Formellement on définit un ensemble de la manière suivante :


    <name> ':' '{' <instance_name> ':' <type> '|' <expression> '}' /// <expression> doit être sémantiquement booléenne  



Un ensemble se définit donc comme un sous ensemble contraint par une expression booléenne d'un autre ensemble plus vaste.
Cette expression booléenne sera vérifié à chaque initialisation/affectation de valeur à la variable de type_t (type_t étant le nom de l'ensemble défini) :


    type_t : {o : other_t | expression_on_other_t(o) } ; /// expression_on_other_t(o) renvois doit renvoyer une valeur booléenne   

    t : type_t = ... /// ... est la valeur affecté à t et doit vérifier la contrainte expression_on_other_t(...) 
                    /// sinon l'affectation ne peut avoir lieu et une erreur est levée (cf gestion des erreurs).

    t = ... /// affectation d'une autre valeur, de même que pour l'initialisation, la nouvelle valeur doit passer la contrainte
            /// avant de pouvoir être affectée à t.


## Instantiation d'un type_t

Maintenant que nous avons vu un certain nombre de type de base possible (pointeur, integral, flottant, reference, set, pod, ...)
il nous faut nous intéresser à leur utilisation de base : l'instantiation. 
Instancier un type signifie déclarer une variable capable de contenir les valeurs de ce type.
Formellement, l'instantiation se déroule de la façon suivante :

    <name> ':' <type> ('=' <expression>) ? ';' 

on a donc une variable '<name>' de type '<type>' avec éventuellement la valeur '<expression>'. L'expression '<expression>' doit 
compatible avec '<type>' (de même type ou bien convertible).

Une variable instancié n'a de sens que dans le scope où elle aura été déclarer. La variable sera détruire à la sortie du scope. 
Nous parlons bien ici de la variable et non pas de la valeur. Car il existe deux cas possible pour la valeur : 
  - elle se situe sur la pile : destruction en même temps que la variable.
  - elle se situe sur le tas : pas de destruction automatique (sauf si pointeur scopé).


### Instanciation statique

L'instanciation statique permet principalement de garantir la durée de vie d'une variable : elle est la même que celle du scope dans
lequel elle a été déclarée. 


### Instanciation dynamique

L'instanciation dynamique elle permet de laisser au développeur le soin de controlé la durée de vie de la valeur de la variable. 
Une allocation dynamique se fait par l'utilisation de l'allocateur 'new' et la destruction par 'delete'. 
Pour éviter toute fuite de mémoire, il y aura donc intérêt à conserver en permanence un pointeur vers la valeur qui a été allouée
dynamiquement pour que le moment venu, sa désallocation puisse se faire. Autrement, la zone mémoire correspondante serait perdue...

    <name> ':' '@'<type> = 'new' <type2> '(' <arguments> ')' ';' /// Allocation dynamique
    <name> ':' <type> = <expression> ';' /// allocation statique  
    'delete' <name> ';' /// désallocation dynamique 


# Pense bête

Le modèle de gestion de la mémoire pourrait être non pas basé sur un garbage collector automatique qui épargne à l'utilisateur toute préoccupation de la mémoire, mais plutôt sur un système semi automatique qui repose sur ce que va décider le développeur sur la manière dont il va modéliser ces données. Je ne veux pas de pointeur mais des références de différentes natures qui vont déterminer si la donnée référencée sera scopée ou non. En gros, je souhaite que le développeur se responsabilise et tienne compte du cycle de vie de ces données dans la mémoire afin de rendre celle-ci optimale (un Garbage Collector est souvent moins efficace qu'un humain sur ce point). Il n'y aura pas d'appel à un quelconque destructeur mais plus la définition du scope (contexte d'existence utile) de la donnée afin de détruire celle-ci automatiquement dès que le scope est invalidé. Ainsi n'est conservé en mémoire que ce qui est vraiment utilisé à un instant t et on s'épargne un thread qui se charge de collecter les références obsolètes et donc les détruires à ce moment là. 


# Module vs Feature

Deux mots clés pour deux choses distinctes :
- feature : signifie que le code dans le scope de ce mot clé est déclaré comme étant du code métier et n'est donc pas exportable en dehors de l'unité de compilation.
- module : signifie que le code dans le scope de ce mot clé est déclaré comme étant du code technique et est donc exportable en dehors de l'unité de compilation.

Exemple feature:
    
    /// Calculatrice.thodd

    feature calc
    {
        add: 
            > a:int 
            > b:int
            -> a + b
    }

Dans cet exemple la fonction add ne pourra être utilisé que dans le fichier Calculatrice.thodd

Exemple module:
    
    /// Calculatrice.thodd

    module calc
    {
        add: 
            > a:int 
            > b:int
            -> a + b
    }

Dans cet exemple, contrairement au précédent, add pourra être utilisé via un import de celle-ci dans d'autres unités de compilation.


# Import d'unité de compilation

Avec l'utilisation du mot clé 'import' dans une unité de compilation (un fichier .thodd), on peut importer des fonction, pod, view d'autres unités de compilation. Attention, tout ce qui a été déclaré dans un scope de type feature ne peut être utilisé autre part que dans ce même scope. 

Plusieurs constructions sont possibles : 
    /// import a module with fullpath
    import thodd.math /// thodd.math.add(....)

    /// import a module with an aliasing
    import thodd.math as math /// math.add(....)

    /// import a function, pod, view from a module
    from thodd.math import add /// add(....)

    /// import a function, pod, view from a module with aliasing 
    from thodd.math import add as plus /// plus(....)
