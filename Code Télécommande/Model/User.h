#ifndef DEF_USER
#define DEF_USER

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>

class User
{
    friend std::ostream & operator<<(std::ostream &os, const User &u);
    friend class boost::serialization::access;
    template<class Archive>
    //Fonction qui va permettre la sérialization de l'objet et la sauvegarde
    //de celui-ci dans un fichier externe
    void serialize(Archive & ar, const unsigned int version){
        ar & userId & userLicenceYear & categoryId & userGenre
        & userFirstName & userLastName & userMail & userAddress
        & userAddressSupplement & userZipCode & userCity & userBirthdate
        & userLicenceNumber & userFixPhone & userMobilePhone & userCommentary;
    }
private:

public:
   
    int userId, userLicenceYear, categoryId, userGenre;
    std::string userFirstName, userLastName, userMail, userAddress, userAddressSupplement, userZipCode, userCity, userBirthdate, userLicenceNumber, userFixPhone, userMobilePhone, userCommentary;
    
    //constructeurs
    User(int userId,std::string userFirstName, std::string userLastName, std::string userMail, std::string userAddress, std::string userAddressSupplement, std::string userZipCode, std::string userCity, std::string userBirthdate, std::string userLicenceNumber, std::string userFixPhone, std::string userMobilePhone, std::string userCommentary, int userLicenceYear, int categoryId, int userGenre);
    User(User &user);
    User(Json::Value res);
    User();

    //setters
    void setUserFirstName(std::string str);
    void setUserLastName(std::string str);
    void setUserMail(std::string str);
    void setUserAddress(std::string str);
    void setUseAddressSupplement(std::string str);
    void setUserZipCode(std::string str);
    void setUserCity(std::string str);
    void setUserBirthdate(std::string str);
    void setUserLicenceNumber(std::string str);
    void setUserFixPhone(std::string str);
    void setUserMobilePhone(std::string str);
    void setUserCommentary(std::string str);
    void setUserId(int number);
    void setUserLicenceYear(int number);
    void setCategoryId(int number);
    void setUserGenre(int number);

    //getters
    std::string getUserFirstName() const;
    std::string getUserLastName() const;
    std::string getUserMail() const;
    std::string getUserAddress() const;
    std::string getUserAddressSupplement() const;
    std::string getUserZipCode() const;
    std::string getUserCity() const;
    std::string getUserBirthdate() const;
    std::string getUserLicenceNumber() const;
    std::string getUserFixPhone() const;
    std::string getUserMobilePhone() const;
    std::string getUserCommentary() const;
    int getUserId() const;
    int getUserLicenceYear() const;
    int getCategoryId() const;
    int getUserGenre() const;

    //Fonctions qui permettent de convertir la valeur d'une clé d'un objet JSON
    //en int ou en string
    int getJsonValueInt(Json::Value json, std::string key) const;
    std::string getJsonValueString(Json::Value json, std::string key) const;
};

//toString
std::ostream& operator<<( std::ostream& s, const User& c);
#endif