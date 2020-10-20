// Your solution goes in this file. You should not change the function prototype.

void pa1p3opt(int n, double c[n][n], double a[n][n], double b[n][n]) {
  int i, j, k;
// TODO: Modify the code below to improve performance.
// After making changes, run Make and run the executable file pa1-p3-sol.
// Performance of the base code and your modified code will be reported.
// If the correctness check fails, it will be reported.
// The only code changes must be below this line.
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      for (k = 0; k < n; k++)
        c[j][i] = c[j][i] + a[k][j] * b[k][i];
}

