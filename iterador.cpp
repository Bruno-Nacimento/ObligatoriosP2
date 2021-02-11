/* 5140889 */

#include "../include/utils.h"
#include "../include/iterador.h"

#include <assert.h>
#include <stdlib.h>

 typedef struct nodoIt *PNodoIt;
 struct nodoIt {
	 nat elem;
	 PNodoIt sig;
 };
 struct repIterador {
	 PNodoIt inicio, fin, actual;
	 bool bloqueado;
 };




TIterador crearIterador(){
TIterador res=new repIterador;
res->actual=res->fin=res->inicio=NULL;
res->bloqueado=false;
return res;
}

TIterador agregarAIterador(nat elem, TIterador iter){
	if (!iter->bloqueado) {
		PNodoIt aux = new nodoIt;
		aux->elem= elem;
		aux->sig= NULL;
		if (iter->inicio==NULL){
			iter->inicio= aux;
			iter->fin= iter->inicio;
		}
		else {
			iter->fin->sig=aux;
			iter->fin=iter->fin->sig;	
		}
	}
return iter;
}

TIterador reiniciarIterador(TIterador iter){
	if (iter->inicio!=NULL){ //si no me llega a aceptar esto podrai fijarme si el inicio es NULL o no.
		iter->actual=iter->inicio;
	}
	iter->bloqueado=true;
	return iter;
}

TIterador avanzarIterador(TIterador iter){
	if (estaDefinidaActual(iter)){
			if (iter->actual==iter->fin)
				iter->actual=NULL;
			else
			iter->actual=iter->actual->sig;
			 
		}
	return iter;
}



nat actualEnIterador(TIterador iter){
	assert(estaDefinidaActual(iter));
		return (iter->actual->elem);
	}

bool estaDefinidaActual(TIterador iter){return (iter->actual!=NULL);}


void liberarIterador(TIterador iter){
		while (iter->inicio!=NULL){
			PNodoIt borrar=iter->inicio;
			iter->inicio=iter->inicio->sig;
			delete borrar;
	
		}
	delete iter;
}

