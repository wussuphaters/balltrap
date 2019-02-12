#ifndef DEF_CHANNEL
#define DEF_CHANNEL

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

class Channel
{
    friend std::ostream & operator<<(std::ostream &os, const Channel &ch);
    friend class boost::serialization::access;
    template<class Archive>

    //Fonction qui va permettre la sérialization de l'objet et la sauvegarde
    //de celui-ci dans un fichier externe
    void serialize(Archive & ar, const unsigned int version){
        ar & channelId & channelName & channelNbPlat & channelNumber;
    }
private:

public:

    int channelId, channelNbPlat;
    std::string channelNumber, channelName;

    //Différents constructeurs
    Channel(int channelId, std::string channelNumber, std::string channelName, int channelNbPlat);
    Channel(Channel &channel);
    Channel(Json::Value res);
    Channel();

    //Les setters
    void setChannelNumber(std::string str);
    void setChannelName(std::string str);
    void setChannelId(int number);
    void setChannelNbPlat(int);

    //Les getters
    std::string getChannelNumber() const;
    std::string getChannelName() const;
    int getChannelId() const;
    int getChannelNbPlat() const;

    //Fonctions qui permettent de convertir la valeur d'une clé d'un objet JSON
    //en int ou en string
    int getJsonValueInt(Json::Value json, std::string key) const;
    std::string getJsonValueString(Json::Value json, std::string key) const;
};

//toString
std::ostream& operator<<( std::ostream& s, const Channel& c);
#endif