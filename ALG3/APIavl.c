#include "APIavl.h"

/*------------------------------------------------------------*/
nodo *buscaEx(nodo *T, int chave){//Essa função funciona como busca na inclusão, retornando o pai do que será incluído
	nodo *p;
	p = T; //Ponteiro para navegação 
	while((p->esq) || (p->dir) != NULL){//Verifica se existe algum nodo filho para poder descer
		if(chave <= p->chave)
			if(p->esq != NULL) 
				p = p->esq;
			else
				return p; //O nodo retornado não é nescessáriamente folha, mas é o último que poderia retornar
		else
			if(p->dir != NULL)
				p = p->dir;
			else
				return p;
	}	
	return p; //Se é folha retorna o próprio
}
/*------------------------------------------------------------*/
nodo *busca(nodo *T, int chave){ //Algoritmo de busca para exclusão em BST visto em sala
	if(T == NULL)
		return NULL;
	if(chave == T->chave)
		return T;
	if(chave < T->chave)
		return busca(T->esq, chave);
	return busca(T->dir, chave);
}
/*------------------------------------------------------------*/
nodo *insereNodo(nodo *p, int chave){ //Função que insere um nodo recebendo como parâmetro o pai
	nodo *novo; 
	novo = malloc(sizeof(nodo));
	novo->esq = NULL;
	novo->dir = NULL;
	
	if(chave <= p->chave){ //Confere se o nodo irá para a esquerda ou direita do pai
		novo->pai = p;
		p->esq = novo;
		novo->chave = chave;
	}
	else{
		novo->pai = p;
		p->dir = novo;
		novo->chave = chave;
	}
	novo->ht = calculaAltura(novo); //Calcula a altura e guarda na variável respectiva
	return novo;
}
/*------------------------------------------------------------*/
nodo *incluiNodo(nodo *T, int chave){ //Algoritmo que incluí numa BST
	nodo *p;
	if(T == NULL){ //Verifica se a árvore está vazia
		p = malloc(sizeof(nodo));//Cria o primeiro nodo, o raiz
		p->chave = chave;//adiciona a chave na raiz
		p->pai = NULL;
		p->esq = NULL;
		p->dir = NULL;//Ligação dos devidos ponteiros
		return p;
	}
	p = buscaEx(T, chave);//Retorna o nodo pai do que será inserido
	p = insereNodo(p, chave);//Insere e p e retorna o ponteiro que aponta para a raiz
	return balanceia(p);//Balanceia recebendo a raiz como parãmetro e retorna um ponteiro pra raiz
}
/*------------------------------------------------------------*/
nodo *excluiNodo(nodo *T, int chave){//Algoritmo que excluí numa BST pelo antecessor
	nodo *p;
	nodo *x;
	p = busca(T, chave); //Acha nodo que será excluído, recebe NULL se não se encontra na árvore
	if(p != NULL){ //Confere se o nodo está na árvore
		if((p->esq == NULL) && (p->dir == NULL)){ //Exclusão na folha
			if(p->pai == NULL){//Verifica se o que será excluído é a raiz
				free(p);
				return NULL;
			}			
			if(p->chave <= p->pai->chave){//Verifica pela chave qual dos ponteiros do pai irá ser atualizado
				p->pai->esq = NULL;
				x = p->pai;
				free(p);
				return balanceia(x);//balanceia após a exlusão, recebendo como parâmetro o pai do antecessor
			}
			else{
				p->pai->dir = NULL;
				x = p->pai;
				free(p);
				return balanceia(x);//idem
			}
		}
		else{
			if((p->esq == NULL) && (p->dir != NULL)){ //Exclusão com o filho da esquerda nulo
				p->dir->pai = p->pai;
				if(p->pai == NULL){//Verifica se o que será excluído é a raiz
					T = p->dir;
					free(p);
					return balanceia(T);
				}
				if(p->chave <= p->pai->chave){//Verifica pela chave qual dos ponteiros do pai irá ser atualizado
					p->pai->esq = p->dir;
					x = p->pai;
					free(p);
					return balanceia(x);
				}
				else{
					p->pai->dir = p->dir;
					x = p->pai;
					free(p);
					return balanceia(x);
				}
			}		
			if((p->esq != NULL) && (p->dir == NULL)){ //Exclusão com o filho da direita nulo
				p->esq->pai = p->pai;
				if(p->pai == NULL){//Verifica se o que será excluído é a raiz
					T = p->esq;
					free(p);
					return balanceia(T);
				}
				if(p->chave <= p->pai->chave){//Verifica pela chave qual dos ponteiros do pai irá ser atualizado
					p->pai->esq = p->esq;
					x = p->pai;
					free(p);
					return balanceia(x);
				}
				else{
					p->pai->dir = p->esq;
					x = p->pai;
					free(p);
					return balanceia(x);
				}
			}
			if((p->esq != NULL) && (p->dir != NULL)){ //Exclusão no meio com dois filhos
				nodo *n = p->esq;
				while(n->dir != NULL)//Acha o antecessor
					n = n->dir; //n é o ponteiro para o antecessor
				x = n->pai;
				if(p->esq != n){ //Caso em que o antecessor não se encontra diretamente à direita do que será excluído
					n->pai->dir = n->esq;
					if(n->esq != NULL)
						n->esq->pai = n->pai;
					n->esq = p->esq;
					n->dir = p->dir;
					n->pai = p->pai;
					p->esq->pai = n;
					p->dir->pai = n;
					if(p->pai == NULL){ //Verifica se o que será excluído é a raiz
						free(p);
						return balanceia(x);//balanceia após a exlusão, recebendo como parâmetro o pai do antecessor
					}
					if(p->chave <= p->pai->chave){//Verifica pela chave qual dos ponteiros do pai irá ser atualizado
						p->pai->esq = n;
						free(p);
						return balanceia(x);//idem
					}
					else{
						p->pai->dir = n;
						free(p);
						return balanceia(x);//idem
					}
				}
				else{//Caso em que o antecessor está diretamente a direita de p
					n->dir = p->dir;
					n->pai = p->pai;
					p->dir->pai = n;//O ponteiro da direita de n continua com ele
					if(p->pai == NULL){//Verifica se o que será excluído é a raiz
						free(p);
						return balanceia(n);
					}
					if(p->chave <= p->pai->chave){//Verifica pela chave qual dos ponteiros do pai irá ser atualizado
						p->pai->esq = n;
						free(p);
						return balanceia(n);
					}
					else{
						p->pai->dir = n;
						free(p);
						return balanceia(n);
					}
				}
			}
		}
	}
	return T; //Se não estiver retorna a raiz sem alterar a árvore
}
/*------------------------------------------------------------*/
nodo *balanceia(nodo *p){ //Função que confere balanceamento e chama as rotações de acordo com os casos
	int hdir;
	int hesq;
	nodo *raiz = p;
	
	while(p != NULL){ 
		if(p->dir != NULL)
			hdir = p->dir->ht;//Altura da direita de p para comparação
		else
			hdir = 0;//Ponteiro NULL recebe altura 0

		if(p->esq != NULL)
			hesq = p->esq->ht;//Altura da esquerda de p para comparação
		else
			hesq = 0;//Ponteiro NULL recebe altura 0

		if(((hesq - hdir) == -2) || ((hesq - hdir) == 2)){//Se o resultado for -2 ou 2 quer dizer que está desbalanceado e p é o nodo problema
			if((hesq - hdir) == -2){//Caso em que o maior caminho está na direita de p
				if(fator(p->dir) == -1)//Se retorna -1 é zig-zig
					rotacaoEsquerda(p);
				if(fator(p->dir) == 1){//Se retorna 1 é zig-zag
					rotacaoDireita(p->dir);
					rotacaoEsquerda(p);
				}
			}
			if((hesq - hdir) == 2){//Caso em que o maior caminho está na esquerda de p
				if(fator(p->esq) == 1)//Se retorna 1 é zig-zig
					rotacaoDireita(p);
				if(fator(p->esq) == -1){//Se retorna -1 é zig-zag
					rotacaoEsquerda(p->esq);
					rotacaoDireita(p);
				}
			}
		}
		p->ht = calculaAltura(p);
		p = p->pai;
	}
	while(raiz->pai != NULL) //Acha o nodo raiz para retornar
		raiz = raiz->pai;
	return raiz;
}
/*------------------------------------------------------------*/
int fator(nodo *p){ //Função que verifica se é zig-zig ou zig-zag
	int hdir;
	int hesq;

	if(p == NULL)
		return 0;

	if(p->dir != NULL) //Confere se existe nodo e recebe a altura
		hdir = p->dir->ht;
	else
		hdir = 0;//NULL é considerado com altura 0

	if(p->esq != NULL)
		hesq = p->esq->ht;
	else
		hesq = 0;

	return(hesq - hdir); //Se for -1 o maior caminho é na direita, se for 1 é na esquerda
}
/*------------------------------------------------------------*/
int calculaAltura(nodo *x){ //Função que calcula a altura que os nodos recebem
	if(x == NULL)
		return 0;
	int h_esq = calculaAltura(x->esq);
	int h_dir = calculaAltura(x->dir);

	if(h_esq > h_dir)
		return (h_esq + 1); 
	else
		return(h_dir + 1);
}
/*------------------------------------------------------------*/
void rotacaoDireita(nodo *x){//Rotação para direita que recebe como parâmetro o nodo que desce
	nodo *y;
	y = x->esq;
	x->esq = y->dir;
	if(y->dir != NULL)
		y->dir->pai = x;
	y->dir = x;
	y->pai = x->pai;
	x->pai = y;
	if(y->pai == NULL)
		return;
	if(y->chave <= y->pai->chave)
		y->pai->esq = y;
	else
		y->pai->dir = y;
	x->ht = calculaAltura(x);//Atualiza as alturas dos nodos que rotacionaram
	y->ht = calculaAltura(y);
}
/*------------------------------------------------------------*/
void rotacaoEsquerda(nodo *x){//Rotação para esquerda que recebe como parâmetro o nodo que desce
	nodo *y;
	y = x->dir;
	x->dir = y->esq;
	if(y->esq != NULL)
		y->esq->pai = x;
	y->esq = x;
	y->pai = x->pai;
	x->pai = y;
	if(y->pai == NULL)
		return;
	if(y->chave <= y->pai->chave)
		y->pai->esq = y;
	else
		y->pai->dir = y;
	x->ht = calculaAltura(x);//Atualiza as alturas dos nodos que rotacionaram
	y->ht = calculaAltura(y);
}
/*------------------------------------------------------------*/
void imprimeAVL(nodo *T){//Imprime em ordem visto em sala
	if(T != NULL){
		imprimeAVL(T->esq);
		int h = contaNivel(T);	
		printf("%d,%d\n",T->chave,h);//Imprime a chave e o nível calculada
		imprimeAVL(T->dir);
	}
}		
/*------------------------------------------------------------*/
int contaNivel(nodo *T){	
	nodo *p;
	int cont = 0;
	for(p = T; p->pai != NULL; p = p->pai) //Incrementa o contador até cegar na raiz
		cont++;
	return cont; //Retorna o nível
}


