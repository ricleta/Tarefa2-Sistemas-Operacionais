#include <stdio.h>
#include "auxiliares.h"
#define NUM_THREADS 8

// nao funciona
void *nao_faz_nada(void *a)
{
  return NULL;
}

int main(void) 
{
  int tam = 0;
  int i = 0;
  int j = 0;
  Timer comeco, fim;
  int status;
  int *vetA, *vetB, *vetC;
  pthread_t threads[NUM_THREADS];

  printf("Tamanho dos vetores: \n");
  scanf("%d", &tam);
  
  vetA = (int *) malloc(sizeof(int) * tam);
  vetB = (int *) malloc(sizeof(int) * tam);
  vetC =  (int *) malloc(sizeof(int) * tam);
  
  preenche_array(1, tam, vetA);
  preenche_array(2, tam, vetB);

  gettimeofday(&comeco, NULL); // incio

  for (i = 0; i < tam; i++)
  {
    vetC[i] = vetA[i] + vetB[i];
    pthread_create(&threads[i], NULL, nao_faz_nada, (void *) &i);
  }

  gettimeofday(&fim, NULL);

  for(j = 0; j<NUM_THREADS; j++)
    pthread_join(threads[j],NULL);
  
  printf("\nTempo : %f ms\n", timediff(comeco, fim)); // fim

  free(vetA);
  free(vetB);
  free(vetC);
  
  return 0;
}