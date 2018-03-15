#!/bin/bash -l

#SBATCH --job-name=matrixmult
#SBATCH --time=00:30:00
#SBATCH --nodes=1
#SBATCH --output=matrixmult-%j.out
#SBATCH --error=matrixmult-%j.err

# load modules
if command -v module 1>/dev/null 2>&1; then
   module load gcc/6.1.0 openblas/0.2.18_gcc-6.1 gnuplot
fi

./basic_dgemm
./blas_dgemm
./blocked_dgemm
