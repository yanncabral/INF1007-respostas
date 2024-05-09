#include <stdio.h>

void troca(char* s, char a, char b){
  if(*s){
	printf("%c", (*s==a)?b:*s);
	troca(s+1, a, b);
  } else
	printf("%c", '\n');
}

int countNoLetter(char* s){
  if(*s)
	return countNoLetter(s+1) + !((*s>='A' && *s<='Z')||(*s>='a' && *s<='z'));
  return 0;
}

int mdc(int a, int b){
  if(!(a%b)) return b;
  return mdc(b, a%b);
}

int main(){
  char v[] = "NOME";
  char* t[] = {"Ah!Tem35", "Prog2"};
  troca(v, 'O', '_');
  troca(v, 'M', '_');
  troca(v, 'N', '_');
  printf("%s: %d\n", t[0], countNoLetter(t[0]));
  printf("%s: %d\n", t[1], countNoLetter(t[1]));
  printf("O mdc de 32 e 40 é: %d\n", mdc(32,40));
  printf("O mdc de 27 e 9 é: %d\n", mdc(27,9));
  printf("O mdc de 13 e 25 é: %d\n", mdc(13,25));
  return 0;
}
