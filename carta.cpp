#include "carta.h"
#include<string>

using std::string;

carta::carta(){
		
}

carta::carta(string symbol,unsigned int value, string colour, char letter){
	setValor(value);
	setSimbolo(symbol);
	setColor(colour);
	setLetra(letter);
}

void carta::setValor(unsigned int valor){
	this->valor=valor;
}

void carta::setSimbolo(string simbolo){
	this->simbolo=simbolo;
}

void carta::setColor(string color){
	this->color=color;
}

void carta::setLetra(char letra){
	this->letra=letra;
}

unsigned int carta::getValor(){
	return this->valor;
}

string carta::getSimbolo(){
	return this->simbolo;
}

string carta::getColor(){
	return this->color;
}

char carta::getLetra(){
	return this->letra;
}
