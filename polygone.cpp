#pragma once
#include "Polygone.h"
#include "tools.h"
#include "cmath"

template<typename T>
Polygone<T>::~Polygone()
{
    delete &polygone;
}

// Implémenter le constructeur
template<typename T>
Polygone<T>::Polygone(Color c, T epai, Color c_bor, Vector2f pos, T r, unsigned int points) : Forme<T>(c, epai, c_bor, pos), rayon(r), nbr_points(points)
{
    switch (points)
	{
	case 3:
		debug("Constructeur : Polygone regulier --> Triangle");
		break;
	case 4:
		debug("Constructeur : Polygone regulier --> Carre");
		break;
	case 8:
		debug("Constructeur : Polygone regulier --> Octogone");
		break;
	default:
		debug("Constructeur : Polygone regulier");
		break;
	}
}

template<typename T>
Polygone<T>::Polygone(Color c, T epai, Color c_bor, T x, T y, T r, unsigned int points) : Forme<T>(c, epai, c_bor, sf::Vector2f((float)x, (float)y)), rayon(r), nbr_points(points)
{

}

//le constructeur par copie
template<typename T>
Polygone<T>::Polygone(const Polygone<T>& x) : Forme<T>(x), rayon(x.rayon), nbr_points(x.nbr_points)
{
    debug("Affectation par copie: Polygone");
}


//constructeur par déplacement
template<typename T>
Polygone<T>::Polygone(Polygone<T>&& x) : Forme<T>(x), rayon(std::move(x.rayon)), nbr_points(std::move(x.nbr_points))
{
    debug("Constructeur par deplacement : Polygone");
}


//affectation par copie
template<typename T>
Polygone<T>& Polygone<T>::operator=(const Polygone<T>& x)
{
    debug("Affectation par copie : Polygone");
    rayon = x.rayon;
    nbr_points= x.nbr_points;
    (Forme<T>)(*this)=(Forme<T>)x;
    return *this;
}

//affectation par déplacement
template<typename T>
Polygone<T>& Polygone<T>::operator=(Polygone<T>&& x)
{
    debug("Affectation par deplacement : Polygone");
    *this = move(x);
    rayon = move(x.rayon);
    nbr_points = move(x.nbr_points);
    *this = x;
    return *this;
}


//changer la couleur d'un polygone
template <typename T>
void Polygone<T>::operator[](const Color c)
{
    this.couleur = c;
}

template <typename T>
Polygone<T>& Polygone<T>::operator*(const int &scale)
{
    this->rayon*= scale;
    Polygone<int> nouveau = *this;
    cout << "surcharge *" << endl;
    return *this;
}

template <typename T>
Polygone<T>& Polygone<T>::operator+(const sf::Vector2f &vect)
{
    this->position.x += vect.x;
    this->position.y += vect.y;
    Polygone<T> nouveau = *this;
    cout << "surcharge +" << endl;
    return *this;
}


template <typename T>
Polygone<T>& Polygone<T>::operator/(const int &scale)
{
    if (scale>0)
    {
        this->rayon /= scale;
        Polygone<int> nouveau = *this;
        cout << "surcharge /" << endl;

    }
    else
    {
        throw string(SCALE_VALUE_INVALIDE);
    }
    return *this;
}


template<typename T>
void Polygone<T>::operator>>(shared_ptr<sf::RenderWindow> &window)
{
    polygone.setRadius(this->rayon);
    polygone.setPointCount(this->nbr_points);
    polygone.setFillColor(this->couleur);
    polygone.setOutlineColor(this->couleur_bor);
    polygone.setOutlineThickness(this->epai_bordure);
    polygone.setPosition(this->position);
    window->draw(polygone);
}

//calculer la superficie d'un rectangle
template<typename T>
T Polygone<T>::superficie() const
{
  return ( (this->nbr_points/2)*(pow(this->rayon, 2))*(sin(360/this->nbr_points)) );
}

//calculer le périmètre d'un rectangle
template<typename T>
T Polygone<T>::perimetre() const
{
    return ( 2*(this->nbr_points)*(this->rayon)*(sin(180/this->nbr_points)) );
}

//récupérer le rayon d'un polygone
template<typename T>
T Polygone<T>::getRayon() const
{
    return this->rayon;
}

//récupérer le nombre de cotés d'un polygone
template<typename T>
T Polygone<T>::getNbr_points() const
{
    return this->nbr_points;
}

template<typename T>
sf::CircleShape& Polygone<T>::getPolygone()
{
    return this->polygone;
}

// pour tester le constructeur par deplacement
template<typename T>
Polygone<T> flushPolygone(Polygone<T> polygone)
{
    return polygone;
}
