#!/bin/bash   
#SBATCH --job-name=peevski_job
#SBATCH --partition=slurm_shortgpu
#SBATCH -N 1 -n 1 --gres=gpu:1		# N requests nodes, Resource selection
#SBATCH --time=0-0:01:00
#SBATCH --output="p1_i.txt" 	# This sends stdoutto a file

module load gcc cuda cmake
cmake .
make clean
make 
cd $SLURM_SUBMIT_DIR
./problem2 50
