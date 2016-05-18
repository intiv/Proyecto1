#include "carta.h"
#include<vector>
#include<ncurses.h>
#include<iostream>
#include<string>

using std::string;
using std::cout;
using std::cin;
using std::endl;

void CrearDeck(carta*,unsigned int);

int main(int argc, char* argv[]){
	cout<<sizeof(carta)<<endl;
	const unsigned int size=52;
	carta* Deck=new carta[size];
	if(!Deck){
		cout<<"Not enough memory!"<<endl;
		delete[] Deck;
	}else{
		CrearDeck(Deck,size);
		delete[] Deck;
	}	
	
	return 0;
}

void CrearDeck(carta* Deck,unsigned int size){
		string simbolo="Treboles";
		Deck[0]=carta(simbolo,'A');
		int cont=2;
		for(int i=1;i<10;i++){
			Deck[i]=carta(simbolo,cont);
			cont++;
		}
		Deck[10]=carta(simbolo,'J');
		Deck[11]=carta(simbolo,'Q');
		Deck[12]=carta(simbolo,'K');

		simbolo="Corazones";
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
		simbolo="Picas";
		Deck[26]=carta(simbolo,'A');
		for(int i=27;i<36;i++){
			Deck[i]=carta(simbolo,cont);
			cont++;
		}
		Deck[36]=carta(simbolo,'J');
		Deck[37]=carta(simbolo,'Q');
		Deck[38]=carta(simbolo,'K');
		
		cont=2;
		simbolo="Diamantes";
		Deck[39]=carta(simbolo,'A');
		for(int i=40;i<49;i++){
			Deck[i]=carta(simbolo,cont);
			cont++;
		}
		Deck[49]=carta(simbolo,'J');
		Deck[50]=carta(simbolo,'Q');
		Deck[51]=carta(simbolo,'K');
		

		for(int i=0;i<size;i++){
			cout<<Deck[i].getSimbolo()<<"\t";
			if(Deck[i].getLetra()=='A'||Deck[i].getLetra()=='J'||Deck[i].getLetra()=='Q'||Deck[i].getLetra()=='K'){
				cout<<Deck[i].getLetra();
			}else{
				cout<<+Deck[i].getLetra();
			}
			cout<<endl;
		}
}
