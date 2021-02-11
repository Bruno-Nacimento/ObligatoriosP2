/* 5140889 */

#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodo {
	TInfo dato;
	TLocalizador anterior;
	TLocalizador siguiente;
};
struct repCadena {
	TLocalizador inicio;
	TLocalizador final;
};

bool esLocalizador(TLocalizador loc) {
return (loc!= NULL);
}

TCadena crearCadena() {
	TCadena res= new repCadena;
	res->inicio=res->final=NULL;
	return res;
}
void liberarCadena(TCadena cad){
	TLocalizador aborrar;
	while (cad->inicio!=NULL){
		aborrar=cad->inicio;
		cad->inicio=cad->inicio->siguiente;
		liberarInfo(aborrar->dato);
		delete aborrar;
	}
	delete cad;
}
bool esVaciaCadena(TCadena cad) {
	assert(((cad->inicio==NULL) && (cad->final==NULL)) ||
	((cad->inicio!=NULL) && (cad->final!=NULL)) );
	return ((cad->inicio==NULL) && (cad->final==NULL));
}
TLocalizador inicioCadena(TCadena cad) {
	TLocalizador res;
	if (esVaciaCadena(cad))
		res=NULL;
	else 
		res= cad->inicio;
	return res;
}

TLocalizador finalCadena(TCadena cad){
	TLocalizador res;
	if (esVaciaCadena(cad)) {
		res=NULL;
	}
	else {
		res= cad->final;
	}
	
	return res;
}
TInfo infoCadena(TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	TInfo aux= loc->dato;
	return (aux); 
	}
	
TLocalizador siguiente(TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	TLocalizador res;
	if (esFinalCadena(loc,cad)) {
		res=NULL;
	}
	else {
		res= loc->siguiente;
	}
	return res;
}


TLocalizador anterior(TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	TLocalizador res;
	if (esInicioCadena(loc, cad))
		res=NULL;
	else
		res=loc->anterior;
	return res;
}
bool esFinalCadena(TLocalizador loc, TCadena cad) {
	if (esVaciaCadena(cad))
		return false;
	else 
		return (loc==finalCadena(cad));
}
bool esInicioCadena(TLocalizador loc, TCadena cad) {
	if (esVaciaCadena(cad))
		return false;
	else 
		return (loc==inicioCadena(cad));	
}
TCadena insertarAlFinal(TInfo i, TCadena cad) {
	TLocalizador aux= new nodo;
	
	aux->dato = i;
	aux->siguiente=NULL;
	if (esVaciaCadena(cad)){
		aux->anterior=NULL;
		cad->inicio= aux;
		cad->final = cad->inicio;
	}
	else {
		cad->final->siguiente= aux;
		aux->anterior= cad->final;
		cad->final= cad->final->siguiente;
	 }
	return cad;
}
TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	TLocalizador valor;
	valor= new nodo;
	valor->dato=i;
	if (esInicioCadena(loc,cad)) {
		valor->siguiente= cad->inicio;
		cad->inicio->anterior= valor;
		valor->anterior=NULL;
		cad->inicio= cad->inicio->anterior;	
	}
	else {
	TLocalizador aux=loc;
	valor->siguiente= aux;
	valor->anterior=aux->anterior;
	aux->anterior->siguiente = valor;
	aux->anterior = valor;
}
return cad;
}
TCadena removerDeCadena(TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	TLocalizador borrador;
	if ((cad->inicio==loc) && (cad->final==loc)){
		borrador=loc;
		cad->inicio = NULL;
		cad->final= cad->inicio;
		liberarInfo(borrador->dato);
		delete borrador;
	
	}
		
	else if (esInicioCadena(loc,cad)) {
		borrador=cad->inicio;
		cad->inicio=cad->inicio->siguiente;
		cad->inicio->anterior=NULL;
		liberarInfo(borrador->dato);
		delete borrador;
		
	}
	else if (esFinalCadena(loc,cad)){
			borrador=cad->final;
			cad->final=cad->final->anterior;
			cad->final->siguiente=NULL;
			liberarInfo(borrador->dato);
			delete borrador;
	}
	else { 
		TLocalizador aux = loc;
		borrador=aux;
		aux->anterior->siguiente= aux->siguiente;
		aux->siguiente->anterior=aux->anterior;
		liberarInfo(borrador->dato);
		delete borrador;
}
return cad;
}




void imprimirCadena(TCadena cad){
		TLocalizador aux;
		aux=cad->inicio;
		while ((esLocalizador(aux))){
			printf("(%d,%.2f)",natInfo(aux->dato),realInfo(aux->dato));    
			aux=siguiente(aux,cad);
		}
		printf("\n");
	}


TLocalizador kesimo(nat k, TCadena cad) {
	TLocalizador cursor,res;
	
	if (k==0)
		res=NULL;
	else {
		cursor=inicioCadena(cad);
		nat contador=1;
		while ((esLocalizador(cursor)) && (contador<k)){
		contador++;
		cursor= siguiente(cursor,cad);
		}	
		res=cursor;	
	}
	return res;
}

bool localizadorEnCadena(TLocalizador loc, TCadena cad) {
TLocalizador cursor = inicioCadena(cad);
while (esLocalizador(cursor) && (cursor != loc)) {
	cursor = siguiente(cursor, cad);
	}
	return esLocalizador(cursor);
}
	
bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
	bool res;
	res= localizadorEnCadena(loc1, cad);
	if(res){
		TLocalizador cursor=loc1;
		while (esLocalizador(cursor) && (cursor!=loc2))
			cursor=siguiente(cursor, cad);
		res= esLocalizador(cursor);
		assert(!res || localizadorEnCadena(loc2,cad));
	}
	return res;
}
TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad){
	assert((esVaciaCadena(cad)) || (localizadorEnCadena(loc, cad)));
	if ((esVaciaCadena(cad)) || (esVaciaCadena(sgm))) {
		if (esVaciaCadena(cad)){
			cad->inicio=sgm->inicio;
			cad->final=sgm->final;
		}
	}	
	else if (esFinalCadena(loc,cad)){
		cad->final->siguiente =sgm->inicio;
		sgm->inicio->anterior=cad->final;
		cad->final= sgm->final;
	}
	
	else {
	TLocalizador aux = loc;
	sgm->final->siguiente= aux->siguiente;
	sgm->inicio->anterior=aux;
	aux->siguiente->anterior=sgm->final;
	aux->siguiente= sgm->inicio;
	}
	

	sgm->inicio=NULL;
	sgm->final=sgm->inicio;
	delete sgm;
	return cad;
}
TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad){
	assert((esVaciaCadena(cad)) || (precedeEnCadena(desde,hasta,cad)));
	TCadena copia= crearCadena();
	if (esVaciaCadena(cad)) {
		return copia;
	}
	else {
		TLocalizador aux = desde;
		while (aux!= hasta){
			insertarAlFinal(copiaInfo(aux->dato),copia);
			aux= siguiente(aux,cad);
		}
		insertarAlFinal(copiaInfo(aux->dato),copia);
		return copia;
	}
}
	

TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
	assert((esVaciaCadena(cad)) || (precedeEnCadena(desde,hasta,cad)));
	if (esVaciaCadena(cad))
	 return cad;
	else {	
	TLocalizador aborrar,aux;
	aux= desde;
	while ((esLocalizador(aux)) && (aux!= hasta)){  

		 aborrar=aux;
		 aux=siguiente(aux,cad);
		 removerDeCadena(aborrar,cad);
	 }
	 aborrar=hasta;
	removerDeCadena(aborrar,cad);
}
return cad;
}
TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
		loc->dato=i;	
	return cad;
}
TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
	assert((localizadorEnCadena(loc1, cad)) && (localizadorEnCadena(loc2, cad)));
	TInfo temp = infoCadena(loc2,cad);
	cambiarEnCadena(loc1->dato,loc2,cad);
	cambiarEnCadena(temp,loc1,cad);
	return cad;
}

TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad){
		assert((esVaciaCadena(cad)) || (localizadorEnCadena(loc, cad)));
		TLocalizador res;
		if (esVaciaCadena(cad))
			res=NULL;
		else {	
			while ((esLocalizador(loc)) && (natInfo(loc->dato)!= clave)) 
				loc=siguiente(loc,cad);
			res=loc;
		}	
		
		return res;
}
TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad){
	assert((esVaciaCadena(cad)) || (localizadorEnCadena(loc, cad)));
	TLocalizador res;
	if (esVaciaCadena(cad))
		res=NULL;
	else {	
			while ((esLocalizador(loc)) && (natInfo(loc->dato)!= clave))
				loc=anterior(loc,cad);
		res=loc; 			
		}	
	return res;	
}

TLocalizador menorEnCadena(TLocalizador loc, TCadena cad) {
	assert((localizadorEnCadena(loc, cad)));
	TLocalizador aux;
	aux= loc;
	nat minimoN=natInfo(aux->dato);
	TLocalizador minimoL= loc;
	while (esLocalizador(aux)) {
		if (minimoN >natInfo(aux->dato)) {
			minimoN= natInfo(aux->dato);
			minimoL=aux;
		}
		aux=siguiente(aux,cad);
	}
	return minimoL;
}
			
			
	 
