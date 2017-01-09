#pragma once

#include "tools.h"
#include "forme.cpp"
#include "rectangle.cpp"
#include "persistence.h"

template <typename C, typename E>
class Interpreteur
{

public:

     /** CONSTRUCTEURS **/
    explicit Interpreteur() = default;
    Interpreteur(shared_ptr<sf::RenderWindow> window, shared_ptr<Persistence<C,Forme<E>>> persistance);

    /** DESTRUCTEUR **/
    ~Interpreteur();

    /* Lire la commande **/
    void lire();

    /* Executer la commande */
    void executer();

private :

    /* Interpreter et retourner un mot de la commande */
    string interpreter();

    /* Interpreter et retourner un mot de la commande */
    int interpreterint();

    /* Lire une commande de creation d'objet */
    void parse();

    /* Commande HELP */
    void help();

    /* Signaler la fin d'une commande au controle d'execution */
    void terminateCommand();

protected:

    /** ATTRIBUTS DE LA CLASSE **/

    shared_ptr<sf::RenderWindow> window; // Fenetre
    shared_ptr<Persistence<C,Forme<E>>> persistance; //Persistance
    string command; // Commande
    istringstream isstream; // Commande transformée en flux
    string keyword; // Mot extrait de la commande
    bool endofcommand; // true = commande lue

    /** ATTRIBUTS TEMPORAIRES, SERVENT POUR LE PASSAGE DE PARAMETRES **/

    string form_id;
    string form_type;
    sf::Color col_f;
    sf::Color col_b;
    int epai;
    int x;
    int y;
    int p1;
    int p2;

};
