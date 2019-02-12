#ifndef DEF_DATABASE
#define DEF_DATABASE

#include <stdlib.h>
#include <iostream>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/

#include "User.h"
#include "UserInfo.h"
#include "UserAuthentification.h"
#include "UserInfo.h"
#include "Channel.h"
#include "Parameter.h"
#include <vector>
#include <stdio.h>
#include <sstream>
#include <map>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>
#include <curl/curl.h>
#include <string>
#include <stdlib.h>

class Database
{

private:

public:

//Curl est une librarie permettant de faire un lien entre l'application et l'API

    //permet de démarrer une connexion avec l'API
    CURL *curl;

    //permet de stocker le résultat d'une requête sur l'API
    CURLcode resCurl;
    std::string urlApi;

    //constructeurs/destructeur
    Database(std::string);
    ~Database();
    Database();

    //Les fonctions suivantes correspondent aux différentes requêtes vers l'API

    //retourne un tireur en fonction d'un id donné
    UserInfo* findUserById(std::string id);

    //retourne la liste des canaux du club
    std::vector<Channel*> getChannels();

    //retourne un canal en fonction d'un id donné
    Channel* findChannelById(int); 

    /* vérifie avant le lancement de la partie, que les tireurs de la liste
     * possédent suffisamment de crédits
     */ 
    std::vector<UserInfo*> checkCredit(std::vector<UserInfo*>*, int);

    //retourne la liste des paramètres de jeu du club
    std::vector<Parameter*> getParameters();

    //retire les crédits à chaque utilisateur de la liste
    void decrCredits(std::vector<UserInfo*> *listeTireurs, int type);

    //retourne le nombre de crédit d'un tireur pour une catégorie donnée (parcours/compak/fosse)
    int howManyCredit(int, int);

    //vérifie si le canal renseigné existe
    bool checkChannel(int);

    //écris dans une chaîne de caractères, le retour de la requête sur l'API
    static size_t write_to_string(void *ptr, size_t size, size_t count, void *stream);

    //parse la chaîne de caractères retournée par une requête sur l'API en un object json
    Json::Value getJsonFromApi(const char*);

    //vérifie que l'application peut accéder à l'API
    bool isConnectedToNetwork();

    //convertit en entier la valeur d'un clé d'un objet json
    int getJsonValueInt(Json::Value json, std::string key) const;

    //convertit en chaîne de caractères la valeur d'un clé d'un objet json
    std::string getJsonValueString(Json::Value json, std::string key) const;
};

#endif