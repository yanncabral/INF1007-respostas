#include <math.h>
#include <stdio.h>

#define PI 3.14159265f

void trianEq(float lado, float* area){
  *area = ((float) pow(lado,2)) * ((float) sqrt(3.0f)/4.0f);
}

void circulo(float area, float* raio, float* perimetro){
  *raio = (float) sqrt(area/PI);
  *perimetro = (float)(2 * *raio * PI);
}

int main(){
  float lado, area, raio, perimetro;
  printf("Digite o valor do lado: ");
  scanf("%f", &lado);
  trianEq(lado, &area);
  circulo(area, &raio, &perimetro);
  printf("Lado: %f Area: %f Raio: %f Circunferencia: %f\n", lado,area,raio,perimetro);
  return 0;
}


