#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
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