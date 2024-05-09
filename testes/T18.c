#include <stdio.h>
#include <stdlib.h>

void exibeNascimeto(char* c){
  printf("%c%c/%c%c/%c%c%c%c\n", c[6],c[7],c[4], c[5], *c,c[1],c[2],c[3]);
}

char* obtemMae(char* c){
  while(*c!='*') c++;
  return c+1;
}

int _strlen(char* s){
  int result = 0;
  while(*s++) result++;
  return result;
}

char* _strcpy(char* s, char* t){
  while((*s++=*t++)!='\0');
  return s;
}

char* _strncpy(char* s, char* t, int n)
{
  while (*t && n--) (*s++ = *t++);
  *s = '\0';
  return s;
}

char* _strconcat(char*s, char* t){
  char* head = s;
  while(*s!='\0') s++;
  while (*t!='\0') (*s++ = *t++);
  *s = '\0';
  return head;
}

int getNumberOfWords(char* s){
  int result = 0;
  while(*s++) result+= (*s==' ');
  return ++result;
}

char* geraIdentidade(char* nome, char* data, char* mae){
  char dia[3], mes[3], ano[5];
  int i;
  _strncpy(dia,data,2);
  _strncpy(mes,data+3,2);
  _strncpy(ano, data+6, 4);
  int size = getNumberOfWords(nome)+_strlen(mae)+_strlen(data); /* -2+1+1; */
  /* 
  char* id = cmalloc(size, char), *head = id;
  */
  char* id = (char*) malloc(size), *head = id;
  if(!id) return NULL;
  for(i=0; i<size; i++)
  {
	id[i] = '\0';
  }
  _strconcat(id, ano);
  _strconcat(id, mes);
  _strconcat(id, dia);
  id += 8;
  *id++ = *nome;
  for(i=0; i<_strlen(nome); i++)
  {
	if(nome[i]==' ')
	{
	  *id++ = *(nome+i+1);
	}
  }
  *id = '*';
  _strconcat(id,mae);
  return head;
}

int main(){
  char* candidato1 = "19820527RAS*CLARA";
  char* nome = "RUI ABREU SOARES";
  char* data = "27/05/1982";
  char* mae = "CLARA";
  char *x;
  char* id;

  exibeNascimeto(candidato1);
  x = obtemMae(candidato1);
  printf("O nome da mae é: %s\n", mae);

  id = geraIdentidade(nome, data, mae);
  printf("Identidade do cara: %s\n", id);
  free(id);

  nome = "ANTONIO CALADO";
  data = "23/10/2009";
  mae = "EVA";

  id = geraIdentidade(nome, data, mae);
  printf("Identidade do cara: %s\n", id);
  free(id);

  return 0;
}
