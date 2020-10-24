// Your solution goes in this file. You should not change the function prototype.

void pa1p2opt(int n, double x[n][n][n], double y[n][n]) {

// TODO: Modify the code below to improve performance.
// After making changes, run Make and run the executable file pa1-p2-sol.
// Performance of the base code and your modified code will be reported.
// If the correctness check fails, it will be reported.
// The only code changes must be below this line.

// We started with this code:
/*
  int i, j, k;
  double sum;
  for (i = 0; i < n; i++)
    for (k = 0; k < n; k++) {
      sum = 0.0;
      for (j = 0; j < n; j++)
        sum += x[i][j][k] * x[i][j][k];
      y[i][k] = sum;
    }
*/

// We first can get rid of the sum variable, noticing that we
// can substitute y[i][k] for sum. This doesn't yet improve performance.
// We now have:
/*
  int i, j, k;
  for (i = 0; i < n; i++) {
    for (k = 0; k < n; k++) {
      y[i][k] = 0.0;
      for (j = 0; j < n; j++) {
        y[i][k] += x[i][j][k] * x[i][j][k];
      }
    }
  }
*/

// We were then able to factor out the initialization
// of y[i][k] to 0.0 (for all i and k) to another loop.
// We still have not yet improved performance, but we're almost there!
/*
  int i, j, k;
  for (i=0; i < n; i++)
    for (k=0; k < n; k++)
      y[i][k] = 0.0;

  for (i = 0; i < n; i++) {
    for (k = 0; k < n; k++) {
      for (j = 0; j < n; j++) {
        y[i][k] += x[i][j][k] * x[i][j][k];
      }
    }
  }
*/

// Now that we have separated the work out into different loops, we can use the same 
// optimiztion technique used in problem 1 and change the loop order so that the loop
// order corresponds with the array access patterns. This allows us to leverage spatial
// locality when caching. Now y[i][k] accesses are in  i-k and i-j-k loops, and a x[i][j][k]
// access is in an i-j-k nested loop. 
// This improves performance to 2.74 GFLOPS

  int i, j, k;
  for (i = 0; i < n; i++)
    for (k = 0; k < n; k++)
      y[i][k] = 0.0;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) { 
      for (k = 0; k < n; k++) {
        y[i][k] += x[i][j][k] * x[i][j][k];
      }
    }
  }
 

}

