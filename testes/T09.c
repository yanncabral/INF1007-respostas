#include <stdio.h>
#include <string.h>

#define IN 1
#define OUT 0

int main(void)
{
	int state = OUT, c, words = 0, lines = 1, characteres = 0;
	int last;
	state = OUT;
	while ((c=getc(stdin)) != EOF) {
	characteres++;

	lines += (c=='\n');

	if(c=='\n' || c=='\t' || c==' ')
	  state = OUT;
	else if (state==OUT){
	  state = !state;
	  words++;
	}
		last = c;
	}
	if(last=='\n') lines--;
	printf("\nlines: %d, words: %d, characters: %d\n", lines, words, characteres);
	return 0;
}
