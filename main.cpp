#include "carta.h"
#include<ncurses.h>
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include<algorithm>

using std::atoi;
using std::stringstream;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::find;


void CrearDeck(carta*,unsigned int);
void draw(carta*,carta*,unsigned int,unsigned int);
int Random(carta*,int*,unsigned int,unsigned int);
bool CompararCarta(carta*,carta,unsigned int);
void PrintHand(carta*,unsigned int);
void ClearScreen();

int main(int argc, char* argv[]){
	srand(time(0));
	initscr();
	/*int c;  Para verificar codigo de teclas
	noecho();
	while((c=getch())!=27){
		
		printw("Tecla: %c, codigo: %d \n",c,c);
		move(0,0);
		refresh();
	}*/
	//raw();
	noecho();	
	ifstream reader("Datos.txt");
	string line;
	int Dinero;
	getline(reader,line);
	stringstream ss(line);
	vector<string> datos;
	while(ss.good()){
		string sub;
		getline(ss,sub,',');
		datos.push_back(sub);
	}
	if(datos.at(0)=="True"){
		int DineroCargado=atoi(datos.at(1).c_str());
		
		printw("Hay un juego guardado, su dinero anterior era: %d \n",DineroCargado);
		printw("Desea jugar con este dinero?\n");
		printw("S = Continuar partida con %d dolares\nN = Empezar de nuevo con 200 dolares",DineroCargado);
		int input=getch();
		if(input==115){
			Dinero=DineroCargado;
			printw("\n%d",Dinero);
		}else{
			Dinero=200;
		}
	}else{
		Dinero=200;
	}
	const unsigned int size=52;
	carta* Deck=new carta[size];
	if(!Deck){
		cout<<"Not enough memory!"<<endl;
		delete[] Deck;
	}else{
		CrearDeck(Deck,size);	
		const unsigned int HandSize=5;
		carta* mano=new carta[HandSize];
		draw(mano,Deck,HandSize,size);
		PrintHand(mano,HandSize);
		getch();
		delete[] Deck;
		delete[] mano;
		Deck=NULL;
		mano=NULL;
	}	
	endwin();
	return 0;
}

void draw(carta* mano,carta* deck, unsigned int handS, unsigned int size){
	int index[handS];
	for(int i=0;i<handS;i++){
		index[i]=Random(deck,index,size,handS);
		mano[i]=deck[index[i]];
	}

}

int Random(carta* deck,int* index,unsigned int size,unsigned int handS){
	bool valido=false;
	int r1, cont;
	while(!valido){
		cont=0;
		r1=rand()%52;
		for(int i=0;i<handS;i++){
			if(r1==index[i]){
				cont++;
			}
		}
		if(cont==0){
			valido=true;
		}		
	}
	return r1;
}

void ClearScreen(){
	int row,col;
	getmaxyx(stdscr,row,col);
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			mvprintw(i,j," ");
		}
	}
}

void PrintHand(carta* mano, unsigned int HandS){
	ClearScreen();
	mvprintw(0,0,"---------------");
	if(mano[0].getLetra()=='J'||mano[0].getLetra()=='Q'||mano[0].getLetra()=='K'||mano[0].getLetra()=='A'){
		mvprintw(1,0,"|%c           %c|",mano[0].getLetra(),mano[0].getLetra());
	}else{
		if(mano[0].getLetra()<10){
			mvprintw(1,0,"|%d           %d|",+mano[0].getLetra(),+mano[0].getLetra());
		}else{
			mvprintw(1,0,"|%d         %d|",+mano[0].getLetra(),+mano[0].getLetra());
		}
	}
	mvprintw(2,0,"|%c           %c|",mano[0].getSimbolo(),mano[0].getSimbolo());
	for(int i=3;i<10;i++){
		if(i!=6)
			mvprintw(i,0,"|             |");
		else
			mvprintw(i,0,"|      %c      |",mano[0].getSimbolo());
	}
	mvprintw(10,0,"|%c           %c|",mano[0].getSimbolo(),mano[0].getSimbolo());
	if(mano[0].getLetra()=='J'||mano[0].getLetra()=='Q'||mano[0].getLetra()=='K'||mano[0].getLetra()=='A'){
		mvprintw(11,0,"|%c           %c|",mano[0].getLetra(),mano[0].getLetra());
	}else{
		if(mano[0].getLetra()<10){
			mvprintw(11,0,"|%d           %d|",+mano[0].getLetra(),+mano[0].getLetra());
		}else{
			mvprintw(11,0,"|%d         %d|",+mano[0].getLetra(),+mano[0].getLetra());
		}
	}
	mvprintw(12,0,"---------------");
		
	//for(int i=0;i<
}

void CrearDeck(carta* Deck,unsigned int size){
		char simbolo='T';
		Deck[0]=carta(simbolo,'A');
		int cont=2;
		for(int i=1;i<10;i++){
			Deck[i]=carta(simbolo,cont);
			cont++;
		}
		Deck[10]=carta(simbolo,'J');
		Deck[11]=carta(simbolo,'Q');
		Deck[12]=carta(simbolo,'K');

		simbolo='C';
		cont=2;
		Deck[13]=carta(simbolo,'A');
		for(int i=14;i<23;i++){
			Deck[i]=carta(simbolo,cont);
			cont++;
		}
		Deck[23]=carta(simbolo,'J');
		Deck[24]=carta(simbolo,'Q');
		Deck[25]=carta(simbolo,'K');
		
		cont=2;
		simbolo='P';
		Deck[26]=carta(simbolo,'A');
		for(int i=27;i<36;i++){
			Deck[i]=carta(simbolo,cont);
			cont++;
		}
		Deck[36]=carta(simbolo,'J');
		Deck[37]=carta(simbolo,'Q');
		Deck[38]=carta(simbolo,'K');
		
		cont=2;
		simbolo='D';
		Deck[39]=carta(simbolo,'A');
		for(int i=40;i<49;i++){
			Deck[i]=carta(simbolo,cont);
			cont++;
		}
		Deck[49]=carta(simbolo,'J');
		Deck[50]=carta(simbolo,'Q');
		Deck[51]=carta(simbolo,'K');
		/*

		for(int i=0;i<size;i++){
			cout<<Deck[i].getSimbolo()<<"\t";
			if(Deck[i].getLetra()=='A'||Deck[i].getLetra()=='J'||Deck[i].getLetra()=='Q'||Deck[i].getLetra()=='K'){
				cout<<Deck[i].getLetra();
			}else{
				cout<<+Deck[i].getLetra();
			}
			cout<<endl;
		}*/
}

bool CompararCarta(carta* Deck, carta Search,unsigned int size){
	for(int i=0;i<size;i++){
		if((Deck[i].getLetra()==Search.getLetra())&&(Deck[i].getSimbolo()==Search.getSimbolo())){
			return true;
		}
	}
	return false;
	
}
