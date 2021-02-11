/* 5140889 */
#include "../include/utils.h"
#include "../include/avl.h"
#include "../include/iterador.h"
#include "../include/mapping.h"
#include "../include/grafo.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct repGrafo{ 
	TMapping map;
	nat maximo;
	TAvl* array;
	};
	
	
TGrafo crearGrafo(nat N, nat M){
	TGrafo grafo= new repGrafo;
	grafo->map= crearMap(M);
	grafo->maximo=N;
	grafo->array= new TAvl[N+1];
	for (nat i=1; i<=N; i++)
		grafo->array[i]=NULL;
	return grafo;
	}
	
static nat max(nat a,nat b){
		nat maximo=0;
		if (a>b)
			maximo= a;
		else 
			maximo=b;
		return maximo;
	
	}	
	
	static nat min(nat a, nat b){
			nat minimo=0;
		if (a<b)
			minimo= a;
		else 
			minimo=b;
		return minimo;
		}
	
static nat F(nat v1,nat v2,TGrafo g){
	return (min(v1,v2)-1)*g->maximo + (max(v1,v2)-1);
	
	
	}	
	
	
nat cantidadVertices(TGrafo g){
	return g->maximo;
	
	} 
	bool hayMParejas(TGrafo g){
		return estaLlenoMap(g->map);
		}
		
		TGrafo hacerVecinos(nat v1, nat v2, double d, TGrafo g){
			g->map=asociarEnMap(F(v1,v2,g),d,g->map);
			g->array[v1]= insertarEnAvl(v2,g->array[v1]);
			g->array[v2]= insertarEnAvl(v1,g->array[v2]);
			return g;
			}
		
	
		bool sonVecinos(nat v1, nat v2, TGrafo g){
			return existeAsociacionEnMap(F(v1,v2,g),g->map); 
			}
		
double distancia(nat v1, nat v2, TGrafo g){ 
	return valorEnMap(F(v1,v2,g),g->map);
	
	}

TIterador vecinos(nat v, TGrafo g){
	TIterador iter=enOrdenAvl(g->array[v]);
	return iter;
	}

void liberarGrafo(TGrafo g){ 
	liberarMap(g->map);
	for (nat i=1;i<=g->maximo;i++)
		liberarAvl(g->array[i]);
	delete [] g->array;
	delete g;
	}

