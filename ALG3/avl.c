#include <stdio.h>
#include <stdlib.h>
#include "APIavl.h"

int main(){
	int chave;
	char op;
	nodo *T;//O ponteiro T sempre irá apontar para a raiz
	T = NULL;

	while(scanf("%c",&op) != -1){ //Lê o char e confere se chegou no fim do arquivo (quando scanf retorna -1) 
		scanf("%d",&chave); //Lê a chave que será incluída
		if(op == 'i')
			T = incluiNodo(T, chave); //Função vai incluir o nodo e retornar um ponteiro apontando para a raiz
		if(op == 'r')
			T = excluiNodo(T,chave); //Idem para exclusão
	}
	imprimeAVL(T); //Função que imprime em ordem
}
