/* 5140889 */
#include "../include/utils.h"
#include "../include/avl.h"
#include "../include/iterador.h"
#include "../include/pila.h"
#include "../include/colaAvls.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
struct repAvl { 
	nat dato;
	nat altura;
	nat cantidad;
	TAvl izq, der;
	};

TAvl crearAvl(){return NULL;}

bool estaVacioAvl(TAvl avl){return avl==NULL;}

static void rotarder( TAvl &avl){
	TAvl aux= avl->izq;
	TAvl aux2 =aux->der;
	
	aux->der=avl;
	avl->izq= aux2;

	if (alturaDeAvl(avl->izq)>  alturaDeAvl(avl->der))
		avl->altura= alturaDeAvl(avl->izq)+1;
	else 
		avl->altura=alturaDeAvl(avl->der)+1;
		
	if (alturaDeAvl(aux->izq)>  alturaDeAvl(aux->der))
			 aux->altura= alturaDeAvl(aux->izq)+1;
	else
		aux->altura= alturaDeAvl(aux->der)+1;
	
	avl=aux;

	}

static void rotarizq( TAvl &avl){
	TAvl aux= avl->der;
	TAvl aux2 =aux->izq;
	
	aux->izq=avl;
	avl->der= aux2;

	if (alturaDeAvl(avl->izq)>  alturaDeAvl(avl->der))
		avl->altura= alturaDeAvl(avl->izq)+1;
	else 
		avl->altura=alturaDeAvl(avl->der)+ 1;
		
	if (alturaDeAvl(aux->izq)>  alturaDeAvl(aux->der))
			 aux->altura= alturaDeAvl(aux->izq)+1;
	else
		aux->altura= alturaDeAvl(aux->der)+1;
	
	avl=aux;

	}
static nat max(nat a,nat b){
		nat maximo=0;
		if (a>b)
			maximo= a;
		else 
			maximo=b;
		return maximo;
	
	}
		
TAvl insertarEnAvl(nat elem, TAvl avl){
	assert(estaVacioAvl(buscarEnAvl(elem,avl)));
	if (avl==NULL){
		avl=new repAvl;
		avl->dato= elem;
		avl->izq=avl->der=NULL;
		avl->altura=1;
		avl->cantidad=1;
		}
	else {
		if(elem<avl->dato){
		
			avl->izq= insertarEnAvl(elem, avl->izq);
			avl->altura= max(alturaDeAvl(avl->izq),alturaDeAvl(avl->der))+1;
			avl->cantidad=cantidadEnAvl(avl->izq)+cantidadEnAvl(avl->der)+1;
				int aux= alturaDeAvl(avl->izq)- alturaDeAvl(avl->der);
				
			if (aux > 1){
				if (alturaDeAvl(avl->izq->izq)>alturaDeAvl(avl->izq->der))
					rotarder(avl);
					
				else{
					rotarizq(avl->izq);
					rotarder(avl);				
				}
								
			}
	
			

	
		}
		else {
			avl->der=insertarEnAvl(elem, avl->der);
			avl->altura= max(alturaDeAvl(avl->izq),alturaDeAvl(avl->der))+1;
			avl->cantidad=cantidadEnAvl(avl->izq)+cantidadEnAvl(avl->der)+1;
			int aux= alturaDeAvl(avl->izq)- alturaDeAvl(avl->der);
			if (aux<-1){
				if (alturaDeAvl(avl->der->der)>alturaDeAvl(avl->der->izq))
					rotarizq(avl);
				else{
					rotarder(avl->der);
					rotarizq(avl);				
				}
			
			}
			

		}	
	}
	return avl;
}
TAvl buscarEnAvl(nat elem, TAvl avl){
	if(avl==NULL)
	 return NULL;
	 else{
	if  (elem<avl->dato) 
		return buscarEnAvl(elem, avl->izq);
	else if (elem > avl->dato)
		return buscarEnAvl(elem,avl->der);
	else 
		return avl;
	
	}
}
nat raizAvl(TAvl avl){
	assert(! estaVacioAvl(avl));
	return avl->dato;
	
	}

TAvl izqAvl(TAvl avl){
	assert(! estaVacioAvl(avl));
	TAvl aux= avl->izq;
	
	return aux; 
	}

TAvl derAvl(TAvl avl){
	assert(! estaVacioAvl(avl));
	TAvl aux= avl->der;
	
	return aux;
	
	}


nat alturaDeAvl(TAvl avl){
	nat havl=0;
	if (avl!=NULL)
		havl=avl->altura;
	return havl;
}
	
nat cantidadEnAvl(TAvl avl){
	if (avl==NULL)
		return 0;
	else {
		nat contador = 1+ cantidadEnAvl(avl->izq) + cantidadEnAvl(avl->der);
		return contador;
		}
		
		}
	
	
static void aux(TAvl avl, TIterador &it){
	if (avl!=NULL) {
		aux(avl->izq, it);
		it=agregarAIterador(avl->dato,it); 
		aux(avl->der,it);
		}
}	
	
TIterador enOrdenAvl(TAvl avl){
		TIterador it= crearIterador();
		aux(avl, it);
		return it;
	}

static TAvl avlauxiliar(nat *elems,int in, int fin,TAvl avl){
	if(in> fin)
       return NULL;

	else { 
		int medio = (in +fin)/2;
		avl=new repAvl;
		avl->dato=(elems[medio]);
		avl->altura= 1;
		avl->cantidad= 1;
		avl->izq= avlauxiliar(elems,in, medio - 1,avl->izq);
		avl->der= avlauxiliar(elems, medio + 1,fin,avl->der);
		avl->altura= max(alturaDeAvl(avl->izq),alturaDeAvl(avl->der))+1;
		avl->cantidad= cantidadEnAvl(avl->izq)+cantidadEnAvl(avl->der)+1;
		return avl; 
		  }
		
}
TAvl arregloAAvl(nat *elems, nat n){
	TAvl avl=crearAvl();
	return avlauxiliar(elems,0,n-1,avl); 
	
	} 


static TAvl avlminAux(nat h, nat &cont,TAvl avl){
 if (h==0)
	return NULL;
 if (h>0){
	
	
	if (h==1){
		 avl= new repAvl;
		 avl->dato= cont+1;
		 avl->izq=NULL;
		 avl->der=NULL;
		 cont=cont+1;
		 avl->cantidad=1;
		 avl->altura=1;
		 }
	 else if(h>1) {
		 avl= new repAvl;
		 avl->izq=avlminAux(h-1,cont,avl->izq);
		 avl->dato=1+cont;
		 cont=cont+1;
		 
		avl->der= avlminAux(h-2,cont,avl->der);
		avl->altura= max(alturaDeAvl(avl->izq),alturaDeAvl(avl->der))+1;
		avl->cantidad= cantidadEnAvl(avl->izq)+cantidadEnAvl(avl->der)+1;
		 }
	
	}		 
	return avl;
	 }
	

TAvl avlMin(nat h){
TAvl avl= crearAvl();
nat cont=0;
	return avlminAux(h,cont,avl);
	}
	void imprimirAvl(TAvl avl){
		 if (avl!=NULL){
			 TColaAvls cola= crearColaAvls();
			  cola= encolar(avl,cola);
			 cola=encolar(NULL,cola);
			 nat N= cantidadEnAvl(avl)+alturaDeAvl(avl);
			 TPila pila= crearPila(N);
			
			 while (!estaVaciaColaAvls(cola)){
				 avl=frente(cola);
				 if (avl==NULL)
					pila= apilar(0,pila);
				else 
					pila = apilar(avl->dato, pila);
				 cola= desencolar(cola);
				 if(avl==NULL && !estaVaciaColaAvls(cola)){
					 cola= encolar(NULL,cola);
				}
				 if (avl!=NULL){ 
					if (avl->der!=NULL)
					 cola=encolar(avl->der,cola);
					if (avl->izq!=NULL)
						cola=encolar(avl->izq,cola);
					}				
				 
			 }
			 for(nat i=1; i<=N;i++){
				if (cima(pila)==0 && !estaLlenaPila(pila))
					printf("\n");
				if (cima(pila)!=0)
					printf("%i ",cima(pila));
				pila= desapilar(pila);
				 }
				 printf("\n");
			liberarColaAvls(cola);
			liberarPila(pila);
			 }
		
		}
void liberarAvl(TAvl avl){
	if(avl!=NULL){
		liberarAvl(avl->izq);
		liberarAvl(avl->der);
		delete avl;
		}
	}
