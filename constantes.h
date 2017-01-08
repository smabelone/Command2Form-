#pragma once

/*****************************/
/*** INCLUDES **************/
/*****************************/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>
#include <map>
#include <dos.h>
#include <dir.h>
#include <thread>
#include <typeinfo>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include "couleur.h"

/*****************************/
/*** NAMESPACE **************/
/*****************************/

using namespace std;
using namespace sf;

/*****************************/
/*** CONFIG ******************/
/*****************************/

#define DEBUG 1 // Activer pour afficher les details des operations

#define WINDOW_POS_X 0
#define WINDOW_POS_Y 0
#define WINDOW_SIZE_X 600
#define WINDOW_SIZE_Y 600
#define MAX_FORM_METER 200
#define MAX_FORM_BORD_SIZE 5
#define MAX_FORM_STORAGE 5
#define FRAME_RATE_LIMIT 60

/*****************************/
/*** COMMANDES **************/
/*****************************/

#define CREATE "create" // new
#define UNSELECT "unselect" // operation
#define CHANGE_COLOR "color" // << ou []
#define MOVE "move" // +
#define ROTATE "rotate" // %
#define SCALEUP "scaleup" // *
#define SCALEDOWN "scaledown" // *
#define REMOVE "remove" // delete
#define CLEAR "removeall"
#define CLS "cls"
#define COPY "duplicate" // new --> +
#define DIST "dist"
#define COLOR "color"
#define LIST "list"
#define HELP "help"
#define TEST "test"
#define ROTATE "rotate"
#define CONTOUR "contour"
#define SUPERFICIE "superficie"
#define PERIMETRE "perimetre"

/*****************************/
/*** MOTS CLES **************/
/*****************************/

#define SUPERIEUR ">"
#define INFERIEUR "<"
#define EGALE "=="
#define TRUE "vrai"
#define FALSE "faux"
#define CONTOUR "contour"
#define BACKGROUND "background"
#define PLUS_PLUS "++"
#define MOINS_MOINS "--"
#define PLUS "+"
#define MOINS "-"

/*****************************/
/*** CAS DE TEST **************/
/*****************************/

#define TEST_RECTANGLE "testrect"
#define TEST_CERCLE "testcercle"
#define TEST_POLYGONE "testpolygone"
#define TESTCASE "testcase"

/*****************************/
/*** FORMES ******************/
/*****************************/

#define RECTANGLE "rectangle"
#define POLYGONE "polygone"
#define CERCLE "cercle"

/*****************************/
/*** COULEURS ******************/
/*****************************/

#define ROUGE "rouge"
#define VERT "vert"
#define BLEU "bleu"
#define NOIR "noir"
#define BLANC "blanc"
#define JAUNE "jaune"
#define MAGENTA "magenta"
#define CYAN "cyan"

/*****************************/
/*** MESSAGES 1 ******************/
/*****************************/

#define START_MSG "Bienvenue !"
#define EXIT_CMD "exit"

#define COMMANDE_INCONNUE "Commande inconnue : "
#define COULEUR_INCONNUE "Couleur inconnue : "
#define FORME_INCONNUE "Forme inconnue : "
#define PARAMETRE_MANQUANT "Commande incomplete : tapez help pour afficher l'aide"
#define TAILLE_INVALIDE "Taille invalide !"
#define UNKNOWN_OPERATOR "Operateur inconnu : "
#define SUPERFLUX_CHAIN "Litteraux superflux a la commande : "

/*****************************/
/*** MESSAGES 2 ******************/
/*****************************/

#define AUCUNE_FORME_SELECTIONNE "nil"
#define MSG_ALREADY_EXISTS "Cette forme existe deja"
#define MSG_NOT_EXISTS "Forme inexistante : "
#define MAX_FORM_MSG "ERREUR : Le nombre maximal de formes est atteint, pensez a supprimer !"
#define MAX_BORD_SIZE_MSG "ERREUR : L'epaisseur de la bordure doit etre inférieure ou egale a " //MAX_FORM_BORD_SIZE
#define WINDOW_OVERFLOW_ORIGIN "ERREUR : L'origine de la forme est a l'exterieur de l'ecran"
#define LONGUEUR_INF_LARGEUR "La longueur doit etre superieure à la largeur"
#define SCALE_VALUE_INVALIDE "argument invalide, la valeur doit etre superieure a 0"
#define NO_CONTOUR_BACKGROUNG_ARG "Le second argument doit avoir les valeurs "
#define SYSTEM_ERROR "Erreur système irrecuperable"
