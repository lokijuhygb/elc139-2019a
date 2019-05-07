lokijuhygb

ELC139 Programação Paralela

# T5: Primeiros passos com MPI

## Parte 1:

+ Implemente uma versão em MPI do programa do trabalho [t2](../t2), que calcula repetidas vezes o produto escalar entre 2 vetores. Os argumentos do programa devem ser: o número de elementos para cada processo e o número de repetições.

	O programa está em [mpi_dotprod.c](mpi_dotprod.c) ou [mpi_dotprod_v2.c](mpi_dotprod_v2.c).

+ Avalie o desempenho do programa conforme as instruções do trabalho [t2](../t2), mas variando o número de processos (-np) ao invés de threads.

	As características da máquina de testes estão em [specs.txt](specs.txt).
    Os resultados estão em [results.ods](results.ods).

O uso do MPI apresentou piores resultados em releção à openmp e a pthread, com uma eficiência entorno de 0,8 quando o número de processos (2) foi igual ao número de threads do processador da máquina de testes. Quando foi superior (4), o programa manteve o speedup exceto para tamanhos de 1000000, onde executou, aproximadamente, num tempo 6 vezes superior ao tempo serial.


| size     | repetitions | speedup_pthread  | speedup_openmp   | speedup_mpi p=2  | efficiency_mpi p=2| speedup_mpi np=4  | efficiency_mpi np=4 | 
|----------|-------------|------------------|------------------|------------------|-------------------|-------------------|---------------------| 
| 1000000  | 1000        | 1,63547915594002 | 1,70709704640299 | 1,61345895957625 | 0,806729479788124 | 0,161538758708987 | 0,040384689677247   | 
| 1000000  | 2000        | 1,63389852122988 | 1,7410478159156  | 1,58076440714171 | 0,790382203570853 | 0,161920262197592 | 0,040480065549398   | 
| 1000000  | 3000        | 1,63575600726038 | 1,74014773758552 | 1,59294013091594 | 0,796470065457971 | 0,159742698934085 | 0,039935674733521   | 
| 10000000 | 1000        | 1,64712480732109 | 1,66472868768994 | 1,62380587281032 | 0,811902936405158 | 1,62201046879248  | 0,40550261719812    | 
| 10000000 | 2000        | 1,63156261761049 | 1,67277692018209 | 1,62048148884905 | 0,810240744424524 | 1,62087375686811  | 0,405218439217026   | 
| 10000000 | 3000        | 1,6419082387083  | 1,6634382143647  | 1,62374622288644 | 0,811873111443222 | 1,61350773211661  | 0,403376933029154   | 
| 20000000 | 1000        | 1,66801436992589 | 1,66088060133683 | 1,64935004039281 | 0,824675020196405 | 1,64675289824294  | 0,411688224560735   | 
| 20000000 | 2000        | 1,66451181442231 | 1,67149820847408 | 1,64698839542328 | 0,82349419771164  | 1,64972648464784  | 0,41243162116196    | 
| 20000000 | 3000        | 1,66129984679822 | 1,67704605623503 | 1,63928194647657 | 0,819640973238287 | 1,63925338444454  | 0,409813346111134   | 


## Parte 2:

Implemente um programa MPI que transporte uma mensagem em um pipeline formado por processos de 0 a NP-1 (processo 0 envia para 1, processo 1 envia para 2, ..., processo NP-1 mostra o resultado). A mensagem é um número inteiro que é incrementado antes de ser passado adiante.

O programa [mpi_pipeline.c](mpi_pipeline.c) implementa esse pipeline. Exemplo:


``` c
$ mpiexec -np 7 mpi_pipeline

Pipeline de 7 processos
[0] valor inicial:	52
[0] enviou para [1]: 	53
[1] recebeu de  [0]:	53
[1] enviou para [2]: 	54
[2] recebeu de  [1]:	54
[2] enviou para [3]: 	55
[3] recebeu de  [2]:	55
[3] enviou para [4]: 	56
[4] recebeu de  [3]:	56
[4] enviou para [5]: 	57
[5] recebeu de  [4]:	57
[5] enviou para [6]: 	58
[6] recebeu de  [5]:	58
[6] valor final:	58
```

## Parte 3:

+ O programa [mpi_errado1.c](mpi_errado1.c) deveria realizar a troca de mensagens entre 2 processos, mas ele não funciona como esperado. Identifique o erro e corrija-o.

[mpi_errado1_corrigido.c](mpi_errado1_corrigido.c). [diff](diff_mpi_errado1.txt)

Problema: tag das mensagens enviadas e recebidas não são as mesmas.

+ O programa [mpi_errado2.c](mpi_errado2.c) deveria realizar a troca de mensagens entre 2 processos, mas também não funciona como esperado. Identifique o erro e corrija-o.

[mpi_errado2_corrigido.c](mpi_errado2_corrigido.c). [diff](diff_mpi_errado2.txt)

Problema: falta a rotina `MPI_Finalize();`.


## Referências

- [Tutorial MPI](https://computing.llnl.gov/tutorials/mpi/)
  Tutorial do Lawrence Livermore National Laboratory (LLNL) sobre MPI.

- [MPI Reduce and Allreduce](http://mpitutorial.com/tutorials/mpi-reduce-and-allreduce/)
