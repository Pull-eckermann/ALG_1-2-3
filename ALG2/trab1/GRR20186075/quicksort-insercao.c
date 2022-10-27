#include "insercao.h"
#include "particiona.h"


/* -------------------------------------------------------------------------- */
/* ordena v[a..b] usando o algoritmo QuickSort com inserção e devolve v       */

int *quicksort_insercao(int v[], int a, int b, unsigned int m) {
  int n = b - a + 1;
  if(a < b){
    m = particiona(v,a,b,v[b]);
    if(n <= m)
      return(insercao(v,a,b));
    quicksort_insercao(v,a,m - 1,m);
    quicksort_insercao(v,m + 1,b,m);
    return v;
  }
}
