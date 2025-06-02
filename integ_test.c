#include "integ.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

void test_1() {
  int n = 1000;
  double eps = 1E-6;
  double lower_limit = 2;
  double upper_limit = 5;
  double res = Integ(lower_limit, upper_limit, n, sin);
  assert(fabs(res + 0.699808) < eps);
}

void test_2() {
  int n = 1000;
  double eps = 1E-6;
  double lower_limit = 0;
  double upper_limit = 1;
  double res = Integ(lower_limit, upper_limit, n, cos);
  assert(fabs(res - 0.841471) < eps);
}

void test_3() {
  int n = 1000;
  double eps = 1E-6;
  double lower_limit = 7.77;
  double upper_limit = 9.99;
  double res = Integ(lower_limit, upper_limit, n, log);
  assert(fabs(res - 4.842231) < eps);
}

void test_4() {
  int n = 1000;
  double eps = 1E-5;
  double lower_limit = -1.7;
  double upper_limit = 3.14;
  double res = Integ(lower_limit, upper_limit, n, atan);
  assert(fabs(res - 1.68445) < eps);
}

int main() {
  test_1();
  test_2();
  test_3();
  test_4();

  return 0;
}
