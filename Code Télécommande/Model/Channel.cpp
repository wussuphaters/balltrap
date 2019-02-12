#include "Channel.h"

using namespace std;

    Channel::Channel(int channelId, std::string channelNumber, std::string channelName, int channelNbPlat){
        this->channelId = channelId;
        this->channelNumber = channelNumber;
        this->channelName = channelName;
        this->channelNbPlat = channelNbPlat;
    }

    Channel::Channel(Channel &channel){
        this->channelId = channel.channelId;
        this->channelNumber = channel.channelNumber;
        this->channelName = channel.channelName;
        this->channelNbPlat = channel.channelNbPlat;
    }

    Channel::Channel(Json::Value res){
        this->channelId=getJsonValueInt(res, "channelId");
        this->channelNumber=getJsonValueString(res, "channelNumber");
        this->channelName=getJsonValueString(res, "channelName");
        this->channelNbPlat=getJsonValueInt(res, "channelNbPlat");
    }

    Channel::Channel(){

    }


    ostream& operator<<( std::ostream& s, const Channel& c){
            s << "----------Channel----------" << endl <<
            "channelId : " << c.getChannelId()  << endl <<
            "channelNumber : " << c.getChannelNumber() << endl <<
            "channelName : " << c.getChannelName() << endl <<
            "channelNbPlat : " << c.getChannelNbPlat() << endl <<
            endl << endl;
            return s;
    }

    void Channel::setChannelNumber(std::string str){
        this->channelNumber = str;
    }

    void Channel::setChannelName(std::string str){
        this->channelName = str;        
    }

    void Channel::setChannelId(int number){
        this->channelId = number;        
    }

    void Channel::setChannelNbPlat(int number){
        this->channelNbPlat = number;        
    }

    string Channel::getChannelNumber() const{
        return this->channelNumber;
    }

    string Channel::getChannelName() const{
        return this->channelName;        
    }

    int Channel::getChannelId() const{
        return this->channelId;        
    }

    int Channel::getChannelNbPlat() const{
        return this->channelNbPlat;        
    }

    int Channel::getJsonValueInt(Json::Value json, string key) const{
        Json::Value value = json[0][key];
        Json::FastWriter fastwriter;
        string valueS = fastwriter.write(value);
        valueS = valueS.substr(1, valueS.size() - 3);
        int valueI = atoi(valueS.c_str());
        return valueI;
    }

    string Channel::getJsonValueString(Json::Value json, string key) const{
        Json::Value value = json[0][key];
        Json::FastWriter fastwriter;
        string valueS = fastwriter.write(value);
        valueS = valueS.substr(1, valueS.size() - 3);
        return valueS;
    }