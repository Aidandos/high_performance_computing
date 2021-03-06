/* ==================================================================== *
 *								        *
 *  block_dgemm.c -- Implement a block matrix multiplication routine    *
 *                                                                      *
 * ==================================================================== */

#include "square_dgemm.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* block parameter ... */
#ifndef BLOCK_SIZE
#  define BLOCK_SIZE ((unsigned) 16)
#endif



/**
 *  square_dgemm -- multiply two block matrices A and B adding result to C, result is C = C + A*B
 */
void square_dgemm (const double  *A, const double  *B,  double  *C, const unsigned  M)
{
	/* TODO: implement the blocked matrix-matrix multiplication */
        //printf("implement square_dgemm routine\n");
        int i, j, k, kk, jj;
        //int steps = M / BLOCK_SIZE;
        //int mod = M % BLOCK_SIZE;
        for(kk = 0; kk < M; kk += BLOCK_SIZE)
        {
          for(jj = 0; jj < M; jj += BLOCK_SIZE)
          {
            for(i=0; i < M; i++)
            {
              //const double *A_ix = A + i*M;
              for(j=jj; (j < jj+BLOCK_SIZE) && (j<M); j++)
              {
                //const double *B_xj = B + j;
                //double cij = C[i*M+j];
                //unsigned	k_ind = 0;
                for(k = kk; (k < kk + BLOCK_SIZE) && (k<M); k++)
                {
                  //cij += A_ix[k]*B_xj[k_ind];
                  C[i*M+j] = C[i*M+j] + A[i*M+k]*B[k*M+j];
                  //k_ind += M;
                }
                //C[i*M + j] = cij;
              }
            }
          }
        }
}
