#!/bin/sh
#SBATCH --nodes=1
#SBATCH --cpus-per-task=4
#SBATCH --time=0-00:05:00
#SBATCH --output=my_output.txt

cp prob1.c $PFSDIR/.
cd $PFSDIR
gcc prob1.c -o prob1 -lrt -pthread -lm
./prob1 1
./prob1 2
./prob1 4
./prob1 8