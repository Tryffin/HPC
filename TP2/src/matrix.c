/* ---------------- */
/* --- matrix.c --- */
/* ---------------- */

#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "nrdef.h"
#include "nrutil.h"

// ---------------------------------------------------
void dup_f32matrix_ij(float32 **A, float32 **B, int n)
// ---------------------------------------------------
{
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            B[i][j] = A[i][j];
        }
    }
}
// ---------------------------------------------------
void dup_f32matrix_ji(float32 **A, float32 **B, int n)
// ---------------------------------------------------
{
    for(int j = 0; j < n; j++){
        for(int i = 0; i < n; i++){
            B[i][j] = A[i][j];
        }
    }
}
// ---------------------------------------------------
void trn_f32matrix_ij(float32 **A, float32 **B, int n)
// ---------------------------------------------------
{
    // la double boucle parcours l'espace d'arrivee en ij
}
// ---------------------------------------------------
void trn_f32matrix_ji(float32 **A, float32 **B, int n)
// ---------------------------------------------------
{
    // la double boucle parcours l'espace d'arrivee en ji
}
// ----------------------------------------------------------------
void add_f32matrix_ij(float32 **A, float32 **B, float32 **C, int n)
// ----------------------------------------------------------------
{
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}
// ----------------------------------------------------------------
void add_f32matrix_ji(float32 **A, float32 **B, float32 **C, int n)
// ----------------------------------------------------------------
{
    for(int j = 0; j < n; j++){
        for(int i = 0; i < n; i++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}
// --------------------------------------------------------
void accumulate_f32matrix_h(float32 **A, float32 *B, int n)
// --------------------------------------------------------
{
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            B[i] += A[i][j];
        }
    }
}
// --------------------------------------------------------
void accumulate_f32matrix_v(float32 **A, float32 *B, int n)
// --------------------------------------------------------
{
    for(int j = 0; j < n; j++){
        for(int i = 0; i < n; i++){
            B[j] += A[i][j];
        }
    }
}
// ---------------------------------------------------------
void accumulate_f32matrix_vh(float32 **A, float32 *B, int n)
// ---------------------------------------------------------
{
    float32 t;
    for(int j = 0; j < n; j++){
        t = 0;
        for(int i = 0; i < n; i++){
            t += A[i][j];
        }
        B[j] = t;
    }
}
// -----------------------------------------------------------------
void mul_f32matrix_ijk(float32 **A, float32 **B, float32 **C, int n)
// -----------------------------------------------------------------
{
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            C[i][j] = 0;
            for(int k = 0; k < n; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
// -----------------------------------------------------------------
void mul_f32matrix_ikj(float32 **A, float32 **B, float32 **C, int n)
// -----------------------------------------------------------------
{
    for(int i = 0; i < n; i++){
        for(int k = 0; k < n; k++){
            for(int j = 0; j < n; j++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
// -----------------------------------------------------------------
void mul_f32matrix_jik(float32 **A, float32 **B, float32 **C, int n)
// -----------------------------------------------------------------
{
    for(int j = 0; j < n; j++){
        for(int i = 0; i < n; i++){
            for(int k = 0; k < n; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
// -----------------------------------------------------------------
void mul_f32matrix_jki(float32 **A, float32 **B, float32 **C, int n)
// -----------------------------------------------------------------
{
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
// -----------------------------------------------------------------
void mul_f32matrix_kij(float32 **A, float32 **B, float32 **C, int n)
// -----------------------------------------------------------------
{
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
// -----------------------------------------------------------------
void mul_f32matrix_kji(float32 **A, float32 **B, float32 **C, int n)
// -----------------------------------------------------------------
{
    for(int k = 0; k < n; k++){
        for(int j = 0; j < n; j++){
            for(int i = 0; i < n; i++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
// ------------------------------------------------------
void sum3_f32matrix_loop(float32 **X, float32 **Y, int n)
/* --------------------------------------------------- */
{
  float32 t;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
          Y[i][j] = 0;
            for(int deti = -1; deti < 2; deti++){
                for(int detj = -1; detj < 2; detj++){
                    t = X[i+deti][j+detj];
                    Y[i][j] += t;
                }
            }
        }
    }
}
// -------------------------------------------------------
void sum3_f32matrix_array(float32 **X, float32 **Y, int n)
// -------------------------------------------------------
{
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            Y[i][j] = X[i-1][j-1] + X[i-1][j] + X[i-1][j+1]
                    + X[i][j-1] + X[i][j] + X[i][j+1]
                    + X[i+1][j-1] + X[i+1][j] + X[i+1][j+1];
        }
    }
}
// -----------------------------------------------------
void sum3_f32matrix_reg(float32 **X, float32 **Y, int n)
// -----------------------------------------------------
{
    float32 x0, x1, x2, x3, x4, x5, x6, x7, x8;
    float32 t;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            x0 = X[i-1][j-1];
            x1 = X[i-1][j];
            x2 = X[i-1][j+1];
            x3 = X[i][j-1];
            x4 = X[i][j];
            x5 = X[i][j+1];
            x6 = X[i+1][j-1];
            x7 = X[i+1][j];
            x8 = X[i+1][j+1];
            t = x0 + x1 + x2 + x3 + x4 + x5 + x6 + x7 + x8;
            Y[i][j] = t;
        }
    }
}
// -----------------------------------------------------
void sum3_f32matrix_rot(float32 **X, float32 **Y, int n)
// -----------------------------------------------------
{
    float32 x0, x1 = X[-1][0], x2=X[-1][1], x3, x4 = X[0][0], x5=X[0][1], x6, x7 = X[1][0], x8=X[1][1];
    float32 t;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            x0 = X[i-1][j-1];
            x3 = X[i][j-1];
            x6 = X[i+1][j-1];
            t = x0 + x1 + x2 + x3 + x4 + x5 + x6 + x7 + x8;
            Y[i][j] = t;
            x1 = x0;
            x2 = x1;
            x4 = x3;
            x5 = x4;
            x7 = x6;
            x8 = x7;
        }
    }
}
// -----------------------------------------------------
void sum3_f32matrix_red(float32 **X, float32 **Y, int n)
// -----------------------------------------------------
{
  float32 x0, x1, x2, x3, x4, x5, x6, x7, x8;
  float32 ra, rb, rc;
  float32 t;
  for(int i = 0; i < n; i++){
     int j = 0;
     x0 = X[i-1][j-1];
     x3 = X[i+0][j-1];
     x6 = X[i+1][j-1];
     ra = x0 + x3 + x6;

     j = 1;
     x1 = X[i-1][j-1];
     x4 = X[i+0][j-1];
     x7 = X[i+1][j-1];
     rb = x1 + x4 + x7;

      for(int j = 0; j < n; j++){
          x2 = X[i-1][j+1];
          x5 = X[i+0][j+1];
          x8 = X[i+1][j+1];
          rc = x2 + x5 + x8;
          t = ra + rb + rc;
          Y[i][j] = t;
          ra = rb;
          rb = rc;
    }
  }
}
// ----------------------------------------------------
void sum3_f32matrix_lu(float32 **X, float32 **Y, int n)
// ----------------------------------------------------
{
  float32 x0 = X[-1][-1], x1 = X[-1][0], x2, x3 = X[0][-1], x4 = X[0][0], x5, x6 = X[1][-1], x7 = X[1][0], x8;
  float32 t1, t2, t3;
  int r = n%3;
  for(int i = 0; i < n; i++){
      for(int j = 0; j < n-r; j+=3){
          x2 = X[i-1][j-1];
          x5 = X[i][j-1];
          x8 = X[i+1][j-1];
          t1 = x0 + x1 + x2 + x3 + x4 + x5 + x6 + x7 + x8;
          Y[i][j] = t1;

          x0 = X[i-1][j+0];
          x3 = X[i][j+0];
          x6 = X[i+1][j+0];
          t2 = x1 + x2 + x0 + x4 + x5 + x3 + x7 + x8 + x6;
          Y[i][j] = t2;

          x1 = X[i-1][j+1];
          x4 = X[i][j+1];
          x7 = X[i+1][j+1];
          t3 = x2 + x0 + x1 + x5 + x3 + x4 + x8 + x6 + x7;
          Y[i][j] = t3;
          switch(r){
              case 2: Y[i][j] = X[i-1][j-1] + X[i-1][j] + X[i-1][j+1]
                      + X[i][j-1] + X[i][j] + X[i][j+1]
                      + X[i+1][j-1] + X[i+1][j] + X[i+1][j+1];
                      j++;

              case 1: Y[i][j] = X[i-1][j-1] + X[i-1][j] + X[i-1][j+1]
                      + X[i][j-1] + X[i][j] + X[i][j+1]
                      + X[i+1][j-1] + X[i+1][j] + X[i+1][j+1];

              case 0: break;
          }
      }
  }
}
// ----------------------------------------------------------------------
void sum3x2_f32matrix_array(float32 **X, float32 **Y, float32 **Z, int n)
// ----------------------------------------------------------------------
{
  sum3_f32matrix_array(X, Y, n);
  sum3_f32matrix_array(Y, Z, n);
}
// --------------------------------------------------------------------
void sum3x2_f32matrix_red(float32 **X, float32 **Y, float32 **Z, int n)
// --------------------------------------------------------------------
{
  sum3_f32matrix_red(X, Y, n);
  sum3_f32matrix_red(Y, Z, n);
}
// ------------------------------------------------------------
void sum3_f32vector_reg(float32 **X, float32 **Y, int i, int n)
// ------------------------------------------------------------
{
  float32 x0, x1, x2, x3, x4, x5, x6, x7, x8;
  float32 ra, rb, rc;
  float32 t;
  for(int j = 0; j < n; j++){

     x0 = X[i-1][j-1];
     x1 = X[i-1][j+0];
     x2 = X[i-1][j+1];
     ra = x0 + x1 + x2;

     x3 = X[i+0][j-1];
     x4 = X[i+0][j+0];
     x5 = X[i+0][j+1];
     rb = x3 + x4 + x5;

     x6 = X[i+1][j-1];
     x7 = X[i+1][j+0];
     x8 = X[i+1][j+1];
     rc = x6 + x7 + x8;

     Y[i][j] = ra + rb + rc;

  }
    // avec scalarisation
}
// ----------------------------------------------------------------------------------------------------
void sum3x2_f32matrix_reg_pipe(float32** restrict X, float32** restrict Y, float32** restrict Z, int n)
// ----------------------------------------------------------------------------------------------------
{
  sum3_f32vector_reg(X, Y, 0, n);
  for(int i=1 ; i < n-1 ; i++){
      sum3_f32vector_reg(X, Y, i, n);
      sum3_f32vector_reg(Y, Z, i+1, n);
  }
  sum3_f32vector_reg(X, Y, n-1, n);

}
// ------------------------------------------------------------------------------
void sum3_f32vector_red(float32** restrict X, float32** restrict Y, int i, int n)
// ------------------------------------------------------------------------------
{
}
// ----------------------------------------------------------------------------------------------------
void sum3x2_f32matrix_red_pipe(float32** restrict X, float32** restrict Y, float32** restrict Z, int n)
// ----------------------------------------------------------------------------------------------------
{
}
// -----------------------------------------------------------------------------------------------------------
void sum3x2_f32matrix_red_pipe_inline(float32** restrict X, float32** restrict Y, float32** restrict Z, int n)
// -----------------------------------------------------------------------------------------------------------
{
}