// NOTE: No modifications are allowed on this file
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#define N (1000)
#define threshold (0.0000001)
void compare(int n, double wref[][n], double w[][n]);
void pa1p3(int n, double c[n][n], double a[n][n], double b[n][n]);
void pa1p3opt(int n, double c[n][n], double a[n][n], double b[n][n]);
double c[N][N], b[N][N], a[N][N], cc[N][N];

int main(int argc, char *argv[]) {
  double rtclock(void);
  double clkbegin, clkend;
  double t1, t2;

  int i, j, k, it, jt, kt, iub, jub, kub, rem;

  printf("Matrix Size = %d\n", N);

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++) {
      a[i][j] = 1.1 * (2 * i + j);
      b[i][j] = 1.2 * (i + 2 * j);
    }
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      c[i][j] = cc[i][j] = 0;
  t1 = rtclock();
  pa1p3(N, c, a, b);
  t2 = rtclock();
  printf("Problem 3 Reference Version: %.2f GFLOPs; Time = %.2f\n",
         2.0e-9 * N * N * N / (t2 - t1), t2 - t1);

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      cc[i][j] = c[i][j];

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      c[i][j] = 0;
  //
  t1 = rtclock();
  pa1p3opt(N, c, a, b);
  t2 = rtclock();
  printf("Problem 3 Optimized Version: %.2f GFLOPs; Time = %.2f\n",
         2.0e-9 * N * N * N / (t2 - t1), t2 - t1);
  compare(N, c, cc);
  return 0;
}
double rtclock(void) {
  struct timezone Tzp;
  struct timeval Tp;
  int stat;
  stat = gettimeofday(&Tp, &Tzp);
  if (stat != 0)
    printf("Error return from gettimeofday: %d", stat);
  return (Tp.tv_sec + Tp.tv_usec * 1.0e-6);
}

void compare(int n, double wref[][n], double w[][n]) {
  double maxdiff, this_diff;
  int numdiffs;
  int i, j;
  numdiffs = 0;
  maxdiff = 0;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      this_diff = wref[i][j] - w[i][j];
      if (this_diff < 0)
        this_diff = -1.0 * this_diff;
      if (this_diff > threshold) {
        numdiffs++;
        if (this_diff > maxdiff)
          maxdiff = this_diff;
      }
    }
  if (numdiffs > 0)
    printf("Correctness Check Failed: %d Diffs found over threshold %f; Max Diff = %f\n", numdiffs,
           threshold, maxdiff);
  else printf("Correctness Check Passed\n");
}

