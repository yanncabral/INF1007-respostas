#include <stdio.h>

void reverse(float* vector, int j)
{
  int i = 0;
  for(--j; i<j; i++, j--)
  {
	float temp = vector[i];
	vector[i] = vector[j];
	vector[j] = temp;
  }
}

void print_float_array(float* vector, int j)
{
  for(int i = 0; i<j; i++)
	printf("%.2f ", vector[i]);
  putchar('\n');
}

int main()
{
  float vector[] = {1,2,3,4,5};
  int lenght = 5;

  printf("Vetor original:\n");
  print_float_array(vector, lenght);
  reverse(vector, lenght);
  printf("Vetor invertido:\n");
  print_float_array(vector, lenght);

  return 0;
}
