#ifndef DEF_CONTROLLER
#define DEF_CONTROLLER

#include <iostream>
#include <string>
#include "../Model/Database.h"
#include "../View/View.h"

class Controller
{

private:
    Database * database;
    View * view;

public:
    virtual void run() = 0;
    virtual void makeUserList() = 0;    
};

#endif