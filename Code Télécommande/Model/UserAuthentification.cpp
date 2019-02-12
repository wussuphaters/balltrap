#include "UserAuthentification.h"

using namespace std;

UserAuthentification::UserAuthentification(int userId, string userLogin, string userPassword, string userType, string userSecurityCode){
    this->userId=userId;
    this->userLogin=userLogin;
    this->userPassword=userPassword;
    this->userType=userType;
    this->userSecurityCode=userSecurityCode;
}

UserAuthentification::UserAuthentification(UserAuthentification &userAuth){
    this->userId=userAuth.userId;
    this->userLogin=userAuth.userLogin;
    this->userPassword=userAuth.userPassword;
    this->userType=userAuth.userType;
    this->userSecurityCode=userAuth.userSecurityCode;
}

UserAuthentification::UserAuthentification(Json::Value res){
    this->userId=getJsonValueInt(res, "userId");
    this->userLogin=getJsonValueString(res, "userLogin");
    this->userPassword=getJsonValueString(res, "userPassword");
    this->userType=getJsonValueString(res, "userType");
    this->userSecurityCode=getJsonValueString(res, "userSecurityCode");
}

UserAuthentification::UserAuthentification(){

}

ostream& operator<<( std::ostream& s, const UserAuthentification& c){
    s << "----------UserAuthentification----------" << endl <<
    "userId : " << c.getUserId()  << endl <<
    "userLogin : " << c.getUserLogin() << endl <<
    "userPassword : " << c.getUserPassword() << endl <<
    "userType : " << c.getUserType() << endl <<
    "userSecurityCode : " << c.getUserSecurityCode() << endl <<
    endl << endl;

    return s;
}

void UserAuthentification::setUserLogin(string str){
    this->userLogin=str;
}

void UserAuthentification::setUserPassword(string str){
    this->userPassword=str;    
}

void UserAuthentification::setUserType(string str){
    this->userType=str;    
}

void UserAuthentification::setUserSecurityCode(string str){
    this->userSecurityCode=str;    
}

void UserAuthentification::setUserId(int number){
    this->userId=number;    
}

string UserAuthentification::getUserLogin() const{
    return this->userLogin;
}

string UserAuthentification::getUserPassword() const{
    return this->userPassword;    
}

string UserAuthentification::getUserType() const{
    return this->userType;  
}

string UserAuthentification::getUserSecurityCode() const{
    return this->userSecurityCode;  
}

int UserAuthentification::getUserId() const{
    return this->userId;  
}

int UserAuthentification::getJsonValueInt(Json::Value json, string key) const{
  Json::Value value = json[0][key];
  Json::FastWriter fastwriter;
  string valueS = fastwriter.write(value);
  valueS = valueS.substr(1, valueS.size() - 3);
  int valueI = atoi(valueS.c_str());
  return valueI;
}

string UserAuthentification::getJsonValueString(Json::Value json, string key) const{
  Json::Value value = json[0][key];
  Json::FastWriter fastwriter;
  string valueS = fastwriter.write(value);
  valueS = valueS.substr(1, valueS.size() - 3);
  return valueS;
}

