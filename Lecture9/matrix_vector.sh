#!/bin/bash
#PBS -l select=3:ncpus=1:mem=2gb -l place=pack
#PBS -l walltime=0:02:00
#PBS -q short_cpuQ
module load mpich-3.2
mpirun.actual -n 3 ./HPC/Lecture9/matrix_vector
