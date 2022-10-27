#ifndef _lista_
#define _lista_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
	
	typedef struct No {
	int exp;		//expoente
	float coe;		//float caso o coeficiente receba numa fração(coeficiente pertence aos Reais)
	struct No *prox;	//proximo no da lista , o no aterior (*ant) nao é usado
	} No;	

	typedef struct lista{	
	struct No *prim;	//primeiro no da lista (termo de maior expoente da lista)
	struct No *ulti;	//ultimo no da lista (termo independente de expoente '0')
	} lista;

	typedef lista *polinomio;
/*---------------------------------------------*/

void aumenta_grau(polinomio p);
int ler_grau(polinomio p);
int ler_exp(No *n);
void normaliza_cima(polinomio p, int valor);
void normaliza_baixo(polinomio p);
polinomio cria_polinomio();
float potencia(float x, int p);
No *encontra_indice(polinomio p, int ind);

#endif
