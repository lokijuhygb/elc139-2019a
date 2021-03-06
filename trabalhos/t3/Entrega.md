ELC139 Programação Paralela

lokijuhygb

# T3: Scheduling com OpenMP

## Resultados

O programa [OpenMPDemoABC.cpp](OpenMPDemoABC.cpp) explora as opções de escalonamento da clausula `schedule` definindo o tipo como `runtime` e manipulando a variável de ambiente [OMP_SCHEDULE](https://gcc.gnu.org/onlinedocs/libgomp/OMP_005fSCHEDULE.html#OMP_005fSCHEDULE), que seta a variável interna `run-sched-var`, utilizada pelo OpenMP para definir o tipo de escalonamento nesse caso.

Reparar que o `item 4`, dos [casos solicitados](README.md), é executado pelo programa antes de qualquer manipulação da variável de ambiente, e que valores negativos de `chunk` implicam em valores `default`, exceto para `auto`, onde é ignorado, mas precisa ser definido porque a função [omp_set_schedule](https://gcc.gnu.org/onlinedocs/libgomp/omp_005fset_005fschedule.html#omp_005fset_005fschedule) espera dois argumentos.

A seguir o resultado do programa para `duas threads`, `um array de 61 posições` e `chunk_size = 4`:

   ```
	$ ./OpenMPDemoABC 2 61 4
	Correct results should total exactly 61 chars
	static  chunk mutex AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBB A=32 B=29 S=61
	static   nop  mutex AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBBB A=31 B=30 S=61
	dynamic chunk mutex AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBB A=57 B=4  S=61
	dynamic  nop  mutex BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBA A=1  B=60 S=61
	guided  chunk mutex BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAA A=15 B=46 S=61
	guided   nop  mutex AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBB A=46 B=15 S=61
	runtime  nop  mutex AAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBA A=9  B=52 S=61
	auto     nop  mutex BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA A=31 B=30 S=61

	static  chunk  nop  ABABABABABABABABABABAABABABABABABABABABABABABABABABABABABA-AA A=32 B=28 S=60
	static   nop   nop  AABABABABABABABABABABABABABABABABABABABABABABABABABBABABABA-A A=31 B=29 S=60
	dynamic chunk  nop  AABBABABABABABABABABABABABABABABABABABABABABABABABABABABAB-BB A=29 B=31 S=60
	dynamic  nop   nop  BABABABABABBABABABABABABABABABABABABABABABABABABABABABABABAB- A=29 B=31 S=60
	guided  chunk  nop  BABABBABABABABABAABABABABABABABABABABABABABABABABABABABABABA- A=30 B=30 S=60
	guided   nop   nop  ABABABABABABAABABABABABABABABABABABABABABABABABABABABABABAB-B A=30 B=30 S=60
	runtime  nop   nop  BBABABABABABABABAABABABABABABABABABABABABABABABABABABABABABA- A=30 B=30 S=60
	auto     nop   nop  BABBABABAABBABABABABABABABABABABABABABABABABABABABABABABABA-A A=30 B=30 S=60

   ```

As colunas mostram, respectivamente, o tipo de escalonamento, se chunk e exclusão mútua foram utilizadas, o array preenchido, a quantidade de cada caracter e a soma de caracteres diferentes de `-`.

## Referências

- [GNU libgomp](https://gcc.gnu.org/onlinedocs/libgomp/)

- [OpenMP: For & Scheduling](http://jakascorner.com/blog/2016/06/omp-for-scheduling.html)

- [Tutorial OpenMP](https://computing.llnl.gov/tutorials/openMP/)
Tutorial do Lawrence Livermore National Laboratory (LLNL) sobre OpenMP.
