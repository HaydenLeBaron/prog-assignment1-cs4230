// Your solution goes here. You should not change the function prototype.
void pa1p1opt(int n, double m[][n], double x[n], double y[n], double z[n]) {
  int i, j;
// TODO: Modify this code to improve performance.
// After making changes, run Make and run the executable file pa1-p1-sol.
// Performance of the base code and your modified code will be reported.
// If the correctness check fails, it will be reported.
// The only code changes must be below this line.


//  Split the loops (because the work in each array doesn't depend on one another)
//  C is a row-major order language. Separating into two loops allows us to take 
//  advantage of this fact and leverage spatial locality via caching.
//
//  If we have memory access in arr[j][i], we want the loop order to be j-i.
//  If we have memory access in arr[i][j], we want the loop order to be i-j.
//  Performance of this implementation: 2.14 GFLOPs

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) 
      y[j] = y[j] + m[i][j] * x[i];

  for (j = 0; j < n; j++)
    for (i = 0; i < n; i++)
      z[j] = z[j] + m[j][i] * x[i];
}

