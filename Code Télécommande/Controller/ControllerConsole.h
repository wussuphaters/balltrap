#ifndef DEF_CTRLCONSOLE
#define DEF_CTRLCONSOLE

#include <iostream>
#include <string>
#include "../View/ViewConsole.h"
#include "../View/ViewMotion.h"
#include "../Model/Game.h"
#include "Controller.h"
#include "../Model/Channel.h"
#include <fstream>
#include <unistd.h>
#include <cstddef>
#include <iomanip>
#include <boost/archive/tmpdir.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>

class ControllerConsole : public Controller
{

    private:

        //objet qui réalise les requêtes sur l'API liée à la base
        Database * database;

        //objet qui permet l'affichage sur la console
        ViewConsole * view;

        //objet qui contient les informations de la partie
        Game * game;

        //booléen qui indique la présence d'une sauvegarde
        bool isSave;

        //entier qui stocke le nombre de plateaux lancés
        int platSent;

    public:

        //constructeurs
        ControllerConsole();
        ControllerConsole(Database &database, ViewConsole &view);
        ControllerConsole(Database &database, ViewConsole *view);
        
        //fonction principale lancée à la création qui contient la boucle de jeu
        virtual void run();

        //
        virtual bool startGame(int);

        //permet l'ajout/la supression et la modification de la liste des tireurs
        virtual void makeUserList();

        //permet le choix du canal
        virtual Channel* chooseChannel();

        //permet la déconnexion de l'utilisateur possédant l'id donné
        bool disconnectUser(const char* id);

        //permet la connexion de l'utilisateur possédant l'id donné
        bool connectUser(const char* id);

        //contient la boucle de jeu dans laquelle les tireurs utilisent leurs plateaux
        virtual void play();

        //permet d'entrer le mot de passe pour l'administration
        bool enterPassword();

        //supprime toutes les sauvegardes et données de jeu dans la télécommande
        virtual void resetAll();

        //sauvegarde l'objet game dans un fichier externe
        void saveGame();

        //permet de reprendre la partie précédemment enregistrée
        void readBackup();

        //enregistre dans un fichier externe tous les plateaux lancés
        void saveAllPlat();

        //permet de consulter le nombre total de plateaux lancés
        bool readAllPlat();

        //vérifie la présence d'un fichier externe dont le nom est passé en paramètre
        bool fileExists(const char * filename);

        //récupère dans la liste de paramètres celui possédant le code donné
        Parameter* getParameterFromCode(std::string) const;
};

#endif