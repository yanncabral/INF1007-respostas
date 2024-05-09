#include <stdio.h>

int main(){
	unsigned int count = 0;
  int c;
  while((c = getc(stdin))!=EOF)
  {
	count++;
	putc(c, stdout);
  }
	printf("\n%i caracteres.\n", count);
}
