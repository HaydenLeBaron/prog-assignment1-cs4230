// Your solution goes in this file. You should not change the function prototype.

void pa1p2opt(int n, double x[n][n][n], double y[n][n]) {

// TODO: Modify the code below to improve performance.
// After making changes, run Make and run the executable file pa1-p2-sol.
// Performance of the base code and your modified code will be reported.
// If the correctness check fails, it will be reported.
// The only code changes must be below this line.

/*
// Original
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

/*
// Get rid of sum variable (correct but same performance)
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

/*
// Get rid of sum var and init y[i][k] to 10 for all i, k--to take out of other loop
// (Same performance)
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

// Do everything done before, but this time invert j and k loops
// so that x[i][j][k] is lined up with loop order
// 2.74 GFLOPS
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

