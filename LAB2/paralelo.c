#include <stdio.h>
#include <pthread.h>
#include "auxiliares.h"
#define NUM_THREADS 8

int main(void)
{
  int i = 0;
  int j = 0;
  Params *parametros = (Params *) malloc(sizeof(Params));
  Timer comeco, fim;
  pthread_t threads[NUM_THREADS];
  
  printf("Tamanho dos vetores: \n");
  scanf("%d", &parametros->tam);
  
  parametros->vetA = (int *)malloc(sizeof(int) * parametros->tam);
  parametros->vetB = (int *)malloc(sizeof(int) * parametros->tam);
  parametros->vetC = (int *)malloc(sizeof(int) * parametros->tam);
    
  preenche_array(1, parametros->tam, parametros->vetA);
  preenche_array(2, parametros->tam, parametros->vetB);

  gettimeofday(&comeco, NULL); // incio
  
  for (i = 0; i < NUM_THREADS; i++)
  {
    parametros->threadid = i;
    pthread_create(&threads[i], NULL, calcula_vetor, parametros);
  }
  
  gettimeofday(&fim, NULL);

  for(j = 0; j<NUM_THREADS; j++)
    pthread_join(threads[j],NULL);
  
  printf("\nTempo : %f ms\n", timediff(comeco, fim));

  free(parametros->vetA);
  free(parametros->vetB);
    
  return 0;
}