
/* 5140889 */

#include "../include/binario.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct repBinario {
	TInfo dato;
	TBinario izq;
	TBinario der;
};

TBinario crearBinario() { return NULL;}


TBinario insertarEnBinario(TInfo i, TBinario b){
	if (b== NULL) {
		b = new repBinario;
		b->dato= i;
		b->izq= NULL;
		b->der= NULL;
	}
	else if  (natInfo(i) < natInfo(b->dato))
		b->izq = insertarEnBinario(i, b->izq);
	else if (natInfo(i)> natInfo(b->dato))
		b->der = insertarEnBinario(i,b->der);
	return b;
}
TInfo mayor(TBinario b){
	assert (! esVacioBinario(b));
		if (b->der==NULL)
			return b->dato;
	return mayor(b->der);
}

TBinario removerMayor(TBinario b) {
		assert (! esVacioBinario(b));
	if(b==NULL)
		return b;
	else if (natInfo(mayor(b))!= natInfo(b->dato))
			b->der= removerMayor(b->der);
	else {
		TBinario borrar= b;
		b=b->izq;
		delete borrar;
	}
	return b;
	} 


TBinario removerDeBinario(nat elem, TBinario b) {
	assert(!esVacioBinario(buscarSubarbol(elem, b)));
	if (b==NULL) 
		return b;
	else if(elem< natInfo(b->dato))
	 b->izq=removerDeBinario(elem, b->izq);
	else if (elem > natInfo(b->dato))
		b->der=removerDeBinario(elem,b->der);
	else {
		if (b->der == NULL) {
			TBinario borrar=b;
			b=b->izq;
			liberarInfo(borrar->dato);
			delete borrar; 
		}
		else if (b->izq == NULL) {
			TBinario borrar=b;
			b=b->der;
			liberarInfo(borrar->dato);
			delete borrar;
		}
		else { 
			liberarInfo(b->dato);
			b->dato = copiaInfo(mayor(b->izq));
			b->izq=removerDeBinario(natInfo(b->dato),b->izq);
			
}
}
 return b; 
}
void liberarBinario(TBinario b){
	if (b!= NULL){
		if ((b->der==NULL) && (b->izq==NULL)){
			liberarInfo(b->dato);
			delete b;
		}
		else{
			liberarBinario(b->izq);
			liberarBinario(b->der);
			liberarInfo(b->dato);
			delete b;
		}
	}
}

	

bool esVacioBinario(TBinario b){
	return (b==NULL);
}

static int avlaux(TBinario b,bool &balanceado){
	if ((b==NULL) || (!balanceado))
		return 0;
	int lizq= avlaux(b->izq,balanceado);
	int lder= avlaux(b->der,balanceado);
	if (abs(lizq-lder)>1)
		balanceado=false;
	if (lizq> lder)
		return lizq+1;
	else 
		return lder +1;
}
	
bool esAvl(TBinario b) {
	bool balanceado=true;
	avlaux(b,balanceado);
	return balanceado;
	}



TInfo raiz(TBinario b){
	assert(! esVacioBinario(b));
	return b->dato;
}

TBinario izquierdo(TBinario b){
	assert(! esVacioBinario(b));
	TBinario aux= b->izq;
	
	return aux; 
}

TBinario derecho(TBinario b) {
	assert(! esVacioBinario(b));
	TBinario aux= b->der;
	
	return aux; 
}

TBinario buscarSubarbol(nat elem, TBinario b){
	if(b==NULL)
	 return NULL;
	 else{
	if  (elem< natInfo(b->dato)) 
		return buscarSubarbol(elem, b->izq);
	else if (elem > natInfo(b->dato))
		return buscarSubarbol(elem,b->der);
	else 
		return b;	
}
}





nat alturaBinario(TBinario b){
	if (b==NULL)
		return 0;
	else{ 
		nat alturaizquierda = alturaBinario(b->izq);
		nat alturaderecha = alturaBinario (b->der);
		if (alturaderecha > alturaizquierda)
			return alturaderecha+1;
		else 
			return alturaizquierda + 1;
		}
		
	} 

nat cantidadBinario(TBinario b) {
	if (b==NULL)
		return 0;
	else {
		nat contador = 1+ cantidadBinario(b->izq) + cantidadBinario(b->der);
		return contador;
	}
}
static void sumaDeUltimos(nat &i, TBinario b, double &suma){
		if (!esVacioBinario(b))
			if (i!=0){
				sumaDeUltimos(i,b->der,suma);
				if((realInfo(b->dato)>0) && (i>0)){
					suma=suma +realInfo(b->dato);
					i=i-1;
				}
				sumaDeUltimos(i,b->izq,suma);
				
}
}
double sumaUltimosPositivos(nat i, TBinario b){
double suma=0;
sumaDeUltimos(i,b,suma);
return suma;
}
 

static void  auxiliar3(TBinario b, TCadena &ordenada) {
	
	if (b!=NULL){
	auxiliar3(b->izq,ordenada);
	ordenada=insertarAlFinal(copiaInfo(b->dato),ordenada);
	auxiliar3(b->der,ordenada); 
	 }
 }
TCadena linealizacion(TBinario b){
	TCadena cad = crearCadena();
	auxiliar3(b,cad);
		return cad;
	}

TBinario menores(double cota, TBinario b) {
		TBinario resultado;
		if (b==NULL)
		resultado=NULL;
		else {
		TBinario menorizq = menores(cota, b->izq);
		TBinario menorder= menores(cota, b->der);
		if (realInfo(b->dato)< cota){
			resultado= new repBinario;
			 resultado->dato= copiaInfo(b->dato);
			 resultado->izq=menorizq;
			 resultado->der=menorder;
		}
		else if (menorizq==NULL)
			resultado=menorder;
		else if (menorder==NULL)
			resultado=menorizq;
		else{
			TInfo elmayor= mayor(menorizq);
			removerMayor(menorizq);
			resultado= new repBinario;
			resultado->dato= elmayor;
			resultado->izq= menorizq;
			resultado->der = menorder;
		}
			
	}
	return resultado;
}
static void auxiliar(TBinario b,nat cont){
	if ((b->izq==NULL) && (b->der==NULL)){
					for (nat i=0; i<cont; i++)
				printf("-");
					printf("(%d,%.2f)\n",natInfo(b->dato),realInfo(b->dato));}
	else if (b->izq==NULL){
		auxiliar(b->der,cont+1);
		for (nat i=0; i<cont; i++)
				printf("-");
		printf("(%d,%.2f)\n",natInfo(b->dato),realInfo(b->dato));
		}
	else if (b->der==NULL){
		for (nat i=0; i<cont; i++)
				printf("-");
		printf("(%d,%.2f)\n",natInfo(b->dato),realInfo(b->dato));
		auxiliar(b->izq,cont+1);
		}
	else {
			auxiliar(b->der,cont+1);
			for (nat i=0; i<cont; i++)
				printf("-");
			printf("(%d,%.2f)\n",natInfo(b->dato),realInfo(b->dato));
			auxiliar(b->izq,cont+1);
		}
				
}
 void imprimirBinario(TBinario b){
	printf("\n");
	if (b!=NULL)
		auxiliar(b,0);
}
