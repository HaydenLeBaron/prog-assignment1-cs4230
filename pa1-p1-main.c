// NOTE: No modifications are allowed on this file
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#define N 4096
#define Niter 10
#define threshold 0.0000001

double A[N][N], x[N], y[N], z[N], yy[N], zz[N];
void compare(int n, double wref[n], double w[n]);
void pa1p1(int n, double m[][n], double x[n], double y[n], double z[n]);
void pa1p1opt(int n, double m[][n], double x[n], double y[n], double z[n]);
int main() {

  double clkbegin, clkend;
  double t;
  double rtclock();

  int i, j, it;

  for (i = 0; i < N; i++) {
    x[i] = i;
    y[i] = 0;
    z[i] = 1.0;
    yy[i] = 0;
    zz[i] = 1.0;
    for (j = 0; j < N; j++)
      A[i][j] = (i + 2.0 * j) / (2.0 * N);
  }

  clkbegin = rtclock();
  for (it = 0; it < Niter; it++)
    pa1p1(N, A, x, y, z);
  clkend = rtclock();

  t = clkend - clkbegin;
  if (y[N / 2] * y[N / 2] < -100.0)
    printf("%f\n", y[N / 2]);
  if (z[N / 2] * z[N / 2] < -100.0)
    printf("%f\n", z[N / 2]);
  printf("Problem 1 Reference Version: Matrix Size = %d; %.2f GFLOPS; Time = "
         "%.3f sec; \n",
         N, 4.0 * 1e-9 * N * N * Niter / t, t);

  for (i = 0; i < N; i++) {
    yy[i] = 0;
    zz[i] = 1.0;
  }
  clkbegin = rtclock();
  for (it = 0; it < Niter; it++)
    pa1p1opt(N, A, x, yy, zz);
  clkend = rtclock();
  t = clkend - clkbegin;
  if (yy[N / 2] * yy[N / 2] < -100.0)
    printf("%f\n", yy[N / 2]);
  if (zz[N / 2] * zz[N / 2] < -100.0)
    printf("%f\n", zz[N / 2]);
  printf("Problem 1 Optimized Version: Matrix Size = %d; %.2f GFLOPS; Time = "
         "%.3f sec; \n",
         N, 4.0 * 1e-9 * N * N * Niter / t, t);
  printf("Checking correctness for y: "); compare(N, y, yy);
  printf("Checking correctness for z: "); compare(N, z, zz);
  return 0;
}

double rtclock() {
  struct timezone Tzp;
  struct timeval Tp;
  int stat;
  stat = gettimeofday(&Tp, &Tzp);
  if (stat != 0)
    printf("Error return from gettimeofday: %d", stat);
  return (Tp.tv_sec + Tp.tv_usec * 1.0e-6);
}

void compare(int n, double wref[n], double w[n]) {
  double maxdiff, this_diff;
  int numdiffs;
  int i;
  numdiffs = 0;
  maxdiff = 0;
  for (i = 0; i < n; i++) {
    this_diff = wref[i] - w[i];
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
  else
    printf("Passed Correctness Check\n");
}
