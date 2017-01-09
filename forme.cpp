#pragma once

#include "forme.h"
#include <SFML/Graphics.hpp>
#include "tools.h"
#include "rectangle.h"
#include "Cercle.h"
#include "Polygone.h"

// test type
template <typename G, typename H>
bool typetest(Forme<H>& forme){

    return !strcmp( typeid(forme).name(), typeid(G).name() );
}


template <typename T>
Forme<T>::~Forme()
{
    delete &couleur;
    delete &couleur_bor;
    delete &position;

}

template <typename T>
Forme<T>::Forme(Color c, T epai, Color c_bor, Vector2f pos) :couleur(c), epai_bordure(epai), couleur_bor(c_bor), position(pos)
{
    debug("Constructeur : Forme");
}

//le constructeur par copie
template<typename T>
Forme<T>::Forme(const Forme<T>& x) : couleur(x.couleur), epai_bordure(x.epai_bordure), couleur_bor(x.couleur_bor), position(x.position)
{
    debug("Constructeur par copie : Forme");
}

//constructeur par déplacement
template<typename T>
Forme<T>::Forme(Forme<T>&& x) noexcept : couleur(std::move(x.couleur)), epai_bordure(std::move(x.epai_bordure)), couleur_bor(std::move(x.couleur_bor)), position(std::move(x.position))
{
    debug("Constructeur par deplacement : Forme");
}


//affectation par copie
template<typename T>
Forme<T>& Forme<T>::operator=(const Forme<T>& x)
{
    debug("Affectation par copie : Forme");
    couleur=x.couleur;
    epai_bordure=x.epai_bordure;
    couleur_bor = x.couleur_bor;
    position = x.position;
    return *this;
}


//affectation par déplacement
template<typename T>
Forme<T>& Forme<T>::operator=(Forme<T>&& x)
{
    debug("Affectation par deplacement : Forme");
    couleur = std::move(x.couleur);
    epai_bordure = std::move(x.epai_bordure);
    couleur_bor = std::move(x.couleur_bor);
    position = std::move(x.position);
    return *this;
}

template <typename T>
Forme<T>& Forme<T>::operator*(const int &scale)
{
    //"cette methode ne doit pas etre appelée"
    return *this;
}

template <typename T>
Forme<T>& Forme<T>::operator/(const int &scale)
{
    //"cette methode ne doit pas etre appelée"
    return *this;
}


template <typename T>
Forme<T>& Forme<T>::operator<<(const sf::Vector2f &vect)
{
    debug("Surcharge operateur << Vecteur");
    this->position.x = vect.x;
    this->position.y = vect.y;
    return *this;
}

template <typename T>
Forme<T>& Forme<T>::operator<<(const Couleur &couleur)
{
    debug("Surcharge operateur << Couleur");
    if (!couleur.type) this->couleur = couleur.col;
    else this->couleur_bor = couleur.col;
    return *this;
}

template<typename T>
void Forme<T>::operator>>(shared_ptr<sf::RenderWindow> &window)
{
    //cout<<"cette methode ne doit pas etre appelée";
    cout << "Affichage de forme .." << endl;

};

template <typename T>
bool Forme<T>::operator<(Forme<T>& forme)
{
    debug("Surcharge operateur <");

    T superficie1,superficie2;

    if ( typetest<Rectangle<int>>(*this) && typetest<Rectangle<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Rectangle<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Rectangle<int>&>(forme)).superficie();
    }

    if ( typetest<Cercle<int>>(*this) && typetest<Cercle<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Cercle<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Cercle<int>&>(forme)).superficie();
    }

    if ( typetest<Rectangle<int>>(*this) && typetest<Cercle<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Rectangle<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Cercle<int>&>(forme)).superficie();
    }

     if ( typetest<Cercle<int>>(*this) && typetest<Rectangle<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Cercle<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Rectangle<int>&>(forme)).superficie();
    }

    if ( typetest<Polygone<int>>(*this) && typetest<Polygone<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Polygone<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Polygone<int>&>(forme)).superficie();
    }

    if ( typetest<Polygone<int>>(*this) && typetest<Rectangle<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Polygone<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Rectangle<int>&>(forme)).superficie();
    }

    if ( typetest<Polygone<int>>(*this) && typetest<Cercle<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Polygone<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Cercle<int>&>(forme)).superficie();
    }

     if ( typetest<Cercle<int>>(*this) && typetest<Polygone<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Cercle<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Polygone<int>&>(forme)).superficie();
    }

     if ( typetest<Rectangle<int>>(*this) && typetest<Polygone<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Rectangle<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Polygone<int>&>(forme)).superficie();
    }

    return superficie1 < superficie2;
}

template <typename T>
bool Forme<T>::operator>(Forme<T>& forme)
{
    debug("Surcharge operateur >");

    T superficie1,superficie2;

    if ( typetest<Rectangle<int>>(*this) && typetest<Rectangle<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Rectangle<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Rectangle<int>&>(forme)).superficie();
    }

    if ( typetest<Cercle<int>>(*this) && typetest<Cercle<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Cercle<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Cercle<int>&>(forme)).superficie();
    }

    if ( typetest<Rectangle<int>>(*this) && typetest<Cercle<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Rectangle<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Cercle<int>&>(forme)).superficie();
    }

     if ( typetest<Cercle<int>>(*this) && typetest<Rectangle<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Cercle<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Rectangle<int>&>(forme)).superficie();
    }

      if ( typetest<Polygone<int>>(*this) && typetest<Polygone<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Polygone<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Polygone<int>&>(forme)).superficie();
    }

    if ( typetest<Polygone<int>>(*this) && typetest<Rectangle<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Polygone<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Rectangle<int>&>(forme)).superficie();
    }

    if ( typetest<Polygone<int>>(*this) && typetest<Cercle<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Polygone<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Cercle<int>&>(forme)).superficie();
    }

     if ( typetest<Cercle<int>>(*this) && typetest<Polygone<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Cercle<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Polygone<int>&>(forme)).superficie();
    }

     if ( typetest<Rectangle<int>>(*this) && typetest<Polygone<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Rectangle<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Polygone<int>&>(forme)).superficie();
    }

    return superficie1 > superficie2;
}

template <typename T>
bool Forme<T>::operator==(Forme<T>& forme)
{
    debug("Surcharge operateur ==");
    T superficie1, superficie2;

    if ( typetest<Rectangle<int>>(*this) && typetest<Rectangle<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Rectangle<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Rectangle<int>&>(forme)).superficie();
    }

    if ( typetest<Cercle<int>>(*this) && typetest<Cercle<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Cercle<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Cercle<int>&>(forme)).superficie();
    }

    if ( typetest<Rectangle<int>>(*this) && typetest<Cercle<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Rectangle<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Cercle<int>&>(forme)).superficie();
    }

     if ( typetest<Cercle<int>>(*this) && typetest<Rectangle<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Cercle<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Rectangle<int>&>(forme)).superficie();
    }

      if ( typetest<Polygone<int>>(*this) && typetest<Polygone<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Polygone<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Polygone<int>&>(forme)).superficie();
    }

    if ( typetest<Polygone<int>>(*this) && typetest<Rectangle<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Polygone<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Rectangle<int>&>(forme)).superficie();
    }

    if ( typetest<Polygone<int>>(*this) && typetest<Cercle<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Polygone<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Cercle<int>&>(forme)).superficie();
    }

     if ( typetest<Cercle<int>>(*this) && typetest<Polygone<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Cercle<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Polygone<int>&>(forme)).superficie();
    }

     if ( typetest<Rectangle<int>>(*this) && typetest<Polygone<int>>(forme) )
    {
        superficie1 = (dynamic_cast<Rectangle<int>&>(*this)).superficie();
        superficie2 = (dynamic_cast<Polygone<int>&>(forme)).superficie();
    }

    return superficie1 == superficie2;
}

//calculer la superficie d'un rectangle
template<typename T>
T Forme<T>::superficie() const
{
    return 0;
}

//calculer le périmètre d'un rectangle
template<typename T>
T Forme<T>::perimetre() const
{
    return 0;
}

// distance entre deux formes
template<typename T>
T Forme<T>::operator%(const Forme<T>& forme){

    T dx = pow(this->position.x - forme.position.x , 2 );
    T dy = pow(this->position.y - forme.position.y , 2 );
    return static_cast<T>( sqrt(dx + dy) );

};

template <typename T>
Forme<T>& Forme<T>::operator+(const int &degre){
    if( typetest<Rectangle<int>>(*this) ){
             debug("surcharge +");
            (dynamic_cast<Rectangle<int>&>(*this).getRectangle()).rotate(degre);
    }

    if( typetest<Cercle<int>>(*this) ){
             debug("surcharge +");
            (dynamic_cast<Cercle<int>&>(*this).getCercle()).rotate(degre);
    }

    if( typetest<Polygone<int>>(*this) ){
             debug("surcharge +");
            (dynamic_cast<Polygone<int>&>(*this).getPolygone()).rotate(degre);
    }

    return *this;
}

template <typename T>
Forme<T>& Forme<T>::operator-(const int &degre){
    if( typetest<Rectangle<int>>(*this) ){
             debug("surcharge -");
            (dynamic_cast<Rectangle<int>&>(*this).getRectangle()).rotate(360-degre);
    }

    if( typetest<Cercle<int>>(*this) ){
             debug("surcharge -");
            (dynamic_cast<Cercle<int>&>(*this).getCercle()).rotate(360-degre);
    }

    if( typetest<Polygone<int>>(*this) ){
             debug("surcharge -");
            (dynamic_cast<Polygone<int>&>(*this).getPolygone()).rotate(360-degre);
    }
    return *this;
}


template <typename T>
Forme<T>& Forme<T>::operator++(){
    debug("surcharge ++");
    epai_bordure++;
    return *this;
}

template <typename T>
Forme<T>& Forme<T>::operator--(){
    debug("surcharge --");
    epai_bordure--;
    return *this;
}


//affichage

template<typename T>
ostream& operator<<(ostream& os, Forme<T>& forme)
{
    //bool isRECT = !strcmp( typeid(forme).name(), typeid(Rectangle<int>).name() );
    bool isRECT = typetest<Rectangle<int>>(forme);

    if ( isRECT ) os << RECTANGLE;

    os << " , ";
    os << getNameByColor(forme.couleur);
    os << " , ";
    os << getNameByColor(forme.couleur_bor);
    os << " , ";
    os << forme.epai_bordure;
    os << " , ";
    os << "x = ";
    os << forme.position.x;
    os << " y = ";
    os << forme.position.y;
    os << " , ";
    // metriques
    // classe
    if ( isRECT )
    {
        os << "longueur : ";
        os << dynamic_cast<Rectangle<T>&>(forme).getLongueur();
        os << " largeur :  ";
        os << dynamic_cast<Rectangle<T>&>(forme).getLargeur();
    }
    os << endl;
    return os;
};
