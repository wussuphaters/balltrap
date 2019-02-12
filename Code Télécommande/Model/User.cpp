#include "User.h"

using namespace std;

/**
*   Constructeurs
*/
User::User(int userId,string userFirstName, string userLastName, string userMail, string userAddress, string userAddressSupplement,
string userZipCode, string userCity, string userBirthdate, string userLicenceNumber, string userFixPhone, string userMobilePhone,
string userCommentary, int userLicenceYear, int categoryId, int userGenre)
{
    this->userId=userId;
    this->userFirstName=userFirstName;
    this->userLastName=userLastName;
    this->userMail=userMail;
    this->userAddress=userAddress;
    this->userAddressSupplement=userAddressSupplement;
    this->userZipCode=userZipCode;
    this->userCity=userCity;
    this->userBirthdate=userBirthdate;
    this->userLicenceNumber=userLicenceNumber;
    this->userFixPhone=userFixPhone;
    this->userMobilePhone=userMobilePhone;
    this->userCommentary=userCommentary;
    this->userLicenceYear=userLicenceYear;
    this->categoryId=categoryId;
    this->userGenre=userGenre;
}

User::User(User &user)
{
    this->userId=user.userId;
    this->userFirstName=user.userFirstName;
    this->userLastName=user.userLastName;
    this->userMail=user.userMail;
    this->userAddress=user.userAddress;
    this->userAddressSupplement=user.userAddressSupplement;
    this->userZipCode=user.userZipCode;
    this->userCity=user.userCity;
    this->userBirthdate=user.userBirthdate;
    this->userLicenceNumber=user.userLicenceNumber;
    this->userFixPhone=user.userFixPhone;
    this->userMobilePhone=user.userMobilePhone;
    this->userCommentary=user.userCommentary;
    this->userLicenceYear=user.userLicenceYear;
    this->categoryId=user.categoryId;
    this->userGenre=user.userGenre;
}

User::User(Json::Value res){
    this->userId=getJsonValueInt(res, "userId");
    this->userFirstName=getJsonValueString(res, "userFirstName");
    this->userLastName=getJsonValueString(res, "userLastName");
    this->userMail=getJsonValueString(res, "userMail");
    this->userAddress=getJsonValueString(res, "userAddress");
    this->userAddressSupplement=getJsonValueString(res, "userAddressSupplement");
    this->userZipCode=getJsonValueString(res, "userZipCode");
    this->userCity=getJsonValueString(res, "userCity");
    this->userBirthdate=getJsonValueString(res, "userBirthdate");
    this->userLicenceNumber=getJsonValueString(res, "userLicenceNumber");
    this->userFixPhone=getJsonValueString(res, "userFixPhone");
    this->userMobilePhone=getJsonValueString(res, "userMobilePhone");
    this->userCommentary=getJsonValueString(res, "userCommentary");
    this->userLicenceYear=getJsonValueInt(res, "userLicenceYear");
    this->categoryId=getJsonValueInt(res, "categoryId");
    this->userGenre=getJsonValueInt(res, "userGenre");
}

User::User(){

}



/**
*   Setters
*/
void User::setUserFirstName(string str){
    this->userFirstName = str;
}

void User::setUserLastName(string str){
    this->userLastName = str;
}

void User::setUserMail(string str){
    this->userMail = str;    
}

void User::setUserAddress(string str){
    this->userAddress = str;    
}

void User::setUseAddressSupplement(string str){
    this->userAddressSupplement = str;
}

void User::setUserZipCode(string str){
    this->userZipCode = str;
}

void User::setUserCity(string str){
    this->userCity = str;
}

void User::setUserBirthdate(string str){
    this->userBirthdate = str;
}

void User::setUserLicenceNumber(string str){
    this->userLicenceNumber = str;
}

void User::setUserFixPhone(string str){
    this->userFixPhone = str;
}

void User::setUserMobilePhone(string str){
    this->userMobilePhone = str;
}

void User::setUserCommentary(string str){
    this->userCommentary = str;
}

void User::setUserId(int number){
    this->userId = number;
}

void User::setUserLicenceYear(int number){
    this->userLicenceYear = number;
}

void User::setCategoryId(int number){
    this->categoryId = number;
}

void User::setUserGenre(int number){
    this->userGenre = number;
}

/**
*   Getters
*/
string User::getUserFirstName() const{
    return this->userFirstName;
}

string User::getUserLastName() const{
    return this->userLastName;    
}

string User::getUserMail() const{
    return this->userMail;  
}

string User::getUserAddress() const{
    return this->userAddress;  
}

string User::getUserAddressSupplement() const{
    return this->userAddressSupplement;  
}

string User::getUserZipCode() const{
    return this->userZipCode;  
}

string User::getUserCity() const{
    return this->userCity;  
}

string User::getUserBirthdate() const{
    return this->userBirthdate;  
}

string User::getUserLicenceNumber() const{
    return this->userLicenceNumber;  
}

string User::getUserFixPhone() const{
    return this->userFixPhone;  
}

string User::getUserMobilePhone() const{
    return this->userMobilePhone;  
}

string User::getUserCommentary() const{
    return this->userCommentary;  
}

int User::getUserId() const{
    return this->userId;  
}

int User::getUserLicenceYear() const{
    return this->userLicenceYear;  
}

int User::getCategoryId() const{
    return this->categoryId;  
}

int User::getUserGenre() const{
    return this->userGenre;  
}

int User::getJsonValueInt(Json::Value json, string key) const{
  Json::Value value = json[0][key];
  Json::FastWriter fastwriter;
  string valueS = fastwriter.write(value);
  valueS = valueS.substr(1, valueS.size() - 3);
  int valueI = atoi(valueS.c_str());
  return valueI;
}

string User::getJsonValueString(Json::Value json, string key) const{
  Json::Value value = json[0][key];
  Json::FastWriter fastwriter;
  string valueS = fastwriter.write(value);
  valueS = valueS.substr(1, valueS.size() - 3);
  return valueS;
}

ostream& operator<<( std::ostream& s, const User& c){
    s << "----------User----------" << endl <<
    "userId : " << c.getUserId()  << endl <<
    "userFirstName : " << c.getUserFirstName() << endl <<
    "userLastName : " << c.getUserLastName() << endl <<
    "userMail : " << c.getUserMail() << endl <<
    "userAddress : " << c.getUserAddress() << endl <<
    "userAddressSupplement : " << c.getUserAddressSupplement() << endl <<
    "userZipCode : " << c.getUserZipCode() << endl <<
    "userCity : " << c.getUserCity() << endl <<
    "userBirthdate : " << c.getUserBirthdate() << endl <<
    "userLicenceNumber : " << c.getUserLicenceNumber() << endl <<
    "userFixPhone : " << c.getUserFixPhone() << endl <<
    "userMobilePhone : " << c.getUserMobilePhone() << endl <<
    "userCommentary : " << c.getUserCommentary() << endl <<
    "userLicenceYear : " << c.getUserLicenceYear() << endl <<
    "categoryId : " << c.getCategoryId() << endl <<
    "userGenre : " << c.getUserGenre() << endl <<
    endl << endl;

    return s;
}
