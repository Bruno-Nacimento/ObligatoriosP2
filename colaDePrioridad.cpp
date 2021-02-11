/* 5140889 */
#include "../include/utils.h"
#include "../include/colaDePrioridad.h"
#include "../include/info.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct infor{
nat elemento;
double prio;
};


struct repCP {
	infor* array;
	nat tope;
	nat maximo;
	nat* array2;
	};
	
	
	TColaDePrioridad crearCP(nat N){
		TColaDePrioridad cp= new repCP;
	cp->tope=0;
	cp->maximo=N;
	cp->array = new infor[N+1];
	cp->array2= new nat[N+1];
	for(nat i=0; i<=N;i++)
	 cp->array2[i]=0;
	return cp;
	
	}
	
nat rangoCP(TColaDePrioridad cp){
	return cp->maximo;
}
	
static void filtradoAscendente ( TColaDePrioridad &cp,nat pos){ 
	if ((pos>1) && (cp->array[pos/2].prio > cp->array[pos].prio)){ 
	infor aux=cp->array[pos];
	cp->array[pos]=cp->array[pos/2];
	cp->array[pos/2]=aux;
	cp->array2[cp->array[pos/2].elemento]=pos/2;
	cp->array2[cp->array[pos].elemento]=pos;
	filtradoAscendente(cp,pos/2);	
		}
	}


TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp){
	if (cp->tope<cp->maximo){
	cp->tope=cp->tope+1; 
	cp->array[cp->tope].elemento=elem;
	cp->array[cp->tope].prio=valor;
	cp->array2[elem]=cp->tope;
	filtradoAscendente(cp,cp->tope);
	}
	return cp;
	}
	
	
	bool estaVaciaCP(TColaDePrioridad cp){
	return cp->tope==0;
	}
	
	nat prioritario(TColaDePrioridad cp){
	return cp->array[1].elemento; 
	}
	
	
static void filtradoDescendente(TColaDePrioridad &cp, nat n, nat pos) {
if (2*pos<=n){
nat aux=2*pos;
if ((aux+1<=n) && (cp->array[aux+1].prio<cp->array[aux].prio))
	aux++;
if(cp->array[aux].prio < cp->array[pos].prio) {
infor inter=cp->array[pos];
cp->array[pos] =cp->array[aux];
cp->array[aux]=inter;
cp->array2[cp->array[pos].elemento]=pos;
cp->array2[cp->array[aux].elemento]=aux;
pos=aux;
filtradoDescendente(cp,n,pos);
}
}
} 
TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp){
	

	if (cp->tope>0){
		cp->array2[cp->array[1].elemento]=0;
		cp->array[1]=cp->array[cp->tope];
		if (cp->tope==1)
		cp->array2[cp->array[cp->tope].elemento]=0;
		else {
			cp->array2[cp->array[cp->tope].elemento]=1;
		}
		cp->tope--;
		if (cp->tope>1)
			filtradoDescendente(cp,cp->tope,1);
		}
	return cp;
}
bool estaEnCP(nat elem, TColaDePrioridad cp){
	
	if (cp->tope>0){
		if (cp->array2[elem]>0) 
		return true;
		else 
			return false;
		}
	else 
		return false;
	}



double prioridad(nat elem, TColaDePrioridad cp){
	return cp->array[cp->array2[elem]].prio; 
	}
	
	TColaDePrioridad actualizarEnCP(nat elem, double valor, TColaDePrioridad cp){
	nat aux=cp->array2[elem];
	double aux2= cp->array[aux].prio;
	
	cp->array[aux].elemento=elem; 
	cp->array[aux].prio=valor; 
	if (aux2>valor)
		filtradoAscendente(cp,aux);
	else if (aux2<valor)
	filtradoDescendente(cp,cp->tope,aux);
	return cp;
	}
	
	void liberarCP(TColaDePrioridad cp){
	delete [] cp->array;
	delete [] cp->array2;
	delete cp;
	}
