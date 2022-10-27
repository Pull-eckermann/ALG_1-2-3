#include "lista.h"
#include "polinomio.h"
#include <stdio.h>
//---------------------------------------------------------------------
//------------------------------Funcoes a parte------------------------
//---------------------------------------------------------------------
void aumenta_grau(polinomio p){
//adiciona uma cadeia de um grau maior e com coef==0

	No *aux;
	aux=malloc(sizeof(No));
	aux->prox=p->prim;	//novo grau recebe & do antigo grau maior
//atualiza os valores dentro do no
	aux->exp=(p->prim->exp)+1;	//novo_exp=antigo_exp+1
	aux->coe=0;		//0*x^(antigo exp+1)
	p->prim=aux;		//novo maior grau atualizado
}
/*--------------------------------------------------*/
int ler_grau(polinomio p){
//retorna o expoente do termo de maior grau

	return(p->prim->exp);	
}
/*--------------------------------------------------*/
int ler_exp(No *n){
//retorna o expoente do termo/no atual

	return(n->exp);	
}
/*--------------------------------------------------*/
void normaliza_cima(polinomio p,int valor){	
//aumenta ate o grau ser = ao valor do parametro(novos graus tem coef == 0)
// nao fazer nada caso p tenha grau menor igual a parametro

	int p_grau;
	p_grau=ler_grau(p);	
//caso valor seja menor ou igual ao grau de p, nada acontece.
	for(p_grau;p_grau<valor;p_grau++){
		aumenta_grau(p);		
	}
}
/*--------------------------------------------------*/
void normaliza_baixo(polinomio p){ 
//remove seus maiores graus(ate termo independente) caso seu coe seja 0
//remove os espoente de maior grau se seus coeficientes forem zeros

	No *aux, *seguinte;
	aux=p->prim;		//coef de maior grau do polinomio
	seguinte=aux->prox;	//prox elemento a ser apagado
	while(seguinte!=NULL){	//percorre e para no termo independente
		if(aux->coe!=0){
			p->prim=aux;		//nao é mais possivel diminuir o grau
			break;	
		}else{				//coef==0
			free(aux);		//apaga o atual
			aux=seguinte;		//aux recebe prox elemento
			seguinte=aux->prox;	//prepara proximo teste
		}
	}

}
/*--------------------------------------------------*/
polinomio cria_polinomio(){
//cria um polinomio com o termo independente (e seu exp)==0

	polinomio p;
	No *aux;

	p=malloc(sizeof(polinomio));	//cria lista
	aux=malloc(sizeof(No));		//cria primeiro no da lista
	p->prim=p->ulti=aux;		//aponta para termo independente zerado
	aux->exp=aux->coe=0;		//zera o termo independente
	aux->prox = NULL;		//termo independente aponta para NULL

	return(p);
}
/*--------------------------------------------------*/
float potencia(float x, int p){
//funcao recursiva que calcula potencia	
	if(p == 0)
		return(1.0);	
	return(x * potencia(x,p - 1));
}
/*--------------------------------------------------*/
No *encontra_indice(polinomio p, int ind){
//dado que p contem o indice ind, a função retorna o endereço do no correspondente ao indice


	No *aux;
	aux=p->prim;			//primeiro no da lista
	while(aux!=NULL){		//percorre o polinomio
		if (ler_exp(aux)==ind)	//exp encontrado
			break;
		aux=aux->prox;		//senao for o expoente,entao continua a busca
	}
	if(aux==NULL)	printf("Indice %d não encontrado, retornando nulo\n",ind);//mensagem de erro
	return(aux);

}


