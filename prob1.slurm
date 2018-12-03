#!/bin/sh
#SBATCH --nodes=1
#SBATCH --cpus-per-task=4
#SBATCH --time=0-00:05:00
#SBATCH --output=my_output.txt

cp prob1 $PFSDIR/.
cd $PFSDIR
./prob1