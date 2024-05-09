#include <stdio.h>

int somaPares(int* v, int n){
  if(n)
	return somaPares(v+1, n-1) + ( (*v>0 && !(v[0]%2) )?*v:0);
  return 0;
}

int somaDigitos(int n){
  if(!n) return 0;
  return n%10 + somaDigitos(n/10);
}

int main(){
  int v[] = {5,-3,-2,2,8,1,7,4};
  int n = 8;
  int result = somaPares(v, n);
  printf("A soma é: %d\n", result);
  printf("A soma de %d é: %d\n", 123, somaDigitos(123));
  printf("A soma de %d é: %d\n", 365, somaDigitos(365));
  printf("A soma de %d é: %d\n", 3651, somaDigitos(3651));
  return 0;
}
