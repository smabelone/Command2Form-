#include "interpreteur.cpp"
#include <cstdlib>

/**================================================================================**/
/**     M   A   I   N                                                              **/
/**================================================================================**/

/** FONCTIONS **/

/* Gestion des evenements de la fenetre Window */
void handle_events(shared_ptr<sf::RenderWindow> window);

/* Configuration de Window */
void config_window(const std::shared_ptr<sf::RenderWindow> window);

/* Message de demarrage */
void start();

/* Message d'arret */
void exit();

/** MAIN **/

int main()
{

    /* WINDOW */
    const std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "", sf::Style::None);
    config_window(window);

    /* GERER LES EVENEMENTS DE LA FENETRE */
    std::thread handle(handle_events,window);

    /* PERSISTENCE */
    std::shared_ptr<Persistence<string, Forme<int>>> disk = std::make_shared<Persistence<string, Forme<int>>>();

    /* INTERPRETEUR */
    std::unique_ptr<Interpreteur<string,int>> interp = nullptr;

    /* START */
    start();

    while (true)
    {

        try
        {
            /* Creer un nouvel interpreteur, detruire le précédent */
            interp = std::make_unique<Interpreteur<string,int>>(window,disk);

            /* Lire la commande entree par l'utilisateur */
            interp->lire();

            /* Executer la commande */
            interp->executer();

            /* Reinitialiser */
            interp.reset();

        }
        catch (string message)
        {
            /* En cas de problème, capter le message du problème, l'afficher et terminer dans un état sain */

            if (message != EXIT_CMD)
            {
                // Message d'erreur
                SetColor(12);
                cout << message << endl;
                SetColor(15);
            }
            else
            {
                // Signal d'exit
                exit();
                handle.join();
                return 0;
            }
        }

        catch ( const std::exception& e )
        {
            // standard exceptions
            SetColor(4);
            cout << e.what() << endl;
        }

    }

    /* STOP HANDLE */
    handle.join();

    return 0;

}

/**================================================================================**/

/** Source : tutoriel SFML **/
void handle_events(shared_ptr<sf::RenderWindow> window)
{
    sf::Event event;

    // while there are pending events...
    while (window->pollEvent(event))
    {
        // check the type of the event...
        switch (event.type)
        {
        // window closed
        case sf::Event::Closed:
            window->close();
            break;

        // key pressed
        case sf::Event::KeyPressed:
            break;

        // we don't process other types of events
        default:
            break;
        }
    }
}

void config_window(const std::shared_ptr<sf::RenderWindow> window)
{
    window->setActive(false);
    window->setFramerateLimit(FRAME_RATE_LIMIT);
    window->setMouseCursorVisible(false);
    window->setVerticalSyncEnabled(false);
    sf::Vector2i pos(WINDOW_POS_X,WINDOW_POS_Y);
    window->setPosition(pos);
    window->display();
}

void start()
{
    SetColor(8);
    cout << START_MSG << endl;
}

void exit()
{
    SetColor(15);
    cout << EXIT_CMD << endl;
}
