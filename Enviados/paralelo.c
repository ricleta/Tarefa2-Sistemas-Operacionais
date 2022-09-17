// Eduardo Dantas Luna, 2111484
// Ricardo Bastos Leta Vieira, 2110526

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#define NUM_THREADS 8

int tam;
int * vetA;
int * vetB;
int * vetC;

typedef struct timeval Timer;

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

void *calcula_vetor(void * params)
{
  int aux = params;
  int j = 0;
  int tam_p = tam / NUM_THREADS;
  
  for (j = tam_p * (aux - 1); j < (aux) * tam_p; j++)
  {
    vetC[j] = vetB[j] + vetA[j]; 
  }

  return NULL;
}

//calcula a diferenca de tempo entre dois Timers 
float timediff(Timer t0, Timer t1)
{
	return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}

int main(void)
{
  int i = 0;
  int j = 0;
  Timer comeco, fim;
  pthread_t threads[NUM_THREADS];

  printf("Tamanho dos vetores: \n");
  scanf("%d", &tam);
  
  vetA = malloc(sizeof(int) * tam);
  vetB = malloc(sizeof(int) * tam);
  vetC = malloc(sizeof(int) * tam);

  preenche_array(1, tam ,vetA);
  preenche_array(2, tam ,vetB);

  gettimeofday(&comeco, NULL); // incio
  
  for (i = 1; i <= NUM_THREADS; i++)
  {
    pthread_create(&threads[i-1], NULL, calcula_vetor, (void *)i);
  }
  
  gettimeofday(&fim, NULL);

  for(j = 0; j<NUM_THREADS; j++)
    pthread_join(threads[j],NULL);
  
  printf("\nTempo : %f ms\n", timediff(comeco, fim));

  return 0;
}