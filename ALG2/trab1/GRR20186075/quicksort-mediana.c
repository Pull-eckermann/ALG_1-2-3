#include "particiona.h"

/* -------------------------------------------------------------------------- */
/* devolve a mediana de a, b e c                                              */

static int mediana(int a, int b, int c,int v[]) {    //acha a mediana por eliminação
int maior, menor, med;
  if (v[a] < v[b] && v[a] < v[c])
    menor = v[a];
  if (v[b] < v[a] && v[b] < v[c])
    menor = v[b];
  if (v[c] < v[a] && v[c] < v[b])
    menor = v[c];
  if (v[a] > v[b] && v[a] > v[c])
    maior = v[a];
  if (v[b] > v[a] && v[b] > v[c])
    maior = v[b];
  if (v[c] > v[a] && v[c] > v[b])
    maior = v[c];
  if (v[a] != maior && v[a] != menor)
    med = a;
  if (v[b] != maior && v[b] != menor)
    med = b;
  if (v[c] != maior && v[c] != menor)
    med = c;
  return (med);
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* ordena v[a..b]  usando o algoritmo  "QuickSort com mediana de  3" e
   devolve v                                                                  */

int *quicksort_mediana(int v[], int a, int b) {
  int m, med, x, y, z;
  if (a >= b){
    return v;
  }
  x = sorteia(a,b);
  y = sorteia(a,b);
  z = sorteia(a,b);
  med = mediana(x,y,z,v);
  int aux = v[med];                   //Troca os valores dos elementos do vetor de indice b e med
  v[med] = v[b];
  v[b] = aux;
  m = particiona(v,a,b,v[b]);
  quicksort_mediana(v,a,m-1);
  quicksort_mediana(v,m+1,b);
  return v;
}
