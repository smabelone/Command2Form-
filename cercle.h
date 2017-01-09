#pragma once

#include "forme.h"

template<typename T>
class Cercle : public Forme<T>
{
public:

    /** CONSTRUCTEURS **/
    explicit Cercle() = default;
    Cercle(Color c, T epai, Color c_bor, Vector2f pos, T r);
    Cercle(Color c, T epai, Color c_bor, T x, T y, T r);
    Cercle(const Cercle<T>& x);
    Cercle(Cercle<T>&& x);

    /** DESTRUCTEUR **/
    ~Cercle();

    /** AFFICHAGE **/
    void operator>>(shared_ptr<sf::RenderWindow> &window);

    /** SURCHARGE OPERATEURS **/

    Cercle<T>& operator=(const Cercle<T>& x);
    Cercle<T>& operator=(Cercle<T>&& x);
    void operator[](Color c);
    Cercle<T>& operator*(const int &scale);
    Cercle<T>& operator+(const sf::Vector2f &vect);
    Cercle<T>& operator/(const int &scale);

    /** METHODES **/

    T superficie() const;
    T perimetre() const;
    T getRayon() const;
    CircleShape& getCercle();
    friend Cercle<T> flushCercle(Cercle<T> cercle);

protected:

    T rayon;
    CircleShape cercle;
};

