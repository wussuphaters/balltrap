#include "Game.h"

using namespace std;

    Game::Game(std::vector<UserInfo*> &gameUsers, Channel &channel, vector<Parameter*> param){
        this->gameUsers=new vector<UserInfo*>(gameUsers);;
        this->gameChannel=new Channel(channel);
        this->gameParameter= param;
        this->gamePosCurrent=0;
        this->gameAllPlat = 0;
    }

    Game::Game(Game &game){
        this->gameUsers=game.gameUsers;
        this->gameChannel=game.gameChannel;
        this->gameParameter=game.gameParameter;
        this->gameCurrentUser=game.gameCurrentUser;
        this->gamePosCurrent=game.gamePosCurrent;
        this->gameAllPlat=game.gameAllPlat;
    }

    Game::Game(){
        this->gameUsers=new vector<UserInfo*>();
        this->gameChannel=new Channel();
        this->gameCurrentUser=new UserInfo();
        this->gamePosCurrent= 0;
        this->gameAllPlat = 0;
    }

    void Game::setGameUsers(vector<UserInfo*> &users){
        this->gameUsers=new vector<UserInfo*>(users);
    }

    void Game::setGameChannel(Channel &ch){
        this->gameChannel=new Channel(ch);
    }

    void Game::setGameParameters(vector<Parameter*> list){
        this->gameParameter = list;
    }

    void Game::setGameCurrentUser(UserInfo * currentUser){
        this->gameCurrentUser=currentUser;
    }

    void Game::setGamePosCurrent(int i){
        this->gamePosCurrent=i;
    }

    void Game::setGameAllPlat(int i){
        this->gameAllPlat=i;
    }

    vector<UserInfo*>* Game::getGameUsers() const{
        return this->gameUsers;
    }

    Channel* Game::getGameChannel() const{
        return this->gameChannel;
    }

    vector<Parameter*> Game::getGameParameters() const{
        return this->gameParameter;
    }

    UserInfo* Game::getGameCurrentUser() const{
        return this->gameCurrentUser;
    }

    UserInfo* Game::getNextUser() const{
        UserInfo* current = this->getGameCurrentUser();
        /*for(unsigned int i = 0; i < this->getGameUsers()->size(); i++){
            if(this->getGameUsers()->at(i) == current){
                if(i != this->getGameUsers()->size() - 1){
                    return this->getGameUsers()->at(i + 1);
                }
                else{
                    if(this->getGameUsers()->size()>1){
                        return this->getGameUsers()->at(1);
                    }
                    else{
                        return this->getGameUsers()->at(0);                        
                    }
                }
            }
        }*/
        if(this->getGameUsers()->size()==1) {
            return current;
        }   else    {
            for(unsigned int i=0;i<this->getGameUsers()->size();i++)  {
                if(this->getGameUsers()->at(i)==current)    {
                    if(i+1==this->getGameUsers()->size())   {
                        return this->getGameUsers()->at(0);
                    }   else return this->getGameUsers()->at(i+1);
                }
            }
        }
        
        return NULL;
    }

    void Game::clearUserList(){
        this->getGameUsers()->clear();
    }
    
    void Game::clearParameterList(){
        this->getGameParameters().clear();
    }

    int Game::getGamePosCurrent() const{
        return this->gamePosCurrent;
    }

    int Game::getGameAllPlat() const{
        return this->gameAllPlat;
    }

    void Game::decrPlat(int i){
        this->gameAllPlat -= i;
    }

     /*// Insertion operator
	ostream& operator<<(ostream& os, const Game * g)
	{
		// write out individual members of g with an end of line between each one
		os << g->getGameUsers() << endl;
		os << g->getGameChannel() << endl;
        os << g->getGameParameter() << endl;
        os << g->getGameCurrentUser() << endl;
        os << g->getGamePosCurrent() << endl;
		return os;
	}

	// Extraction operator
    istream& operator>>(istream& is, Game * g)
	{
		// read in individual members of g
        is >> g->gamePosCurrent;
		return is;
	}*/

    Parameter* Game::getParameterFromCode(string code) const{
    for(unsigned int i = 0; i < this->getGameParameters().size(); i++){
        if(code == this->getGameParameters().at(i)->getParameterCode()){
            return this->getGameParameters().at(i);
        }
    }
    return NULL;
}

    
    ostream& operator<<( std::ostream& s, const Game& c){
        s << "------------------------------Game------------------------------" << endl <<
        "------Liste------" << endl << "gameUsers : ";
        for (unsigned int i = 0; i < c.getGameUsers()->size(); i++)
            cout << *(c.getGameUsers()->at(i)) << endl;
        s << "-----FinListe-----" << endl << "gameChannel : " << *c.getGameChannel() << endl <<
        "------Liste------" << endl << "gameParameters : ";
       // for (unsigned int i = 0; i < c.getGameParameter()->size(); i++)
         //   cout << *(c.getGameParameter()->at(i)) << endl;
        s << "-----FinListe-----" << endl;
        s << "gameCurrentUser : " << *c.getGameCurrentUser() << endl <<
        "----------------------------------------------------------------------" << endl;

        return s;
    }

