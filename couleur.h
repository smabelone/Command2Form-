#pragma once
#include "constantes.h"

struct Couleur
{

public :

    explicit Couleur() = default;
    Couleur (sf::Color col, bool type);
    ~Couleur() = default;

    sf::Color col;
    bool type;

};
