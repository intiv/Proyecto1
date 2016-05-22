
#ifndef CARTA_H
#define CARTA_H
#pragma once
#include<ncurses.h>
#include<string>

using std::string;
class carta{
	public:
		
		carta();
		carta(char,char);
		
		char getSimbolo();
		void setSimbolo(char);
		void setLetra(char);
		char getLetra();
		string toString();
	private:
		char simbolo;
		char letra;
};

#endif
