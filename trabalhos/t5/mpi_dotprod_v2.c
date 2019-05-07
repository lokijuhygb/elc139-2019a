/*
 * Exemplo de programa para calculo de produto escalar em paralelo, usando MPI.
 */

#include <stdio.h>
#include <stdlib.h>
// #include <sys/time.h>
#include "mpi.h"

typedef struct
{
	double *a;
	double *b;
	double c;
	int wsize;
	int repeat;
} dotdata_t;

dotdata_t dotdata;

/* Preenche vetor */
void fill(double *a, int size, double value)
{
	int i;
	for(i = 0; i < size; i++)
	{
		a[i] = value;
	}
}

/* Funcao do calculo do produto escalar executada pelos processos */
double dotprod_mpi(int wsize, int repeat)
{
	dotdata.a = (double*) malloc(wsize * sizeof(double));
	fill(dotdata.a, wsize, 0.01);
	dotdata.b = (double*) malloc(wsize * sizeof(double));
	fill(dotdata.b, wsize, 1);
	dotdata.wsize = wsize;
	dotdata.repeat = repeat;

	double *a = dotdata.a;
	double *b = dotdata.b;
	double mysum;

	for(int k = 0; k < repeat; k++)
	{
		mysum = 0.0;
		for(int i = 0; i < wsize; i++)
		{
			mysum += (a[i] * b[i]);
		}
	}

	free(dotdata.a);
	free(dotdata.b);

	return mysum;
}

int main(int argc, char **argv)
{
	int rank;			/* rank do processo (0 a P-1) */
	int p;				/* número de processos */
	int source;         /* rank do processo remetente */
	int dest = 0;		/* rank do processo destinatário */
	int tag = 0;		/* etiqueta da mensagem */
	double result;		/* a mensagem (resultado do calculo) */
	MPI_Status status;	/* status de uma operação efetuada */
	int wsize, repeat;
	double start_time_mpi, end_time_mpi;
	double total_dotprod;

	MPI_Init(&argc,&argv);					/* MPI_Init deve ser invocado antes de qualquer outra chamada MPI */
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);	/* Descobre o "rank" do processo */
	MPI_Comm_size(MPI_COMM_WORLD,&p);		/* Descobre o número de processos */

	if(argc != 3)
	{
		fprintf(stderr,"Usage: %s <worksize> <repetitions>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	wsize = atoi(argv[1]);
	repeat = atoi(argv[2]);

	start_time_mpi = MPI_Wtime();
	/* Calculam e enviam mensagem ao processo 0 */
	if(rank != 0)
	{
		result = dotprod_mpi(wsize, repeat);
		MPI_Send(&result, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD); 
	}
	else	/* Calcula e recebe as mensagens dos processos e totaliza */
	{
		double total_dotprod = dotprod_mpi(wsize, repeat);

		/* recebe p-1 mensagens */
		for(source = 1; source < p; source++)
		{
			MPI_Recv(&result, 1, MPI_DOUBLE, source, tag, MPI_COMM_WORLD, &status);
			total_dotprod += result;
		}

		end_time_mpi = MPI_Wtime();

		printf("%d,%d,%d,%f\n", p, wsize, repeat, (end_time_mpi - start_time_mpi) * 1000000);
	}

	MPI_Finalize(); /* finaliza MPI */

	return EXIT_SUCCESS;
}
