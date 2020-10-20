void pa1p1(int n, double m[][n], double x[n], double y[n], double z[n]) {
  int i, j;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      y[j] = y[j] + m[i][j] * x[i];
      z[j] = z[j] + m[j][i] * x[i];
    }
}
