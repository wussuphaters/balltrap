#ifndef DEF_VIEWCONSOLE
#define DEF_VIEWCONSOLE

#include <iostream>
#include <string>
#include "View.h"
#include "../Model/Game.h"
#include "../Model/UserInfo.h"

class ViewConsole : public View
{

private:


public:

    //constructeurs
    ViewConsole();
    ViewConsole(View &view);

    //affiche la liste des tireurs connectés
    virtual void showUsers(std::vector<UserInfo*> * gameUsers, bool showScore) const; 
    
    //affiche les paramètres de la partie
    virtual void showInitInformations(int deductMode, int maxPlateau, Game * game) const;
    
    //affiche les informations de la partie
    virtual void showGameInformations(int deductMode, int maxPlateau, UserInfo * userInfo) const;
    
    //affiche les différentes options pendant la partie
    virtual void showShootOption() const;
    
    //affiche les différentes actions pouvant être réalisées sur la liste des tireurs
    virtual void showUserListOptions() const;
    
    //affiche les choix possibles au chargement de la sauvegarde
    virtual void showSaveListOptions() const;
    
    //affiche les choix possibles lors de la relance d'une partie
    virtual void showNewGameStart() const;
    
    //affiche le nombre total de plateaux envoyés
    virtual void showPlatSent(int i) const;
    
    //affiche les options disponibles avec le compteur de plateaux envoyés
    virtual void showConfigOptions() const;
    
    //affiche la chaîne de caractères passée en paramètre
    virtual void showMessage(const char* msg);
};

#endif