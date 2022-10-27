#include "biblioteca.h"

/* -------------------------------------------------------------------------- */
/* ordena v[a..b] pelo método da seleção e devolve v */

int busca(int x, int v[], int a, int b){
  if(a > b)
    return(a - 1);
  if(compara(x,v[b]) == 1)
    return b;
  return(busca(x,v,a,b - 1));
}

int *insere(int v[], int a, int b){
  int p, i;
  p = busca(v[b],v,a,b - 1);
  i = b;
  while (i > p + 1){
    troca(v,i,i - 1);
    i--;
  }
  return v;
}

int *insercao(int v[], unsigned int a, unsigned int b) {
  if(a >= b)
    return v;
  insercao(v,a,b - 1);
  insere(v,a,b);
  return v;
}
