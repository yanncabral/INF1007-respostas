#include <stdio.h>

double pi_series(int n){
  double pi = 0;
  double signal = 1;
  for(double i = 1; i<=(n*2); i+=2)
  {
	pi += (4/i) * signal;
	signal *= -1;
  }
  return pi;
}

int main(){
  unsigned int terms = 5000;
  double pi = pi_series(terms);
  printf("Gregory Leibniz Series: PI = %.10lf\t(%i termos)\n", pi, terms);
  return 0;
}
