/*
 * Exemplo de programa para calculo de produto escalar em paralelo, usando openMP.
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

typedef struct
{
    double *a;
    double *b;
    double c;
    int wsize;
    int repeat;
} dotdata_t;

/* Variaveis globais, acessiveis por todas threads */
dotdata_t dotdata;

/* Funcao executada por uma thread */
void *dotprod_worker(int nthreads)
{
    int i, j;
    double *a = dotdata.a;
    double *b = dotdata.b;
    int wsize = dotdata.wsize * nthreads;
    double mysum;

    #pragma omp parallel for shared(a,b) reduction(+:mysum) private(i,j)
    for(j = 0; j < dotdata.repeat; j++)
    {
        mysum = 0.0;
        for(i = 0; i < wsize; i++)
        {
            mysum += (a[i] * b[i]);
        }
    }

    dotdata.c = mysum;
}

/* Tempo (wallclock) em microssegundos */
long wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec*1000000 + t.tv_usec;
}

/* Preenche vetor */
void fill(double *a, int size, double value)
{
    int i;
    for(i = 0; i < size; i++)
    {
        a[i] = value;
    }
}

/* Funcao principal */
int main(int argc, char **argv)
{
    int nthreads, wsize, repeat;
    long start_time, end_time;

    if((argc != 4))
    {
        printf("Uso: %s <nthreads> <worksize> <repetitions>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    nthreads = atoi(argv[1]);
    wsize    = atoi(argv[2]); /* worksize = tamanho do vetor de cada thread */
    repeat   = atoi(argv[3]); /* numero de repeticoes dos calculos (para aumentar carga) */

    /* Cria vetores */
    dotdata.a = (double *) malloc(wsize * nthreads * sizeof(double));
    fill(dotdata.a, wsize * nthreads, 0.01);
    dotdata.b = (double *) malloc(wsize * nthreads * sizeof(double));
    fill(dotdata.b, wsize * nthreads, 1.0);
    dotdata.c = 0.0;
    dotdata.wsize = wsize;
    dotdata.repeat = repeat;

    /* Calcula c = a . b em nthreads, medindo o tempo */
    omp_set_num_threads(nthreads); /* https://computing.llnl.gov/tutorials/openMP/#OMP_SET_NUM_THREADS */
    start_time = wtime();
    dotprod_worker(nthreads);
    end_time = wtime();

    /* Mostra resultado e estatisticas da execucao */
    printf("%f\n", dotdata.c);
    printf("%d thread(s), %ld usec\n", nthreads, (long) (end_time - start_time));
    fflush(stdout);

    free(dotdata.a);
    free(dotdata.b);

    return EXIT_SUCCESS;
}
