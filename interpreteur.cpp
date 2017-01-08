#include "interpreteur.h"
#include "rectangle.cpp"
#include "forme.cpp"
#include "persistence.cpp"

constexpr unsigned int hashed(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (hashed(str, h+1) * 33) ^ str[h];
}

template <typename C, typename E>
Interpreteur<C,E>::Interpreteur(shared_ptr<sf::RenderWindow> window, shared_ptr<Persistence<C,Forme<E>>> persistance)
{
    this->window = window;
    this->persistance = persistance;
    this->command = "";
    this->keyword = "";
    this->isstream.str("");
    this->p1 = 0;
    this->p2 = 0;
    this->endofcommand = false;
}

template <typename C, typename E>
Interpreteur<C,E>::~Interpreteur()
{
    window.reset();
    persistance.reset();
    delete isstream;

}

template <typename C, typename E>
void Interpreteur<C,E>::lire()
{
    SetColor(10);
    cout << "> ";
    getline(cin, command);
    isstream.str(command);
    if (command == EXIT_CMD)
    {
        throw string(EXIT_CMD);
    }
    SetColor(15);
}

template <typename C, typename E>
void Interpreteur<C,E>::executer()
{

    // lire la commande
    keyword = interpreter();

    // case
    switch ( hashed(keyword.c_str()) )
    {

    // create
    case hashed(CREATE) :

        // lire les données communes
        parse();

        switch( hashed(form_type.c_str()) )
        {

        // rectangle
        case hashed(RECTANGLE) :
        {
            cout << "rectangle" << endl;

            // creer le rectangle
            Rectangle<int> forme(col_f,epai,col_b,x,y,p1,p2);
            forme >> window;

            // ajouter à la persistence
            shared_ptr<Rectangle<int>> ptr = std::make_unique<Rectangle<int>>(forme);
            (*persistance)(form_id, ptr, window);

            break;

        }

        // case cercle

        case hashed(CERCLE):
        {

        }

        // polygone

        case hashed(POLYGONE) :
        {

        }


        default :
            throw string(FORME_INCONNUE) + string(form_type);
            break;

        }
        break;

    // scale
    case hashed(SCALEUP) :
    {
        keyword = interpreter();
        p1 = interpreterint();
        terminateCommand();

        shared_ptr<Forme<int>> ptr = (*persistance)[keyword];
        *ptr = *ptr * p1;
        *persistance >> window;
        break;

    }

    // scale
    case hashed(SCALEDOWN) :
    {
        keyword = interpreter();
        p1 = interpreterint();
        terminateCommand();

        shared_ptr<Forme<int>> ptr = (*persistance)[keyword];
        *ptr = *ptr / p1;
        *persistance >> window;
        break;

    }

    // move
    case hashed(MOVE) :
    {
        keyword = interpreter();
        p1 = interpreterint();
        p2 = interpreterint();
        terminateCommand();

        shared_ptr<Forme<int>> ptr = (*persistance)[keyword];
        *ptr << sf::Vector2f((double) p1, (double) p2);
        *persistance >> window;
        break;

    }

    // copy
    case hashed(COPY) :
    {
        // lire forme originale
        keyword = interpreter();
        shared_ptr<Forme<int>> ptr = (*persistance)[keyword];

        //cout << typeid(*ptr).name() << endl;

        // lire id copie
        keyword = interpreter();
        shared_ptr<Forme<int>> ptrcopie;

        p1 = interpreterint();
        p2 = interpreterint();

        terminateCommand();

        // copier
        if ( typetest<Rectangle<int>>(*ptr) )
        {
            Rectangle<int> copie = dynamic_cast<Rectangle<int>&>(*ptr);
            ptrcopie = make_shared<Rectangle<int>>(copie);
        }


        *ptrcopie = *ptrcopie << sf::Vector2f((double) p1, (double) p2);

        //ptrcopie = &copie;
        (*persistance)(keyword, ptrcopie, window);
        *persistance >> window;
        break;

    }

    //
    case hashed(COLOR) :
    {
        bool decision;
        keyword = interpreter();
        if ( keyword == CONTOUR ) decision = true;
        else if (keyword == BACKGROUND) decision = false;
        else throw string(NO_CONTOUR_BACKGROUNG_ARG) + CONTOUR + string(" ou ") + BACKGROUND;
        keyword = interpreter();
        shared_ptr<Forme<int>> ptr = (*persistance)[keyword];
        keyword = interpreter();

        terminateCommand();

        *ptr << Couleur( getColorByName(keyword), decision);
        *persistance >> window;
        break;
    }

    // help
    case hashed(HELP) :
    {
        terminateCommand();

        help();
        break;
    }

    // clear
    case hashed(CLEAR) :
    {

        terminateCommand();

        persistance->vider(window);
        break;
    }

    // remove
    case hashed(REMOVE) :
    {

        keyword = interpreter();
        terminateCommand();

        persistance->supprimer(keyword, window);

        break;
    }

    // list
    case hashed(LIST) :
    {
        terminateCommand();

        cout << persistance;
        break;
    }

    // list
    case hashed(CLS) :
    {
        terminateCommand();
        system("cls");
        break;
    }

    // test
    case hashed(TEST_RECTANGLE) :
    {

        terminateCommand();

        // creer le rectangle
        Rectangle<int> forme(sf::Color::Red,epai,sf::Color::Green,10,10,20,20);
        forme >> window;

        // ajouter à la persistence
        shared_ptr<Rectangle<int>> ptr = std::make_unique<Rectangle<int>>(forme);
        (*persistance)(TEST_RECTANGLE, ptr, window);

        break;
    }

    case hashed(TESTCASE) :
    {
        terminateCommand();

        // creer le rectangle
        Rectangle<int> forme(sf::Color::Red,3,sf::Color::Green,10,10,20,20);
        Rectangle<int> copie = forme;

        copie << sf::Vector2f(100,100);
        forme >> window;
        copie >> window;

        // ajouter à la persistence
        shared_ptr<Rectangle<int>> ptr = std::make_shared<Rectangle<int>>(forme);
        (*persistance)(TEST_RECTANGLE, ptr, window);

        shared_ptr<Rectangle<int>> ptr2 = std::make_shared<Rectangle<int>>(copie);
        (*persistance)("copie", ptr2, window);

        break;
    }

    // comparer entre les formes selon la superficie
    case hashed(TEST) :
    {
        //lire l'id de la premiere forme
        keyword = interpreter();
        shared_ptr<Forme<int>> ptr1 = (*persistance)[keyword];

        //lire l'operateur de comparaison
        keyword = interpreter();
        string op = keyword;

        // lire l’id de la deuxieme forme
        keyword = interpreter();
        shared_ptr<Forme<int>> ptr2 = (*persistance)[keyword];

        terminateCommand();

        string reponse;

        if (op == string(SUPERIEUR)) *ptr1>*ptr2 ? reponse = TRUE : reponse = FALSE;
        else if (op == string(INFERIEUR)) *ptr1<*ptr2 ? reponse = TRUE : reponse = FALSE;
        else if (op == string(EGALE)) *ptr1==*ptr2 ? reponse = TRUE : reponse = FALSE;
        else throw string(UNKNOWN_OPERATOR) + string(op);

        cout << reponse << endl;

        break;
    }

    // distance
    case hashed(DIST) :
    {
        //lire l'id de la premiere forme
        keyword = interpreter();
        shared_ptr<Forme<int>> ptr1 = (*persistance)[keyword];

        // lire l’id de la deuxieme forme
        keyword = interpreter();
        shared_ptr<Forme<int>> ptr2 = (*persistance)[keyword];

        terminateCommand();

        cout << *ptr1 % *ptr2 << endl;

        break;
    }
    //rotate
    case hashed(ROTATE) :
    {
        keyword = interpreter();
        //cout<<keyword<<endl;
        shared_ptr<Forme<int>> ptr = (*persistance)[keyword];

        keyword = interpreter();
        //cout<<keyword<<endl;

        p1 = interpreterint();
        terminateCommand();

         if (keyword == string(PLUS)) {

            *ptr = (*ptr) + p1;
         }

         if (keyword == string(MOINS)){

            *ptr = (*ptr) - p1;
         }

        *persistance >> window;
        break;
    }

     //Incrémenter la bordure
    case hashed(CONTOUR) :
    {
        keyword = interpreter();
        cout<<keyword<<endl;
        shared_ptr<Forme<int>> ptr = (*persistance)[keyword];

        keyword = interpreter();
        cout<<keyword<<endl;

        terminateCommand();

         if (keyword == string(PLUS_PLUS)) {
            ++*ptr;
         }

         if (keyword == string(MOINS_MOINS)){
            --*ptr;
         }

        *persistance >> window;
        break;
    }

    //Get Superficie d'une forme
    case hashed(SUPERFICIE) :
    {
        keyword = interpreter();
        terminateCommand();

        //cout<<keyword<<endl;
        shared_ptr<Forme<int>> ptr = (*persistance)[keyword];

        //Rectangle<int> copie;
        if ( typetest<Rectangle<int>>(*ptr) ){
            cout << (dynamic_cast<Rectangle<int>&>(*ptr)).superficie();
        }

    }

    //Get Perimetre d'une forme
    case hashed(PERIMETRE) :
    {
        keyword = interpreter();
        terminateCommand();

        //cout<<keyword<<endl;
        shared_ptr<Forme<int>> ptr = (*persistance)[keyword];

        //Rectangle<int> copie;
        if ( typetest<Rectangle<int>>(*ptr) ){
            cout << (dynamic_cast<Rectangle<int>&>(*ptr)).perimetre();
        }

    }

    // default
    default :
        terminateCommand();
        throw string(COMMANDE_INCONNUE) + keyword;
        break;

    }

    // reset command
    command = "";

}

// interpreter une chaine de caractères
template <typename C, typename E>
string Interpreteur<C,E>::interpreter()
{
    string word = "";
    getline(isstream, word, ' ');

    if (word != "" && endofcommand)
    {
        throw string(SUPERFLUX_CHAIN) + string(word);
    }

    if ( word == "" && !endofcommand)
    {
        throw string(PARAMETRE_MANQUANT);
    }

    return word;
}

// interpreter un chaine comme un entier
template <typename C, typename E>
int Interpreteur<C,E>::interpreterint()
{
    int taille;
    try
    {
        taille = atoi( interpreter().c_str() );

        // tous les entiers doivent etre positifs
        if (taille < 0)
        {
            throw string(TAILLE_INVALIDE);
        }
    }
    catch (std::exception const & e)
    {
        throw string(TAILLE_INVALIDE);
    }
    return taille;
}

template <typename C, typename E>
int Interpreteur<C,E>::interpreterintextra()
{
    int taille;
    try
    {
        taille = atoi( interpreter().c_str() );
    }
    catch (std::exception const & e)
    {
        throw string(TAILLE_INVALIDE);
    }
    return taille;
}

template <typename C, typename E>
void Interpreteur<C,E>::parse()
{

    // lire le type de la forme

    form_type = interpreter();
    cout << string("Forme TYPE : ") + string(form_type) << endl;

    if ( string(form_type) != string(RECTANGLE) &&
            string(form_type) != string(CERCLE) &&
            string(form_type) != string(POLYGONE))
    {
        throw string(FORME_INCONNUE) + string(form_type);
    }

    // lire le id de la forme

    form_id = interpreter();

    // lire les couleurs

    col_f = getColorByName(interpreter());
    col_b = getColorByName(interpreter());

    // lire l'epaisseur et les positions

    if ( (epai = interpreterint()) > MAX_FORM_BORD_SIZE )
    {
        throw string(MAX_BORD_SIZE_MSG) + string (MAX_BORD_SIZE_MSG);
    } ;

    if ( (x = interpreterint()) > WINDOW_SIZE_X)
    {
        throw string(WINDOW_OVERFLOW_ORIGIN);
    }

    if ( (y = interpreterint()) > WINDOW_SIZE_Y)
    {
        throw string(WINDOW_OVERFLOW_ORIGIN);
    }

    if (x < y)
    {
        throw string(LONGUEUR_INF_LARGEUR);
    }

    /** lire les parametres extra **/

    // rectangle ou polygone, 2 parametres
    if (string(form_type) == string(RECTANGLE) || string(form_type) == string(POLYGONE))
    {
        p1 = interpreterint();
        p2 = interpreterint();
    }
    else if (string(form_type) == string(CERCLE))
    {
        p1 = interpreterint();
    }
    else
    {
        throw string(FORME_INCONNUE) + string(form_type);
    }

    /** Terminer la commande **/

}

template <typename C, typename E>
void Interpreteur<C,E>::help()
{
    cout << "liste des commandes valables" << endl;
    cout << endl;
    cout << CREATE + string(" [Forme_Type] [Forme_ID] [Coul_Fond] [Coul_Contour] [Epaisseur] [Position<x,y>] metriques") << endl;
    cout << SCALEUP + string(" [Forme_ID] [facteur_echelle]") << endl;
    cout << SCALEDOWN + string(" [Forme_ID] [facteur_echelle]") << endl;
    cout << TEST + string(" [Forme_ID] [operateur_comparaison] [Forme_ID]") << endl;
    cout << ROTATE + string(" [Forme_ID] [+/-] [angle_rotation]") << endl;
    cout << CONTOUR + string(" [Forme_ID] [++/--]") << endl;
    cout << SUPERFICIE + string(" [Forme_ID] ") << endl;
    cout << PERIMETRE + string(" [Forme_ID] ") << endl;
}

template <typename C, typename E>
void Interpreteur<C,E>::terminateCommand()
{
    endofcommand = true;
    interpreter();

}
