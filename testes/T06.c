#include <stdio.h>

int main(){
	int count = 0;
	while(getc(stdin)!=EOF)
		count++;
	printf("%i caracteres.", count);
}