/* 5140889 */
#include "../include/conjunto.h"
#include "../include/avl.h"
#include "../include/iterador.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct repConjunto {
	TAvl avl;
	};
TConjunto crearConjunto(){
	TConjunto c= new repConjunto;
	c->avl=NULL;
	return c;
	}

TConjunto singleton(nat elem){
	TConjunto c= crearConjunto();
	c->avl= insertarEnAvl(elem,c->avl);
	return c;
	}



static void unionDeIteradores(TIterador iter1, TIterador iter2,TIterador &iter3){

while (estaDefinidaActual(iter1) && estaDefinidaActual(iter2)){
	if (actualEnIterador(iter1)>actualEnIterador(iter2)){
		iter3=agregarAIterador(actualEnIterador(iter2),iter3);
		iter2=avanzarIterador(iter2);
	}
	else if (actualEnIterador(iter2)>actualEnIterador(iter1)){
		iter3=agregarAIterador(actualEnIterador(iter1),iter3);
		iter1=avanzarIterador(iter1);
		
		}
	else {
		iter3=agregarAIterador(actualEnIterador(iter2),iter3);
		iter1=avanzarIterador(iter1);
		iter2=avanzarIterador(iter2);
		}
	
}
if (estaDefinidaActual(iter1))
	while (estaDefinidaActual(iter1)){
		agregarAIterador(actualEnIterador(iter1),iter3);
		avanzarIterador(iter1);
	}
else if (estaDefinidaActual(iter2)){
	while (estaDefinidaActual(iter2)){
		agregarAIterador(actualEnIterador(iter2),iter3);
		avanzarIterador(iter2);
	} 
	}

}

static void iteradorArreglo(nat* &array,TIterador iter){ 
	iter= reiniciarIterador(iter);
	nat i=0;
	while (estaDefinidaActual(iter)){
	array[i]=actualEnIterador(iter);
	iter= avanzarIterador(iter);
	i++;	
}
	}

static nat cantidadDeElementos(TIterador iter){
	nat cont =0;
	iter=reiniciarIterador(iter);
	while (estaDefinidaActual(iter)) {
		cont++;
		avanzarIterador(iter);
		}		
	return cont;
	
	}

TConjunto unionDeConjuntos(TConjunto c1, TConjunto c2){
TIterador iter1= iteradorDeConjunto(c1);
TIterador iter2= iteradorDeConjunto(c2);
iter2=reiniciarIterador(iter2);
iter1=reiniciarIterador(iter1);
TIterador iter3= crearIterador();
unionDeIteradores(iter1,iter2,iter3);
nat n= cantidadDeElementos(iter3);
nat*array= new nat[n];
iteradorArreglo(array,iter3);
liberarIterador(iter1);
liberarIterador(iter2);
liberarIterador(iter3);
TConjunto conjunto= arregloAConjunto(array,n);
	delete [] array;
	return conjunto; 
}



static void diferenciaDeIteradores(TIterador iter1, TIterador iter2,TIterador &iter3){

while (estaDefinidaActual(iter1) && estaDefinidaActual(iter2)){
	if (actualEnIterador(iter1) < actualEnIterador(iter2)){
	iter3=	agregarAIterador(actualEnIterador(iter1), iter3);
		iter1=avanzarIterador(iter1);
	}
	else if (actualEnIterador(iter2) <actualEnIterador(iter1)){
		
		iter2=avanzarIterador(iter2);
	}
	else {
		iter1=avanzarIterador(iter1);
		iter2=avanzarIterador(iter2);
		}	
	}
	while (estaDefinidaActual(iter1)){
		iter3=agregarAIterador(actualEnIterador(iter1), iter3);
		iter1=avanzarIterador(iter1);
	}

}

TConjunto diferenciaDeConjuntos(TConjunto c1, TConjunto c2){
	 
	TIterador iter1= iteradorDeConjunto(c1);
	TIterador iter2= iteradorDeConjunto(c2);
	iter2=reiniciarIterador(iter2);
	iter1=reiniciarIterador(iter1);
	TIterador iter3= crearIterador();
	diferenciaDeIteradores(iter1,iter2,iter3);
	nat n=cantidadDeElementos(iter3);
	nat*array= new nat[n];
	iteradorArreglo(array, iter3);
	liberarIterador(iter1);
	liberarIterador(iter2);
	liberarIterador(iter3);
	TConjunto conjunto= arregloAConjunto(array,n);
	delete [] array;
	return conjunto;
	}


static bool perteneceAvl(nat elem, TAvl avl){
	if (estaVacioAvl(avl))
		return false;
	
	else if (elem < raizAvl(avl))
		return perteneceAvl(elem,izqAvl(avl));
	else if (elem > raizAvl(avl))
		return perteneceAvl(elem,derAvl(avl));
	else {
		return true; 
		
	}
}
bool perteneceAConjunto(nat elem, TConjunto c){
	return perteneceAvl(elem, c->avl);
		}

bool estaVacioConjunto(TConjunto c){
		return estaVacioAvl(c->avl);
		
		}
nat cardinalidad(TConjunto c){return cantidadEnAvl(c->avl);}
	
	
TConjunto arregloAConjunto(nat *elems, nat n){
	
TConjunto c =crearConjunto();
 c->avl=arregloAAvl(elems, n); 
return c;
}
TIterador iteradorDeConjunto(TConjunto c){
	TIterador iter = enOrdenAvl(c->avl);
	return iter;
	
	}
void liberarConjunto(TConjunto c){
	liberarAvl(c->avl);
	delete c;
	}
