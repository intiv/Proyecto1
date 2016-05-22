#include "carta.h"
#include<string>
#include<sstream>


using std::string;
using std::stringstream;
using std::endl;

carta::carta(){

}

carta::carta(char symbol, char letter){
	this->simbolo=symbol;
	this->letra=letter;
}

void carta::setSimbolo(char simbolo){
	this->simbolo=simbolo;
}

void carta::setLetra(char letra){
	this->letra=letra;
}

char carta::getSimbolo(){
	return this->simbolo;
}

char carta::getLetra(){
	return this->letra;
}

string carta::toString(){
	stringstream ss;
	ss<<this->simbolo<<"  "<<this->letra<<endl;
	return ss.str();
}
