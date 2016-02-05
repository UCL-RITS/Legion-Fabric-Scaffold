#!/bin/bash -l
#Example submission script: fabric preferred
#$ -S /bin/bash
#$ -P RCSoftDev
#$ -l h_rt=0:0:30
#$ -N OMPExample
#$ -pe smp 4
#$ -wd /home/ucgajhe/Scratch/Scaffold/output
module unload compilers
module load compilers/gnu/4.9.2
/home/ucgajhe/devel/omp-scaffold/Legion-Fabric-Scaffold/build/src/omp_example
