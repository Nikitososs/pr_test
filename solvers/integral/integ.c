#include <math.h>

double Integ(double a, double b, int n, double f()) {
  double h = (b - a) / n;
  double integ = 0;
  for (int i = 0; i < n; i++) {
    integ += (f(a) + f(a + h)) / 2 * h;
    a = a + h;
  }
  return integ;
}
