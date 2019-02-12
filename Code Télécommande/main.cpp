#include <iostream>
#include <string>
#include <stdlib.h>
#include <gtkmm-3.0/gtkmm.h>
#include "Model/User.h"
#include "Model/UserAuthentification.h"
#include "Model/UserCredit.h"
#include "Model/Channel.h"
#include "Model/Parameter.h"
#include "Model/Database.h"
#include "View/View.h"
#include "View/ViewConsole.h"
#include "Controller/Controller.h"
#include "Controller/ControllerConsole.h"
#include "Controller/ControllerMotion.h"
#include "View/ViewMotion.h"
#include "Model/UserInfo.h"
#include "Model/Game.h"

using namespace std;

int main(int argc,char **argv)
{
    
    Gtk::Main m(argc, argv);
    ViewMotion * window = new ViewMotion();
    m.run(*window);
    return EXIT_SUCCESS;
    
/*
    Database* database = new Database("http://localhost/balltrap/SiteWeb/public/api/command/");
    ViewConsole *view = new ViewConsole();
    Controller* controller = new ControllerConsole(*database, *view);
    controller->run();
    delete database;
*/
}
