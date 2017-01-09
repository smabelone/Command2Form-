#pragma once
#include "rectangle.h"
#include "tools.h"

template<typename T>
Rectangle<T>::~Rectangle()
{
    delete &rectangle;
}

// Implémenter le constructeur
template<typename T>
Rectangle<T>::Rectangle(Color c, T epai, Color c_bor, Vector2f pos, T lo, T la) : Forme<T>(c, epai, c_bor, pos), longueur(lo), largeur(la)
{
    debug("Constructeur : Rectangle");
}

template<typename T>
Rectangle<T>::Rectangle(Color c, T epai, Color c_bor, T x, T y, T lo, T la) : Forme<T>(c, epai, c_bor, sf::Vector2f((float)x, (float)y)), longueur(lo), largeur(la)
{

}

//le constructeur par copie
template<typename T>
Rectangle<T>::Rectangle(const Rectangle<T>& x) : Forme<T>(x), longueur(x.longueur), largeur(x.largeur)
{
    debug("Affectation par copie: Rectangle");
}

//constructeur par déplacement
template<typename T>
Rectangle<T>::Rectangle(Rectangle<T>&& x) : Forme<T>(x), longueur(std::move(x.longueur)), largeur(std::move(x.largeur))
{
    debug("Constructeur par deplacement : Rectangle");
}


//affectation par copie

template<typename T>
Rectangle<T>& Rectangle<T>::operator=(const Rectangle<T>& x)
{
    debug("Affectation par copie : Rectangle");
    longueur = x.longueur;
    largeur = x.largeur;
    (Forme<T>)(*this)=(Forme<T>)x;
    return *this;
}

//affectation par déplacement
template<typename T>
Rectangle<T>& Rectangle<T>::operator=(Rectangle<T>&& x)
{
    debug("Affectation par deplacement : Rectangle");
    *this = move(x);
    longueur = move(x.longueur);
    largeur = move(x.largeur);
    *this = x;
    return *this;
}

//changer la couleur d'un rectangle
template <typename T>
void Rectangle<T>::operator[](const Color c)
{
    this.couleur = c;
}

template <typename T>
Rectangle<T>& Rectangle<T>::operator*(const int &scale)
{
    this->longueur *= scale;
    this->largeur *= scale;
    Rectangle<int> nouveau = *this;
    cout << "surcharge *" << endl;
    return *this;
}

template <typename T>
Rectangle<T>& Rectangle<T>::operator+(const sf::Vector2f &vect)
{
    this->position.x += vect.x;
    this->position.y += vect.y;
    Rectangle<T> nouveau = *this;
    cout << "surcharge +" << endl;
    return *this;
}

template <typename T>
Rectangle<T>& Rectangle<T>::operator/(const int &scale)
{
    if (scale>0)
    {
        this->longueur /= scale;
        this->largeur /= scale;
        Rectangle<int> nouveau = *this;
        cout << "surcharge /" << endl;

    }
    else
    {
        throw string(SCALE_VALUE_INVALIDE);
    }
    return *this;
}

template<typename T>
void Rectangle<T>::operator>>(shared_ptr<sf::RenderWindow> &window)
{

    this->rectangle.setSize(sf::Vector2f(this->longueur, this->largeur));
    rectangle.setFillColor(this->couleur);
    rectangle.setOutlineColor(this->couleur_bor);
    rectangle.setOutlineThickness(this->epai_bordure);
    rectangle.setPosition(this->position);
    window->draw(rectangle);
}


//calculer la superficie d'un rectangle
template<typename T>
T Rectangle<T>::superficie() const
{
    return (this->longueur)*(this->largeur);
}

//calculer le périmètre d'un rectangle
template<typename T>
T Rectangle<T>::perimetre() const
{
    return (longueur+largeur)*2;
}

//calculer la superficie d'un rectangle
template<typename T>
T Rectangle<T>::getLongueur() const
{
    return longueur;
}

//calculer le périmètre d'un rectangle
template<typename T>
T Rectangle<T>::getLargeur() const
{
    return largeur;
}

template<typename T>
sf::RectangleShape& Rectangle<T>::getRectangle()
{
    return this->rectangle;
}

// pour tester le constructeur par deplacement
template<typename T>
Rectangle<T> flushRectangle(Rectangle<T> rect)
{
    return rect;
}
