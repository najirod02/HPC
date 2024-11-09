# How to compile and run on local and on cluster

## Basic commands
A list of the most used commands:
- mpicc
- mpirun / mpiexec
- qsub
- qstat (-u $USER)

# How to run on local
Here a brief description on how to both compile and run programs
that uses MPI and/or OpenMPI.

# MPI

## Compilation
```bash
mpicc -g -Wall -o <output_file> <source_file>
```

## Execution
```bash
mpiexec -n <number_of_processes> <executable>
```

Note that some of the commands above are also used on the cluster,
for more details keep reading.

# OpenMPI
With OpenMPI it is much more simple to both compile and run the code

## Compilation
```bash
gcc −fopenmp -o <output_file> <source_file>
```
Really important to specify the library to use while compiling.

## Execution
```bash
./<exe_file> <optional arguments>
```

# How to run on cluster

### General rules
- The only way to __execute__ your code is by using __qsub__!
- After every __modification__ applied to the __source code__, you need to __compile__ again.

#

After compiling the source code, you need to create a shell file
using PBS directives in order to import modules, select the number
of chunck, cpus and ram to submit your job.<br/>
Here an example of the structure:

Using MPI
```shell
#!bin/bash
#set number of chunks, cpus and memory
#PBS -l select=1:ncpus=4:mem=2gb

#set placing strategies (optional)
#[pack, scatter, pack:excl, scatter:excl]
#PBS -l place=pack

#set max execution time
#PBS -l walltime=0:05:00

#set the queue
#PBS -q short_cpuQ

module load mpich-3.2

mpirun.actual -n <number_of_processes> <executable>
```

Using OpenMPI
```shell
#!bin/bash
#set number of chunks, cpus and memory
#PBS -l select=1:ncpus=4:mem=2gb

#set placing strategies (optional)
#[pack, scatter, pack:excl, scatter:excl]
#PBS -l place=pack

#set max execution time
#PBS -l walltime=0:05:00

#set the queue
#PBS -q short_cpuQ

module load openmpi-4.0.4

#if you want to set the environmental variable
#export OMP_NUM_THREADS=<# of threads>

./<executable>
```

Then, on the login node of the cluster, simply type to submit your job
and execute it:

```bash
qsub <shell_file>
```


If you want to redirect the output and/or error file simply do as follows:

```bash
qsub <executable> -o /path/to/output/file.txt -e /path/to/error/file.txt
```
And with __${JOB_ID}__ you can get the job id and use it as the file name.


Remember to always compile the source code if any modifications are applied (using the mpicc command on the login node).

## Common problems
When creating the shell file in order to submit your code, you need to specify the entire __path__ of the file, __from the home directory__.

For example: 
```bash
mpirun.actual -n 3 /path/to/your/file.sh
```