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
#  define BLOCK_SIZE ((unsigned) 1)
#endif



/**
 *  square_dgemm -- multiply two block matrices A and B adding result to C, result is C = C + A*B
 */
void square_dgemm (const double  *A, const double  *B,  double  *C, const unsigned  M)
{
	/* TODO: implement the blocked matrix-matrix multiplication */
        printf("implement square_dgemm routine\n");
        int i, j,k,kk,jj;
        double sum;

        for (i = 0; i < M; i++)
        {
          for(j=0; j <M; j++)
          {
            C[i][j] = 0.0;
          }
        }

        for(kk = 0; kk < M; kk += BLOCK_SIZE)
        {
          for(jj = 0; jj < M; jj =+ BLOCK_SIZE)
          {
            for(i=0; i < M; i++)
            {
              for(j=jj; j < jj+BLOCK_SIZE; j++)
              {
                sum = *C[i][j];
                for(k = kk; k < kk + BLOCK_SIZE; k++)
                {
                  sum += (*A[i][k])*(*B[k][j]);
                }
                C[i][j] = sum;
              }
            }
          }
        }
}
