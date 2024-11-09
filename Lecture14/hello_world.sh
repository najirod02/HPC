#!/bin/bash
#PBS -l select=1:ncpus=10:mem=2gb
#PBS -l walltime=0:02:00
#PBS -q short_cpuQ
module load mpich-3.2
./HPC/Lecture14/hello_world