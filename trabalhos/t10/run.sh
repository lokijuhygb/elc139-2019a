#!/bin/bash
#SBATCH -J mandelbrot          # job name
#SBATCH -o mandelbrot%j.out    # output file name (%j expands to jobID), this file captures standered output from the shell
#SBATCH -e mandelbrot%j.err    # error  file name (%j expands to jobID), this file captures errors generated from the program
#SBATCH  --nodes 1             # total number of nodes requested
#SBATCH --ntasks-per-node 1    # total number of proccess per node.
#SBATCH -p qCDER               # partition --qCDER (to find out available partitions please run 'sinfo' command)
#SBATCH --nodelist=cder03      # 
#SBATCH --mem-per-cpu=4000     # request specific amount of RAM per CPU, now since we request 16 cores, the total amount of memory avilable for the program is 48GB
#SBATCH -t 10:00:00            # run time (hh:mm:ss)

module load Compilers/intel_TBB_2017
module load Compilers/OpenMPI4.0.1

# compila os programas
srun make

lscpu >> resultados.csv

for problem in mandelbrot1.in mandelbrot2.in mandelbrot3.in
do
	# executa 3 testes para cada programa
	for program in mandelbrot_serial
	do
		for nthread in 1
		do
			# executa 3 vezes
			for qtd in $(seq 1 1 3)
			do
				start=`date +%s.%N`
					srun ./$program < $problem
				end=`date +%s.%N`

				echo $problem,$program,$nthread,$qtd,$start,$end >> resultados.csv
			done
		done
	done
done

for problem in mandelbrot1.in mandelbrot2.in mandelbrot3.in
do
	for nthread in 36 32 24 16 8 4 2
	do
		# executa 3 testes para cada programa
		for program in mandelbrot_openmp mandelbrot_openmp_simd mandelbrot_tbb mandelbrot_tbb_simd
		do
			# executa 3 vezes
			for qtd in $(seq 1 1 3)
			do
				start=`date +%s.%N`
# 					export OMP_NUM_THREADS=$nthread
					srun ./$program $nthread < $problem
				end=`date +%s.%N`

				echo $problem,$program,$nthread,$qtd,$start,$end >> resultados.csv
			done
		done
	done
done
