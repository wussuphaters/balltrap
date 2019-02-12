#include "Parameter.h"

using namespace std;

    Parameter::Parameter(int parameterId, std::string parameterCode, std::string parameterValue, std::string parameterName){
        this->parameterId=parameterId;
        this->parameterCode=parameterCode;
        this->parameterValue=parameterValue;
        this->parameterName=parameterName;
    }

    Parameter::Parameter(Parameter &param){
        this->parameterId=param.parameterId;
        this->parameterCode=param.parameterCode;
        this->parameterValue=param.parameterValue;
        this->parameterName=param.parameterName;
    }

    Parameter::Parameter(Json::Value res){
        this->parameterId=getJsonValueInt(res, "parameterId");
        this->parameterCode=getJsonValueString(res, "parameterCode");
        this->parameterName=getJsonValueString(res, "parameterName");
        this->parameterValue=getJsonValueString(res, "parameterValue");
    }

    Parameter::Parameter(){
        
    }

    void Parameter::setParameterCode(std::string str){
        this->parameterCode=str;
    }

    void Parameter::setParameterValue(std::string str){
        this->parameterValue=str;
    }

    void Parameter::setParameterName(std::string str){
        this->parameterName=str;
    }

    void Parameter::setParameterId(int number){
        this->parameterId=number;
    }

    std::string Parameter::getParameterCode() const{
        return this->parameterCode;
    }

    std::string Parameter::getParameterValue() const{
        return this->parameterValue;
    }

    std::string Parameter::getParameterName() const{
        return this->parameterName;
    }

    int Parameter::getParameterId() const{
        return this->parameterId;        
    }

    int Parameter::getJsonValueInt(Json::Value json, string key) const{
        Json::Value value = json[0][key];
        Json::FastWriter fastwriter;
        string valueS = fastwriter.write(value);
        valueS = valueS.substr(1, valueS.size() - 3);
        int valueI = atoi(valueS.c_str());
        return valueI;
    }

    string Parameter::getJsonValueString(Json::Value json, string key) const{
        Json::Value value = json[0][key];
        Json::FastWriter fastwriter;
        string valueS = fastwriter.write(value);
        valueS = valueS.substr(1, valueS.size() - 3);
        return valueS;
    }

    ostream& operator<<( std::ostream& s, const Parameter& c){
        s << "----------Parameter----------" << endl <<
        "parameterId : " << c.getParameterId()  << endl <<
        "parameterCode : " << c.getParameterCode() << endl <<
        "parameterName : " << c.getParameterName() << endl <<
        "parameterValue : " << c.getParameterValue() << endl <<
        endl << endl;

        return s;
    }

