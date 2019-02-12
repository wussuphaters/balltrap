#ifndef DEF_USERAUTH
#define DEF_USERAUTH

#include <iostream>
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>
#include <stdlib.h>
#include <stdio.h>

class UserAuthentification
{
    friend std::ostream & operator<<(std::ostream &os, const UserAuthentification &u);
    friend class boost::serialization::access;
    template<class Archive>
    //Fonction qui va permettre la sérialization de l'objet et la sauvegarde
    //de celui-ci dans un fichier externe
    void serialize(Archive & ar, const unsigned int version){
        ar & userId & userLogin & userPassword & userType & userSecurityCode;
    }
private:

public:

    int userId;
    std::string userLogin, userPassword, userType, userSecurityCode;
    
    //constructeurs
    UserAuthentification(int userId, std::string userLogin, std::string userPassword, std::string userType, std::string userSecurityCode);
    UserAuthentification(UserAuthentification &userAuth);
    UserAuthentification(Json::Value res);
    UserAuthentification();

    //setters
    void setUserLogin(std::string str);
    void setUserPassword(std::string str);
    void setUserType(std::string str);
    void setUserSecurityCode(std::string str);
    void setUserId(int number);

    //getters
    std::string getUserLogin() const;
    std::string getUserPassword() const;
    std::string getUserType() const;
    std::string getUserSecurityCode() const;
    int getUserId() const;

    //Fonctions qui permettent de convertir la valeur d'une clé d'un objet JSON
    //en int ou en string
    int getJsonValueInt(Json::Value json, std::string key) const;
    std::string getJsonValueString(Json::Value json, std::string key) const;
};

//toString
std::ostream& operator<<( std::ostream& s, const UserAuthentification& c);
#endif