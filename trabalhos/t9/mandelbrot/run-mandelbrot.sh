#!/bin/bash
#SBATCH -J mandelbrot          # job name
#SBATCH -o mandelbrot%j.out    # output file name (%j expands to jobID), this file captures standered output from the shell
#SBATCH -e mandelbrot%j.err    # error  file name (%j expands to jobID), this file captures errors generated from the program
#SBATCH  --nodes  1            # total number of nodes requested
#SBATCH --ntasks-per-node 1    # total number of proccess per node.
#SBATCH -p qCDER               # partition --qCDER (to find out available partitions please run 'sinfo' command)
#SBATCH --mem-per-cpu=10000    # request specific amount of RAM per CPU, now since we request 16 cores, the total amount of memory avilable for the program is 48GB
#SBATCH -t 01:10:00            # run time (hh:mm:ss) - 10 minutes

unzip mandelbrot.zip

srun make
srun ./mandelbrot < mandelbrot.in
