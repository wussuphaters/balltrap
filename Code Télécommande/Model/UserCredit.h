#ifndef DEF_USERCREDIT
#define DEF_USERCREDIT

#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>
#include <stdlib.h>
#include <string>
#include <stdio.h>

class UserCredit
{
    friend std::ostream & operator<<(std::ostream &os, const UserCredit &u);
    friend class boost::serialization::access;
    template<class Archive>
    //Fonction qui va permettre la sérialization de l'objet et la sauvegarde
    //de celui-ci dans un fichier externe
    void serialize(Archive & ar, const unsigned int version){
        ar & userId & creditCompak & creditParcours & creditFosse;
    }
private:

public:

    int userId, creditCompak, creditParcours, creditFosse;

    //constructeurs
    UserCredit(int userId, int creditCompak, int creditParcours, int creditFosse);
    UserCredit(UserCredit &userCredit);
    UserCredit(Json::Value res);    
    UserCredit();

    //setters
    void setCreditFosse(int number);
    void setCreditParcours(int number);
    void setCreditCompak(int number);
    void setUserId(int number);

    //getters
    int getCreditFosse() const;
    int getCreditParcours() const;
    int getCreditCompak() const;
    int getUserId() const;
    int getJsonValueInt(Json::Value json, std::string key) const;
    std::string getJsonValueString(Json::Value json, std::string key) const;
};

//toString
std::ostream& operator<<( std::ostream& s, const UserCredit& c);

#endif