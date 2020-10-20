void pa1p3(int n, double c[n][n], double a[n][n], double b[n][n]) {
  int i, j, k;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      for (k = 0; k < n; k++)
        c[j][i] = c[j][i] + a[k][j] * b[k][i];
}
