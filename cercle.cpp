

#pragma once
#include "Cercle.h"
#include "tools.h"

template<typename T>
Cercle<T>::~Cercle()
{
    delete &cercle;
}

// pour tester le constructeur par deplacement
template<typename T>
Cercle<T> flushCercle(Cercle<T> cercle)
{
    return cercle;
}

// Implémenter le constructeur
template<typename T>
Cercle<T>::Cercle(Color c, T epai, Color c_bor, Vector2f pos, T r) : Forme<T>(c, epai, c_bor, pos), rayon(r)
{
    debug("Constructeur : Cercle");
}

template<typename T>
Cercle<T>::Cercle(Color c, T epai, Color c_bor, T x, T y, T r) : Forme<T>(c, epai, c_bor, sf::Vector2f((float)x, (float)y)), rayon(r)
{
}

//le constructeur par copie
template<typename T>
Cercle<T>::Cercle(const Cercle<T>& x) : Forme<T>(x), rayon(x.rayon)
{
    debug("Affectation par copie: Cercle");
}

//constructeur par déplacement
template<typename T>
Cercle<T>::Cercle(Cercle<T>&& x) : Forme<T>(x), rayon(std::move(x.rayon))
{
    debug("Constructeur par deplacement : Cercle");
}


//affectation par copie
template<typename T>
Cercle<T>& Cercle<T>::operator=(const Cercle<T>& x)
{
    debug("Affectation par copie : Cercle");
    rayon = x.rayon;
    (Forme<T>)(*this)=(Forme<T>)x;
    return *this;
}


//affectation par déplacement
template<typename T>
Cercle<T>& Cercle<T>::operator=(Cercle<T>&& x)
{
    debug("Affectation par deplacement : Cercle");
    *this = move(x);
    rayon = move(x.rayon);
    *this = x;
    return *this;
}


//changer la couleur d'un cercle
template <typename T>
void Cercle<T>::operator[](const Color c)
{
    this.couleur = c;
}


template <typename T>
Cercle<T>& Cercle<T>::operator*(const int &scale)
{
    this->rayon *= scale;
    Cercle<int> nouveau = *this;
    cout << "surcharge *" << endl;
    return *this;
}


template <typename T>
Cercle<T>& Cercle<T>::operator+(const sf::Vector2f &vect)
{
    this->position.x += vect.x;
    this->position.y += vect.y;
    Cercle<T> nouveau = *this;
    cout << "surcharge +" << endl;
    return *this;
}


template <typename T>
Cercle<T>& Cercle<T>::operator/(const int &scale)
{
    if (scale>0)
    {
        this->rayon /= scale;
        Cercle<int> nouveau = *this;
        cout << "surcharge /" << endl;

    }
    else
    {
        throw string(SCALE_VALUE_INVALIDE);
    }
    return *this;
}


template<typename T>
void Cercle<T>::operator>>(shared_ptr<sf::RenderWindow> &window)
{
    this->cercle.setRadius(this->rayon);
    cercle.setFillColor(this->couleur);
    cercle.setOutlineColor(this->couleur_bor);
    cercle.setOutlineThickness(this->epai_bordure);
    cercle.setPosition(this->position);
    window->draw(cercle);
}


//calculer la superficie d'un cercle
template<typename T>
T Cercle<T>::superficie() const
{
    return (this->rayon)*(this->rayon)*(3.14);
}

//calculer le périmètre d'un cercle
template<typename T>
T Cercle<T>::perimetre() const
{
    return (this->rayon)*(3.14);
}


//récupérer le rayon d'un cercle
template<typename T>
T Cercle<T>::getRayon() const
{
    return this->rayon;
}

//récupérer le circleShape
template<typename T>
sf::CircleShape& Cercle<T>::getCercle()
{
    return this->cercle;
}
