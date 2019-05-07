#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>

int main(int argc,char *argv[])
{
	int p,rank,value,tag = 0;
	MPI_Status status;

	MPI_Init(&argc,&argv);					/* MPI_Init deve ser invocado antes de qualquer outra chamada MPI */
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);	/* Descobre o "rank" do processo */
	MPI_Comm_size(MPI_COMM_WORLD,&p);		/* Descobre o número de processos */

	/* Se rank > 0 recebe mensagem. Se rank = 0 não recebe, imprime o valor inicial */
	if(rank > 0)
	{
		MPI_Recv(&value,1,MPI_INT,rank - 1,tag,MPI_COMM_WORLD,&status);	/* Recebe mensagem */
		printf("[%d] recebeu de  [%d]:\t%d\n",rank,status.MPI_SOURCE,value);
	}
	else
	{
		/* Gera um valor inicial aleatório */
		srand(time(NULL));
		value = rand() % 100;

		printf("Pipeline de %d processos\n",p);
		printf("[%d] valor inicial:\t%d\n",rank,value);
	}

	/* Se rank < p-1 envia mensagem. Se rank = p-1 não envia, imprime o valor final */
	if(rank < p-1)
	{
		value++; /* Incrementa antes de enviar para o próximo processo */
		printf("[%d] enviou para [%d]: \t%d\n",rank,rank + 1,value);
		MPI_Send(&value,1,MPI_INT,rank + 1,tag,MPI_COMM_WORLD);	/* Envia mensagem */
	}
	else
	{
		printf("[%d] valor final:\t%d\n",rank,value);
	}

	MPI_Finalize();	/* finaliza MPI */

	return EXIT_SUCCESS;
}
