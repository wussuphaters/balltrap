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
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <stdint.h>

using namespace std;

ControllerMotion::ControllerMotion(){
    this->database = new Database("http://192.168.0.108/balltrap/public/api/command/");
    this->game = new Game();
    this->channelPointer=0;
    this->isParamRefreshed=false;
    this->isSave = false;
    this->pwd = "";
    this->delaiRafale=4;
    this->nbCreditsCurrentPlayer=1;
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
        case 9:{
        	std::ostringstream ss;
			ss << delaiRafale;
        	this->view->showDelayChoose(ss.str().c_str());
        	break;}
        default:
            break;
    }
}

int ControllerMotion::getPlatType(){
    return this->platType;
}

void ControllerMotion::changeDelay(int moreOrLess)	{
		if(moreOrLess==0 && this->delaiRafale>4.1) this->delaiRafale=this->delaiRafale-0.1;
		else if(moreOrLess==1) this->delaiRafale=this->delaiRafale+0.1;
		std::ostringstream ss;
		ss << delaiRafale;
	    this->view->showDelayChoose(ss.str().c_str());
}

void ControllerMotion::changeCanalNumber(int moreOrLess){
    if(moreOrLess==0){
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
}

void ControllerMotion::changeNbCredits(int moreOrLess)	{
	if(moreOrLess==0)	{
		if(this->nbCreditsCurrentPlayer>1) this->nbCreditsCurrentPlayer--;
	}
	else if(moreOrLess==1) this->nbCreditsCurrentPlayer++;
	std::ostringstream ss;
	ss << this->nbCreditsCurrentPlayer;
	this->view->showNbCreditsChoose(ss.str().c_str());
}

void ControllerMotion::addUser(){
    if(this->game->getGameUsers()->size()<10){
        int id = this->scanQRCode();
        if(id != -1){
            if(this->database->isConnectedToNetwork()){
                if(!this->isParamRefreshed){
                    this->refreshParams();
                }
                int nbCred = this->database->howManyCredit(id,1);
                if(nbCred==0) this->view->showMessage("Vous n'avez plus de crédits\nImpossible de rejoindre la partie !");
                else if(nbCred==-1) this->view->showMessage("Impossible de récupérer le nombre de crédits !");
                else if(nbCred<nbCreditsCurrentPlayer) this->view->showMessage("Vous n'avez plus assez de crédits\nImpossible de rejoindre la partie !");
                else this->connectUser(to_string(id).c_str());
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
                    this->view->setNoView(3);
                    this->redirectAfterMessage();
                }
                else{
                    this->view->showMessage("Impossible de lancer la partie !");
                }
            }
            else{
                this->view->showMessage("Aucune connexion internet\nVeuillez vous approcher d'un\nrépéteur wi-fi et recommencer");
                this->view->setNoView(2);       
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

void ControllerMotion::sendWave(int numLanceur16, int numCanal16){
	int fd;
	int numCanal10=base16ToBase10(numCanal16);
	int numLanceur10=base16ToBase10(numLanceur16);
 	fd = open("/dev/ttyUSB0", O_WRONLY | O_NOCTTY | O_NDELAY );	

	struct termios SerialPortSettings;	
    tcgetattr(fd, &SerialPortSettings);
	cfsetospeed(&SerialPortSettings,B9600); 
	tcsetattr(fd,TCSANOW,&SerialPortSettings);

	/*Construction de la trame d'activation du relais*/
	uint8_t on[20] = {0x7E, 0x00, 0x10, 0x17, 0x01};
	for(int i = 5; i<11; ++i){
		on[i] = 0x00;
	}
	for (int i = 11; i<13; ++i){
		on[i] = 0xFF;
	}
	add_addr16(on, numCanal10, numLanceur10);
	on[15] = 0x02;
	on[16] = 0x44; 
	on[17] = 0x31;
	on[18] = 0x05;
	add_cksum(on, sizeof(on));

	/*Construction de la trame de désactivation du relais*/
	uint8_t off[20] = {0x7E, 0x00, 0x10, 0x17, 0x01};
	for(int i = 5; i<11; ++i){
		off[i] = 0x00;
	}
	for (int i = 11; i<13; ++i){
		off[i] = 0xFF;
	}
	add_addr16(off, 255, 254);
	off[15] = 0x02;
	off[16] = 0x44; 
	off[17] = 0x31;
	off[18] = 0x04;
	add_cksum(off, sizeof(off));

	write(fd,on,sizeof(on));
	close(fd);


	int fd2 = open("/dev/ttyUSB0",O_WRONLY | O_NOCTTY | O_NDELAY);
	sleep(0.1);
	write(fd2, off, sizeof(off));
	cout<<"Delai de "<<delaiRafale<<"secondes";
	close(fd2);
}

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

float ControllerMotion::getDelaiRafale()	{
	return this->delaiRafale;
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
	cout<<"je suis dans pushletter";
	cout << this->pwd;
    switch(key){
        case 65457:
			this->pwd+='1';
			break;
		case 65458:
			this->pwd+='2';
			break;
		case 65459:
			this->pwd+='3';
			break;
		case 65460:
			this->pwd+='4';
			break;
		case 65461:
			this->pwd+='5';
			break;
		case 65462:
			this->pwd+='6';
			break;
		case 65463:
			this->pwd+='7';
			break;
		case 65464:
			this->pwd+='8';
			break;
		case 65465:
			this->pwd+='9';
			break;
		case 65466:
			this->pwd+='0';
			break;
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

void ControllerMotion::add_cksum(uint8_t p[], int pktsize){
	  uint8_t cksum = 0;  // start with a zero checksum
	  for (int i = 3; i < pktsize-1; i++) {  // skip the Start and len, start with byte 4.
	    // (remembering that C arrays start at 0, not 1.)
	    cksum += p[i];    // Add in this byte.
	  }  // next byte
	  cksum &= 0xFF;        // low order 8 bits
	  cksum = 0xFF - cksum; // subtract from 0xFF
	  p[19] = cksum;
}

void ControllerMotion::add_addr16(uint8_t p[], int channel, int remote){
	uint8_t ch = (uint8_t) channel;
	uint8_t re = (uint8_t) remote;
	p[13] = ch;
	p[14] = re;
}

int ControllerMotion::base16ToBase10(int hex)	{
	int dizaine = hex / 10;
	int unite = hex%10;
	int ret = dizaine*16 + unite;
	return ret;
}

