#include <stdio.h>
#include <stdlib.h>

int* pares(int* vector, int j, int* count)
{
  int i;
  for(*count = 0, i = 0; i<j; i++)
	*count += !((vector[i]) % 2);
  if(*count==0) return NULL;
  int* result = (int*) malloc(*count*sizeof(int)), *head = result;
  if(!result) return NULL;
  for(i = 0; i<j; i++)
	if(!((vector[i]) % 2))
	  *(result++) = vector[i];
  return head;
}

void printIntArray(int* vector, int j){
	for(int i = 0; i<j; i++)
		printf("%d ", vector[i]);
	putchar('\n');
}

int main(){
  int vector[] = {1,2,3,4,5};
  int lenght = 5;
  int count = 0;
  printf("Vetor original:\n");
  printIntArray(vector, lenght);
  int* vpares = pares(vector, lenght, &count);
  if(vpares){
	printf("Vetor de pares:\n");
	printIntArray(vpares, count);
	free(vpares);
  } else if(count==0) printf("Não tinha números pares.");

  return 0;
}
