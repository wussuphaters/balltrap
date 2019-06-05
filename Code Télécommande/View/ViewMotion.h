#ifndef DEF_VIEWMOTION
#define DEF_VIEWMOTION

#include <iostream>
#include <string>
#include <stdlib.h>
#include <gtkmm-3.0/gtkmm.h>
#include "View.h"
#include "../Model/Game.h"
#include "../Model/UserInfo.h"
#include "../Controller/ControllerMotion.h"
class ControllerMotion;
class ViewMotion : public Gtk::Window
{

private:
    int viewNo,optionNo,isMessage,isInitializaton;
    Gtk::Window* MainWindow;
    Gtk::Label label1, label2, label3, label4, label5, label6, label7, label8, label9;
    ControllerMotion * controller;
    Gtk::Grid grid;

public:

    //constructeur et déstructeur
    ViewMotion();
    ~ViewMotion();

    //getter et setter sur le numéro de la vue
    int getNoView() const;
    int getNoOption() const;
    void setNoView(int);
    bool getOptionStatus();

    /*
    * Fonction qui permet de créer et afficher une vue contenant le message
    * passé en paramètre et un bouton suivant
    */
    virtual void showMessage(const char* msg);

    //Définit les actions à réaliser en fonction de l'évènement (appuie clavier) réalisé
    bool on_key_release_event(GdkEventKey*) override;

    void showScan();

    void showOption(const char*);

    //Affichage de la vue de jeu principale
    void showGame(Game*);

    //Affichage de la vue du choix de canal
    void showChannelChoose(const char*);

    void showPlatCountTypeChoose(const char*);

    //Affichage de la vue de changement de delai entre chaque rafale
    void showDelayChoose(const char*);

    //Affichage de la vue de choix de nombre de credits a utiliser pour la partie
    void showNbCreditsChoose(const char*);

    //Affichage de la vue permettant de choisir ou non de lancer la sauvegarde
    void showSaveChoose();

    //Affichage de la vue demandant le mot de passe
    void showPwdChoose();

    //Affichage de la vue permettant de consulter le nombre de plateau lancé par la télécommande
    void showPlatChoose();

    //Affichage de la liste des tireurs de la partie
    void showPlayerList(std::vector<UserInfo*>*);

    //Affichage de la vue de fin de partie avec les scores des tireurs
    void showEndGame(std::vector<UserInfo*>* userList);
    //void showDemandeRaZ();

    //Affichage du message d'erreur indiquant l'incapacité de la télécommande de se connecter à l'API
    void showNoConnection();

    //Affichage de la vue permettant de relancer une partie
    void showAskChangeChannel();

    //Permet de vider le tableau contenant les différents labels
    void resetGrid();

    //
    void setLabelExpandable();

    /*
    * Permet de récupérer un double appuie en vérifiant que deux boutons ont été
    * pressés sans qu'un des deux n'ait été relaché
    */
    bool on_key_press(GdkEventKey *e);
};

#endif