#ifndef __PERSISTANCE__
#define __PERSISTANCE__

#include "constantes.h"

template <typename C, typename V>
class Persistence;

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
    //void ajouter(C cle, shared_ptr<V> valeur, shared_ptr<sf::RenderWindow> window);
    void supprimer(C cle, shared_ptr<sf::RenderWindow> window);
    void vider(shared_ptr<sf::RenderWindow> window);

    /** SURCHARGE OPERATEURS **/
    shared_ptr<V>& operator[](const C &cle);
    void operator()(const C &cle, const shared_ptr<V> &valeur, shared_ptr<sf::RenderWindow> &window);
    void operator>>(shared_ptr<sf::RenderWindow> &window) const;


    /** AFFICHAGE **/
    friend ostream& operator<< <>(ostream& os, const shared_ptr<Persistence>& persist);

    private :
    int existe(C cle);

protected:

    map<C,shared_ptr<V>> data;

};

#endif // __PERSISTANCE__

