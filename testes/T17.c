#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


char* strUpper(char* s){
	char* result = (char*) malloc(strlen(s) +1), *head = result;
	if(!result) return NULL;
	while((*result++=toupper(*s++))!='\0');
	return head;
}

char* mystrdup(char* s){
	char* result = (char*) malloc(strlen(s) +1), *head = result;
	if(!result) return NULL;
	while((*result++=*s++)!='\0');
	return head;
}

int mystrcmp(char* s, char* t){
  while((*s!='\0') && (*s++==*t++));
  return *(s-1)-*(t-1);
}

char* mystrcat(char* s, char* t){
	for(char* r = s+strlen(s); (*r=*t)!='\0'; r++,t++);
	return s;
}

char* strShift(char* s){
	char* result = (char*) malloc(strlen(s) +1), *head = result;
	if(!result) return NULL;
	for(; *s!='\0'; *result++ = (*s++)+1);
	*s = '\0';
	return head;
}

int main(){

	char s[] = "puc";
	char *w;
	char v[] = "rio";
	char r[] = "Ana";
	char t[] = "-";
	char *u = (char*)malloc(100);
	char z[] = "zaZA";

	w = strUpper(s);
	if(w==NULL) printf("Memória insuficiente.\n");
	printf("%s : %s\n", s,w);
	free(w);
	w = mystrdup(s);
	if(w!=NULL){
		printf("%s duplicada em %s\n", s,w);
		printf("%s comparada com %s: %d\n", s,w, mystrcmp(s,w));
		printf("%s comparada com %s: %d\n", s,v, mystrcmp(s,v));
		printf("%s comparada com %s: %d\n", v,s, mystrcmp(v,s));
		strcpy(u,s);
		printf("concatena %s com %s e com %s\n",v,t,u);
		u = mystrcat(mystrcat(u,t),v);
		printf("string final: %s\n", u);
		free(u);
	} else printf("Memória insuficiente.\n");
	free(w);
	w = strShift(r);
	if(w!=NULL)
		printf("%s shifted to %s\n",r,w);
	else
		printf("Memória insuficiente.\n");
	free(w);
	w = strShift(z);
	if(w!=NULL)
		printf("%s shifted to %s\n",z,w);
	else
		printf("Memória insuficiente.\n");
	free(w);
	return 0;
}
