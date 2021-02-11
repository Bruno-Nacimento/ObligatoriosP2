/* 5140889 */
#include "../include/utils.h"
#include "../include/avl.h"
#include "../include/colaAvls.h"


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
struct Nodo {
TAvl arbol;
Nodo *sig;
};
struct repColaAvls {
	Nodo *ini,*fin;
};

TColaAvls crearColaAvls(){
	TColaAvls c = new repColaAvls ;
	c->ini = c->fin = NULL;
	return c;
}
TColaAvls encolar(TAvl avl, TColaAvls c){
		Nodo *aux= new Nodo;
		aux->arbol=avl;
		aux->sig= NULL;
		if (c->ini==NULL){
			c->ini= aux;
			c->fin=aux;
		}
		else {
			c->fin->sig= aux;
			c->fin=c->fin->sig;
		}
	return c;	
}
TColaAvls desencolar(TColaAvls c){
	
	if (c->ini!=NULL){
		Nodo *borrar=c->ini;
		if (c->ini ==c->fin){
			c->ini=NULL;
			c->fin=NULL;
			delete borrar;
		}
	
		else {
			c->ini=c->ini->sig;
			delete borrar;
		}
		
	}
	return c;
}
void liberarColaAvls(TColaAvls c){
	Nodo *aux;
	while (c->ini!= NULL){
		aux = c->ini;
		c->ini= c->ini->sig;
		delete aux;
	}
	delete c;
}
bool estaVaciaColaAvls(TColaAvls c){return c->ini==NULL;}

TAvl frente(TColaAvls c){
	assert(!estaVaciaColaAvls(c));
	return c->ini->arbol;
}





