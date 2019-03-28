lokijuhygb
ELC139 Programação Paralela

# T2: Programação Paralela Multithread 

## Parte I: Pthreads

1. Escolha um computador com mais de um núcleo de processamento. Verifique suas características (processador, memória).

    As características estão em [specs.txt](specs.txt).

2. Faça fetch e merge do repositório original da disciplina para obter os arquivos necessários para o trabalho.

3. Você vai trabalhar com 2 programas que usam POSIX threads para cálculo de um produto escalar: [pthreads_dotprod.c](pthreads_dotprod/pthreads_dotprod.c) e [pthreads_dotprod2.c](pthreads_dotprod/pthreads_dotprod2.c).

4. Compile esses programas:

    ```
    make
    ```

5. Execute o programa pthreads_dotprod usando 1 thread, para vetor de 1000000 de elementos, com 2000 repetições:

    ```
    ./pthreads_dotprod 1 1000000 2000
    ```

    ```
    $./pthreads_dotprod 1 1000000 2000
    10000.000000
    1 thread(s), 10500391 usec
    ```

6. Execute o mesmo programa usando 2 threads, com 500000 elementos para cada thread, 2000 repetições:

    ```
    ./pthreads_dotprod 2 500000 2000
    ```

    O resultado deve ser o mesmo do caso anterior, mas o tempo de processamento deve ser diferente.

    ```
    $./pthreads_dotprod 2 500000 2000
    10000.000000
    2 thread(s), 6336197 usec
    ```

7. Estude o código-fonte do programa, verificando as funções que implementam o paralelismo.

8. Observe que o programa [pthreads_dotprod2.c](pthreads_dotprod/pthreads_dotprod2.c) é semelhante a [pthreads_dotprod.c](pthreads_dotprod/pthreads_dotprod.c), mas tem **[2 linhas a menos](pthreads_dotprod/output_diff_pdp_pdp2.txt)**.


### Questões Pthreads


1. Explique como se encontram implementadas as 4 etapas de projeto: particionamento, comunicação, aglomeração, mapeamento (use trechos de código para ilustrar a explicação).

    O programa calcula o produto escalar de dois vetores por meio de uma soma de produtos escalares de vetores menores. Cada parcela dessa soma aglomera produtos coordenada a coordenada, que são as partições, são mapeadas para uma thread, e o número de parcelas é igual ao número de threads.


    Os produtos coordenada a coordenada são implementados em

    ```
    mysum += (a[i] * b[i]);
    ```

    Eles são aglomerados da esquerda para direita, com tamanho wsize, pelo laço em 

    ```
    for(i = start; i < end; i++)
    {
        mysum += (a[i] * b[i]);
    }
    ```

    A comunicação se resume em acumular os resultados dos produtos coordenada a coordenada. Dentro de cada aglomeração o acumulo está implementado em 

    ```
    mysum += (a[i] * b[i]);
    ```

    e entre elas está em

    ```
    pthread_mutex_lock (&mutexsum);
    dotdata.c += mysum;
    pthread_mutex_unlock (&mutexsum);
    ```

    O mapeamento é estático, cada thread executa produtos escalares de mesmo tamanho. Ele está implementado em

    ```
    for(i = 0; i < nthreads; i++)
    {
        pthread_create(&threads[i], &attr, dotprod_worker, (void *) i);
    }
    ```

2. Considerando o tempo (em microssegundos) mostrado na saída do programa, qual foi a aceleração (speedup) com o uso de threads?

    ```
    Speedup (p) = Tseq / Tpar(p) = 10500391 / 6336197 = 1,65720715438614
    ```

3. A aceleração se sustenta para outros tamanhos de vetores, números de threads e repetições? Para responder a essa questão, você terá que realizar diversas execuções, variando o tamanho do problema (tamanho dos vetores e número de repetições) e o número de threads (1, 2, 4, 8..., dependendo do número de núcleos). Cada caso deve ser executado várias vezes, para depois calcular-se um tempo de processamento médio para cada caso. Atenção aos fatores que podem interferir na confiabilidade da medição: uso compartilhado do computador, tempos muito pequenos, etc.

    Para cada caso foram realizadas 5 execuções. Os resultados estão em [results.csv](results.csv). A aceleração se sustentou, a média foi de 1,6466172643574 com desvio padrão de 0,014346144859129.


4. Elabore um gráfico/tabela de aceleração a partir dos dados obtidos no exercício anterior.

| size     | repetitions | speedup_pthread  | speedup_openmp   | 
|----------|-------------|------------------|------------------| 
| 1000000  | 1000        | 1,63547915594002 | 1,70709704640299 | 
| 1000000  | 2000        | 1,63389852122988 | 1,7410478159156  | 
| 1000000  | 3000        | 1,63575600726038 | 1,74014773758552 | 
| 10000000 | 1000        | 1,64712480732109 | 1,66472868768994 | 
| 10000000 | 2000        | 1,63156261761049 | 1,67277692018209 | 
| 10000000 | 3000        | 1,6419082387083  | 1,6634382143647  | 
| 20000000 | 1000        | 1,66801436992589 | 1,66088060133683 | 
| 20000000 | 2000        | 1,66451181442231 | 1,67149820847408 | 
| 20000000 | 3000        | 1,66129984679822 | 1,67704605623503 | 


5. Explique as diferenças entre [pthreads_dotprod.c](pthreads_dotprod/pthreads_dotprod.c) e [pthreads_dotprod2.c](pthreads_dotprod/pthreads_dotprod2.c). Com as linhas removidas, o programa está correto?

    A linha

    ```
    dotdata.c += mysum;
    ```

    é uma região crítica, por manipular o recurso compartilhado dotdata.c. Nela é feita uma leitura, uma soma com mysum e uma gravação do resultado em dotdata.c. Sua execução tem que ser atômica para evitar condição de corrida ou condição de concorrência. O primeiro programa implementa exclusão mútua utilizando mutex, o segundo não.

    [Sem as linhas removidas](output_diff_pdp_pdp2.txt) o programa não está correto, porque o resultado do produto escalar vai depender da sequencia que as operações serão realizadas entras as linhas de execução. Se for só uma linha de execução, não tem condição de corrida.



## Parte II: OpenMP


1. Nesta parte você vai trabalhar com um programa muito simples que usa OpenMP: [ompsimple.c](openmp/ompsimple.c).

2. Compile o programa usando a flag `-fopenmp`, que habilita OpenMP:

    ```
    gcc -fopenmp -o ompsimple ompsimple.c
    ```

3. Execute o programa com 8 threads:

    ```
    OMP_NUM_THREADS=8 ./ompsimple
    ```

    ```
    $OMP_NUM_THREADS=8 ./ompsimple
    Hello Word
    Hello Word
    Hello Word
    Hello Word
    Hello Word
    Hello Word
    Hello Word
    Hello Word
    ```

### Implementação OpenMP

1. Implemente um programa equivalente a [pthreads_dotprod.c](pthreads_dotprod/pthreads_dotprod.c) usando OpenMP.

    O programa está em [openmp_dotprod.c](openmp/openmp_dotprod.c).

2. Avalie o desempenho do programa em OpenMP, usando os mesmos dados/argumentos do programa com threads POSIX. 

    Os resultados estão em [results.csv](results.csv).

| size     | repetitions | speedup_pthread  | speedup_openmp   | 
|----------|-------------|------------------|------------------| 
| 1000000  | 1000        | 1,63547915594002 | 1,70709704640299 | 
| 1000000  | 2000        | 1,63389852122988 | 1,7410478159156  | 
| 1000000  | 3000        | 1,63575600726038 | 1,74014773758552 | 
| 10000000 | 1000        | 1,64712480732109 | 1,66472868768994 | 
| 10000000 | 2000        | 1,63156261761049 | 1,67277692018209 | 
| 10000000 | 3000        | 1,6419082387083  | 1,6634382143647  | 
| 20000000 | 1000        | 1,66801436992589 | 1,66088060133683 | 
| 20000000 | 2000        | 1,66451181442231 | 1,67149820847408 | 
| 20000000 | 3000        | 1,66129984679822 | 1,67704605623503 | 


| Tool     | Media            | Desvio Padrão     | 
|----------|------------------|-------------------| 
| pthreads | 1,6466172643574  | 0,014346144859129 | 
| openmp   | 1,68874014313186 | 0,03239899964527  | 


## Referências

- [POSIX Threads Programming](http://www.llnl.gov/computing/tutorials/pthreads/)
Tutorial do Lawrence Livermore National Laboratory (LLNL) sobre Pthreads.

- [Tutorial OpenMP](https://computing.llnl.gov/tutorials/openMP/)
Tutorial do Lawrence Livermore National Laboratory (LLNL) sobre OpenMP.
