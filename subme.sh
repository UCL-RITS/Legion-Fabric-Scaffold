#!/bin/bash -l
#Example submission script: use of fabric preferred
#$ -S /bin/bash
#$ -P RCSoftDev
#$ -l h_rt=0:0:30
#$ -N MPIExample
#$ -pe mpi 4
#$ -wd /home/ucgajhe/Scratch/Scaffold/output
module unload compilers
module unload mpi
module load compilers/gnu/4.9.2
module load mpi/openmpi/1.10.1/gnu-4.9.2
gerun /home/ucgajhe/devel/mpi-scaffold/Legion-Fabric-Scaffold/build/src/mpi_example
