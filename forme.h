#pragma once

#include "constantes.h"

/** TEMPLATE DE CLASSE **/
template <typename T>
class Forme;

/** SURCHARGE DE std::cout << Forme **/
template <typename T>
ostream& operator<<(ostream& os, Forme<T>& forme);

template <typename T>
class Forme
{
public:

    /** CONSTRUCTEURS **/

    // Constructeur par defaut
    explicit Forme() = default;

    // Destrcuteur virtual pour autoriser l'appel des methodes des classes filles
    virtual ~Forme();

    // Constructeur avec parametres
    Forme(Color c, T epai, Color c_bor, Vector2f pos);

    // Constructeur par copie
    Forme(const Forme<T>& x);

    // Constructeur par deplacement
    Forme(Forme<T>&& x) noexcept;

    /** AFFECTATIONS **/

    // Affectation par copie
    Forme<T>& operator=(const Forme<T>& x);

    // Affectation par deplacement
    Forme<T>& operator=(Forme<T>&& x);

    /** AFFICHAGE **/

    // Afficher les details de la forme sur console
    friend ostream& operator<< <>(ostream& os, Forme& forme);

    // Afficher la forme sur fenetre
    virtual void operator>>(shared_ptr<sf::RenderWindow> &window);

    /** OPERATEURS **/

    // Taille +
    virtual Forme<T>& operator*(const int &scale);

    // Taille -
    virtual Forme<T>& operator/(const int &scale);

    // Positionner une forme
    Forme<T>& operator<<(const sf::Vector2f &vect);

    // Changer les couleurs
    Forme<T>& operator<<(const Couleur &couleur);

    // distance entre deux formes
    T operator%(const Forme<T>& forme);

    // comparer la superficie de deux formes
    bool operator<(Forme<T>& forme);
    bool operator>(Forme<T>& forme);
    bool operator==(Forme<T>& forme);

    // rotation
    Forme<T>& operator+(const int &degre);
    Forme<T>& operator-(const int &degre);

    // changement de la taille du contour
    Forme<T>& operator++();
    Forme<T>& operator--();

    /** METHODES **/

    virtual T superficie() const;
    virtual T perimetre() const;

    /** TEST TYPE  : Template de fonction **/

    // tester si 'forme' est de type G<H>
    template <typename G, typename H>
    friend bool typetest(Forme& forme);

protected:

    /** ATTRIBUTS **/

    Color couleur;
    T epai_bordure;
    Color couleur_bor;
    Vector2f position;

};
