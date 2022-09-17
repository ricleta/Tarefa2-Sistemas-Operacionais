// Eduardo Dantas Luna, 2111484
// Ricardo Bastos Leta Vieira, 2110526

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#define NUM_THREADS 8

void *nao_faz_nada(void *a)
{
  return NULL;
}

typedef struct timeval Timer;

typedef struct _params{
  int * vetA;
  int * vetB;
  int * vetC;
  int threadid;
  int tam;
}Params;

// bota valor de cada elemento do vetor de tamanho tam como a int valor
void preenche_array(int valor, int tam, int *arr)
{
  int i;

  if (arr == NULL)
  {
    exit(-1);
  }

  for (i = 0; i < tam; i++)
  {
    arr[i] = valor;
  }
}

//calcula a diferenca de tempo entre dois Timers 
float timediff(Timer t0, Timer t1)
{
	return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
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
  }

  for(int k = 0; k < NUM_THREADS; k++)
  {
    pthread_create(&threads[k], NULL, nao_faz_nada, (void *) &k);
  }

  gettimeofday(&fim, NULL);

  for(j = 0; j < NUM_THREADS; j++)
    pthread_join(threads[j],NULL);
  
  printf("\nTempo : %f ms\n", timediff(comeco, fim)); // fim

  free(vetA);
  free(vetB);
  free(vetC);
  
  return 0;
}
