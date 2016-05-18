#include "carta.h"
#include<string>

using std::string;

carta::carta(){

}

carta::carta(string symbol, char letter){
	this->simbolo=symbol;
	this->letra=letter;
}
/*
carta::carta(string symbol, string colour, int numero){
	set
}
*/
void carta::setSimbolo(string simbolo){
	this->simbolo=simbolo;
}

void carta::setLetra(char letra){
	this->letra=letra;
}

string carta::getSimbolo(){
	return this->simbolo;
}

char carta::getLetra(){
	return this->letra;
}
