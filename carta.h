#ifndef CARTA_H
#define CARTA_H
#include<ncurses.h>
#include<string>

using std::string;
class carta{
	public:
		carta();
		carta(string,unsigned int,string,char);
	private:
		string simbolo;
		unsigned int valor;
		string color;
		char letra;
	
		void setSimbolo(string);
		void setValor(unsigned int);
		void setColor(string);
		void setLetra(char);

		string getSimbolo();
		unsigned int getValor();
		string getColor();
		char getLetra();
};




#endif
