#ifndef __INTERPRETEUR__
#define __INTERPRETEUR__

#include "tools.h"
#include "forme.cpp"
#include "rectangle.cpp"
#include "persistence.h"

template <typename C, typename E>
class Interpreteur
{

public:

    explicit Interpreteur() = default;
    Interpreteur(shared_ptr<sf::RenderWindow> window, shared_ptr<Persistence<C,Forme<E>>> persistance);
    ~Interpreteur();
    void lire();
    void executer();

private :

    string interpreter();
    int interpreterint();
    int interpreterintextra(); // Autorise les entiers négatifs
    void parse();
    void help();
    void terminateCommand();

protected:

    bool endofcommand;
    shared_ptr<sf::RenderWindow> window;
    shared_ptr<Persistence<C,Forme<E>>> persistance;
    string command;
    istringstream isstream;
    string keyword;

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

#endif // __INTERPRETEUR__
