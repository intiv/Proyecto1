#include "carta.h"
#include<ncurses.h>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include<vector>

using std::atoi;
using std::stringstream;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;
using std::cout;
using std::cin;
using std::endl;

void CrearDeck(carta*,unsigned int);
void draw(carta*,carta*,unsigned int,unsigned int);
int Random(carta*,int*,unsigned int,unsigned int);
bool CompararCarta(carta*,carta,unsigned int);
void PrintHand(carta*,unsigned int);
void ClearScreen();
void Cambiar(carta*,carta*,unsigned int,unsigned int);
bool Par(carta*,unsigned int);
bool DosPar(carta*,unsigned int);
bool Trio(carta*,unsigned int);
bool Escalera(carta*,unsigned int);
bool Flush(carta*,unsigned int);
bool FullHouse(carta*,unsigned int);
bool CuatroIguales(carta*,unsigned int);
bool EscaleraReal(carta*,unsigned int);
int GetApuesta(int&);
void Random2(carta*,carta*,vector<int>&,int*,int);

int main(int argc, char* argv[]){
	srand(time(0));
	initscr();
/*	int c; // Para verificar codigo de teclas
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
		bool continuar=true;
		CrearDeck(Deck,size);	
		const unsigned int HandSize=5;
		carta* mano=new carta[HandSize];
		while(continuar){
			draw(mano,Deck,HandSize,size);
			PrintHand(mano,HandSize);
			mvprintw(16,0,"Dinero: %d",Dinero);
			int apuesta=GetApuesta(Dinero);
			refresh();
			ClearScreen();
			PrintHand(mano,HandSize);
			mvprintw(16,0,"Dinero: %d",Dinero);
			mvprintw(17,0,"Apuesta: %d\n",apuesta);	
			if(apuesta==0){
				continuar=false;
			}else{
				move(17,0);
				refresh();
				Cambiar(Deck,mano,size,HandSize);
				ClearScreen();
				PrintHand(mano,HandSize);
				
			}
		}
		delete[] Deck;
		delete[] mano;
		Deck=NULL;
		mano=NULL;
	}	
	endwin();
	return 0;
}

void Cambiar(carta* deck, carta* mano, unsigned int size, unsigned int handS){
	echo();
	printw("Ingrese los numeros de las cartas que desea cambiar, separados por comas (',')  Ejemplo: (1,3,5)\n");
	char CurrChar;
	string input="";
		while((CurrChar=getch())!=10){
		if(CurrChar=='1'||CurrChar=='2'||CurrChar=='3'||CurrChar=='4'||CurrChar=='5'||CurrChar==','){
			input.push_back(CurrChar);
		}
	}
	stringstream convert(input);
	vector<string> indices;
	while(convert.good()){
		string sub;
		getline(convert,sub,',');
		indices.push_back(sub);
	}
	noecho();
	int HandIndex[indices.size()];
	int DeckIndex[indices.size()];
	for(int i=0;i<indices.size();i++){
		int temp=atoi(indices.at(i).c_str())-1;
		for(int j=0;j<size;j++){
			if((mano[temp].getLetra()==deck[j].getLetra())&&(mano[temp].getSimbolo()==deck[j].getSimbolo())){
				HandIndex[i]=temp;
				DeckIndex[i]=j;
				j=size;
			}
		}
	}
//terminar
	vector<int> NIndex;
	Random2(deck,mano,NIndex,DeckIndex,indices.size());
	mvprintw(28,0,"NIndexes: ");
	for(int i=0;i<NIndex.size();i++){
		mvprintw(29+i,0,"%d",NIndex.at(i));
	}	
	for(int i=0;i<indices.size();i++){
		mano[HandIndex[i]]=deck[NIndex.at(i)];
	}
	ClearScreen();
	PrintHand(mano,handS);
	getch();
}



int GetApuesta(int &Dinero){
	echo();
	int bet;
	bool ValidBet=false;
	while(!ValidBet){
		mvprintw(20,0,"Ingrese apuesta (Si no desea seguir jugando, apueste 0): ");
		char actual;
		int TempBet;
		string getbet="";
		while((actual=getch())!=10){
			if(actual>47&&actual<58){
				getbet.push_back(actual);
			}
		}
		
		TempBet=atoi(getbet.c_str());
		if(Dinero<TempBet){
			mvprintw(23,0,"Apuesta invalida, no puede apostar una cantidad mayor a su dinero actual (%d)",Dinero);
		}else{
			bet=TempBet;
			Dinero-=bet;
			ValidBet=true;
		}	
	}
	noecho();
	return bet;

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

void Random2(carta* deck, carta* mano,vector<int> &NIndex, int* DeckIndex, int DeckIndexS){
	bool valido=false;
	int r2,cont, cont2,cont3=0,cont4;
	while(!valido){
		cont=0;
		cont2=0;
		cont4=0;
		r2=rand()%52;
		for(int i=0;i<DeckIndexS;i++){
			if(r2==DeckIndex[i]){
				cont++;
			}
			for(int j=0;j<NIndex.size();j++){
				if(r2==NIndex.at(j)){
					cont2++;
				}
			}
		}
		if(cont==0&&cont2==0){
			NIndex.push_back(r2);
		}
		for(int i=0;i<NIndex.size();i++){
			if(NIndex.at(i)>=0&&NIndex.at(i)<52){
				cont4++;
			}
		}
		if(cont4==DeckIndexS){
			valido=true;
		}
	
	}
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

	//Primera carta
	/*start_color();
	init_pair(1,COLOR_RED,COLOR_WHITE);
	init_pair(2,COLOR_BLACK,COLOR_WHITE);
	if(mano[0].getSimbolo()=='D'||mano[0].getSimbolo()=='C'){	
		attron(COLOR_PAIR(1));
	}else{
		attron(COLOR_PAIR(2));
	}*/
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
	
	/*if(mano[0].getSimbolo()=='D'||mano[0].getSimbolo()=='C'){	
		attroff(COLOR_PAIR(1));
	}else{
		attroff(COLOR_PAIR(2));
	}
	refresh();*/
	mvprintw(13,7,"1");
	//segunda carta	
	mvprintw(0,20,"---------------");
	if(mano[1].getLetra()=='J'||mano[1].getLetra()=='Q'||mano[1].getLetra()=='K'||mano[1].getLetra()=='A'){
		mvprintw(1,20,"|%c           %c|",mano[1].getLetra(),mano[1].getLetra());
	}else{
		if(mano[1].getLetra()<10){
			mvprintw(1,20,"|%d           %d|",+mano[1].getLetra(),+mano[1].getLetra());
		}else{
			mvprintw(1,20,"|%d         %d|",+mano[1].getLetra(),+mano[1].getLetra());
		}
	}
	mvprintw(2,20,"|%c           %c|",mano[1].getSimbolo(),mano[1].getSimbolo());
	for(int i=3;i<10;i++){
		if(i!=6)
			mvprintw(i,20,"|             |");
		else
			mvprintw(i,20,"|      %c      |",mano[1].getSimbolo());
	}
	mvprintw(10,20,"|%c           %c|",mano[1].getSimbolo(),mano[1].getSimbolo());
	if(mano[1].getLetra()=='J'||mano[1].getLetra()=='Q'||mano[1].getLetra()=='K'||mano[1].getLetra()=='A'){
		mvprintw(11,20,"|%c           %c|",mano[1].getLetra(),mano[1].getLetra());
	}else{
		if(mano[1].getLetra()<10){
			mvprintw(11,20,"|%d           %d|",+mano[1].getLetra(),+mano[1].getLetra());
		}else{
			mvprintw(11,20,"|%d         %d|",+mano[1].getLetra(),+mano[1].getLetra());
		}
	}
	mvprintw(12,20,"---------------");
	mvprintw(13,27,"2");
	//Tercera carta
	mvprintw(0,40,"---------------");
	if(mano[2].getLetra()=='J'||mano[2].getLetra()=='Q'||mano[2].getLetra()=='K'||mano[2].getLetra()=='A'){
		mvprintw(1,40,"|%c           %c|",mano[2].getLetra(),mano[2].getLetra());
	}else{
		if(mano[2].getLetra()<10){
			mvprintw(1,40,"|%d           %d|",+mano[2].getLetra(),+mano[2].getLetra());
		}else{
			mvprintw(1,40,"|%d         %d|",+mano[2].getLetra(),+mano[2].getLetra());
		}
	}
	mvprintw(2,40,"|%c           %c|",mano[2].getSimbolo(),mano[2].getSimbolo());
	for(int i=3;i<10;i++){
		if(i!=6)
			mvprintw(i,40,"|             |");
		else
			mvprintw(i,40,"|      %c      |",mano[2].getSimbolo());
	}
	mvprintw(10,40,"|%c           %c|",mano[2].getSimbolo(),mano[2].getSimbolo());
	if(mano[2].getLetra()=='J'||mano[2].getLetra()=='Q'||mano[2].getLetra()=='K'||mano[2].getLetra()=='A'){
		mvprintw(11,40,"|%c           %c|",mano[2].getLetra(),mano[2].getLetra());
	}else{
		if(mano[2].getLetra()<10){
			mvprintw(11,40,"|%d           %d|",+mano[2].getLetra(),+mano[2].getLetra());
		}else{
			mvprintw(11,40,"|%d         %d|",+mano[2].getLetra(),+mano[2].getLetra());
		}
	}
	mvprintw(12,40,"---------------");
	mvprintw(13,47,"3");
	//Cuarta carta
	mvprintw(0,60,"---------------");
	if(mano[3].getLetra()=='J'||mano[3].getLetra()=='Q'||mano[3].getLetra()=='K'||mano[3].getLetra()=='A'){
		mvprintw(1,60,"|%c           %c|",mano[3].getLetra(),mano[3].getLetra());
	}else{
		if(mano[3].getLetra()<10){
			mvprintw(1,60,"|%d           %d|",+mano[3].getLetra(),+mano[3].getLetra());
		}else{
			mvprintw(1,60,"|%d         %d|",+mano[3].getLetra(),+mano[3].getLetra());
		}
	}
	mvprintw(2,60,"|%c           %c|",mano[3].getSimbolo(),mano[3].getSimbolo());
	for(int i=3;i<10;i++){
		if(i!=6)
			mvprintw(i,60,"|             |");
		else
			mvprintw(i,60,"|      %c      |",mano[3].getSimbolo());
	}
	mvprintw(10,60,"|%c           %c|",mano[3].getSimbolo(),mano[3].getSimbolo());
	if(mano[3].getLetra()=='J'||mano[3].getLetra()=='Q'||mano[3].getLetra()=='K'||mano[3].getLetra()=='A'){
		mvprintw(11,60,"|%c           %c|",mano[3].getLetra(),mano[3].getLetra());
	}else{
		if(mano[3].getLetra()<10){
			mvprintw(11,60,"|%d           %d|",+mano[3].getLetra(),+mano[3].getLetra());
		}else{
			mvprintw(11,60,"|%d         %d|",+mano[3].getLetra(),+mano[3].getLetra());
		}
	}
	mvprintw(12,60,"---------------");
	mvprintw(13,67,"4");
	//Quinta carta
	mvprintw(0,80,"---------------");
	if(mano[4].getLetra()=='J'||mano[4].getLetra()=='Q'||mano[4].getLetra()=='K'||mano[4].getLetra()=='A'){
		mvprintw(1,80,"|%c           %c|",mano[4].getLetra(),mano[4].getLetra());
	}else{
		if(mano[4].getLetra()<10){
			mvprintw(1,80,"|%d           %d|",+mano[4].getLetra(),+mano[4].getLetra());
		}else{
			mvprintw(1,80,"|%d         %d|",+mano[4].getLetra(),+mano[4].getLetra());
		}
	}
	mvprintw(2,80,"|%c           %c|",mano[4].getSimbolo(),mano[4].getSimbolo());
	for(int i=3;i<10;i++){
		if(i!=6)
			mvprintw(i,80,"|             |");
		else
			mvprintw(i,80,"|      %c      |",mano[4].getSimbolo());
	}
	mvprintw(10,80,"|%c           %c|",mano[4].getSimbolo(),mano[4].getSimbolo());
	if(mano[4].getLetra()=='J'||mano[4].getLetra()=='Q'||mano[4].getLetra()=='K'||mano[4].getLetra()=='A'){
		mvprintw(11,80,"|%c           %c|",mano[4].getLetra(),mano[4].getLetra());
	}else{
		if(mano[4].getLetra()<10){
			mvprintw(11,80,"|%d           %d|",+mano[4].getLetra(),+mano[4].getLetra());
		}else{
			mvprintw(11,80,"|%d         %d|",+mano[4].getLetra(),+mano[3].getLetra());
		}
	}
	mvprintw(12,80,"---------------");
	mvprintw(13,87,"5");
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
