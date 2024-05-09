#include <stdio.h>
#include "geometria.h"

int main(){
  float lado, area, raio, perimetro;
  printf("Digite o valor do lado: ");
  scanf("%f", &lado);
  trianEq(lado, &area);
  circulo(area, &raio, &perimetro);
  printf("Lado: %f Area: %f Raio: %f Circunferencia: %f\n", lado,area,raio,perimetro);
  return 0;
}