#include "Database.h"
#include <sstream>

using namespace std;

Database::Database(string url)
{
  this->urlApi = url;
  this->curl = curl_easy_init();
}

Database::~Database(){
}

Database::Database(){
}

UserInfo* Database::findUserById(string id){
    string chaine = this->urlApi+"user/"+id;
    char * urlConcat = &chaine[0u];
    Json::Value res = getJsonFromApi(urlConcat);
    if(res == "[]"){
      return NULL;
    }
    else{
      User * user = new User(res);
      UserCredit * userCredit = new UserCredit(res);
      UserAuthentification * userAuth = new UserAuthentification(res);
      UserInfo * ret = new UserInfo(*user, *userAuth, *userCredit);
      return ret;
    }    
  return NULL;
}

vector<Channel*> Database::getChannels(){
  vector<Channel*> list;
  string chaine = this->urlApi+"channels/";
  char * urlConcat = &chaine[0u];
  Json::Value res = getJsonFromApi(urlConcat);
  if(res == "[]"){
    cout << "Impossible de récupérer les canaux" << endl;
  }
  else{
    for (Json::Value::iterator it = res.begin(); it != res.end(); ++it) {
      string idS = (*it)["channelId"].asString();
      int id = atoi(idS.c_str());
      string number = (*it)["channelNumber"].asString();
      string name = (*it)["channelName"].asString();
      string nbPlatS = (*it)["channelNbPlat"].asString();
      int nbPlat = atoi(nbPlatS.c_str());

      Channel * c = new Channel(id, number, name, nbPlat);
      list.push_back(c);
    }
  }
  return list;
}

bool Database::checkChannel(int id){
  stringstream strs;
  strs << id;
  string temp_str = strs.str();
  char const* pchar = temp_str.c_str(); 
  string chaine = this->urlApi+"channel/"+pchar;
  char * urlConcat = &chaine[0u];
  Json::Value res = getJsonFromApi(urlConcat);
  if(res != "[]"){
    return true;
  }
  else{
    return false;
  }
  return false;
}

Channel* Database::findChannelById(int id){
  stringstream strs;
  strs << id;
  string temp_str = strs.str();
  char const* pchar = temp_str.c_str(); 
  string chaine = this->urlApi+"channel/"+pchar;
  char * urlConcat = &chaine[0u];
  Json::Value res = getJsonFromApi(urlConcat);
  if(res != "[]"){
    Channel * chan = new Channel(res);
    return chan;
  }
  else{
    return NULL;
  }
  return NULL;
}

vector<UserInfo*> Database::checkCredit(vector<UserInfo*>* list, int cate){
  string type;
  map<int, int> mapId;
  int n = cate;
  n = 1;    //Forcer parcours
  switch(n){
    case 0 : type = "creditCompak";break;
    case 1 : type = "creditParcours";break;
    case 2 : type = "creditFosse";break;
    default : type = "creditParcours";break;
  }
  vector<UserInfo*> noCredit;
  for(unsigned int i = 0; i < list->size(); i++){
    int id= list->at(i)->getUser()->getUserId();

    if(mapId[id]){
      mapId[id]++;
    }
    else{
      mapId[id] = 1;
    }
  }

	std::map<int, int>::iterator it = mapId.begin();
 
	// Iterate over the map using Iterator till end.
	while (it != mapId.end())
	{
		// Accessing KEY from element pointed by it.
		int id = it->first;
    stringstream strs;
    strs << id;
    string temp_str = strs.str();
    char const* pchar = temp_str.c_str();
		// Accessing VALUE from element pointed by it.
		int count = it->second-1;
    stringstream strs2;
    strs2 << count;
    string temp_str2 = strs2.str();
    char const* pchar2 = temp_str2.c_str();
    string chaine = this->urlApi+"user/"+pchar+"/checkCredit/"+type+"/"+pchar2;
    char * urlConcat = &chaine[0u];
    Json::Value res = getJsonFromApi(urlConcat);
    if(res.size() < 1){
      UserInfo* user = this->findUserById(pchar);
      noCredit.push_back(user);
    }
    it++;
  }
    return noCredit;
}


int Database::howManyCredit(int id, int cate){
  string type;
  int cat = cate;
  cat = 1;    //forcer parcours
  switch(cat){
    case 0 : type = "creditCompak";break;
    case 1 : type = "creditParcours";break;
    case 2 : type = "creditFosse";break;
    default : type = "creditParcours";break;
  }
  stringstream strs;
  strs << id;
  string temp_str = strs.str();
  char const* pchar = temp_str.c_str();

  string chaine = this->urlApi+"user/"+pchar+"/howMany/"+type;
  char * urlConcat = &chaine[0u];
  Json::Value res = getJsonFromApi(urlConcat);
  if(res != "[]"){
    int nbcred = getJsonValueInt(res, type);
    return nbcred; 
  }
  else
    return -1;
  return -1;
}

bool Database::isConnectedToNetwork(){
  CURL *curl;
  CURLcode res;
 
  curl = curl_easy_init();
  if(curl) {
    char * urlConcat = &this->urlApi[0u];
    curl_easy_setopt(curl, CURLOPT_URL, urlConcat);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3L);
    if ((res = curl_easy_perform(curl)) != CURLE_OK){
      const char *str = curl_easy_strerror( res );
      cout << "code : " << str << endl;
      cout << "res : " << res << endl;
      curl_easy_cleanup(curl);
      return false;
    }
    else{
      curl_easy_cleanup(curl);
      return true;
    }    
  }
  else{
    return false;
  }
}

void Database::decrCredits(vector<UserInfo*> *listeTireurs, int cate){
  unsigned int i = 0;
  string typeCredit;
  int type = cate;
  type = 1;      //forcer parcours
  switch (type){
    case 0 : typeCredit = "creditCompak"; break;
    case 1 : typeCredit = "creditParcours"; break;
    case 2 : typeCredit = "creditFosse"; break;
    default : typeCredit = "creditParcours"; break;
  }
  for(i = 0; i < listeTireurs->size(); i++){
    int id = listeTireurs->at(i)->getUser()->getUserId();
    stringstream strs;
    strs << id;
    string temp_str = strs.str();
    char const* pchar = temp_str.c_str();

    string chaine = this->urlApi+"user/"+pchar+"/decrCredit/"+typeCredit;
    char * urlConcat = &chaine[0u];
    Json::Value res = getJsonFromApi(urlConcat);
  }
}

size_t Database::write_to_string(void *ptr, size_t size, size_t count, void *stream) {
  ((string*)stream)->append((char*)ptr, 0, size*count);
  return size*count;
}

Json::Value Database::getJsonFromApi(const char* url){
  this->curl = curl_easy_init();
  Json::Value root;   
  if(this->curl) {
    curl_easy_setopt(this->curl, CURLOPT_URL, url);

    string response;
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, write_to_string);
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &response);

    /* Perform the request, res will get the return code */
    this->resCurl = curl_easy_perform(this->curl);
    /* Check for errors */
    if(this->resCurl != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(this->resCurl));

    Json::Reader reader;
    bool parsingSuccessful = reader.parse( response.c_str(), root );     //parse process
    if ( !parsingSuccessful )
    {
        cout  << "Failed to parse" << reader.getFormattedErrorMessages();
        return 0;
    }
    curl_easy_cleanup(this->curl);
  }
  return root;
}

int Database::getJsonValueInt(Json::Value json, string key) const{
    Json::Value value = json[0][key];
    Json::FastWriter fastwriter;
    string valueS = fastwriter.write(value);
    valueS = valueS.substr(1, valueS.size() - 3);
    int valueI = atoi(valueS.c_str());
    return valueI;
}

string Database::getJsonValueString(Json::Value json, string key) const{
    Json::Value value = json[0][key];
    Json::FastWriter fastwriter;
    string valueS = fastwriter.write(value);
    valueS = valueS.substr(1, valueS.size() - 3);
    return valueS;
}

vector<Parameter*> Database::getParameters(){
    string chaine = this->urlApi+"parameters/";
    char * urlConcat = &chaine[0u];
    Json::Value res = getJsonFromApi(urlConcat);
    vector<Parameter*> listParam;

    for (Json::Value::iterator it = res.begin(); it != res.end(); ++it) {
      string idS = (*it)["parameterId"].asString();
      int id = atoi(idS.c_str());
      string value = (*it)["parameterValue"].asString();
      string code = (*it)["parameterCode"].asString();
      string name = (*it)["parameterName"].asString();

      Parameter * p = new Parameter(id, code, value, name);
      listParam.push_back(p);
    }
    return listParam;
}