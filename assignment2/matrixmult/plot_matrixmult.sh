#!/bin/bash

# load modules
if command -v module 1>/dev/null 2>&1; then
   module load gcc/6.1.0 openblas/0.2.18_gcc-6.1 gnuplot
fi

gnuplot timing.gp
