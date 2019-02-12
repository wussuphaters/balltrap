#include "ControllerConsole.h"
#include <string>
#include <sstream>

using namespace std;

ControllerConsole::ControllerConsole(){

}

ControllerConsole::ControllerConsole(Database &database, ViewConsole &view){
    this->database= new Database(database);
    this->view = new ViewConsole(view);
    this->game = new Game();
}

ControllerConsole::ControllerConsole(Database &database, ViewConsole * view){
    this->database= new Database(database);
    this->view = view;
    this->game = new Game();
    this->isSave = false;
    this->platSent = 0;
}

bool ControllerConsole::startGame(int type){
    vector<UserInfo*> list;
    //0 : compak / 1 : parcours / 2 : fosse
    list = this->database->checkCredit(this->game->getGameUsers(), type);
    if(list.size() > 0){
        this->view->showMessage("Pas assez de crédit :");
        this->view->showUsers(&list, false);
    }
    else if(list.size() == 0){
        this->database->decrCredits(this->game->getGameUsers(), type);
        for(unsigned int i = 0; i < this->game->getGameUsers()->size(); i++){
            this->game->getGameUsers()->at(i)->setScore(0);
        }
        this->view->showMessage("Début de la partie !!");
        this->game->setGameCurrentUser(this->game->getGameUsers()->at(0));
        this->saveGame();
        this->play();
        return true;
        
    }
    else{
        this->view->showMessage("Impossible de lancer la partie !!");
        return false;
    }
    return false;
}

void ControllerConsole::run(){
    bool readTrue = this->readAllPlat();
    if(!readTrue)
        return;
    this->readBackup();
    while(1){
    this->game->setGameParameters(this->database->getParameters());
    Parameter* paramDefaultNbPlat = this->game->getParameterFromCode("defaultNbPlat");
    int paramDefaultNbPlatValue = atoi(paramDefaultNbPlat->getParameterValue().c_str());
        if(!this->isSave){
            this->makeUserList();
            if(isSave == false || (isSave == true && paramDefaultNbPlatValue == 1))
                this->chooseChannel();
            if(this->startGame(0)){
                remove("save.txt");
                this->view->showMessage("Partie finie");
                this->view->showUsers(this->game->getGameUsers(), true);
                this->view->showNewGameStart();
                this->game=new Game();
            }
            else{
                this->view->showNewGameStart();
                this->game=new Game();
            }
        }
        else{
            this->play();
            this->view->showMessage("Partie finie");
            remove("save.txt");
            this->isSave = false;
            this->view->showUsers(this->game->getGameUsers(), true);
            this->view->showNewGameStart();
            this->game=new Game();
        }
    }
}

void ControllerConsole::play(){
    //O par tireur | 1 pour tous
    string in;
    Parameter* param = this->game->getParameterFromCode("cptType");
    int deductMode = atoi(param->getParameterValue().c_str());
    bool stop = false;
    Parameter* paramDefaultNbPlat = this->game->getParameterFromCode("defaultNbPlat");
    Parameter* nbPlatMax = this->game->getParameterFromCode("nbPlat");
    int paramDefaultNbPlatValue = atoi(paramDefaultNbPlat->getParameterValue().c_str());
    int maxp;
    if(paramDefaultNbPlatValue == 1){
         maxp = atoi(nbPlatMax->getParameterValue().c_str());
    }
    else if(paramDefaultNbPlatValue == 0){
         maxp = this->game->getGameChannel()->getChannelNbPlat();
    }
    else{
        this->view->showMessage("Problème de paramètrage du nombre de plateaux, veuillez contacter un administrateur !");
        return;
    }
    if(!this->isSave){
        this->game->setGameAllPlat(maxp * this->game->getGameUsers()->size());
        if(deductMode == 0){
            for(unsigned int i = 0; i < this->game->getGameUsers()->size(); i++){
                UserInfo* current = this->game->getGameUsers()->at(i);
                current->setNbPlateau(maxp);
            }
        }
        this->view->showInitInformations(deductMode, this->game->getGameAllPlat(), this->game);
    }
    else{
        this->view->showGameInformations(deductMode, this->game->getGameAllPlat(), this->game->getGameCurrentUser());   
    }
    bool endgame = false;
    int size = this->game->getGameUsers()->size();
    while(!endgame){
        this->saveGame();
        UserInfo* current = this->game->getGameCurrentUser();
        stop = false;
        while(!stop){
            this->view->showShootOption();
            cin >> in;
            int value;
            stringstream(in) >> value;
            switch(value){
                default : break;
                case 1 : {
                    if(deductMode == 0){
                        if(current->getNbPlateau() > 0){
                            current->decrPlateau(1);
                            this->game->decrPlat(1);
                            this->platSent++;
                            this->saveAllPlat();
                            stop = true;
                        }
                        else{
                            this->view->showMessage("Pas assez de plateaux restants");
                        }
                    }
                    else{
                        if(this->game->getGameAllPlat() > 0){
                            this->game->decrPlat(1);
                            this->platSent++;
                            this->saveAllPlat();
                            stop = true;
                        }
                        else{
                            this->view->showMessage("Pas assez de plateaux restants");
                        }
                    }
                    break;
                }
                case 2 : {
                    if(deductMode == 0){
                        if(current->getNbPlateau() > 1){
                            current->decrPlateau(2);
                            this->game->decrPlat(2);
                            this->platSent += 2;
                            this->saveAllPlat();
                            stop = true;
                        }
                        else{
                            this->view->showMessage("Pas assez de plateaux restants");
                        }
                    }
                    else{
                        if(this->game->getGameAllPlat() > 1){
                            this->game->decrPlat(2);
                            this->platSent += 2;
                            this->saveAllPlat();
                            stop = true;
                        }
                        else{
                            this->view->showMessage("Pas assez de plateaux restants");
                        }
                    }
                    break;
                }
                case 3 : {
                    if(deductMode == 0){
                        if(current->getNbPlateau() > 1){
                            current->decrPlateau(2);
                            this->game->decrPlat(2);
                            this->platSent += 2;
                            this->saveAllPlat();
                            stop = true;
                        }
                        else{
                            this->view->showMessage("Pas assez de plateaux restants");
                        }
                    }
                    else{
                        if(this->game->getGameAllPlat() > 1){
                            this->game->decrPlat(2);
                            this->platSent += 2;
                            this->saveAllPlat();
                            stop = true;
                        }
                        else{
                            this->view->showMessage("Pas assez de plateaux restants");
                        }
                    }
                    break;
                }
                case 4 : {
                    stop = true;
                    if(this->game->getGameAllPlat() < 1){
                        endgame = true;
                    }
                        current = this->game->getGameCurrentUser();
                        for(int i = 0; i < size; i++){
                            if(this->game->getGameUsers()->at(i) == current){
                                if(i != size - 1){
                                    this->game->setGameCurrentUser(this->game->getGameUsers()->at(i + 1));
                                }
                                else{
                                    this->game->getGameUsers()->push_back(this->game->getGameUsers()->at(0));
                                    this->game->getGameUsers()->erase(this->game->getGameUsers()->begin());
                                    this->game->setGameCurrentUser(this->game->getGameUsers()->at(0));
                                }
                            }
                        }
                    break;
                }
                case 5 : {
                    stop = true;
                    if(deductMode == 0){
                        if (this->game->getGameCurrentUser()->getScore() < maxp){
                            this->game->getGameCurrentUser()->incrScore();
                        }
                    }
                    else{
                        this->game->getGameCurrentUser()->incrScore();
                    }
                    break;
                }
                case 6 : {
                    stop = true;
                    if(deductMode == 0){
                        if(this->game->getGameCurrentUser()->getScore() > 0){
                            this->game->getGameCurrentUser()->decrScore(); 
                        }
                    }
                    else{
                        if(this->game->getGameCurrentUser()->getScore() > 0){
                            this->game->getGameCurrentUser()->decrScore();
                        }
                    }
                    break;
                }
                case 1996 : {
                    stop = true;
                    if(this->enterPassword() == true){
                        this->resetAll();
                    }
                }
            }
            this->view->showGameInformations(deductMode, this->game->getGameAllPlat(), this->game->getGameCurrentUser());
        }
        
    }
    
}

Channel* ControllerConsole::chooseChannel(){
    int i;
    bool exist = false;
    while(!exist){
        this->view->showMessage("Choisissez votre canal : ");
        while(!(cin>>i)) {
 	        cin.clear();
 	        cin.ignore(999,'\n');
 	        this->view->showMessage("Entrée invalide, veuillez recommencer : ");
        }
        if(i == 1996){
            if(this->enterPassword() == true){
                this->resetAll();
            }
        }
        else{
            exist = this->database->checkChannel(i);
            if(!exist){
                this->view->showMessage("Canal inexistant !");
            }
        }
    }
    Channel* chan = this->database->findChannelById(i);
    this->game->setGameChannel(*chan);

    stringstream strs;
    strs << "Vous avez choisi le canal : ";
    strs << i;
    string temp_str = strs.str();
    char const* pchar = temp_str.c_str();
    this->view->showMessage(pchar);

    return chan;
}

void ControllerConsole::makeUserList(){
    bool stop = false;
    string in, incase;
    
    while(!stop){
        this->view->showUsers(this->game->getGameUsers(), false);
        this->view->showUserListOptions();
        cin >> in;
        int value;
        stringstream(in) >> value;
        switch(value){
            case 1:  {
                this->view->showMessage("ID :");
                cin >> incase;
                int nbCred;
                nbCred = this->database->howManyCredit(atoi(incase.c_str()),1);
                switch(nbCred){
                    case 0 : {
                        this->view->showMessage("Vous n'avez plus de crédit disponibles, impossible de rejoindre la partie !");
                        break;
                    }
                    case 1 : {
                        if(atoi(this->game->getParameterFromCode("lockAccount")->getParameterValue().c_str()) == 1){
                            if(this->database->findUserById(incase)->getUserAuthentification()->getUserType() == "EVENT"){
                                this->connectUser(incase.c_str());
                                this->view->showMessage("Il ne vous reste qu'un seul crédit !");
                                break;
                            }
                            else{
                                this->view->showMessage("L'accès aux comptes personnels est limité pour le moment"); break;
                            }
                        }
                        else{
                            if(this->database->findUserById(incase)->getUserAuthentification()->getUserType() != "EVENT"){
                                this->view->showMessage("Il ne vous reste qu'un seul crédit !");
                                this->connectUser(incase.c_str()); break;
                            }
                            else{
                                this->view->showMessage("Les comptes évènements ne sont pas autorisés pour le moment");
                            }
                        }
                        break;
                    }
                    case 2 : {
                        if(atoi(this->game->getParameterFromCode("lockAccount")->getParameterValue().c_str()) == 1){
                            if(this->database->findUserById(incase)->getUserAuthentification()->getUserType() == "EVENT"){
                                this->connectUser(incase.c_str());
                                this->view->showMessage("Il ne vous reste que deux crédits !");
                                break;
                            }
                            else{
                                this->view->showMessage("L'accès aux comptes personnels est limité pour le moment"); break;
                            }
                        }
                        else{
                            if(this->database->findUserById(incase)->getUserAuthentification()->getUserType() != "EVENT"){
                                this->view->showMessage("Il ne vous reste que deux crédits !");
                                this->connectUser(incase.c_str()); break;
                            }
                            else{
                                this->view->showMessage("Les comptes évènements ne sont pas autorisés pour le moment");
                            }
                        }
                        break;
                    }
                    case 3 : {
                        if(atoi(this->game->getParameterFromCode("lockAccount")->getParameterValue().c_str()) == 1){
                            if(this->database->findUserById(incase)->getUserAuthentification()->getUserType() == "EVENT"){
                                this->view->showMessage("Il ne vous reste que trois crédits !");
                                this->connectUser(incase.c_str());
                                break;
                            }
                            else{
                                this->view->showMessage("L'accès aux comptes personnels est limité pour le moment"); break;
                            }
                        }
                        else{
                            if(this->database->findUserById(incase)->getUserAuthentification()->getUserType() != "EVENT"){
                                this->view->showMessage("Il ne vous reste que trois crédits !");
                                this->connectUser(incase.c_str()); break;
                            }
                            else{
                                this->view->showMessage("Les comptes évènements ne sont pas autorisés pour le moment");
                            }
                        }
                        break;
                    }
                    case -1 : {
                        this->view->showMessage("Impossible de récupérer le nombre de crédits !");
                        break;
                    }
                    default : {
                        if(atoi(this->game->getParameterFromCode("lockAccount")->getParameterValue().c_str()) == 1){
                            if(this->database->findUserById(incase)->getUserAuthentification()->getUserType() == "EVENT"){
                                this->connectUser(incase.c_str());
                                break;
                            }
                            else{
                                this->view->showMessage("L'accès aux comptes personnels est limité pour le moment"); break;
                            }
                        }
                        else{
                            if(this->database->findUserById(incase)->getUserAuthentification()->getUserType() != "EVENT"){
                                this->connectUser(incase.c_str()); break;
                            }
                            else{
                                this->view->showMessage("Les comptes évènements ne sont pas autorisés pour le moment");
                            }
                        }
                    }
                }
                break;
                }
            case 2:
                this->view->showMessage("ID :");
                cin >> incase;
                if(incase == "1996"){
                    if(this->enterPassword() == true){
                    this->resetAll();
                    }
                }
                this->disconnectUser(incase.c_str());
                break;
            case 3:
                if(this->game->getGameUsers()->size() > 0)
                    stop = true;
                break;
            case 1996 :
                if(this->enterPassword() == true){
                    this->resetAll();
                }
            case 2000 : 
            {
                if(this->enterPassword() == true){
                    this->view->showMessage("---------------------");
                    this->view->showPlatSent(this->platSent);
                    this->view->showConfigOptions();
                    int y;
                    while(!(cin>>y)) {
                        cin.clear();
                        cin.ignore(999,'\n');
                        this->view->showMessage("Entrée invalide, veuillez recommencer : ");
                    }
                    switch(y){
                        case 1 : this->view->showMessage("---------------------"); break;
                        case 2 : this->platSent = 0; this->saveAllPlat();
                            this->view->showMessage("Compteur réinitialisé");
                            this->view->showMessage("---------------------"); break;
                    }
                }
            }
            default:
                break;
        }
        this->view->showMessage("------------------");
    }
}

bool ControllerConsole::connectUser(const char* id){
    UserInfo * user = this->database->findUserById(id);
    if(user != NULL){
        int lockAccount = atoi(this->game->getParameterFromCode("lockAccount")->getParameterValue().c_str());
        if(user->getUserAuthentification()->getUserType() == "MEMBRE" || user->getUserAuthentification()->getUserType() == "EVENT"){
            for( unsigned int i=0;i<this->game->getGameUsers()->size();i++){
                if(this->game->getGameUsers()->at(i)->getUser()->getUserId() == user->getUser()->getUserId()){
                    this->view->showMessage("Utilisateur déjà connecté");
                    return false;
                }
            }
            if(lockAccount == 1 && user->getUserAuthentification()->getUserType() != "EVENT"){
                this->view->showMessage("L'accès aux comptes personnels est limité pour le moment");                
                return false;                
            }
            else if(lockAccount == 0 && user->getUserAuthentification()->getUserType() == "EVENT"){
                this->view->showMessage("Les comptes évènements ne sont pas autorisés pour le moment");                
                return false;
            }
            else{
                this->game->getGameUsers()->push_back(user);
                this->view->showMessage("Utilisateur ajouté avec succès");
                return true;
            }
            
        }
        else if(user->getUserAuthentification()->getUserType() == "BUREAU" || user->getUserAuthentification()->getUserType() == "ADMIN"){
            if(lockAccount == 1){
                this->view->showMessage("L'accès aux comptes personnels est limité pour le moment");                
                return false;
            }
            else{
                int cpt = 0;
                for( unsigned int i=0;i<this->game->getGameUsers()->size();i++){
                    if(this->game->getGameUsers()->at(i)->getUser()->getUserId() == user->getUser()->getUserId()){
                        cpt++;
                    }
                }
                if(cpt==0){
                    this->game->getGameUsers()->push_back(user);
                    this->view->showMessage("Utilisateur ajouté avec succès");
                }
                else{
                    if(this->database->howManyCredit(user->getUser()->getUserId(),1) > cpt){
                        stringstream cptString;
                        cptString << cpt;
                        user->getUser()->setUserLastName(user->getUser()->getUserLastName()+" ("+cptString.str()+")");
                        this->game->getGameUsers()->push_back(user);
                        this->view->showMessage("Utilisateur ajouté avec succès");
                    }
                    else
                       this->view->showMessage("Pas assez de crédit"); 
                }
                return true;
            }
        }

    }
    return false;
}

bool ControllerConsole::disconnectUser(const char* id){
    bool deleted = false;
    int idInt;
    unsigned int i;
    stringstream(id) >> idInt;
    bool condition = true;
    while(condition){
        condition = false;
        for(i = 0; i < this->game->getGameUsers()->size(); i++){
            if(this->game->getGameUsers()->at(i)->getUser()->getUserId() == idInt){
                deleted = true;
                condition = true;
                this->game->getGameUsers()->erase(this->game->getGameUsers()->begin()+i);
                break;
                  //Stop for à l'endroit où supprimer
            }
        }
    }
    if(!deleted){
        this->view->showMessage("Utilisateur non connecté");
        return false; //Nothing to delete
    }
    else{
        this->view->showMessage("Utilisateur déconnecté");
        return true; //Deleted
    }
}

void ControllerConsole::resetAll(){
    this->view->showMessage("RESET !");
    remove("save.txt");
    this->game = new Game();
    this->run();
}

bool ControllerConsole::enterPassword(){
    this->view->showMessage("Veuillez renseigner le mot de passe : ");
    string in;
    cin >> in;
    Parameter* codeParam = this->game->getParameterFromCode("codeAdmin");
    if (in == codeParam->getParameterValue()){
        return true;
    }
    else{
        this->view->showMessage("Mot de passe incorrect !");
        return false;
    }
}

void ControllerConsole::saveAllPlat(){
    ofstream myfile;
    myfile.open ("plats.txt");
    myfile << this->platSent;
    myfile.close();
}

bool ControllerConsole::readAllPlat(){
    string line;
    ifstream myfile ("plats.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            this->platSent = atoi(line.c_str());
        }
    myfile.close();
    return true;
  }
  else{
    this->view->showMessage("Fichier de décompte introuvable, veuillez contacter un administrateur");
    return false;
  }
}

void ControllerConsole::saveGame(){
    std::ofstream ofs("save.txt");
    boost::archive::text_oarchive oa(ofs);
    oa << this->game;
}

void ControllerConsole::readBackup(){
    if(fileExists("save.txt")){
        this->view->showMessage("Une sauvegarde a été trouvée..");
        this->view->showSaveListOptions();
        int value = 0;
        string in;
        while(value != 1 && value != 2){
            cin >> in;
            stringstream(in) >> value;
        }
        if(value == 1){
            std::ifstream ifs("save.txt");
            boost::archive::text_iarchive ia(ifs);
            ia >> this->game;
            this->isSave = true;
        }
        else{
            remove("save.txt");
        }
    }
}

bool ControllerConsole::fileExists(const char * filename){
    ifstream infile(filename);
    return infile.good();
}