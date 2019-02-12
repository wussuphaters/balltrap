#ifndef DEF_USERINFO
#define DEF_USERINFO

#include <iostream>
#include <string>
#include "User.h"
#include "UserAuthentification.h"
#include "UserCredit.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class UserInfo
{
    friend class boost::serialization::access;
    template<class Archive>
    //Fonction qui va permettre la sérialization de l'objet et la sauvegarde
    //de celui-ci dans un fichier externe
    void serialize(Archive & ar, const unsigned int version){
        ar & user;
        ar & userAuthentification;
        ar & userCredit;
        ar & score;
        ar & nbPlateau;
    }
    private:

    public:

        User * user;
        UserAuthentification * userAuthentification;
        UserCredit * userCredit;
        int score, nbPlateau;

        //constructeurs
        UserInfo(User &user, UserAuthentification &userAuthentification, UserCredit &userCredit);
        UserInfo(UserInfo &userInfo);
        UserInfo();

        //setters
        void setUser(User &user);
        void setUserAuthentification(UserAuthentification &userAuth);
        void setUserCredit(UserCredit &userCredit);
        void setScore(int score);
        void setNbPlateau(int nbPlateau);
        void decrPlateau(int nbPlateau);
        void decrScore();
        void incrScore();

        //getters
        User* getUser() const;
        UserAuthentification* getUserAuthentification() const;
        UserCredit* getUserCredit() const;
        int getScore() const;
        int getNbPlateau() const;
};

//toString
std::ostream& operator<<( std::ostream& s, const UserInfo& c);
#endif