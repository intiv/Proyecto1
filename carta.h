#ifndef CARTA_H
#define CARTA_H
#include<ncurses.h>
#include<string>

using std::string;
class carta{
	public:
		
		carta();
		carta(string,char);
		
		string getSimbolo();
		void setSimbolo(string);
		void setLetra(char);
		char getLetra();
	private:
		string simbolo;
		char letra;
};




#endif
