#include <string.h>
#include <stdio.h>
#include <stdlib.h>

FILE * openFile(char * file, char * mode)
{
  FILE * f;
  if ((f = fopen(file, mode)) == NULL)
  {
	printf("Erro: %s nao pode ser aberto\n", file);
	exit(1);
  }
  return f;
}

void* s_malloc(int size)
{
  void* result = malloc(size);
  if(result==NULL)
  {
	printf("Erro ao alocar memoria!\n");
	exit(2);
  }
  return result;
}

char** readLines(FILE* file, int* count)
{
  char * password;
  char ** vetor;
  int d, m, y;
  *count = 0;
  vetor = (char ** ) s_malloc(50 * sizeof(char * ));

  while ((!feof(file)))
  {
	password = (char * ) s_malloc(sizeof(char) * 64);
	int np = fscanf(file, "%d %d %d\t%s", & d, & m, & y, password);
	if(np!=EOF)
	{
	  if(np!=4){
		printf("Erro proximo a linha %d.\n", *count + 1);
		exit(3);
	  }
	} 
	printf("%d %d %d\t%s\n", d, m, y, password);
	vetor[(*count)++] = password;
  }
  return vetor;
}

int updatePassword(char** vetor, int count, int id, char* newPassword)
{
  int changed = 0;
  for (int i = 0; i < count; i++)
  {
	if (i == id)
	{
	  if(strcmp(vetor[i], newPassword))
	  {
		free(vetor[i]);
		vetor[i] = (char*)s_malloc((strlen(newPassword) + 1) * sizeof(char));
		strcpy(vetor[i], newPassword);
		changed = 1;
		printf("your password has successfully changed\n");
	  }
	  else
	  {
		printf("you typed the same password\n");
	  }
	}
  }
  return changed;
}

void writeLines(FILE* file, char** vetor, int count, int changed, int id)
{
  for (int i = 0; i < count; i++)
  {
	if (i == id && changed)
	  fprintf(file, "%s\tALTERADO", vetor[i]);
	else
	  fprintf(file, "%s", vetor[i]);
	if(i!=count-1) fprintf(file, "\n");
	free(vetor[i]);
  }
}

int main()
{
  FILE * inputFile = openFile("T22-senhas.txt", "r");
  FILE * outputFile = openFile("T22-novasSenhas.txt", "w");
  int count;
  char ** vetor = readLines(inputFile, &count);

  int id;
  char newPassword[64];

  printf("\ntype your id:\n>>> ");
  scanf("%d", &id);
  printf("type your new password\n>>> ");
  scanf("%s", newPassword);

  int changed = updatePassword(vetor, count, id, newPassword);
  writeLines(outputFile, vetor, count, changed, id);

  fclose(inputFile);
  fclose(outputFile);
  free(vetor);
  return 0;
}
