#ifndef APIavl_h_
#define APIavl_h_
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
	int ht; //Guarda a altura do nodo
	int chave;
	struct nodo *esq;//Implementaçã com ponteiros para esquerda, direita e pai respectivamente
	struct nodo *dir;
	struct nodo *pai;
}nodo;
/*------------------------------------------------------------*/
nodo *incluiNodo(nodo *T, int chave); //Funçôes utilizadas
nodo *insereNodo(nodo *p, int chave);
nodo *excluiNodo(nodo *T, int chave);
nodo *buscaEx(nodo *T, int chave);
nodo *busca(nodo *T, int chave);
void rotacaoDireita(nodo *x);
void rotacaoEsquerda(nodo *x);
nodo *balanceia(nodo *p);
int calculaAltura(nodo *x);
void imprimeAVL(nodo *T);
int contaNivel(nodo *T);
int fator(nodo *p);

#endif // APIavl_H_
