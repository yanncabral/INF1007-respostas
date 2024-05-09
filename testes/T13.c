#include <stdio.h>

void maxmin(int *vector, int lenght, int* max, int* min){
  *min = *max = *(vector++);
  for(int index = 1; index<lenght; index++, vector++)
  {
	if(*vector > *max) *max = *vector;
	if(*vector < *min) *min = *vector;
  }
}

int main()
{
  int vector[10], lenght, max, min;
  printf("Digite o tamanho do vetor (max 10): ");
  scanf("%d", &lenght);
  printf("Digite os elementos do vetor: \n");
  int index = 0;
  for(; index<lenght; index++)
	scanf("%d", &vector[index]);
  maxmin(vector, lenght, &max, &min);
  printf("max= %d min=%d\n", max,min);
  return 0;
}