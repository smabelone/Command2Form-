#include "interpreteur.h"
#include "rectangle.cpp"
#include "cercle.cpp"
#include "polygone.cpp"
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
//    delete isstream;

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
            //cout << "rectangle" << endl;

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
             //cout << "cercle" << endl;

            // creer le cercle
            Cercle<int> forme(col_f,epai,col_b,x,y,p1);
            forme >> window;

            // ajouter à la persistence
            shared_ptr<Cercle<int>> ptr = std::make_unique<Cercle<int>>(forme);
            (*persistance)(form_id, ptr, window);

            break;

        }

        // polygone
        case hashed(POLYGONE) :
        {
            //cout << "polygone" << endl;

            // creer le polygone
            Polygone<int> forme(col_f,epai,col_b,x,y,p1,p2);
            forme >> window;

            // ajouter à la persistence
            shared_ptr<Polygone<int>> ptr = std::make_unique<Polygone<int>>(forme);
            (*persistance)(form_id, ptr, window);

            break;
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

        if ( typetest<Cercle<int>>(*ptr) )
        {
            Cercle<int> copie = dynamic_cast<Cercle<int>&>(*ptr);
            ptrcopie = make_shared<Cercle<int>>(copie);
        }

         if ( typetest<Polygone<int>>(*ptr) )
        {
            Polygone<int> copie = dynamic_cast<Polygone<int>&>(*ptr);
            ptrcopie = make_shared<Polygone<int>>(copie);
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
        Rectangle<int> forme(sf::Color::Red,1,sf::Color::Green,20,20,20,20);
        forme >> window;

        // ajouter à la persistence
        shared_ptr<Rectangle<int>> ptr = std::make_unique<Rectangle<int>>(forme);
        (*persistance)(TEST_RECTANGLE, ptr, window);

        break;
    }

    // test
    case hashed(TEST_CERCLE) :
    {

        terminateCommand();

        // creer le rectangle
        Cercle<int> forme(sf::Color::Blue,2,sf::Color::Magenta,70,10,50);
        forme >> window;

        // ajouter à la persistence
        shared_ptr<Cercle<int>> ptr = std::make_unique<Cercle<int>>(forme);
        (*persistance)(TEST_CERCLE, ptr, window);

        break;
    }

    // test
    case hashed(TEST_POLYGONE) :
    {

        terminateCommand();

        // creer le rectangle
        Polygone<int> forme(sf::Color::White,3,sf::Color::Yellow,100,120,20,5);
        forme >> window;

        // ajouter à la persistence
        shared_ptr<Polygone<int>> ptr = std::make_unique<Polygone<int>>(forme);
        (*persistance)(TEST_POLYGONE, ptr, window);

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

        if ( typetest<Cercle<int>>(*ptr) ){
            cout << (dynamic_cast<Cercle<int>&>(*ptr)).superficie();
        }

        if ( typetest<Polygone<int>>(*ptr) ){
            cout << (dynamic_cast<Polygone<int>&>(*ptr)).superficie();
        }

        cout << endl;
        break;

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

         if ( typetest<Cercle<int>>(*ptr) ){
            cout << (dynamic_cast<Cercle<int>&>(*ptr)).perimetre();
        }

         if ( typetest<Polygone<int>>(*ptr) ){
            cout << (dynamic_cast<Polygone<int>&>(*ptr)).perimetre();
        }
        cout << endl;
        break;
    }

    // flush
    case (hashed(FLUSH)) :
    {

        keyword = interpreter();
        terminateCommand();

        auto ptr = (*persistance)[keyword];
        if ( typetest<Rectangle<int>>(*ptr) )
        {

            ptr = make_unique<Rectangle<int>>( flushRectangle<int>(dynamic_cast<Rectangle<int>&>(*ptr) ) );
            persistance->supprimer(keyword, window);
            std::this_thread::sleep_for (std::chrono::seconds(1));
        }

        else if ( typetest<Cercle<int>>(*ptr) )
        {
            ptr = make_unique<Cercle<int>>( flushCercle<int>(dynamic_cast<Cercle<int>&>(*ptr) ) );
            persistance->supprimer(keyword, window);
            std::this_thread::sleep_for (std::chrono::seconds(1));
        }

        else if ( typetest<Polygone<int>>(*ptr) )
        {
            ptr = make_unique<Polygone<int>>( flushPolygone<int>(dynamic_cast<Polygone<int>&>(*ptr) ) );
            persistance->supprimer(keyword, window);
            std::this_thread::sleep_for (std::chrono::seconds(1));
        }

        // re-sauvegarder
        (*persistance)(keyword, ptr, window);

        break;
    }

    // default
    default :
        //terminateCommand();
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
void Interpreteur<C,E>::parse()
{

    // lire le type de la forme

    form_type = interpreter();
    //cout << string("Forme TYPE : ") + string(form_type) << endl;

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
    if (string(form_type) == string(RECTANGLE))
    {
        p1 = interpreterint();
        p2 = interpreterint();
    }
    else if (string(form_type) == string(CERCLE))
    {
        p1 = interpreterint();
    }
    else if(string(form_type) == string(POLYGONE)){
        p1 = interpreterint();
        if ( (p2 = interpreterint()) < 3 ){
             throw new string(NOT_A_POLYGON);
        };
    }

    else {
        throw string(FORME_INCONNUE) + string(form_type);
    }

    /** Terminer la commande **/
    terminateCommand();

}


template <typename C, typename E>
void Interpreteur<C,E>::help()
{
    SetColor(8);
    cout << " [C O M M A N D E S]" << endl;
    SetColor(15);
    cout << CREATE + string(" [Forme_Type] [Forme_ID] [Coul_Fond] [Coul_Contour] [Epaisseur] [Position x] [Position y] <metriques*>") << endl;
    cout << REMOVE + string(" [Forme_ID] ") << endl;
    cout << FLUSH + string(" [Forme_ID] ") << endl;
    cout << SCALEUP + string(" [Forme_ID] [facteur_echelle]") << endl;
    cout << SCALEDOWN + string(" [Forme_ID] [facteur_echelle]") << endl;
    cout << COPY + string(" [Forme_ID] [New_Forme_ID] [poision_x] [position_y]") << endl;
    cout << MOVE + string(" [Forme_ID] [poision_x] [position_y]") << endl;
    cout << TEST + string(" [Forme_ID_1] {>|<|==} [Forme_ID_2]") << endl;
    cout << DIST + string(" [Forme_ID_1][Forme_ID_2]") << endl;
    cout << ROTATE + string(" [Forme_ID] {+|-} [angle_rotation]") << endl;
    cout << CONTOUR + string(" [Forme_ID] {++|--}") << endl;
    cout << COLOR + string(" {background|contour} [Forme_ID] [Coul_ID]") << endl;
    cout << SUPERFICIE + string(" [Forme_ID] ") << endl;
    cout << PERIMETRE + string(" [Forme_ID] ") << endl;
    cout << CLEAR << endl;
    cout << LIST << endl;
    cout << CLS << endl;
    cout << HELP << endl;
    cout << endl;
    SetColor(8);
    cout << " [F O R M E S      E T     M E T R I Q U E S]" << endl;
    SetColor(15);
    cout << "Forme_Type = " + string(RECTANGLE) + "|" + string(CERCLE) + "|" + string(POLYGONE) << endl;
    cout << "Metriques d'un " + string(RECTANGLE) + " : " + " [Longeur] [Largeur]" << endl;
    cout << "Metriques d'un " + string(CERCLE) + " : " + " [Rayon]" << endl;
    cout << "Metriques d'un " + string(POLYGONE) + " : " + " [Rayon] [Nb_Sommets]" << endl;
    cout << endl;
    SetColor(8);
    cout << " [C O U L E U R S]" << endl;
    SetColor(15);
    cout << "{Coul_Fond|Coul_Contour[Coul_ID} = " + string(ROUGE) + "|" + string(VERT) + "|" + string(BLEU) + "|"
     + string(NOIR) + "|" + string(BLANC) + "|" + string(CYAN) + "|" + string(JAUNE) + "|" + string(MAGENTA) << endl;
    cout << endl;
}



template <typename C, typename E>
void Interpreteur<C,E>::terminateCommand()
{
    endofcommand = true;
    interpreter();

}
