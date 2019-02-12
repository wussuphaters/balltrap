#ifndef DEF_PARAMETER
#define DEF_PARAMETER

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

class Parameter
{
    friend std::ostream & operator<<(std::ostream &os, const Parameter &p);
    friend class boost::serialization::access;
    template<class Archive>
    //Fonction qui va permettre la sérialization de l'objet et la sauvegarde
    //de celui-ci dans un fichier externe
    void serialize(Archive & ar, const unsigned int version){
        ar & parameterId & parameterCode & parameterValue & parameterName;
    }
private:

public:

    int parameterId;
    std::string parameterCode, parameterValue, parameterName;
    
    //constructeurs
    Parameter(int parameterId, std::string parameterCode, std::string parameterValue, std::string parameterName);
    Parameter(Parameter &param);
    Parameter(Json::Value res);
    Parameter();

    //setters
    void setParameterCode(std::string str);
    void setParameterValue(std::string str);
    void setParameterName(std::string str);
    void setParameterId(int number);

    //getters
    std::string getParameterCode() const;
    std::string getParameterValue() const;
    std::string getParameterName() const;
    int getParameterId() const;

    //Fonctions qui permettent de convertir la valeur d'une clé d'un objet JSON
    //en int ou en string
    int getJsonValueInt(Json::Value json, std::string key) const;
    std::string getJsonValueString(Json::Value json, std::string key) const;
};

//ToString
std::ostream& operator<<( std::ostream& s, const Parameter& c);
#endif