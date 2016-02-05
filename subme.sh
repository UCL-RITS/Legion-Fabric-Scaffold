#!/bin/bash -l
#$ -S /bin/bash
#$ -P RCSoftDev
#$ -l h_rt=0:0:30
#$ -N GPUExample
#$ -l gpu=1
#$ -wd /home/ucgajhe/Scratch/Scaffold/output
#$ -ac allow="P"
module unload compilers
module load compilers/gnu/4.9.2
module load cuda/7.5.18/gnu-4.9.2
/home/ucgajhe/devel/gpu-scaffold/Legion-Fabric-Scaffold/build/src/cuda_example
