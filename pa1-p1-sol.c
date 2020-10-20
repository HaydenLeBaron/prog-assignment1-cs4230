// Your solution goes here. You should not change the function prototype.
void pa1p1opt(int n, double m[][n], double x[n], double y[n], double z[n]) {
  int i, j;
// TODO: Modify this code to improve performance.
// After making changes, run Make and run the executable file pa1-p1-sol.
// Performance of the base code and your modified code will be reported.
// If the correctness check fails, it will be reported.
// The only code changes must be below this line.
   for (i = 0; i < n; i++)
     for (j = 0; j < n; j++) {
       y[j] = y[j] + m[i][j] * x[i];
       z[j] = z[j] + m[j][i] * x[i];
     }
 }

