// Your solution goes in this file. You should not change the function prototype.

void pa1p2opt(int n, double x[n][n][n], double y[n][n]) {

// TODO: Modify the code below to improve performance.
// After making changes, run Make and run the executable file pa1-p2-sol.
// Performance of the base code and your modified code will be reported.
// If the correctness check fails, it will be reported.
// The only code changes must be below this line.

  int i, j, k;
  double sum;
  for (i = 0; i < n; i++)
    for (k = 0; k < n; k++) {
      sum = 0.0;
      for (j = 0; j < n; j++)
        sum += x[i][j][k] * x[i][j][k];
      y[i][k] = sum;
    }
}

