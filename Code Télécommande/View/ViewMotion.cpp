#include "ViewMotion.h"
#include "../Controller/Controller.h"
#include "../Controller/ControllerConsole.h"
#include "../Model/Database.h"

using namespace std;


static gboolean is_a_pressed = false;
static gboolean is_b_pressed = false;
static gboolean is_c_pressed = false;
static gboolean is_d_pressed = false;
int currentView;
int choice;

ViewMotion::ViewMotion(): Gtk::Window(Gtk::WINDOW_TOPLEVEL)
{

    this->viewNo = 1;
    this->isMessage = 0;
    this->isInitializaton = 1;
    MainWindow = this;
    MainWindow->set_default_size(485, 325);
    MainWindow->resize(485,325);
    MainWindow->set_position(Gtk::WIN_POS_CENTER_ALWAYS);
    MainWindow->set_decorated(FALSE);
    MainWindow->add_events( Gdk::KEY_PRESS_MASK ); 
    MainWindow->signal_key_press_event().connect(sigc::mem_fun(*this, &ViewMotion::on_key_press));
    MainWindow->signal_key_release_event().connect(sigc::mem_fun(*this, &ViewMotion::on_key_release_event));
    //Paramétrage
    GtkCssProvider *cssProvider = gtk_css_provider_new ();
    gtk_css_provider_load_from_path(cssProvider,"./style.css",NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    Gtk::Grid grid;
    setLabelExpandable();
    MainWindow->add(grid);
    grid.set_column_homogeneous(true);
    grid.set_row_homogeneous(true);
    controller = new ControllerMotion();
    controller->setViewMotion(this);
    if(!controller->readAllPlat()){
        std::ofstream myfile("plats.txt");
        /*myfile.open("plats.txt");
        myfile << "0";
        myfile.close();*/
    }
    controller->checkBackup();
    this->controller->redirectAfterMessage();
    gtk_main();
}

ViewMotion::~ViewMotion(){
}

int ViewMotion::getNoView() const{
    return this->viewNo;
}

void ViewMotion::setNoView(int no){
    this->viewNo=no;
}

/**
* 1 : liste des tireurs
* 2 : choix canal
* 3 : Partie
* 4 : Score
* 5 : Annonce nouvelle partie
* 6 : Sauvegarde
* 7 : Administration
**/
bool ViewMotion::on_key_release_event(GdkEventKey* event){
    if (event->keyval == 65451){
        is_a_pressed = FALSE;
    }

    if (event->keyval == 65288){
        is_b_pressed = FALSE;
    }

    if (event->keyval == 99){
        is_c_pressed = FALSE;
    }

    if (event->keyval == 38){
        is_d_pressed = FALSE;
    }


    cout << event->keyval <<endl;
    
    /*
    if(this->isInitializaton){
        //controller->refreshParams();
        this->isInitializaton=0;
    }
    */

    if(this->isMessage){
        if(event->keyval == 233 || event->keyval == 65450){
            this->controller->redirectAfterMessage();
            this->isMessage=0;
        }
    }
    else{
        switch(viewNo){
            case 1:
                switch(event->keyval){
                    case 38:             
                    case 65455:
                        this->controller->addUser();
                        break;
                    case 233:
                    case 65450:
                        this->controller->deleteUser();
                        break;
                    case 34:
                    case 65453:
                        cout << "vue1";
                        if(this->controller->checkUsers())  {
                            this->controller->initializeCanalView();            
                            this->setNoView(2);
                            this->controller->redirectAfterMessage();
                        }
                        break;
                }
                break;
            case 2:
                switch(event->keyval){
                    case 38:
                    case 65455:
                        this->controller->changeCanalNumber(0);
                        break;
                    case 233:
                    case 65450:
                        this->controller->changeCanalNumber(1);
                        break;
                    /*case 34:*/
                    case 65453:
                        cout << "vue2";
                        this->viewNo = 3;
                        this->controller->startGame(1);
                        break;
                }
                break;
            case 3:
                switch(event->keyval){
                    case 65455:
                        this->controller->changeScore(0);
                        break;
                    case 65450:
                    cout <<"test";
                        this->controller->changeScore(1);                    
                        break;
                    case 65453:
                        cout << "vue3";
                        this->controller->changePlayer();
                        break;
                    /*default:
                        this->controller->shoot(event->keyval);
                        break;*/
                }
                break;
            case 4:
                switch(event->keyval){
                    case 65455:
                        break;
                    case 65450:
                        viewNo = 5;
                        this->controller->redirectAfterMessage();
                        break;
                    case 65453:
                        cout << "vue4";
                        break;
                }
                break;
            case 5:
                switch(event->keyval){
                    case 65455:
                        break;
                    case 65450:
                        this->controller->restartGame();
                        break;
                    case 65453:
                        cout << "vue5";                  
                        break;
                }
                break;
            case 6:
                switch(event->keyval){
                    case 65455:
                        this->controller->readBackup(0);
                        break;
                    case 65450:
                        break;
                    case 65453:  
                        cout << "vue6";               
                        this->controller->readBackup(1);
                        break;
                }
                break;
            case 7:
                switch(event->keyval){
                    case 65455:
                        this->setNoView(currentView);
                        this->controller->resetPwd();
                        this->controller->redirectAfterMessage();
                        break;
                    case 65450:
                        break;
                    case 65453:
                        cout << "vue7";                
                        this->controller->confirmPwd(choice);
                        break;
                    default:
                        this->controller->pushLetter(event->keyval);break;

                }
                break;
            case 8:
                switch(event->keyval){
                    case 65455:
                        this->controller->resetPlat();
                        this->setNoView(currentView);
                        this->controller->resetPwd();
                        this->controller->redirectAfterMessage();
                        this->showMessage("Compteur réinitialisé");
                        break;
                    case 65450:
                        break;
                    case 65453:
                        cout << "vue8";
                        this->setNoView(currentView);
                        this->controller->resetPwd();
                        this->controller->redirectAfterMessage();                
                        break;
                }
                break;
            case 9:
                switch(event->keyval){
                    case 65455:
                        this->controller->changeDelay(0);
                        break;
                    case 65450:
                        this->controller->changeDelay(1);
                        break;
                    case 65453:
                        this->viewNo=3;
                        this->controller->redirectAfterMessage();              
                        break;
                }
                break;
            /*case 10:
                switch(event->keyval){
                    case 65455:
                        this->controller->changeNbCredits(0);
                        break;
                    case 65450:
                        this->controller->changeNbCredits(1);
                        break;
                    case 65453:
                        this->viewNo=1;
                        this->controller->addUser();
                        //this->controller->redirectAfterMessage();              
                        break;
                }
                break;*/
        }
    }
    return true;
}

bool ViewMotion::on_key_press (GdkEventKey *e)
{
    if(this->viewNo==3) {
        switch(e->keyval){
                    case 65455:
                    break;
                    case 65450:
                    break;
                    case 65453:
                    break;
                    default:
                        this->controller->shoot(e->keyval);
                        sleep(this->controller->getDelaiRafale());
                        break;
                }
    }
    if(this->viewNo==1) {
        if (e->keyval == 65451 && is_a_pressed == FALSE){
            is_a_pressed = TRUE;
        }

        if (e->keyval == 65288 && is_b_pressed == FALSE)
            is_b_pressed = TRUE;

        if (e->keyval == 65421 && is_c_pressed == FALSE)
            is_c_pressed = TRUE;

        if (is_a_pressed && is_b_pressed){
            currentView = this->getNoView();
            this->controller->resetPwd();
            this->setNoView(7);
            this->controller->redirectAfterMessage();
            choice = 1;
            is_a_pressed = FALSE;
            is_b_pressed = FALSE;
        }

        if (is_c_pressed && is_b_pressed){
            this->controller->resetPwd();
            currentView = this->getNoView();
            this->setNoView(7);
            choice = 2;
            this->controller->redirectAfterMessage();
            is_c_pressed = FALSE;
            is_d_pressed = FALSE;
        }        
    }

    if(this->viewNo==3) {
        if (e->keyval == 65451 && is_a_pressed == FALSE){
            is_a_pressed = TRUE;
        }
        if (e->keyval == 65288 && is_b_pressed == FALSE)
            is_b_pressed = TRUE;
        if (is_a_pressed && is_b_pressed){
            currentView = this->getNoView();
            this->setNoView(9);
            this->controller->redirectAfterMessage();
            is_a_pressed = FALSE;
            is_b_pressed = FALSE;
        }
    }

  /* let the event propagate further */
  return GDK_EVENT_PROPAGATE;
}

void ViewMotion::showGame(Game * game){
    MainWindow->remove();    
    resetGrid();

    string label1Content = "Canal : ";
    string label2Content = "Suivant : ";
    string label3Content = "";
    string label5Content = "Score : ";
    string label6Content = "";

    label1Content+=game->getGameChannel()->getChannelNumber();

    label2Content+=game->getNextUser()->getUser()->getUserFirstName()+" "+game->getNextUser()->getUser()->getUserLastName()[0]+".";
    if(game->getNextUser()->getUser()->getUserLastName().back() == ')'){
        label2Content+=game->getNextUser()->getUser()->getUserLastName().substr( game->getNextUser()->getUser()->getUserLastName().size() - 3 );
    }

    label3Content+=game->getGameCurrentUser()->getUser()->getUserFirstName()+" "+game->getGameCurrentUser()->getUser()->getUserLastName()[0]+".";
    if(game->getGameCurrentUser()->getUser()->getUserLastName().back() == ')'){
        label3Content+=game->getGameCurrentUser()->getUser()->getUserLastName().substr( game->getGameCurrentUser()->getUser()->getUserLastName().size() - 3 );
    }

    label5Content+=to_string(game->getGameCurrentUser()->getScore());
    cout << "Type :"<<this->controller->getPlatType()<<endl;
    if(this->controller->getPlatType()){
        label6Content+=to_string(game->getGameAllPlat());        
    }
    else{
        label6Content+=to_string(game->getGameCurrentUser()->getNbPlateau());
    }

    label1.set_label(label1Content);
    label2.set_label(label2Content);
    label3.set_label(label3Content);
    label4.set_label("Plateaux");
    label5.set_label(label5Content);
    label6.set_label(label6Content);
    label7.set_label("-");
    label8.set_label("+");
    label9.set_label("Suivant");

    label1.set_name("label1");
    label2.set_name("label2");
    label3.set_name("label3");
    label4.set_name("label4");
    label5.set_name("label5");
    label6.set_name("label6");
    label7.set_name("label7");
    label8.set_name("label8");
    label9.set_name("label9");
    
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);

    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);

    grid.attach(label1, 0, 0, 3, 1);
    grid.attach(label2, 3, 0, 3, 1);
    grid.attach(label3, 0, 1, 4, 2);
    grid.attach(label4, 4, 1, 2, 2);
    grid.attach(label5, 0, 3, 4, 2);
    grid.attach(label6, 4, 3, 2, 2);
    grid.attach(label7, 0, 5, 2, 1);
    grid.attach(label8, 2, 5, 2, 1);
    grid.attach(label9, 4, 5, 2, 1);

    MainWindow->add(grid); 
    MainWindow->show_all(); 
}

void ViewMotion::showChannelChoose(const char* canalNumber){
    MainWindow->remove();        
    resetGrid();
    label1.set_label("Choisissez votre canal");
    label2.set_label(canalNumber);
    label7.set_label("-");
    label8.set_label("+");
    label9.set_label("Suivant");

    label1.set_name("canallabel1");
    label2.set_name("canallabel2");
    label7.set_name("canallabel7");
    label8.set_name("canallabel8");
    label9.set_name("canallabel9");
    
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);

    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);

    grid.attach(label1, 0, 0, 3, 1);
    grid.attach(label2, 0, 1, 3, 4);
    grid.attach(label7, 0, 5, 1, 1);
    grid.attach(label8, 1, 5, 1, 1);
    grid.attach(label9, 2, 5, 1, 1);

    MainWindow->add(grid); 
    MainWindow->show_all();    
}

void ViewMotion::showNbCreditsChoose(const char* nbCredits){
    MainWindow->remove();        
    resetGrid();
    label1.set_label("Combien de crédits souhaitez-vous utiliser ?");
    label2.set_label(nbCredits);
    label7.set_label("-");
    label8.set_label("+");
    label9.set_label("Valider");

    label1.set_name("canallabel1");
    label2.set_name("canallabel2");
    label7.set_name("canallabel7");
    label8.set_name("canallabel8");
    label9.set_name("canallabel9");
    
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);

    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);

    grid.attach(label1, 0, 0, 3, 1);
    grid.attach(label2, 0, 1, 3, 4);
    grid.attach(label7, 0, 5, 1, 1);
    grid.attach(label8, 1, 5, 1, 1);
    grid.attach(label9, 2, 5, 1, 1);

    MainWindow->add(grid); 
    MainWindow->show_all();    
}

void ViewMotion::showDelayChoose(const char* delay){
    MainWindow->remove();        
    resetGrid();
    label1.set_label("Délai entre tirs en rafale");
    label2.set_label(delay);
    label7.set_label("-");
    label8.set_label("+");
    label9.set_label("Valider");

    label1.set_name("canallabel1");
    label2.set_name("canallabel2");
    label7.set_name("canallabel7");
    label8.set_name("canallabel8");
    label9.set_name("canallabel9");
    
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);

    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);

    grid.attach(label1, 0, 0, 3, 1);
    grid.attach(label2, 0, 1, 3, 4);
    grid.attach(label7, 0, 5, 1, 1);
    grid.attach(label8, 1, 5, 1, 1);
    grid.attach(label9, 2, 5, 1, 1);

    MainWindow->add(grid); 
    MainWindow->show_all();    
}

void ViewMotion::showPlayerList(std::vector<UserInfo*>* userList){
    string left = "";
    string right = "";
    if(userList->size()<=5){
        for(unsigned int i=0;i<userList->size();i++){
            left+=userList->at(i)->getUser()->getUserFirstName()+" "+userList->at(i)->getUser()->getUserLastName()[0]+".";
            if(userList->at(i)->getUser()->getUserLastName().back() == ')'){
                left+=userList->at(i)->getUser()->getUserLastName().substr( userList->at(i)->getUser()->getUserLastName().size() - 3 );
                
            }
            if(i!=userList->size()-1){
                left += "\n";
            }
        }
    }
    else{
        for(unsigned int i=0;i<5;i++){
            left+=userList->at(i)->getUser()->getUserFirstName()+" "+userList->at(i)->getUser()->getUserLastName()[0]+".";
            if(userList->at(i)->getUser()->getUserLastName().back() == ')'){
                left+=userList->at(i)->getUser()->getUserLastName().substr( userList->at(i)->getUser()->getUserLastName().size() - 3 );
            }
            if(i!=4){
                left += "\n";
            }
        }
        for(unsigned int i=5;i<userList->size();i++){
            right+=userList->at(i)->getUser()->getUserFirstName()+" "+userList->at(i)->getUser()->getUserLastName()[0]+".";
            if(userList->at(i)->getUser()->getUserLastName().back() == ')'){
                right+=userList->at(i)->getUser()->getUserLastName().substr( userList->at(i)->getUser()->getUserLastName().size() - 3 );
            }
            if(i!=userList->size()-1){
                right += "\n";
            }
        }
    }
    MainWindow->remove();    
    resetGrid();
    label1.set_label("Liste des tireurs");
    label2.set_label(left);
    label3.set_label(right);
    label7.set_label("Ajouter");
    label8.set_label("Supprimer");
    label9.set_label("Commencer");

    label1.set_name("listelabel1");
    label2.set_name("listelabel2");
    label3.set_name("listelabel3");
    label7.set_name("listelabel7");
    label8.set_name("listelabel8");
    label9.set_name("listelabel9");
    
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);

    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);

    grid.attach(label1, 0, 0, 6, 1);
    grid.attach(label2, 0, 1, 3, 4);
    grid.attach(label3, 3, 1, 3, 4);
    grid.attach(label7, 0, 5, 2, 1);
    grid.attach(label8, 2, 5, 2, 1);
    grid.attach(label9, 4, 5, 2, 1);

    MainWindow->add(grid); 
    MainWindow->show_all(); 
}

void ViewMotion::showMessage(const char* msg){
    this->isMessage=1;
    MainWindow->remove();    
    resetGrid();
    label1.set_label(msg);
    label7.set_label(" ");
    label8.set_label("Suivant");
    label9.set_label(" ");

    label1.set_name("listelabel1");
    label7.set_name("listelabel7");
    label8.set_name("listelabel8");
    label9.set_name("listelabel9");
    
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);

    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);

    grid.attach(label1, 0, 0, 3, 5);
    grid.attach(label7, 0, 5, 1, 1);
    grid.attach(label8, 1, 5, 1, 1);
    grid.attach(label9, 2, 5, 1, 1);

    MainWindow->add(grid); 
    MainWindow->show_all(); 
}

void ViewMotion::showNoConnection(){

    MainWindow->remove();    
    resetGrid();

    label1.set_label("En attente de connexion WiFi ...");

    label1.set_name("labelErrorCo");
    
    grid.insert_column(0);

    grid.insert_column(0);

    grid.insert_row(0);

    grid.attach(label1, 0, 0, 1, 1);

    MainWindow->add(grid); 
    MainWindow->show_all(); 
}

void ViewMotion::showEndGame(std::vector<UserInfo*>* userList){
    string left = "";
    string right = "";
    if(userList->size()<=5){
        for(unsigned int i=0;i<userList->size();i++){
            left+=userList->at(i)->getUser()->getUserFirstName()+" "+userList->at(i)->getUser()->getUserLastName()[0]+".";
            if(userList->at(i)->getUser()->getUserLastName().back() == ')'){
                left+=userList->at(i)->getUser()->getUserLastName().substr( userList->at(i)->getUser()->getUserLastName().size() - 3 );
                
            }
            left+=" - "+to_string(userList->at(i)->getScore());
            if(i!=userList->size()-1){
                left += "\n";
            }
        }
    }
    else{
        for(unsigned int i=0;i<5;i++){
            left+=userList->at(i)->getUser()->getUserFirstName()+" "+userList->at(i)->getUser()->getUserLastName()[0]+".";
            if(userList->at(i)->getUser()->getUserLastName().back() == ')'){
                left+=userList->at(i)->getUser()->getUserLastName().substr( userList->at(i)->getUser()->getUserLastName().size() - 3 );
            }
            left+=" - "+to_string(userList->at(i)->getScore());
            if(i!=4){
                left += "\n";
            }
        }
        for(unsigned int i=5;i<userList->size();i++){
            right+=userList->at(i)->getUser()->getUserFirstName()+" "+userList->at(i)->getUser()->getUserLastName()[0]+".";
            if(userList->at(i)->getUser()->getUserLastName().back() == ')'){
                right+=userList->at(i)->getUser()->getUserLastName().substr( userList->at(i)->getUser()->getUserLastName().size() - 3 );
            }
            right+=" - "+to_string(userList->at(i)->getScore());
            if(i!=userList->size()-1){
                right += "\n";
            }
        }
    }
    MainWindow->remove();    
    resetGrid();
    label1.set_label("Partie terminée");
    label2.set_label(left);
    label3.set_label(right);
    label7.set_label("");
    label8.set_label("Suivant");
    label9.set_label("");

    label1.set_name("listelabel1");
    label2.set_name("listelabel2");
    label3.set_name("listelabel3");
    label7.set_name("listelabel7");
    label8.set_name("listelabel8");
    label9.set_name("listelabel9");
    
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);

    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);

    grid.attach(label1, 0, 0, 6, 1);
    grid.attach(label2, 0, 1, 3, 4);
    grid.attach(label3, 3, 1, 3, 4);
    grid.attach(label7, 0, 5, 2, 1);
    grid.attach(label8, 2, 5, 2, 1);
    grid.attach(label9, 4, 5, 2, 1);

    MainWindow->add(grid); 
    MainWindow->show_all(); 
}

/*void ViewMotion::showDemandeRaZ(){
    MainWindow->remove();        
    resetGrid();
    label1.set_label("Souhaitez vous remettre à \n  zéro la liste des tireurs ?");
    label7.set_label("Non");
    label8.set_label(" ");
    label9.set_label("Oui");

    label1.set_name("razlabel1");
    label7.set_name("razlabel7");
    label8.set_name("razlabel8");
    label9.set_name("razlabel9");
    
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);

    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);

    grid.attach(label1, 0, 0, 3, 5);
    grid.attach(label7, 0, 5, 1, 1);
    grid.attach(label8, 1, 5, 1, 1);
    grid.attach(label9, 2, 5, 1, 1);

    MainWindow->add(grid); 
    MainWindow->show_all(); 

}*/

void ViewMotion::showAskChangeChannel(){

    MainWindow->remove();        
    resetGrid();
    label1.set_label("Nouvelle partie !");
    label7.set_label("");
    label8.set_label("Suivant");
    label9.set_label("");

    label1.set_name("razlabel1");
    label7.set_name("razlabel7");
    label8.set_name("razlabel8");
    label9.set_name("razlabel9");
    
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);

    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);

    grid.attach(label1, 0, 0, 3, 5);
    grid.attach(label7, 0, 5, 1, 1);
    grid.attach(label8, 1, 5, 1, 1);
    grid.attach(label9, 2, 5, 1, 1);

    MainWindow->add(grid); 
    MainWindow->show_all(); 

}

void ViewMotion::resetGrid(){
    for(int i=0;i<10;i++){
        grid.remove_column(0);
        grid.remove_row(0);
    }
}

void ViewMotion::setLabelExpandable(){
    label1.set_vexpand(true);
    label2.set_vexpand(true);
    label3.set_vexpand(true);
    label4.set_vexpand(true);
    label5.set_vexpand(true);
    label6.set_vexpand(true);
    label7.set_vexpand(true);
    label8.set_vexpand(true);
    label9.set_vexpand(true);

    label1.set_hexpand(true);
    label2.set_hexpand(true);
    label3.set_hexpand(true);
    label4.set_hexpand(true);
    label5.set_hexpand(true);
    label6.set_hexpand(true);
    label7.set_hexpand(true);
    label8.set_hexpand(true);
    label9.set_hexpand(true);
}

void ViewMotion::showSaveChoose(){

    MainWindow->remove();        
    resetGrid();
    label1.set_label("Une partie a été trouvée..\nVoulez-vous la charger ?");
    label7.set_label("Non");
    label8.set_label("");
    label9.set_label("Oui");

    label1.set_name("razlabel1");
    label7.set_name("razlabel7");
    label8.set_name("razlabel8");
    label9.set_name("razlabel9");
    
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);

    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);

    grid.attach(label1, 0, 0, 3, 5);
    grid.attach(label7, 0, 5, 1, 1);
    grid.attach(label8, 1, 5, 1, 1);
    grid.attach(label9, 2, 5, 1, 1);

    MainWindow->add(grid); 
    MainWindow->show_all(); 

}

void ViewMotion::showPwdChoose(){

    MainWindow->remove();        
    resetGrid();
    label1.set_label("Mot de passe ?");
    label7.set_label("Annuler");
    label8.set_label("");
    label9.set_label("Valider");

    label1.set_name("razlabel1");
    label7.set_name("razlabel7");
    label8.set_name("razlabel8");
    label9.set_name("razlabel9");
    
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);

    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);

    grid.attach(label1, 0, 0, 3, 5);
    grid.attach(label7, 0, 5, 1, 1);
    grid.attach(label8, 1, 5, 1, 1);
    grid.attach(label9, 2, 5, 1, 1);

    MainWindow->add(grid); 
    MainWindow->show_all(); 

}

void ViewMotion::showPlatChoose(){

    MainWindow->remove();        
    resetGrid();
    label1.set_label(this->controller->getPlatSent());
    label7.set_label("Réinitialiser");
    label8.set_label("");
    label9.set_label("Continuer");

    label1.set_name("razlabel1");
    label7.set_name("razlabel7");
    label8.set_name("razlabel8");
    label9.set_name("razlabel9");
    
    grid.insert_column(0);
    grid.insert_column(0);
    grid.insert_column(0);

    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);
    grid.insert_row(0);

    grid.attach(label1, 0, 0, 3, 5);
    grid.attach(label7, 0, 5, 1, 1);
    grid.attach(label8, 1, 5, 1, 1);
    grid.attach(label9, 2, 5, 1, 1);

    MainWindow->add(grid); 
    MainWindow->show_all(); 

}