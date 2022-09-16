// Eduardo Dantas Luna, 2111484
// Ricardo Bastos Leta Vieira, 2110526

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#define NUM_THREADS 8

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

void *calcula_vetor(void * params)
{
  Params *p = (Params *) params;
  
  int j, i=p->threadid;
  int tam_p = p->tam/8;
  
  for (j = tam_p * (i); j < (i+1) * tam_p; j++)
  {
    p->vetC[j] = p->vetB[j] + p->vetA[j];
  }
  
  return NULL;
}

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