#ifndef DEF_VIEW
#define DEF_VIEW

#include <iostream>
#include <string>
#include "../Model/Game.h"
#include "../Model/UserInfo.h"

class View
{

private:


public:
    
    virtual void showUsers(std::vector<UserInfo*> * gameUsers, bool showScore) const = 0;
    virtual void showInitInformations(int deductMode, int maxPlateau, Game * game) const = 0;
    virtual void showGameInformations(int deductMode, int maxPlateau, UserInfo * userInfo) const = 0;
    virtual void showShootOption() const = 0;
    virtual void showUserListOptions() const = 0;
    virtual void showConfigOptions() const = 0;
    virtual void showSaveListOptions() const = 0;
    virtual void showPlatSent(int) const = 0; 
    virtual void showNewGameStart() const = 0;
    virtual void showMessage(const char* msg) = 0;
};

#endif