#include "ViewConsole.h"

using namespace std;

ViewConsole::ViewConsole(){

}

ViewConsole::ViewConsole(View &view){

}

void ViewConsole::showUsers(vector<UserInfo*> * gameUsers, bool showScore) const{
    if(showScore){
        cout << "Score :" <<endl;
    }
    else{
        cout << "Liste des tireurs :" <<endl;
    }
    for(unsigned int i=0;i<gameUsers->size();i++){
        cout << gameUsers->at(i)->getUser()->getUserFirstName() << " " << gameUsers->at(i)->getUser()->getUserLastName();
        if(showScore){
            cout << "    " <<gameUsers->at(i)->getScore();
        }
        cout << endl;
    }
}

void ViewConsole::showMessage(const char* msg){
    cout << msg << endl;
}

void ViewConsole::showPlatSent(int i) const{
    cout << "Nombre de plateaux lancés : " << i << endl;
}

void ViewConsole::showConfigOptions() const{
    cout << endl;
    cout << "1- Garder le compteur actuel " <<endl;
    cout << "2- Réinitialiser le compteur " <<endl;
}

void ViewConsole::showNewGameStart() const{
    cout << "-----------" << endl << "Nouvelle partie" << endl;
}

void ViewConsole::showUserListOptions() const{
    cout << endl;
    cout << "1- Ajouter un nouveau tireur " <<endl;
    cout << "2- Supprimer un tireur " <<endl;
    cout << "3- Commencer la partie " <<endl;
}

void ViewConsole::showSaveListOptions() const{
    cout << "1- Charger la sauvegarde " <<endl;
    cout << "2- Ignorer la sauvegarder " <<endl;
}

void ViewConsole::showShootOption() const{
    cout << endl;
    cout << "1- Appui simple " <<endl;
    cout << "2- Appui long " <<endl;
    cout << "3- Appui double " <<endl;
    cout << "4- Tireur suivant " <<endl;
    cout << "5- +1 score " <<endl;
    cout << "6- -1 score " <<endl;
}

void ViewConsole::showGameInformations(int deductMode, int maxPlateau, UserInfo * userInfo) const{
    if(deductMode == 0){
        cout << "Plateaux restants : " << userInfo->getNbPlateau() << endl;
    }
    else{
        cout << "Plateaux restants : " << maxPlateau << endl;
    }
    cout << "Tireur actuel : " << userInfo->getUser()->getUserFirstName()
    << " " << userInfo->getUser()->getUserLastName() << endl
    << "Score Actuel : " << userInfo->getScore() <<endl;
}

void ViewConsole::showInitInformations(int deductMode, int maxPlateau, Game * game) const{
    if(deductMode == 0){
        for(unsigned int i = 0; i < game->getGameUsers()->size(); i++){
            UserInfo* current = game->getGameUsers()->at(i);            
            cout << current->getUser()->getUserFirstName() << " " << current->getUser()->getUserLastName() << " : "
                << current->getNbPlateau() << " plateau(x) " << endl;
        }
    }
    else{
        cout << "Nombre de plateaux : " << maxPlateau << endl;
    }
    cout << endl << "Tireur actuel : " << game->getGameCurrentUser()->getUser()->getUserFirstName()
    << " " << game->getGameCurrentUser()->getUser()->getUserLastName() << endl;
}
