#include "ControllerMotion.h"
#include <string>
#include <sstream>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "sys/wait.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

using namespace std;

ControllerMotion::ControllerMotion(){
    this->database = new Database("http://192.168.43.240/balltrap/public/api/command/");
    this->game = new Game();
    this->channelPointer=0;
    this->isParamRefreshed=false;
    this->isSave = false;
    this->pwd = "";
}

void ControllerMotion::setViewMotion(ViewMotion* view){
    this->view=view;
}

void ControllerMotion::run(){
    
}

void ControllerMotion::refreshParams(){
    this->channelList = this->database->getChannels();
    this->game->setGameParameters(database->getParameters());
    this->platType = atoi(this->game->getParameterFromCode("cptType")->getParameterValue().c_str());
    this->nbPlatMax = atoi(this->game->getParameterFromCode("nbPlat")->getParameterValue().c_str());
    this->paramDefaultNbPlat = atoi(this->game->getParameterFromCode("defaultNbPlat")->getParameterValue().c_str());
    this->isParamRefreshed=true;
}


void ControllerMotion::makeUserList(){
    
}

void ControllerMotion::initializeCanalView(){
    this->game->setGameChannel(*(this->channelList.at(this->channelPointer)));
    this->view->showChannelChoose(this->game->getGameChannel()->getChannelNumber().c_str());
}

void ControllerMotion::redirectAfterMessage(){
    switch(this->view->getNoView()){
        case 1:
            this->view->showPlayerList(this->game->getGameUsers());
            break;
        case 2:
            this->view->showChannelChoose(this->game->getGameChannel()->getChannelNumber().c_str());            
            break;
        case 3:
            this->view->showGame(this->game);
            break;
        case 4:
            remove("save.txt");
            this->view->showEndGame(this->game->getGameUsers());
            break;
        case 5:
            this->view->showAskChangeChannel();
            break;
        case 6:
            this->view->showSaveChoose();
            break;
        case 7:
            this->view->showPwdChoose();
            break;
        case 8:
            this->view->showPlatChoose();
            break;
        default:
            break;
    }
}

int ControllerMotion::getPlatType(){
    return this->platType;
}

/**** Fonction pour Vue 1 ( canal ) ****/

void ControllerMotion::changeCanalNumber(int idParcours){
    /*if(moreOrLess==0){
        if(this->channelPointer>0){
            this->channelPointer--;
        }
    }
    else if(moreOrLess==1){
        if(this->channelPointer<(this->channelList.size()-1)){
            this->channelPointer++;
        }
    }
    this->game->setGameChannel(*(this->channelList.at(this->channelPointer)));    
    this->view->showChannelChoose(this->game->getGameChannel()->getChannelNumber().c_str());
    */
    this->channelPointer=idParcours-1;
    this->game->setGameChannel(*(this->channelList.at(this->channelPointer)));    
    this->view->showChannelChoose(this->game->getGameChannel()->getChannelNumber().c_str());
}

/**** Fonction pour Vue 2 ( Liste ) ****/


void ControllerMotion::addUser(){
    if(this->game->getGameUsers()->size()<10){
        int id = this->scanQRCode();
        if(id != -1){
            if(this->database->isConnectedToNetwork()){
                if(!this->isParamRefreshed){
                    this->refreshParams();
                }
                int nbCred = this->database->howManyCredit(id,1);
                switch(nbCred){
                    case 0 : {
                        this->view->showMessage("Vous n'avez plus de crédit disponibles\nImpossible de rejoindre la partie !");
                        break;
                    }
                    case 1 : {
                        this->view->showMessage("Il ne vous reste qu'un seul crédit !");
                        this->connectUser(to_string(id).c_str());
                        break;
                    }
                    case 2 : {
                        this->view->showMessage("Il ne vous reste que deux crédits !");
                        this->connectUser(to_string(id).c_str());
                        break;
                    }
                    case 3 : {
                        this->view->showMessage("Il ne vous reste que trois crédits !");
                        this->connectUser(to_string(id).c_str());
                        break;
                    }
                    case -1 : {
                        this->view->showMessage("Impossible de récupérer le nombre de crédits !");
                        break;
                    }
                    default : this->connectUser(to_string(id).c_str()); break;
                }
            }
            else{
                this->view->showMessage("Aucune connexion internet\nVeuillez vous approcher d'un\nrépéteur wi-fi et recommencer");               
            }
        }
        else{
            this->view->showMessage("Aucun code QR valide scanné\nVeuillez recommencer");        
        }
    }
    else{
        this->view->showMessage("Nombre maximum de tireur atteint");        
    }
}

void ControllerMotion::deleteUser(){
    if(this->game->getGameUsers()->size()>0){
        this->game->getGameUsers()->pop_back();
        this->view->showMessage("Utilisateur supprimé avec succès");    
    }
    else{
        this->view->showMessage("Aucune personne connectée");            
    }
}

bool ControllerMotion::checkUsers()	{
	bool rep=true;
	if(this->game->getGameUsers()->size()==0){
		rep=false;
        this->view->showMessage("Il faut ajouter des joueurs\n avant de lancer la partie !");
    }
    return rep;
}

void ControllerMotion::startGame(int type){
    if(this->isSave == false){
            if(this->database->isConnectedToNetwork()){
                this->refreshParams();
                vector<UserInfo*> list;
                //0 : compak / 1 : parcours / 2 : fosse
                list = this->database->checkCredit(this->game->getGameUsers(), type);
                if(list.size() > 0){
                    this->view->showMessage("Certains joueurs n'ont plus de crédit");
                }
                else if(list.size() == 0){
                    
                    int maxp;

                    if(this->paramDefaultNbPlat == 1){
                        maxp = this->nbPlatMax;
                    }
                    else if(this->paramDefaultNbPlat == 0){
                        maxp = this->channelList.at(this->channelPointer)->getChannelNbPlat();
                    }
                    else{
                        this->view->showMessage("Problème de paramètrage\nveuillez contacter un administrateur !\nErr : plateaux");
                        return;
                    }
                    //if(!this->isSave){
                    this->game->setGameAllPlat(maxp * this->game->getGameUsers()->size());
                    if(this->platType == 0){                                  
                        for(unsigned int i = 0; i < this->game->getGameUsers()->size(); i++){
                            UserInfo* current = this->game->getGameUsers()->at(i);
                            current->setNbPlateau(maxp);
                        }
                    }

                    this->database->decrCredits(this->game->getGameUsers(), type);
                    for(unsigned int i = 0; i < this->game->getGameUsers()->size(); i++){
                        this->game->getGameUsers()->at(i)->setScore(0);
                    }
                    this->game->setGameCurrentUser(this->game->getGameUsers()->at(0));
                    // this->saveGame();
                    this->view->setNoView(3);
                    this->redirectAfterMessage();
                }
                else{
                    this->view->showMessage("Impossible de lancer la partie !");
                }
            }
            else{
                this->view->showMessage("Aucune connexion internet\nVeuillez vous approcher d'un\nrépéteur wi-fi et recommencer");            
            }
    }
    else{
        this->view->setNoView(3);
        this->redirectAfterMessage();
    }
}


int ControllerMotion::scanQRCode(){
    int id=0,i=0,tempsAttenteMax=10,curseur=14;
    string idStr="";
    ifstream fichierUtilisateurLecture;
    ofstream fichierUtilisateurEcriture;
    const char* cheminFichier="/home/pi/dirlist.txt";
    pid_t pid = fork();

    if(pid == 0 )   { //enfant
        int fd;
        if((fd = open(cheminFichier, O_RDWR | O_CREAT, 0666))==-1){
            perror("open");
            return -1;
        }
        dup2(fd,STDOUT_FILENO);
        dup2(fd,STDERR_FILENO);
        close(fd);
        execlp("zbarcam","zbarcam","--prescale=100x100",NULL);
        sleep(2);
        exit(0);
    }
    if(pid > 1 )    { //parent
    	fichierUtilisateurEcriture.open(cheminFichier, ios::out | ios::trunc);
    	fichierUtilisateurEcriture << "0";
    	fichierUtilisateurEcriture.close();
        string chaine="0";
        while(chaine=="0")    {
            fichierUtilisateurLecture.open(cheminFichier);
            std::cout << i+1 << '\n';
            getline(fichierUtilisateurLecture,chaine);
            i++;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if(i==tempsAttenteMax)   {
                std::cout << "timeout" << '\n';
                fichierUtilisateurLecture.close();
                kill(pid, SIGKILL);
                return -1;
            }
            fichierUtilisateurLecture.close();
        }
        kill(pid, SIGKILL);
        while(chaine.at(curseur) != ',')	{
        	idStr+=chaine.at(curseur);
        	curseur++;
        }
        id=atoi(idStr.c_str());
        std::cout << "ID de la carte scannée : " << id << "\n";
    }
    fichierUtilisateurEcriture.open(cheminFichier, ios::out | ios::trunc);
    fichierUtilisateurEcriture << "0";
    fichierUtilisateurEcriture.close();

    return id;
}

int ControllerMotion::addParcours()	{
	int id=this->scanParcours();
    if(id!=-1)  {
    	this->changeCanalNumber(id);
    	return 0;
    }
    return -1;
}

int ControllerMotion::scanParcours(){
    int id=-1,i=0,tempsAttenteMax=10,curseur=17;
    string idStr="";
    ifstream fichierUtilisateurLecture;
    ofstream fichierUtilisateurEcriture;
    const char* cheminFichier="/home/pi/dirlist.txt";
    pid_t pid = fork();

    if(pid == 0 )   { //enfant
        int fd;
        if((fd = open(cheminFichier, O_RDWR | O_CREAT, 0666))==-1){
            perror("open");
            return -1;
        }

        dup2(fd,STDOUT_FILENO);
        dup2(fd,STDERR_FILENO);
        close(fd);
        execlp("zbarcam","zbarcam","--prescale=100x100"/*,"--nodisplay"*/,NULL);
        sleep(2);
        exit(0);
    }
    if(pid > 1 )    { //parent
        string chaine= "0";
        while(chaine=="0")    {
            fichierUtilisateurLecture.open(cheminFichier);
            std::cout << i+1 << '\n';
            getline(fichierUtilisateurLecture,chaine);
            i++;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if(i==tempsAttenteMax)   {
                std::cout << "timeout" << '\n';
                fichierUtilisateurLecture.close();
                kill(pid, SIGKILL);
                return -1;
            }
            fichierUtilisateurLecture.close();
        }
        kill(pid, SIGKILL);
        while(chaine.at(curseur) != '$')	{
        	idStr+=chaine.at(curseur);
        	curseur++;
        }
        id=atoi(idStr.c_str());
        std::cout << "ID du parcours scanné : " << id << "\n";
        fichierUtilisateurEcriture.open(cheminFichier, ios::out | ios::trunc);
        fichierUtilisateurEcriture << "0";
        fichierUtilisateurEcriture.close();
    }

    return id;
}

bool ControllerMotion::connectUser(const char* id){
    /*UserInfo * user = this->database->findUserById(id);
    if(user != NULL){
        if(user->getUser()->getUserFirstName().length() > 12){
            user->getUser()->setUserFirstName(user->getUser()->getUserFirstName().substr(0,10));
        }
        if(user->getUserAuthentification()->getUserType() == "MEMBRE"){
            for( unsigned int i=0;i<this->game->getGameUsers()->size();i++){
                if(this->game->getGameUsers()->at(i)->getUser()->getUserId() == user->getUser()->getUserId()){
                    this->view->showMessage("Utilisateur déjà connecté");
                    return false;
                }
            }
            this->game->getGameUsers()->push_back(user);
            this->view->showMessage("Utilisateur ajouté avec succès");
            return true;
        }
        else if(user->getUserAuthentification()->getUserType() == "BUREAU" || user->getUserAuthentification()->getUserType() == "ADMIN"){
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
                stringstream cptString;
                cptString << cpt;
                user->getUser()->setUserLastName(user->getUser()->getUserLastName()+" ("+cptString.str()+")");
                this->game->getGameUsers()->push_back(user);
                this->view->showMessage("Utilisateur ajouté avec succès");
            }
            return true;
        }
        else{
            this->view->showMessage("Impossible de se connecter avec \n un compte evenement");
            return false;            
        }

    }
            return false;

*/
    UserInfo * user = this->database->findUserById(id);
    if(user != NULL){
        if(user->getUser()->getUserFirstName().length() > 12){
            user->getUser()->setUserFirstName(user->getUser()->getUserFirstName().substr(0,10));
        }
        int lockAccount = atoi(this->game->getParameterFromCode("lockAccount")->getParameterValue().c_str());
        if(user->getUserAuthentification()->getUserType() == "MEMBRE" || user->getUserAuthentification()->getUserType() == "EVENT"){
            for( unsigned int i=0;i<this->game->getGameUsers()->size();i++){
                if(this->game->getGameUsers()->at(i)->getUser()->getUserId() == user->getUser()->getUserId()){
                    this->view->showMessage("Utilisateur déjà connecté");
                    return false;
                }
            }
            if(lockAccount == 1 && user->getUserAuthentification()->getUserType() != "EVENT"){
                this->view->showMessage("L'accès aux comptes personnels\n est limité pour le moment");                
                return false;                
            }
            else if(lockAccount == 0 && user->getUserAuthentification()->getUserType() == "EVENT"){
                this->view->showMessage("Les comptes évènements ne sont\n pas autorisés pour le moment");                
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
                this->view->showMessage("L'accès aux comptes personnels\n est limité pour le moment");                
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
                    stringstream cptString;
                    cptString << cpt;
                    user->getUser()->setUserLastName(user->getUser()->getUserLastName()+" ("+cptString.str()+")");
                    this->game->getGameUsers()->push_back(user);
                    this->view->showMessage("Utilisateur ajouté avec succès");
                }
                return true;
            }
        }

    }
    return false;
}

/**** Vue 3 ****/

void ControllerMotion::changeScore(int moreOrLess){
    if(moreOrLess){
        this->game->getGameCurrentUser()->setScore(this->game->getGameCurrentUser()->getScore()+1);        
    }
    else{
        if(this->game->getGameCurrentUser()->getScore()>0){   
            this->game->getGameCurrentUser()->setScore(this->game->getGameCurrentUser()->getScore()-1);
        }
    }
    this->saveGame();
    this->view->showGame(this->game);
}

void ControllerMotion::changePlayer(){
    if(this->game->getGameAllPlat() < 1){
        this->view->setNoView(4);
        remove("save.txt");
        this->isSave = false;
        this->view->showEndGame(this->game->getGameUsers());        
    }
    else{
        UserInfo* current = this->game->getGameCurrentUser();
        for(unsigned int i = 0; i < this->game->getGameUsers()->size(); i++){
            if(this->game->getGameUsers()->at(i) == current){
                if(i != this->game->getGameUsers()->size() - 1){
                    this->game->setGameCurrentUser(this->game->getGameUsers()->at(i + 1));
                }
                else{
                    this->game->getGameUsers()->push_back(this->game->getGameUsers()->at(0));
                    this->game->getGameUsers()->erase(this->game->getGameUsers()->begin());
                    this->game->setGameCurrentUser(this->game->getGameUsers()->at(0));
                }
            }
        }
        this->view->showGame(this->game);
    }
}

void ControllerMotion::shoot(int keyval){
    bool canIShoot=true;
    int numLanceur=0,numCanal=0;
    if(this->platType == 0){
        if(this->game->getGameCurrentUser()->getNbPlateau() <= 0){
            this->saveGame();
            canIShoot=false;
        }
    }
    else{
        if(this->game->getGameAllPlat() <= 0){
            this->saveGame();
            canIShoot=false;
        }
    }
    if(canIShoot){
        if(keyval>=65457&&keyval<=65465){
        	switch(keyval)	{
        		case 65457:
        			numLanceur=1;
        			break;
        		case 65458:
        			numLanceur=2;
        			break;
        		case 65459:
        			numLanceur=3;
        			break;
        		case 65460:
        			numLanceur=4;
        			break;
        		case 65461:
        			numLanceur=5;
        			break;
        		case 65462:
        			numLanceur=6;
        			break;
        		case 65463:
        			numLanceur=7;
        			break;
        		case 65464:
        			numLanceur=8;
        			break;
        		case 65465:
        			numLanceur=9;
        			break;
        	}
        	numCanal=atoi(this->game->getGameChannel()->getChannelNumber().c_str());
        	cout << "Tir du lanceur " << numLanceur << " sur le canal " << numCanal << endl;
            this->sendWave(numLanceur,numCanal);
            this->game->getGameCurrentUser()->decrPlateau(1);
            this->game->decrPlat(1);
            this->platSent++;
            this->saveAllPlat();
            this->saveGame();
            this->view->showGame(this->game);
        }
    }
    else{
        this->view->showMessage("Vous n'avez plus de plateaux");
    }
}

/**
*   keyval : 97 : A / 98 : B .... 104 : H
*   channel : numéro du channel de 1 à 32
*/
void ControllerMotion::sendWave(int numLanceur, int numCanal){
	char dest_addr_16[8];
	if(numLanceur<10){
		sprintf(dest_addr_16, "%d0%d", numCanal, numLanceur);
	}else{
		sprintf(dest_addr_16, "%d%d", numCanal, numLanceur);
	}
	pid_t pid = fork();
	if(pid==0)	{
		execl("/usr/bin/java", "/usr/bin/java","-Djava.library.path=/usr/lib/jni", "-cp", ".:/usr/share/java/RXTXcomm.jar",  "-jar", "/home/pi/xbee.jar", dest_addr_16, NULL);
	}
}

/**** Vue 4 ****/


/**** Vue 5 ****/

void ControllerMotion::restartGame(){
    this->game->clearUserList();
    this->view->setNoView(1);
    this->channelPointer=0;
    this->isParamRefreshed=false;
    this->redirectAfterMessage();
}

void ControllerMotion::saveGame(){
    std::ofstream ofs("save.txt");
    boost::archive::text_oarchive oa(ofs);
    oa << this->game;
}

void ControllerMotion::checkBackup(){
    if(fileExists("save.txt")){
        this->view->setNoView(6);
        this->redirectAfterMessage();
    }
}

void ControllerMotion::readBackup(int keyValue){   
    if(keyValue == 1){
        if(this->database->isConnectedToNetwork()){
            this->refreshParams();
            std::ifstream ifs("save.txt");
            boost::archive::text_iarchive ia(ifs);
            ia >> this->game;
            this->isSave = true;
            this->view->setNoView(2);
            this->redirectAfterMessage();
        }
        else{
            this->view->showMessage("Aucune connexion internet\nVeuillez vous approcher d'un\nrépéteur wi-fi et recommencer");               
        }
    }
    else{
        remove("save.txt");
        this->view->setNoView(1);
        this->redirectAfterMessage();
    }
}

bool ControllerMotion::fileExists(const char * filename){
    ifstream infile(filename);
    return infile.good();
}

void ControllerMotion::confirmPwd(int choice){

    this->pwd.erase(0,1);
    if(this->database->isConnectedToNetwork()){
        if(!this->isParamRefreshed){
            this->refreshParams();
        }
        if(this->game->getParameterFromCode("codeAdmin")->getParameterValue() == this->pwd){
            if(choice == 1)
                this->resetAll();
            else{
                this->view->setNoView(8);
                this->redirectAfterMessage();
            }
        }
        else{
        this->view->showMessage("Mot de passe incorrect");            
        }
    }
    else{
        this->view->showMessage("Aucune connexion internet\nVeuillez vous approcher d'un\nrépéteur wi-fi et recommencer");            
    }
}

void ControllerMotion::pushLetter(int key){
    switch(key){
        case 97:
            this->pwd += 'A'; break;
        case 98:
            this->pwd += 'B'; break;
        case 99:
            this->pwd += 'C'; break;
        case 100:
            this->pwd += 'D'; break;
        case 101:
            this->pwd += 'E'; break;
        case 102:
            this->pwd += 'F'; break;
        case 103:
            this->pwd += 'G'; break;
        case 104:
            this->pwd += 'H'; break;
    }
}

void ControllerMotion::resetAll(){
    this->game->clearUserList();
    this->view->setNoView(1);
    this->channelPointer=0;
    this->isParamRefreshed=false;
    this->redirectAfterMessage();
    remove("save.txt");
    this->view->setNoView(1);
    this->redirectAfterMessage();
    this->view->showMessage("Télécommande réinitialisée");
}

void ControllerMotion::resetPwd(){
    this->pwd = "";
}

bool ControllerMotion::readAllPlat(){
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
    this->platSent = 0;      
    //this->view->showMessage("Fichier de décompte introuvable\n veuillez contacter un administrateur");
    return false;
  }
}

void ControllerMotion::saveAllPlat(){
    ofstream myfile;
    myfile.open ("plats.txt");
    myfile << this->platSent;
    myfile.close();
}

void ControllerMotion::resetPlat(){
    this->platSent = 0;
    this->saveAllPlat();
}

string ControllerMotion::getPlatSent(){
    stringstream strs;
    strs << "Plateau(x) : ";
    strs << this->platSent;
    string temp_str = strs.str();
    char const* pchar = temp_str.c_str();
    std::string s = pchar;
    return pchar;
}

