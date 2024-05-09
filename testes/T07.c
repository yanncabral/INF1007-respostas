#include <stdio.h>

int main()
{
  int chars = 0, lines = 0;
  int c;

  while ((c = getc(stdin)) != EOF)
  {
	if(c == '\n')
	{
	  lines++;
	} else
	{
	  chars++;
	}
  }

  printf("\nContagem: %i caracteres e %i linhas.\n", chars, lines); 

  return 0;
}