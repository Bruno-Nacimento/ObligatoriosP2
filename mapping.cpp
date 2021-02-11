/* 5140889 */
#include "../include/utils.h"
#include "../include/mapping.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
struct nodo{
	nat clave;
	double valor;
	nodo*sig;
};

struct repMap{
	nodo** hash;
	nat maxmap;
	nat cantelem;
	};

TMapping crearMap(nat M){
	TMapping map= new repMap;
	map->hash= new nodo*[M];
	for (nat i=0;i<M; i++)
		map->hash[i]=NULL;
	map->maxmap=M;
	map->cantelem=0;
	return map;
	
	}
	
TMapping asociarEnMap(nat clave, double valor, TMapping map){
	assert(!estaLlenoMap(map) && !existeAsociacionEnMap(clave, map));
	nat i= clave % map->maxmap;
	nodo* aux= new nodo;
	aux->clave=clave;
	aux->valor=valor;
	aux->sig= map->hash[i];
	map->hash[i]=aux;
	map->cantelem++;
	return map;
	
	}

TMapping desasociarEnMap(nat clave, TMapping map){
	assert (existeAsociacionEnMap(clave, map));
	nat i= clave % map->maxmap;
	if (map->hash[i]->clave== clave){
		nodo* borrador= map->hash[i];
		map->hash[i]=map->hash[i]->sig;
		delete borrador;
		map->cantelem--;
		}
	else{ 
		nodo* aux= map->hash[i];
		while (aux->sig!=NULL){
			if(aux->sig->clave==clave){
				nodo* borrador= aux->sig;
				aux->sig=aux->sig->sig;
				delete borrador;
				map->cantelem--;
			}
		else
			aux=aux->sig;
	}
	}
	return map;
}
bool existeAsociacionEnMap(nat clave, TMapping map){
	nat i= clave%map->maxmap;
	nodo* aux= map->hash[i];
	while ((aux!= NULL) && (clave != aux->clave))
		aux=aux->sig;
	return aux!=NULL;
	}

double valorEnMap(nat clave, TMapping map){
	assert(existeAsociacionEnMap(clave,map));
	nat i = clave% map->maxmap;
	nodo*aux= map->hash[i];
	while (clave != aux->clave)
		aux=aux->sig;
	return aux->valor;
	
	}
bool estaLlenoMap(TMapping map){
	return map->maxmap==map->cantelem;
	}
void liberarMap(TMapping map){
for (nat i=0;i<map->maxmap;i++){
	while (map->hash[i]!=NULL){
		nodo*borrar= map->hash[i];
		map->hash[i]=map->hash[i]->sig;
		delete borrar;
	}
	 delete map->hash[i];
	}
	delete[] map->hash;
	delete map;
	}
