#pragma once

#include "forme.h"

template<typename T>
class Polygone : public Forme<T>
{
public:

    /** CONSTRUCTEURS **/
    explicit Polygone() = default;
    Polygone(Color c, T epai, Color c_bor, Vector2f pos, T r, unsigned int points);
    Polygone(Color c, T epai, Color c_bor, T x, T y, T r, unsigned int points);
    Polygone(const Polygone<T>& x);
    Polygone(Polygone<T>&& x);

    /** DESTRUCTEUR **/
    ~Polygone();

    /** AFFICHAGE **/
    void operator>>(shared_ptr<sf::RenderWindow> &window);

    /** SURCHARGE OPERATEURS **/
    Polygone<T>& operator=(const Polygone<T>& x);
    Polygone<T>& operator=(Polygone<T>&& x);
    void operator[](Color c);
    Polygone<T>& operator*(const int &scale);
    Polygone<T>& operator+(const sf::Vector2f &vect);
    Polygone<T>& operator/(const int &scale);

    /** METHODES **/
    T superficie() const;
    T perimetre() const;
    T getRayon() const;
    T getNbr_points() const;
    CircleShape& getPolygone();

    friend Polygone<T> flushPolygone(Polygone<T> polygone);

protected:

    T rayon;
	unsigned int nbr_points;
    CircleShape polygone;
};

