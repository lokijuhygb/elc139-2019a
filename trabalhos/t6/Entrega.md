lokijuhygb

ELC139 Programação Paralela

# T6: Comunicação coletiva em MPI

## Parte 1:

[matrix_mult_sr_v1.c](matrix_mult_sr_v1.c)

A matriz B e as linhas da matriz A são enviadas pelo processo zero e recebidas pelos demais por meio de chamadas [MPI_Send](https://www.open-mpi.org/doc/current/man3/MPI_Send.3.php) e [MPI_Recv](https://www.open-mpi.org/doc/current/man3/MPI_Recv.3.php). Os processos calculam o produto das linhas de A pelas colunas de B, resultando nas linhas da matriz produto C que são coletas e reunidas no processo zero por meio da chamada [MPI_Gather](https://www.open-mpi.org/doc/current/man3/MPI_Gather.3.php). O uso dessa chamada sugere o uso de sua inversa, a [MPI Scatter](https://www.open-mpi.org/doc/current/man3/MPI_Scatter.3.php), para distribuir as linhas da matriz A. E, como B é distribuída e recebida inteira, a chamada [MPI_Bcast](https://www.open-mpi.org/doc/current/man3/MPI_Bcast.3.php) pode ser usada para substituir as chamadas de envio e recebimento.


## Parte 2:

[Resumo](resumo.txt)


## Referências

- [MPI Scatter, Gather, and Allgather](https://mpitutorial.com/tutorials/mpi-scatter-gather-and-allgather/)

- [Open MPI: Open Source High Performance Computing](https://www.open-mpi.org/)

- [MPI Broadcast and Collective Communication](https://mpitutorial.com/tutorials/mpi-broadcast-and-collective-communication/)

- [MPI Reduce and Allreduce](http://mpitutorial.com/tutorials/mpi-reduce-and-allreduce/)

- [MPI Documents](https://www.mpi-forum.org/docs/)

- [Tutorial MPI](https://computing.llnl.gov/tutorials/mpi/)
  Tutorial do Lawrence Livermore National Laboratory (LLNL) sobre MPI.

- [Send-receive considered harmful: Myths and realities of message passing](https://dl.acm.org/citation.cfm?id=963780)
