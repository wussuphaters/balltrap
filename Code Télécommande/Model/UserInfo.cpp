#include "UserInfo.h"

using namespace std;


UserInfo::UserInfo(User &user, UserAuthentification &userAuthentification, UserCredit &userCredit){
    this->user= new User(user);
    this->userAuthentification= new UserAuthentification(userAuthentification);
    this->userCredit= new UserCredit(userCredit);
    this->nbPlateau = 0;
    this->score = 0;
}

UserInfo::UserInfo(UserInfo &userInfo){
    this->user=userInfo.user;
    this->userAuthentification=userInfo.userAuthentification;
    this->userCredit=userInfo.userCredit;
    this->nbPlateau = userInfo.nbPlateau;
    this->score = userInfo.score;    
}

UserInfo::UserInfo(){
        
}

ostream& operator<<( std::ostream& s, const UserInfo& c){
    s << *c.getUser() << " " << *c.getUserAuthentification() << " "<< *c.getUserCredit();
    s << "---score---" << c.getScore();
    return s;
}

void UserInfo::decrScore(){
    this->score--;
}

void UserInfo::incrScore(){
    this->score++;
}

void UserInfo::decrPlateau(int nb){
    this->nbPlateau-=nb;
}
    

void UserInfo::setUser(User &user){
    this->user= new User(user); 
}
    
void UserInfo::setUserAuthentification(UserAuthentification &userAuth){
    this->userAuthentification= new UserAuthentification(userAuth);
}
    
void UserInfo::setUserCredit(UserCredit &userCredit){
    this->userCredit= new UserCredit(userCredit);
}

void UserInfo::setScore(int score){
    this->score=score;
}

void UserInfo::setNbPlateau(int nbPlateau){
    this->nbPlateau=nbPlateau;
}

int UserInfo::getScore() const{
    return this->score;
}

int UserInfo::getNbPlateau() const{
    return this->nbPlateau;
}
    
User* UserInfo::getUser() const{
   return this->user;
}
    
UserAuthentification* UserInfo::getUserAuthentification() const{
    return this->userAuthentification;
}
    
UserCredit* UserInfo::getUserCredit() const{
    return this->userCredit;
}
    