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

void sort(carta*,unsigned int);
void CrearDeck(carta*,unsigned int);
void draw(carta*,carta*,unsigned int,unsigned int);
int Random(carta*,int*,unsigned int,unsigned int);
bool CompararCarta(carta*,carta,unsigned int);
void PrintHand(carta*,unsigned int);
void ClearScreen();
void Cambiar(carta*,carta*,unsigned int,unsigned int);
bool Par(carta*,unsigned int);
bool DosPar(carta*,unsigned int);
bool Trio(carta*);
bool Escalera(carta*);
bool Flush(carta*);
bool FullHouse(carta*);
bool CuatroIguales(carta*);
bool StraightFlush(carta*);
bool EscaleraReal(carta*,unsigned int);
unsigned int GetApuesta(unsigned int&);
void Random2(carta*,carta*,vector<int>&,int*,int);
void Jugada(carta*,unsigned int,unsigned int,unsigned int&);
bool FileExists(const char* Archivo);

int main(int argc, char* argv[]){
	srand(time(0));
	initscr();	
	noecho();
	const char Archivo[10]="Datos.txt";
	unsigned int Dinero;
	bool nRonda=false;
	vector<string> datos;
	if(FileExists(Archivo)){
		ifstream reader("Datos.txt");
		string line;
		getline(reader,line);
		stringstream ss(line);
		while(ss.good()){
			string sub;
			getline(ss,sub,',');
			datos.push_back(sub);
		}
		if(datos.at(0)=="True"){
			nRonda=true;
		}
	}
	const unsigned int size=52;
	carta* Deck=new carta[size];
	if(!Deck){
		mvprintw(25,25,"Not enough memory!");
		getch();
		ClearScreen();
		delete[] Deck;
	}else{
		bool continuar=false;
		CrearDeck(Deck,size);	
		int row,col;	
		getmaxyx(stdscr,row,col);
		if(row<80&&col<20){
			mvprintw(row/2,col/2,"Por favor agranda la ventana para disfrutar de la experiencia completa");
			mvprintw(row/2+1,col/2+6,"(Presiona cualquier tecla para continuar)");
			getch();
		}
		ClearScreen();
		mvprintw(row/2-4,col/2-20,"*-----------------------------------------------*");
		mvprintw(row/2-3,col/2-20,"|						 |");
		mvprintw(row/2-2,col/2-20,"|	     ******************************      |");
		mvprintw(row/2-1,col/2-20,"| 	     *BIENVENIDO AL CASINO DEL SOL*      |");
		mvprintw(row/2,col/2-20,"|	     ******************************      |");
		mvprintw(row/2+1,col/2-20,"|					         |");
		mvprintw(row/2+2,col/2-20,"|		1.- JUGAR POKER INCA	         |");
		mvprintw(row/2+3,col/2-20,"|		2.- COMO JUGAR POKER INCA        |");
		mvprintw(row/2+4,col/2-20,"|		3.- SALIR DEL CASINO	         |");
		mvprintw(row/2+5,col/2-20,"|					         |");
		mvprintw(row/2+6,col/2-20,"|					         |");
		mvprintw(row/2+7,col/2-20,"*-----------------------------------------------*");
		int opcion=getch();
		if(opcion==49){
			ClearScreen();
			continuar=true;
			
		}else if(opcion==50){
			ClearScreen();
			continuar=true;	
			mvprintw(row/2-8,col/2-20,"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
			mvprintw(row/2-7,col/2-20,"| El poker inca es completamente identico al videopoker tradicional   |");
			mvprintw(row/2-6,col/2-20,"| Instrucciones de juego:                                             |");
			mvprintw(row/2-5,col/2-20,"| 1.-Ingrese cuanto dinero desea apostar esa ronda.                   |");
			mvprintw(row/2-4,col/2-20,"| 2.-Se le presentara una mano de 5 cartas.                           |");
			mvprintw(row/2-3,col/2-20,"| 3.-Se le preguntara si desea cambiar cartas (Teclas: S=Si, N=No).   |");
			mvprintw(row/2-2,col/2-20,"| 4.-Ingrese los numeros de las cartas, separados por comas (,).      |");
			mvprintw(row/2-1,col/2-20,"| 5.-Se cambiaran las cartas elegidas por otras de la baraja          |");
			mvprintw(row/2,col/2-20,"| 6.-Confirme su nueva mano presionando cualquier tecla.              |");
			mvprintw(row/2+1,col/2-20,"| 7.-El programa usara sus avanzados algoritmos de poker para         |");
			mvprintw(row/2+2,col/2-20,"| verificar su mejor jugada, y ganara o perdera dinero de acuerdo     |");
			mvprintw(row/2+3,col/2-20,"| a la cantidad de dinero apostada y su mejor jugada.                 |");			
			mvprintw(row/2+4,col/2-20,"|                                                                     |");
			mvprintw(row/2+5,col/2-20,"| -Posibles manos: Par x1, 2 Pares x2, Trio x3, Escalera x4, Flush x5 |");
			mvprintw(row/2+6,col/2-20,"| Full House x9, 4Iguales x25, StraightFlush x50, ESCALERA REAL x250  |");
			mvprintw(row/2+7,col/2-20,"| -D=Diamantes, C=Corazones, P=Picas, T=Treboles.                     |");
			mvprintw(row/2+8,col/2-20,"| -Al haber leido las instrucciones, usted esta listo para:           |");
			mvprintw(row/2+9,col/2-20,"| ~Apostar en Grande                                                  |");
			mvprintw(row/2+10,col/2-20,"| ~Ganar en Grande                                                    |");
			mvprintw(row/2+11,col/2-20,"|                                                                     |");
			mvprintw(row/2+12,col/2-20,"|               Presiona cualquier tecla para continuar               |");
			mvprintw(row/2+13,col/2-20,"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
			getch();
		}
		const unsigned int HandSize=5;
		carta* mano=new carta[HandSize];
		bool Salida=false;
		Dinero=100;
		while(continuar){
			if(nRonda){
				ClearScreen();
				int op;
				mvprintw(row/2-1,col/2-10,"-------------------");
				mvprintw(row/2,col/2-10,"| Elija una opcion  |");
				mvprintw(row/2+1,col/2-10,"-------------------");
				mvprintw(row/2+2,col/2-20,"1.- Volver a jugar con %d dolares",Dinero);
				mvprintw(row/2+3,col/2-20,"2.- Empezar nueva ronda con 100 dolares",Dinero);
				mvprintw(row/2+4,col/2-20,"3.- Salir del juego",Dinero);
				op=getch();
				if(op==49){
					Dinero=atoi(datos.at(1).c_str());
				}else if(op==50){
					Dinero=100;
				}else if(op==51){
					ClearScreen();
					Salida=true;
					continuar=false;
					break;
				}
			}
			if(Dinero>0){	
				draw(mano,Deck,HandSize,size);
				PrintHand(mano,HandSize);
				mvprintw(22,0,"Dinero: %d",Dinero);
				int apuesta=GetApuesta(Dinero);
				mvprintw(22,0,"Dinero: %d",Dinero);
				mvprintw(23,0,"Apuesta: %d",apuesta);
				refresh();	
				if(apuesta==0){
					nRonda=true;
				}else{
					PrintHand(mano,HandSize);
					mvprintw(22,0,"Dinero: %d",Dinero);
					mvprintw(23,0,"Apuesta: %d",apuesta);
					mvprintw(18,0,"Desea Cambiar cartas [S= Si/N= No]? ");
					char change=getch();
					if(change=='s'||change=='S'){
						Cambiar(Deck,mano,size,HandSize);
						ClearScreen();	
					}
					PrintHand(mano,HandSize);
					sort(mano,HandSize);
					mvprintw(20,0,"Dinero: %d",Dinero);
					mvprintw(21,0,"Apuesta: %d",apuesta);
					mvprintw(18,0,"Esta es su nueva mano, Presiona cualquier tecla para ver el resultado!");
					getch();
					Jugada(mano,HandSize,apuesta,Dinero);
				}
			}else{
				ClearScreen();
				mvprintw(0,0,"Ya no tiene dinero");
				continuar=false;
			}
		}
		if(FileExists(Archivo)&&Salida){
			ofstream salida;
			salida.open(Archivo,std::ios::trunc);
			salida<<"True,"<<Dinero;
			salida.close();
		}else{
			ofstream salida;
			salida.open(Archivo,std::ios::trunc);
			salida<<"Falso,0";
			salida.close();
		}
		int maxy,maxx;
		getmaxyx(stdscr,maxy,maxx);
		mvprintw(maxy/2-10,maxx/2-10,"GRACIAS POR JUGAR!");
		delete[] Deck;
		delete[] mano;
		Deck=NULL;
		mano=NULL;
		getch();
	}	
	endwin();
	return 0;
}

void sort(carta* mano,unsigned int HandSize){
	carta temp;
	for(int i=0;i<HandSize;i++){
		for(int j=0;j<HandSize-1;j++){
			if(mano[j].getValor()>mano[j+1].getValor()){
				temp=mano[j];
				mano[j]=mano[j+1];
				mano[j+1]=temp;
			}
		}
	}
}

bool FileExists(const char* Archivo){
	if(!ifstream(Archivo)){
		ofstream crear(Archivo);
		ofstream write;
		write.open(Archivo);
		write<<"Falso,0";
		write.close();
		crear.close();
		return true;
	}else{
		return true;
	}
		
}
void Jugada(carta* mano,unsigned int HandSize,unsigned int apuesta,unsigned int &Dinero){
	ClearScreen();
	int col,row;
	getmaxyx(stdscr,row,col);
	if(EscaleraReal(mano,HandSize)){
		apuesta*=250;
		mvprintw(row/2,col/2 - 5,"ESCALERA REAL!");
		mvprintw(row/2 + 1,col/2 - 5,"GANASTE %d !!!",apuesta);
		Dinero+=apuesta;
	}else if(StraightFlush(mano)){
		apuesta*=50;
		mvprintw(row/2,col/2 - 5,"STRAIGHT FLUSH!");
		mvprintw(row/2 + 1,col/2 - 5,"GANASTE %d !!!",apuesta);
		Dinero+=apuesta;
	}else if(CuatroIguales(mano)){
		apuesta*=25;
		mvprintw(row/2,col/2 - 5,"4 IGUALES!");
		mvprintw(row/2 + 1,col/2 - 5,"GANASTE %d !!!",apuesta);
		Dinero+=apuesta;
	}else if(FullHouse(mano)){
		apuesta*=9;
		mvprintw(row/2-1,col/2,"----------------");
		mvprintw(row/2,col/2 - 5,"|\tFULL HOUSE!\t|");
		mvprintw(row/2 + 1,col/2 - 5,"|\tGANASTE %d !!!\t|",apuesta);
		mvprintw(row/2 + 2,col/2-5,"----------------");
		Dinero+=apuesta;
	}else if(Flush(mano)){
		apuesta*=5;
		mvprintw(row/2,col/2 - 5,"FLUSH!");
		mvprintw(row/2 + 1,col/2 - 5,"GANASTE %d !!!",apuesta);
		Dinero+=apuesta;
	}else if(Escalera(mano)){
		apuesta*=4;
		mvprintw(row/2,col/2 - 5,"ESCALERA!");
		mvprintw(row/2 + 1,col/2 - 5,"GANASTE %d !!!",apuesta);
		Dinero+=apuesta;
	}else if(Trio(mano)){
		apuesta*=3;
		mvprintw(row/2,col/2-5,"TRIO!");
		mvprintw(row/2 + 1,col/2-5,"GANASTE %d !!!",apuesta);
		Dinero+=apuesta;
	}else if(DosPar(mano,HandSize)){
		apuesta*=2;
		mvprintw(row/2,col/2 - 5,"DOS PARES!");
		mvprintw(row/2 + 1,col/2 - 5,"GANASTE %d !!!",apuesta);
		Dinero+=apuesta;
	}else if(Par(mano,HandSize)){
		mvprintw(row/2,col/2 - 5,"PAR!");
		mvprintw(row/2 + 1,col/2 - 5,"GANASTE %d !!!",apuesta);
		Dinero+=apuesta;
	}else{
		mvprintw(row/2,col/2-5,"PERDISTE! MEJOR SUERTE A LA PROXIMA!");
	}	
	getch();
}

bool EscaleraReal(carta* mano,unsigned int HandSize){
	if(mano[0].getValor()==10&&mano[1].getValor()==11&&mano[2].getValor()==12&&mano[3].getValor()==13&&mano[4].getValor()==14&&StraightFlush(mano)){
		return true;
	}else{
		return false;
	}
}

bool StraightFlush(carta* mano){
	if(Escalera(mano)&&Flush(mano)){
		return true;
	}else{
		return false;
	}
}

bool CuatroIguales(carta* mano){
	if(mano[0].getValor()==mano[1].getValor()&&mano[0].getValor()==mano[2].getValor()&&mano[0].getValor()==mano[3].getValor()){
		return true;
	}else if(mano[1].getValor()==mano[2].getValor()&&mano[1].getValor()==mano[3].getValor()&&mano[1].getValor()==mano[4].getValor()){
		return true;
	}else{
		return false;
	}
}

bool FullHouse(carta* mano){
	if((mano[0].getValor()==mano[1].getValor())&&(mano[2].getValor()==mano[3].getValor()&&mano[2].getValor()==mano[4].getValor())){
		return true;
	}else if((mano[0].getValor()==mano[1].getValor()&&mano[0].getValor()==mano[2].getValor())&&(mano[3].getValor()==mano[4].getValor())){
		return true;
	}else{
		return false;
	}
}

bool Flush(carta* mano){
	if(mano[0].getSimbolo()==mano[1].getSimbolo()&&mano[0].getSimbolo()==mano[2].getSimbolo()&&mano[0].getSimbolo()==mano[3].getSimbolo()&&mano[0].getSimbolo()==mano[4].getSimbolo()){
		return true;
	}else{
		return false;
	}
}

bool Escalera(carta* mano){
	if(mano[0].getValor()==2&&mano[1].getValor()==3&&mano[2].getValor()==4&&mano[3].getValor()==5&&mano[4].getValor()==14){
		return true;
	}else if((mano[0].getValor()==(mano[1].getValor()-1))&&(mano[0].getValor()==(mano[2].getValor()-2))&&(mano[0].getValor()==(mano[3].getValor()-3))&&(mano[0].getValor()==(mano[4].getValor()-4))){
		return true;
	}else{
		return false;
	}
}

bool Trio(carta* mano){
	for(int i=0;i<3;i++){
			if(mano[i].getLetra()==mano[i+1].getLetra()&&mano[i].getLetra()==mano[i+2].getLetra()){
				return true;
			}
	}
	return false;
}

bool DosPar(carta* mano,unsigned int HandSize){
	int index;
	for(int i=0;i<HandSize;i++){
		if(mano[i].getLetra()=='J'||mano[i].getLetra()=='Q'||mano[i].getLetra()=='K'||mano[i].getLetra()=='A'){
			index=i;
			i=HandSize;
		}
	}
	if(index<=1){
		if(index==0){
			if((mano[0].getLetra()=='J'||mano[0].getLetra()=='Q'||mano[0].getLetra()=='K'||mano[0].getLetra()=='A')&&
			   (mano[3].getLetra()=='J'||mano[3].getLetra()=='Q'||mano[3].getLetra()=='K'||mano[0].getLetra()=='A')){
				if((mano[0].getLetra()==mano[1].getLetra())&&(mano[2].getLetra()==mano[3].getLetra())){
					return true;
				}else{
					 return false; 
				}
			}else{
				return false;
			}
		}else if(index==1){
			if((mano[1].getLetra()=='J'||mano[1].getLetra()=='Q'||mano[1].getLetra()=='K'||mano[1].getLetra()=='A')&&
			   (mano[4].getLetra()=='J'||mano[4].getLetra()=='Q'||mano[4].getLetra()=='K'||mano[4].getLetra()=='A')){
				if((mano[1].getLetra()==mano[2].getLetra())&&(mano[3].getLetra()==mano[4].getLetra())){
					return true;
				}else{
					 return false; 
				}
			}else{
				return false;
			}
		}else{
			return false;
		}

	}else{
		return false;
	}
	
}

bool Par(carta* mano,unsigned int HandSize){
	for(int i=0;i<HandSize;i++){
		if(mano[i].getLetra()=='J'||mano[i].getLetra()=='Q'||mano[i].getLetra()=='K'||mano[i].getLetra()=='A'){
			for(int j=0;j<HandSize;j++){
				if(i!=j){
					if(mano[i].getLetra()==mano[j].getLetra()){
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Cambiar(carta* deck, carta* mano, unsigned int size, unsigned int handS){
	echo();
	mvprintw(18,0,"Ingrese los numeros de las cartas que desea cambiar, separados por comas (',')  Ejemplo: (1,3,5)\n");
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
	vector<int> NIndex;
	Random2(deck,mano,NIndex,DeckIndex,indices.size());
	for(int i=0;i<indices.size();i++){
		mano[HandIndex[i]]=deck[NIndex.at(i)];
	}
	ClearScreen();
	PrintHand(mano,handS);
}



unsigned int GetApuesta(unsigned int &Dinero){
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
		Deck[0]=carta(simbolo,'A',14);
		int cont=2;
		for(int i=1;i<10;i++){
			Deck[i]=carta(simbolo,cont,cont);
			cont++;
		}
		Deck[10]=carta(simbolo,'J',11);
		Deck[11]=carta(simbolo,'Q',12);
		Deck[12]=carta(simbolo,'K',13);

		simbolo='C';
		cont=2;
		Deck[13]=carta(simbolo,'A',14);
		for(int i=14;i<23;i++){
			Deck[i]=carta(simbolo,cont,cont);
			cont++;
		}
		Deck[23]=carta(simbolo,'J',11);
		Deck[24]=carta(simbolo,'Q',12);
		Deck[25]=carta(simbolo,'K',13);
		
		cont=2;
		simbolo='P';
		Deck[26]=carta(simbolo,'A',14);
		for(int i=27;i<36;i++){
			Deck[i]=carta(simbolo,cont,cont);
			cont++;
		}
		Deck[36]=carta(simbolo,'J',11);
		Deck[37]=carta(simbolo,'Q',12);
		Deck[38]=carta(simbolo,'K',13);
		
		cont=2;
		simbolo='D';
		Deck[39]=carta(simbolo,'A',14);
		for(int i=40;i<49;i++){
			Deck[i]=carta(simbolo,cont,cont);
			cont++;
		}
		Deck[49]=carta(simbolo,'J',11);
		Deck[50]=carta(simbolo,'Q',12);
		Deck[51]=carta(simbolo,'K',13);
	
		/*for(int i=0;i<size;i++){
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
