#pragma once

#include "forme.h"

template<typename T>
class Rectangle : public Forme<T>
{
public:

    /* CONSTRUCTEURS */
    explicit Rectangle() = default;
    Rectangle(Color c, T epai, Color c_bor, Vector2f pos, T lo, T la);
    Rectangle(Color c, T epai, Color c_bor, T x, T y, T lo, T la);
    Rectangle(const Rectangle<T>& x);
    Rectangle(Rectangle<T>&& x);

    /* DESTRUCTEUR */
    ~Rectangle();

    /* AFFICHAGE */
    void operator>>(shared_ptr<sf::RenderWindow> &window);

    /* SURCHARGE OPERATEURS */
    Rectangle<T>& operator=(const Rectangle<T>& x);
    Rectangle<T>& operator=(Rectangle<T>&& x);
    void operator[](Color c);
    Rectangle<T>& operator*(const int &scale);
    Rectangle<T>& operator+(const sf::Vector2f &vect);
    Rectangle<T>& operator/(const int &scale);

    /* METHODES */
    T superficie() const;
    T perimetre() const;
    T getLongueur() const;
    T getLargeur() const;
    RectangleShape& getRectangle();

protected:

    T longueur;
    T largeur;
    RectangleShape rectangle;
};
