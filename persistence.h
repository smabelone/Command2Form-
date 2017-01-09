#pragma once

#include "constantes.h"

/** TEMPLATE DE CLASSE **/
template <typename C, typename V>
class Persistence;

/** SURCHARGE DE std::cout << Persistance **/
template <typename C, typename V>
ostream& operator<<(ostream& os, const shared_ptr<Persistence<C,V>>& persist);

template <typename C, typename V>
class Persistence
{

public :

    /** CONSTRUCTEURS **/
    explicit Persistence() = default;

    /** DESTRUCTEUR **/
    ~Persistence();

    /** METHODES **/

    /* Supprimer un element */
    void supprimer(C cle, shared_ptr<sf::RenderWindow> window);

    /* Supprimer tout les elements de la persistance */
    void vider(shared_ptr<sf::RenderWindow> window);

    /** SURCHARGE OPERATEURS **/

    /* atteindre un element via une clé */
    shared_ptr<V>& operator[](const C &cle);

    /* inserer un couple clé-valeur */
    void operator()(const C &cle, const shared_ptr<V> &valeur, shared_ptr<sf::RenderWindow> &window);

    /* Afficher tout les objets de la persistance sur Window */
    void operator>>(shared_ptr<sf::RenderWindow> &window) const;

    /** AFFICHAGE **/
    friend ostream& operator<< <>(ostream& os, const shared_ptr<Persistence>& persist);

    private :

    /* Voir si un element existe, selon la clé */
    int existe(C cle);

protected:

    /* Utilisation de la classe std::map */
    map<C,shared_ptr<V>> data;

};

