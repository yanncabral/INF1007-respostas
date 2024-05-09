#include <stdio.h>

double harmonica(int n){
  if(n) return 1.0/n + harmonica(n-1);
  return 0;
}

int soma(int* v, int n){
  if(n) return v[n-1] + soma(v, n-1);
  return 0;
}

int main(){
  double t1 = harmonica(3);
  printf("%.2f\n", t1);
  int v[] = {5,-3,-2,2,8};
  printf("%d\n", soma(v, 5));
}
