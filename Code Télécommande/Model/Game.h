#ifndef DEF_GAME
#define DEF_GAME

#include <iostream>
#include <string>
#include <vector>
#include "UserInfo.h"
#include "Channel.h"
#include "Parameter.h"
#include <fstream>
#include <boost/serialization/vector.hpp>

class Game
{
    friend class boost::serialization::access;
    template<class Archive>
    //Fonction qui va permettre la sérialization de l'objet et la sauvegarde
    //de celui-ci dans un fichier externe
    void serialize(Archive & ar, const unsigned int version)
        {
            ar & gameUsers;
            ar & gameChannel;
            ar & gameParameter;
            ar & gameCurrentUser;
            ar & gamePosCurrent;
            ar & gameAllPlat;
        }
    private:

    public:

        //liste des tireurs de la partie
        std::vector<UserInfo*> * gameUsers;

        //canal de la partie en cours
        Channel * gameChannel;

        //liste des paramètres de jeu du club
        std::vector<Parameter*> gameParameter;

        //joueur actuel
        UserInfo * gameCurrentUser;

        //position du joueur actuel dans la liste
        int gamePosCurrent;

        //nombre total de plateaux utilisables restants
        int gameAllPlat;

        //constructeurs
        Game(std::vector<UserInfo*> &users, Channel &channel, std::vector<Parameter*>);
        Game(Game &game);
        Game();

        //setters
        void setGameUsers(std::vector<UserInfo*> &users);
        void setGameChannel(Channel &channel);
        void setGameCurrentUser(UserInfo * currentUser);
        void setGamePosCurrent(int);
        void setGameAllPlat(int);
        void setGameParameters(std::vector<Parameter*> list);

        //getters
        std::vector<UserInfo*>* getGameUsers() const;
        Channel* getGameChannel() const;
        std::vector<Parameter*> getGameParameters() const;
        UserInfo* getGameCurrentUser() const;
        int getGamePosCurrent() const;
        int getGameAllPlat() const;

        //diminue le nombre de plateaux restants
        void decrPlat(int);

        void clearUserList();

        void clearParameterList();

        UserInfo* getNextUser() const;

        Parameter* getParameterFromCode(std::string) const;
};

//toString
std::ostream& operator<<( std::ostream& s, const Game& c);
#endif