// Your solution goes in this file. You should not change the function prototype.

void pa1p3opt(int n, double c[n][n], double a[n][n], double b[n][n]) {
  int i, j, k;
// TODO: Modify the code below to improve performance.
// After making changes, run Make and run the executable file pa1-p3-sol.
// Performance of the base code and your modified code will be reported.
// If the correctness check fails, it will be reported.
// The only code changes must be below this line.

// We started with this code:
/*
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      for (k = 0; k < n; k++)
        c[j][i] = c[j][i] + a[k][j] * b[k][i];
*/
// But the array access pattern does not line up with
// loop index order. We thus are not taking advantage of
// spatial locality when caching. We have the following access patterns:
//
// c[j][i]
// a[k][j]
// b[k][i]
//
// Thus, the optimal solution will have j before i, k before j, and k before i.
// This implies the pattern k-j-i. Sure enough, when we permute the loops we get
// performance at 6.06 GFLOPs:

 for (k = 0; k < n; k++)
   for (j = 0; j < n; j++)
     for (i = 0; i < n; i++)
        c[j][i] = c[j][i] + a[k][j] * b[k][i];

}

