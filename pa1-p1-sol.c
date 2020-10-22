// Your solution goes here. You should not change the function prototype.
void pa1p1opt(int n, double m[][n], double x[n], double y[n], double z[n]) {
  int i, j;
// TODO: Modify this code to improve performance.
// After making changes, run Make and run the executable file pa1-p1-sol.
// Performance of the base code and your modified code will be reported.
// If the correctness check fails, it will be reported.
// The only code changes must be below this line.
/*
   for (i = 0; i < n; i++)
     for (j = 0; j < n; j++) {
       y[j] = y[j] + m[i][j] * x[i];
       z[j] = z[j] + m[j][i] * x[i];
     }
*/


// j-tiled loop version:

/*
const int j_tile = 128;

for (jj = 0; jj < n; jj+= j_tile)
    for (i = 0; i < n; i++) {
#pragma vector aligned
        for (j = jj; j < jj+j_tile; j++) {
           y[j] = y[j] + m[i][j] * x[i];
       	   z[j] = z[j] + m[j][i] * x[i];
        }
    }
*/
 

// i,j-tiled loop version (this is better than simply j tiled version)
// BEST SO FAR
/*
const int j_tile = 64; // best so far: 64 @0.79 GFLOPS (>=128 bad)
const int i_tile = 64; // best so far: 128/64/16/32 (all about the same)

for (ii = 0; ii < n; ii += i_tile)
for (jj = 0; jj < n; jj+= j_tile)
    for (i = ii; i < ii+i_tile; i++) {
#pragma vector aligned
        for (j = jj; j < jj+j_tile; j++) {
           y[j] = y[j] + m[i][j] * x[i];
       	   z[j] = z[j] + m[j][i] * x[i];
        }
    }
*/

// i-j inverted i-j tiled loop version 
/*
const int j_tile = 32; // best so far: 64 @0.50 GFLOPS (>=128 bad)
const int i_tile = 32; // best so far: 128/64/16/32 (all about the same)

for (jj = 0; jj < n; jj+= j_tile)
for (ii = 0; ii < n; ii += i_tile)
#pragma vector aligned
    for (j = jj; j < jj+j_tile; j++) {
    for (i = ii; i < ii+i_tile; i++) {
           y[j] = y[j] + m[i][j] * x[i];
       	   z[j] = z[j] + m[j][i] * x[i];
        }
    }

*/
/*
const int j_tile = 64; // best so far: 64 @0.79 GFLOPS (>=128 bad)
const int i_tile = 64; // best so far: 128/64/16/32 (all about the same)

double y_copy = y;
double z_copy = z;

for (ii = 0; ii < n; ii += i_tile)
  for (jj = 0; jj < n; jj+= j_tile)
    for (i = ii; i < ii+i_tile; i++) {
#pragma vector aligned
      for (j = jj; j < jj+j_tile; j++) {
         y[j] = y[j] + m[i][j] * x[i];
 	 z[j] = z[j] + m[j][i] * x[i];
      }
    }
*/

/* COPY y and z to unblock operation
 * // FIXME: I am making an error copying into memory
  double *y_copy;
  y_copy = (double *) malloc(sizeof(y));
  double *z_copy;
  z_copy = (double *) malloc(sizeof(z));

  memcpy(y_copy, y, sizeof(y));
  memcpy(z_copy, z, sizeof(z));

  for (j = 0; j < n; j++) { // Inverted loops
    for (i = 0; i < n; i++)
       y[j] = y_copy[j] + m[i][j] * x[i];
       z[j] = z_copy[j] + m[j][i] * x[i];
     }
*/

/*
const int j_tile = 64; // best so far: 64 @0.79 GFLOPS (>=128 bad)
const int i_tile = 64; // best so far: 128/64/16/32 (all about the same)
int xi;

for (ii = 0; ii < n; ii += i_tile)
for (jj = 0; jj < n; jj+= j_tile)
    for (i = ii; i < ii+i_tile; i++) {
        xi = x[i]; // This doesn't improve performance
#pragma vector aligned
        for (j = jj; j < jj+j_tile; j++) {
           y[j] = y[j] + m[i][j] * xi;
       	   z[j] = z[j] + m[j][i] * xi;
        }
    }
*/

/* 2-way j-loop unroll
 * // CORRECT, but doesn't improve performance at all
   for (i = 0; i < n; i++)
     for (j = 0; j < n-1; j+=2) {
       y[j] = y[j] + m[i][j] * x[i];
       y[j+1] = y[j+1] + m[i][j+1] * x[i];
       z[j] = z[j] + m[j][i] * x[i];
       z[j+1] = z[j+1] + m[j+1][i] * x[i];
     }
*/

/* 4-way j-loop unroll 
 *CORRECT: but doesn't improve performance at all
   for (i = 0; i < n; i++)
     for (j = 0; j < n-3; j+=4) {
       y[j] = y[j] + m[i][j] * x[i];
       y[j+1] = y[j+1] + m[i][j+1] * x[i];
       y[j+2] = y[j+2] + m[i][j+2] * x[i];
       y[j+3] = y[j+3] + m[i][j+3] * x[i];
       z[j] = z[j] + m[j][i] * x[i];
       z[j+1] = z[j+1] + m[j+1][i] * x[i];
       z[j+2] = z[j+2] + m[j+2][i] * x[i];
       z[j+3] = z[j+3] + m[j+3][i] * x[i];
     }

*/

// i-loop unroll 
// 2-way 0.45 GFLOPS
// 3-way 0.49 GFLOPS
// 4-way: 0.58 GFLOPS
// 8-way: 0.58 GFLOPS
/*
   for (i = 0; i < n-7; i+=8)
     for (j = 0; j < n; j++) {
       y[j] = y[j] + m[i][j] * x[i];
       y[j] = y[j] + m[i+1][j] * x[i+1];
       y[j] = y[j] + m[i+2][j] * x[i+2];
       y[j] = y[j] + m[i+3][j] * x[i+3];
       y[j] = y[j] + m[i+4][j] * x[i+4];
       y[j] = y[j] + m[i+5][j] * x[i+5];
       y[j] = y[j] + m[i+6][j] * x[i+6];
       y[j] = y[j] + m[i+7][j] * x[i+7];

       z[j] = z[j] + m[j][i] * x[i];
       z[j] = z[j] + m[j][i+1] * x[i+1];
       z[j] = z[j] + m[j][i+2] * x[i+2];
       z[j] = z[j] + m[j][i+3] * x[i+3];
       z[j] = z[j] + m[j][i+4] * x[i+4];
       z[j] = z[j] + m[j][i+5] * x[i+5];
       z[j] = z[j] + m[j][i+6] * x[i+6];
       z[j] = z[j] + m[j][i+7] * x[i+7];
     }
*/

/*
// i-j loop unroll
// i_factor=2, j_factor=2: 0.49 GFLOPS
// TODO: try larger unroll factors
   for (i = 0; i < n-1; i+=2)
     for (j = 0; j < n-1; j+=2) 
     {

       y[j] = y[j] + m[i][j] * x[i];
       y[j] = y[j] + m[i+1][j] * x[i+1];

       y[j+1] = y[j+1] + m[i][j+1] * x[i];
       y[j+1] = y[j+1] + m[i+1][j+1] * x[i+1];

       z[j] = z[j] + m[j][i] * x[i];
       z[j] = z[j] + m[j][i+1] * x[i+1];

       z[j+1] = z[j+1] + m[j+1][i] * x[i];
       z[j+1] = z[j+1] + m[j+1][i+1] * x[i+1];
     }

*/

//  Split the loops (because the work in each array doesn't depend on one another)
//  2.14 GFLOPs
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) 
      y[j] = y[j] + m[i][j] * x[i];

  for (j = 0; j < n; j++)
    for (i = 0; i < n; i++)
      z[j] = z[j] + m[j][i] * x[i];

/*
// Split loops and tile inner loops
// 2.03 GFLOPs (tiling doesn't help)
  int jj, ii;
  const int j_tile = 4096;
  const int i_tile = 4096;

for (jj = 0; jj < n; jj+=j_tile)
  for (i = 0; i < n; i++)
    for (j = jj; j < jj+j_tile; j++) 
      y[j] = y[j] + m[i][j] * x[i];

for (ii = 0; ii < n; ii+=i_tile)
  for (j = 0; j < n; j++)
    for (i = ii; i < ii+i_tile; i++)
      z[j] = z[j] + m[j][i] * x[i];
*/

}

