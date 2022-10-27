#include "polinomio.h"

//apenas as funcoes principais do trabalho
/*----------------------------------------------------------------------------*/
polinomio constroi_polinomio(char *s) {

	polinomio p;
	No *elem;
	int tam, j, expo;
	float coef = 0, coef_parcial = 0;

	p = cria_polinomio();
	elem = p->prim; 	//Variável usada para navegar sobre p
	tam = strlen(s);
	j = tam - 1;  		//j vai receber o tamanho - 1, pois representa o último elemento da string

	while(j >= 0){  //Percorre a string de trás pra frente
		expo = 0;		
		while((s[j] != ' ') && (j >= 0)){ //Laço que faz ser possível ler numeros com mais dígitos	
			if((s[j] != ' ') && (s[j] != '-')){

				coef_parcial = (float) s[j];
				coef_parcial = coef_parcial - 48.0; //Operação para receber o valor que quero pela ASCII
				coef_parcial = coef_parcial * (potencia(10,expo));

				coef = coef + coef_parcial;	
			}
			expo++;	 //Aumenta o expoente da potencia de 10, para as casas decimais.			
			j--;
		}
		if(s[j + 1] == '-'){ //Confere se é um char que representa sinal negativo
				coef = -coef; //Transforma em negativo
		}				
		elem->coe = coef;
		aumenta_grau(p); //Aumenta o grau colocando um novo elemento na lista
		elem = p->prim;			
		coef = 0;  //Seta o coeficiente para zero denovo
		j--;			 
	}		
	p->prim = elem->prox;	
	free(elem);	
	return(p);
}
/*----------------------------------------------------------------------------*/
void destroi_polinomio(polinomio p) { 

	No *aux,*seguinte;		//variaveis usadas para percorrer o polinomio p

	aux=p->prim;			//coef de maior grau do poli

	while(aux!=NULL){		//apaga nos da cadeia
		seguinte=aux->prox;	//prox elemento a ser apagado
		free(aux);		//apaga o atual
		aux=seguinte;		//aux recebe prox elemento
	}

	free (p);			//apaga a lista
	
 }
/*----------------------------------------------------------------------------*/
polinomio escreve_polinomio(polinomio p) { 
//escreve polinomio no terminal	
		
	No *aux;				//variavel usada para percorrer o polinomio p
	float truncamento;			//variavel usada para testar se a parte decimal em float do coeficiente existe	
	/* a principal função da variavel truncamento é escrever polinomios pós-primitiva,
	 pois como há divizao resultados em fraçoes é possivel*/
	aux=p->prim;
	while(aux->prox!=NULL){			//faz ate termo com exp 1
		if(aux->coe!=0){		//nao imprime 0x^n
			truncamento=aux->coe;	
			if(truncamento == (int)truncamento)		//testa se existe parte decimal no float
				printf("%.0fx^%d",aux->coe,aux->exp);	//n imprime parte decimal
			else 	printf("%.2fx^%d",aux->coe,aux->exp);	//imprime parte decimal dos floats nao inteiro

		}
		aux=aux->prox;			//aux recebe proximo No para teste
		if (aux->coe!=0){		//analisa o sinal do prox termo
			if((aux->coe)>0)	//caso coe positivo
				printf(" +");
			else			//caso coe negativo
				printf(" ");
		}
		
	}
	if(aux->coe!=0){				//n imprime 0x^0
		truncamento=aux->coe;
		if(truncamento == (int)truncamento)	//testa se existe parte decimal no float
			printf("%.0f",aux->coe);	//n imprime parte decimal
		else	printf("%.2f",aux->coe);	//imprime parte decimal dos floats nao inteiros
	}
	printf("\n");
	return(p);
}
/*----------------------------------------------------------------------------*/
polinomio soma(polinomio p, polinomio q) { 

	polinomio r;		//polinomio r de resposta que a função retorna
	No *paux, *qaux, *raux;	//variaveis usadas para percorrer os polinomios p,q e r
	int pgrau, qgrau, ctrl;	//grau dos polinomios e variavel de controle
	/*aumenta grau r para o maior grau (P ou Q)*/
	r = cria_polinomio();
	pgrau = ler_grau(p);
	qgrau = ler_grau(q);
	if(pgrau > qgrau)
		normaliza_cima(r,pgrau);		
	else
		normaliza_cima(r,qgrau);	

	paux = p->prim;	
	qaux = q->prim;
	raux = r->prim;

	ctrl=pgrau-qgrau;		
	//variavel de controle para saber qual polinomio tem maior grau
	//com 2 'if's, ctrl>0,ctrl<0 
	

	for(ctrl; ctrl > 0; ctrl--){	//ctrl>0, p é maior
		raux->coe = paux->coe;
		raux = raux->prox;
		paux = paux->prox;
	}		
	
	
	for(ctrl; ctrl < 0; ctrl++){	//ctrl<0, q é maior
		raux->coe = qaux->coe;////
		raux = raux->prox;
		qaux = qaux->prox;	
	}

	
	while(raux!=NULL){		//crtl=0, p==q
		raux->coe = (paux->coe) + (qaux->coe);
		raux = raux->prox;	//final do polinomio
		paux = paux->prox;
		qaux = qaux->prox;
	}	

	normaliza_baixo(r);	//caso coeficientes de grau maior se anulem
	return(r);
}
/*----------------------------------------------------------------------------*/
polinomio multiplica(polinomio p, polinomio q) {

	polinomio r;
	No *paux,*qaux,*raux;
	int pgrau,qgrau,rmaxgrau,pos_exp;
	float mult_parcial;
	/*aumenta grau r para o maior grau possivel (grau_P * grau_Q)*/
	pgrau=ler_grau(p);
	qgrau=ler_grau(q);
	rmaxgrau=pgrau*qgrau;

	r=cria_polinomio();
	normaliza_cima(r,rmaxgrau);	//cria um r com o expoente maximo possivel com coeficientes zerados


	paux=p->prim;	
	while(paux!=NULL){	//percorre p
		qaux=q->prim;
		while(qaux!=NULL){	//percorre q
			mult_parcial=(paux->coe)*(qaux->coe);		//multiplicação parcial dos termos atuais
			pos_exp=(paux->exp)*(qaux->exp);		//posição baseado no exp
			raux=encontra_indice(r,pos_exp);		//encontra indice correspondente
			raux->coe=(raux->coe) + mult_parcial;		//faz a soma parcial
			
			qaux=qaux->prox;	//avança para proximo termo do polinomio q
		}

		paux=paux->prox;	//avança para proximo termo do polinomio p
	}	


	normaliza_baixo(r);		//apagua posiveis termos que se anularam
	return(r);
}
/*----------------------------------------------------------------------------*/
polinomio subtrai(polinomio p, polinomio q) {

	polinomio r;
	No *paux,*qaux,*raux;
	int pgrau,qgrau,ctrl;
	/*aumenta grau r para o maior grau (P ou Q)*/
	r=cria_polinomio();
	pgrau=ler_grau(p);
	qgrau=ler_grau(q);
	if(pgrau>qgrau){
		normaliza_cima(r,pgrau);		
	}else{
		normaliza_cima(r,qgrau);	
	}

	paux=p->prim;	
	qaux=q->prim;
	raux=r->prim;

	ctrl=pgrau-qgrau;		//variavel de controle para saber qual polinomio tem maior grau
	//com 2 'if's, ctrl>0,ctrl<0


	//ctrl>0, p é maior	
	for(ctrl;ctrl>0;ctrl--){
		raux->coe=paux->coe;
		raux=raux->prox;
		paux=paux->prox;
	}		
 			
	//ctrl<0, q é maior
	for(ctrl;ctrl<0;ctrl++){	
		raux->coe=-(qaux->coe);////
		raux=raux->prox;
		qaux=qaux->prox;	
	}
		
	//crtl=0, p==q
	while(raux!=NULL){	
		raux->coe=(paux->coe)-(qaux->coe);
		raux=raux->prox;	//final do polinomio
		paux=paux->prox;
		qaux=qaux->prox;
	}
	normaliza_baixo(r);	//caso coeficientes de grau maior se anulem
	return(r);
}
/*----------------------------------------------------------------------------*/
polinomio derivada(polinomio p) { 

	polinomio r;
	No *paux,*raux;
	int i;
	r=cria_polinomio();
	i=ler_grau(p)-1;	//cria "r" um grau menor que "p"
	normaliza_cima(r,i);	//para facilitar futuros calculos de exp
	paux=p->prim;		//p->prim tem exp n
	raux=r->prim;		//r->prim tem exp (n-1)
	while(raux!=NULL){	//vai ate termo independente de r
		raux->coe=(paux->coe)*(paux->exp);
		raux=raux->prox;
		paux=paux->prox;	
		//n é necessario atualizar exp ja que:
		//raux->exp sempre é um menor que paux-exp 
	}
	return(r) ;
}
/*----------------------------------------------------------------------------*/
polinomio primitiva(polinomio p) {

	polinomio r;
	No *noP, *noR; //Variáveis que serão usadas para navegar pelas listas
	int expo;
	float c = 0; //constante arbritrária para o coeficiente com o expoente de menor grau

 	r = cria_polinomio();
	expo = ler_grau(p) + 1;  //Grau para r sempre será 1 a mais que o grau de p
	normaliza_cima(r,expo);  //Aumenta a lista r até chegar em 1 acima de p
	
	noP = p->prim;
	noR = r->prim;

	while(ler_exp(noR) >= 0){  //Vai até o termo independente, que tem exp == 0
		if(noR->exp == 0){ //Se for igual exp = 0 o coeficiente de r recebe a constante
			noR->coe = c;
			break;
		}else{   //Se não for, então faz o processo de integração
			noR->coe = ((noP->coe) / ((noP->exp) +1));
			noR = noR->prox;
			noP = noP->prox;
		}
	}	
	return(r);
}
/*----------------------------------------------------------------------------*/
float avalia(polinomio p, float x) {

	float result = 0;
	No *paux;

	paux = p->prim; //Variável que navega na lista p recebe o primeiro elemento de p
	while(paux != NULL){ //Vai até que paux aponte para NULL
		result = result + ((paux->coe) * (potencia(x,paux->exp)));
		paux = paux->prox;
	}
	return(result);
}




