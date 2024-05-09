#include <stdio.h>
#include <stdlib.h>

float* reverse(float* vector, int j)
{
  int i = 0;
  float* result = (float*)malloc(j*sizeof(float));
  if(!result) return NULL;
  for(--j; i<j; i++, j--)
	result[i] = vector[j];
  return result;
}

void print_float_array(float* vector, int j)
{
  for(int i = 0; i<j; i++)
	printf("%.2f ", vector[i]);
  putchar('\n');
}

int main(){
  float vector[] = {1,2,3,4,5};
  int lenght = 5;
  printf("Vetor original:\n");
  print_float_array(vector, lenght);
  float* reversedVector = reverse(vector, lenght);
  if(reversedVector){
	printf("Vetor invertido:\n");
	print_float_array(reversedVector, lenght);
	free(reversedVector);
  }

  return 0;
}
