/* 5140889 */
#include "../include/conjunto.h"
#include "../include/cadena.h"
#include "../include/usoTads.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/grafo.h"
#include "../include/colaDePrioridad.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

bool pertenece(nat elem, TCadena cad){
	TLocalizador aux = inicioCadena(cad);
	while ((esLocalizador(aux)) && (natInfo(infoCadena(aux,cad))!= elem))
		aux=siguiente(aux,cad);
	return (esLocalizador(aux));
}

nat longitud(TCadena cad) {
	nat cont ;
	if  (esVaciaCadena(cad))
		cont=0;
	else {
		cont=0;
		TLocalizador aux = inicioCadena(cad);
		while (esLocalizador(aux)) {
			cont++;
			aux=siguiente(aux,cad);
		}
	}
	return cont;
}

bool estaOrdenadaPorNaturales(TCadena cad) {
	if (esVaciaCadena(cad))
		return true;
	else {
		TLocalizador aux = inicioCadena(cad);
		while ((esLocalizador(siguiente(aux,cad))) && (natInfo(infoCadena(aux,cad))<= natInfo(infoCadena(siguiente(aux,cad),cad))))//si  no me acepta aux->siguiente porbar con siguiente(aux,cad) 
			aux=siguiente(aux,cad);
	
	
	return (!esLocalizador(siguiente(aux,cad)));
	}
}

bool hayNatsRepetidos(TCadena cad){
	bool res;
	if (esVaciaCadena(cad))
		res= false;
	else {
	TLocalizador aux = inicioCadena(cad);
	TLocalizador aux2;
	res=false;
	while ((esLocalizador(aux)) && (!res)) {
		aux2= siguiente(aux,cad);
		while ((esLocalizador(aux2)) &&  (natInfo(infoCadena(aux,cad))!= natInfo(infoCadena(aux2,cad))))
			aux2=siguiente(aux2,cad);
		if (esLocalizador(aux2))
			res=true;
		aux=siguiente(aux,cad);	
	}
	}	
return res;
}

bool sonIgualesCadena(TCadena c1, TCadena c2) {
	bool res;
	res=false;
	if ((esVaciaCadena(c1)) && (esVaciaCadena(c2)))
		res= true;
	else if (longitud(c1)== longitud(c2)) {
		TLocalizador aux,aux2;
		aux= inicioCadena(c1);
		aux2=inicioCadena(c2);
		while ((esLocalizador(aux)) && sonIgualesInfo(infoCadena(aux,c1),infoCadena(aux2,c2))){
			aux=siguiente(aux,c1);
			aux2=siguiente(aux2,c2);
	}
	res= (!esLocalizador(aux));	
}
return res;
	
}

TCadena concatenar(TCadena c1, TCadena c2) {
	TCadena nueva;
	if (esVaciaCadena(c1)) {
		if (!esVaciaCadena(c2)) 
			nueva = copiarSegmento(inicioCadena(c2),finalCadena(c2),c2);
		else nueva= crearCadena();
	}
    else {
	nueva = copiarSegmento(inicioCadena(c1),finalCadena(c1),c1);
		if (!esVaciaCadena(c2))	{
			insertarSegmentoDespues(copiarSegmento(inicioCadena(c2),finalCadena(c2),c2),finalCadena(nueva),nueva);
		}
	}
	return nueva;
}

TCadena ordenar(TCadena cad){
	assert(!hayNatsRepetidos(cad));
	if (!esVaciaCadena(cad)){
		TLocalizador aux = inicioCadena(cad);
		TLocalizador cursor;
		while (esLocalizador(aux)) {
			cursor = menorEnCadena(aux,cad);
			if (cursor!= aux)
				intercambiar(aux,cursor,cad);
			aux=siguiente(aux,cad);	
		}	
	}
return cad;
}

TCadena cambiarTodos(nat original, nat nuevo, TCadena cad) {
	if (!esVaciaCadena(cad)) {
		TLocalizador aux;
		aux=inicioCadena(cad);
		TInfo valor;
		while (esLocalizador(aux)){
			if (natInfo(infoCadena(aux,cad))== original){
			valor= crearInfo(nuevo,realInfo(infoCadena(aux,cad)));
			liberarInfo(infoCadena(aux,cad));
			cambiarEnCadena(valor,aux,cad);
			}
		aux=siguiente(aux,cad);
		}
	}
	return cad;
}

TCadena subCadena(nat menor, nat mayor, TCadena cad){
	assert ((estaOrdenadaPorNaturales(cad)) && (menor <= mayor) && (pertenece(menor, cad)) && (pertenece(mayor, cad)));
	TLocalizador aux= inicioCadena(cad);
	TCadena nueva = crearCadena();
	while (esLocalizador(aux)){
		if ((natInfo(infoCadena(aux,cad))>= menor) && (natInfo(infoCadena(aux,cad))<=mayor))
			insertarAlFinal(copiaInfo(infoCadena(aux,cad)),nueva);
		aux=siguiente(aux,cad);
		
	}
return nueva;
}

static TCadena ayudaNivel(nat l, TBinario b, TCadena cad, nat cont,nat altura){
	if (esVacioBinario(b))
		return cad;
	else if (l> altura)
		return cad;
	else{
		if (cont<l){
		cad = ayudaNivel(l,izquierdo(b),cad,cont+1,altura);
		cad = ayudaNivel(l,derecho(b),cad,cont+1,altura);
		}
		else 
		cad=insertarAlFinal(copiaInfo(raiz(b)),cad);				
	}
	return cad;
}

TCadena nivelEnBinario(nat l, TBinario b) {
	assert (l > 0);
	TCadena cad = crearCadena();
	return ayudaNivel(l,b,cad,1,alturaBinario(b));
	
	}



static bool caminoAuxiliar ( TBinario b,TCadena cad,TLocalizador aux){
if(b==NULL || aux==NULL)
return false;
else if ((natInfo(infoCadena(aux,cad))==natInfo(raiz(b))) && (izquierdo(b) == NULL && derecho(b) == NULL) && (!esLocalizador(siguiente(aux,cad))))
 return true;
 
 else 
 return (natInfo(infoCadena(aux,cad)) == natInfo(raiz(b))) && (caminoAuxiliar(izquierdo(b),cad,siguiente(aux,cad)) || (caminoAuxiliar(derecho(b),cad,siguiente(aux,cad)))) ;
}
bool esCamino (TCadena c, TBinario b ) {
if(inicioCadena(c) == NULL && b == NULL) {return true ;} 
else {
	TLocalizador aux=inicioCadena(c);
	return caminoAuxiliar (b,c,aux);
}
}
TConjunto interseccionDeConjuntos(TConjunto c1, TConjunto c2){
	 TConjunto c3= diferenciaDeConjuntos(c1,c2);
	 TConjunto c4= diferenciaDeConjuntos(c1,c3);
	 liberarConjunto(c3);
	 return c4;
	}
	
	
static void auxiliar(nat v ,TGrafo g, ArregloBools &array,TIterador iter){
	iter=reiniciarIterador(iter);
	if (estaDefinidaActual(iter)){
		while (estaDefinidaActual(iter)){ 
			while (estaDefinidaActual(iter) && array[actualEnIterador(iter)]==true)
				iter=avanzarIterador(iter);
			if (estaDefinidaActual(iter)){
				array[actualEnIterador(iter)]=true;
				auxiliar(v,g,array,vecinos(actualEnIterador(iter),g));
				iter=avanzarIterador(iter);
			}
		}
		liberarIterador(iter);
	}
	else 
	liberarIterador(iter);
}

ArregloBools accesibles(nat v, TGrafo g){
	ArregloBools array= new bool[cantidadVertices(g)+1];
	for (nat i=1;i<=cantidadVertices(g);i++)
		array[i]=false;
	array[v]=true;
	TIterador iter= vecinos(v,g);
	auxiliar(v,g,array,iter);
	return array;
}
static void longitudAux(nat v,TIterador iter,TColaDePrioridad &cp,TGrafo g,nat &prio,ArregloDoubles &array){

iter=reiniciarIterador(iter);
while (estaDefinidaActual(iter)){
	
	if (array[actualEnIterador(iter)]==DBL_MAX){                  
		double aux= distancia(prio,actualEnIterador(iter),g)+array[prio];
		if (!estaEnCP(actualEnIterador(iter),cp))
			cp =insertarEnCP(actualEnIterador(iter),aux,cp);
	
	
	if(aux< prioridad(actualEnIterador(iter),cp))
		actualizarEnCP(actualEnIterador(iter),aux,cp);
	
	}
	iter=avanzarIterador(iter);
}


while(!estaVaciaCP(cp)){
array[prioritario(cp)]=prioridad(prioritario(cp),cp);
prio=prioritario(cp);
cp=eliminarPrioritario(cp); 
longitudAux(v,vecinos(prio,g),cp,g,prio,array);
}
liberarIterador(iter);
}

ArregloDoubles longitudesCaminosMasCortos(nat v, TGrafo g){
	ArregloDoubles array= new double[cantidadVertices(g)+1];
	for (nat i=1;i<=cantidadVertices(g);i++)
		array[i]=DBL_MAX;
	array[v]=0;
	TColaDePrioridad cp= crearCP(cantidadVertices(g));
	TIterador iter= vecinos(v,g);
	longitudAux(v,iter,cp,g,v,array);
	liberarCP(cp);
	return array;
	
	
	}
