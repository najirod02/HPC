# How to compile and run on local

## Compilation
```bash
mpicc -g -Wall -o <output_file> <source_file>
```

## Execution
```bash
mpiexec -n <number_of_processes> <executable>
```

# How to run on cluster

After compiling the source code, you need to create a shell file
using PBS directives in order to import modules, select the number
of chunck, cpus and ram to submit your job.<br/>
Here an example of the structure:

```shell
#!bin/bash
#set number of chunks, cpus and memory
#PBS -l select=1:ncpus=4:mem=2gb

#set max execution time
#PBS -l walltime=0:05:00

#set the queue
#PBS -q short_cpuQ

module load mpich-3.2
mpirun.actual -n <number_of_processes> <executable>
```

Then, on the login node of the cluster, simply type to submit your job
and execute it:

```bash
qsub <shell_file>
```

Remember to always compile the source code if any modifications are applied (using the mpicc command on the login node).

## Notes
When creating the shell file in order to submit your code, you need to specify the entire path of the file, from the home directory.