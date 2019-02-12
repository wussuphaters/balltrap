#include "UserCredit.h"

using namespace std;

UserCredit::UserCredit(int userId, int creditCompak, int creditParcours, int creditFosse){
    this->userId=userId;
    this->creditCompak=creditCompak;
    this->creditParcours=creditParcours;
    this->creditFosse=creditFosse;
}

UserCredit::UserCredit(UserCredit &userCredit){
    this->userId=userCredit.userId;
    this->creditCompak=userCredit.creditCompak;
    this->creditParcours=userCredit.creditParcours;
    this->creditFosse=userCredit.creditFosse;
}

UserCredit::UserCredit(Json::Value res){
    this->userId=getJsonValueInt(res, "userId");
    this->creditCompak=getJsonValueInt(res, "creditCompak");
    this->creditParcours=getJsonValueInt(res, "creditParcours");
    this->creditFosse=getJsonValueInt(res, "creditFosse");
}

UserCredit::UserCredit(){

}

ostream& operator<<( std::ostream& s, const UserCredit& c){
    
    s << "----------UserCredit----------" << endl <<
    "userId : " << c.getUserId()  << endl <<
    "creditCompak : " << c.getCreditCompak() << endl <<
    "creditParcours : " << c.getCreditParcours() << endl <<
    "creditFosse : " << c.getCreditFosse() << endl <<
    endl << endl;


    return s;
}

void UserCredit::setCreditFosse(int number){
    this->creditFosse=number;    
}

void UserCredit::setCreditParcours(int number){
    this->creditParcours=number;    
}

void UserCredit::setCreditCompak(int number){
    this->creditCompak=number;    
}

void UserCredit::setUserId(int number){
    this->userId=number;        
}

int UserCredit::getCreditFosse() const{
    return this->creditFosse;
}

int UserCredit::getCreditParcours() const{
    return this->creditParcours;
}

int UserCredit::getCreditCompak() const{
    return this->creditCompak;
}

int UserCredit::getUserId() const{
    return this->userId;    
}

int UserCredit::getJsonValueInt(Json::Value json, string key) const{
  Json::Value value = json[0][key];
  Json::FastWriter fastwriter;
  string valueS = fastwriter.write(value);
  valueS = valueS.substr(1, valueS.size() - 3);
  int valueI = atoi(valueS.c_str());
  return valueI;
}

string UserCredit::getJsonValueString(Json::Value json, string key) const{
  Json::Value value = json[0][key];
  Json::FastWriter fastwriter;
  string valueS = fastwriter.write(value);
  valueS = valueS.substr(1, valueS.size() - 3);
  return valueS;
}
