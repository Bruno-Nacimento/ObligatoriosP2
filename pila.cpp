/* 5140889 */
#include "../include/utils.h"
#include "../include/pila.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
struct repPila  {

nat* Array;
nat tope;
nat cota;
};


TPila crearPila(nat tamanio){
	assert(tamanio > 0);
	TPila pila= new repPila ();
	pila->tope=0;
	pila->Array = new nat [tamanio];
	pila->cota= tamanio;
	return pila;
	}
TPila apilar(nat num, TPila p){
	if(!estaLlenaPila(p)){
		p->Array [p->tope]= num;
		p->tope++;
	}
return p;
}


TPila desapilar(TPila p){
		if(!estaVaciaPila(p)){
			p->tope--;
	}
	return p;
}
void liberarPila(TPila p){	
delete [] p->Array;
delete p;
}

bool estaVaciaPila(TPila p){
	return p->tope==0;
	}
bool estaLlenaPila(TPila p){return p->tope==p->cota;}

nat cima(TPila p) {
	assert(!estaVaciaPila(p));
	return p->Array [p->tope-1];
	
	}
