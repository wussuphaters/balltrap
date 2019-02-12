#ifndef DEF_CTRLMOTION
#define DEF_CTRLMOTION

#include <iostream>
#include <string>
#include "../View/ViewConsole.h"
#include "../View/ViewMotion.h"
#include "../Model/Game.h"
#include "Controller.h"
#include "../Model/Channel.h"
#include <fstream>
#include <cstdio>
#include <unistd.h>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

class ViewMotion;
class ControllerMotion : public Controller
{

private:

    Database * database;
    ViewMotion  *view;
    Game * game;

    std::vector<Channel*> channelList;
    std::string pwd;
    unsigned int channelPointer;
    int platType, nbPlatMax, paramDefaultNbPlat, platSent;
    bool isParamRefreshed;
    bool isSave;

public:

    //constructeur
    ControllerMotion();

    //accesseurs
    void setViewMotion(ViewMotion*);
    int getPlatType();
    std::string getPlatSent();


    /*Hérité de Controller*/
    virtual void run();
    virtual void makeUserList();

    //Permet de requêter l'API afin d'obtenir la liste des paramètres de jeu    
    void refreshParams();

    //Change la vue actuelle par celle défini dans la variable noView
    void redirectAfterMessage();
    
    //Insert dans la variable game, l'id du canal choisit par l'utilisateur
    void initializeCanalView();
    
    //Permet de naviguer à la main entre les différents canaux lors du choix
    void changeCanalNumber(int);
    
    /* 
    *  Permet d'ajouter un tireur à la liste
    *  en récupérant son identifiant avec addUser
    *  et en vérifiant qu'il respecte bien les conditions (nombre de plateaux, type de compte...) 
    *  avec connectUser
    */
    void addUser();
    bool connectUser(const char*);

    //Permet de retirer un tireur de la liste
    void deleteUser();

    /*
    * Vérifie que les conditions de lancement sont remplies
    * à savoir la connexion avec l'API, le nombre de crédit suffisant sur chaque tireur
    * et décrémente chaque tireur d'un crédit
    */
    void startGame(int);

    //Scanne un code QR d'utilisateur
    int scanQRCode();

    //Permet de choisir un parcours/canal
    int addParcours();

    //Scanne un code QR de parcours
    int scanParcours();

    //Permet d'incrémenter ou de décrémenter le score des tireurs
    void changeScore(int);

    //Permet de vérifier si la partie comporte des joueurs
    bool checkUsers();
    //Permet de passer au tireur suivant lors d'une partie
    void changePlayer();

    //Récupère la saisie de l'utilisateur et vérifie que le lancement du plateau est possible
    void shoot(int);

    //Fonction à implémenter (envoyer l'onde correspondante au canal et lanceur donné)
    void sendWave(int,int);

    //A la fin d'une partie, permet d'en relancer une nouvelle
    void restartGame();

    //Vérifie la présence d'un fichier externe dont le nom est passé en paramètre
    bool fileExists(const char *);

    //Permet la lecture d'un fichier externe, contenant une sauvegarde des variables d'une partie antérieure
    void readBackup(int);

    //Sauvegarde dans un fichier txt, l'état actuel de la variable game
    void saveGame();

    //Vérifie, au lancement de l'application, la présence d'une sauvegarde sur la télécommande
    void checkBackup();

    /*
    * Vérifie la correspondance entre la saisie de l'utilisateur et le mot de passe administrateur
    * puis redirige l'utilisateur en fonction du résultat et du paramètre
    */
    void confirmPwd(int);

    //Lors de la saisie d'un mot de passe, converti l'entrée de l'utilisateur en une lettre et l'ajoute dans une liste
    void pushLetter(int);

    //Permet de réinitialisé toutes les variables de la télécommande et de repartir à zéro
    void resetAll();

    //Vide de la liste des caractères entrés par l'utilisateur
    void resetPwd();

    /*
    * Vérifie la présence du fichier txt permettant de stocker le nombre total de plateaux
    * envoyés par la télécommande
    */
    bool readAllPlat();

    //A chaque lancement de plateaux, incrémente le nombre de plateaux lancés et l'écrit dans le ficher txt  
    void saveAllPlat();

    //Permet de remettre à zéro le nombre de plateaux lancés par la télécommande
    void resetPlat();

    
};

#endif