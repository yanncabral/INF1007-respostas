#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct bioData BioData;
typedef struct cliente *Cliente;


struct bioData
{
  float peso;
  float altura;
};

struct cliente
{
  char *nome;
  int id;
  BioData bio;
};


void exibeCliente(Cliente cliente){
  printf("Informações sobre o cliente %d:\n", cliente->id);
  printf("\tNome:\t%s\n", cliente->nome);
  printf("\tPeso:\t%.2fkg\n", cliente->bio.peso);
  printf("\tAltura:\t%.2fm\n", cliente->bio.altura);
}

float calculaIMC(Cliente cliente, int *status){
  float imc = cliente->bio.peso / (cliente->bio.altura*cliente->bio.altura);
  *status = imc >= 25;
  return imc;
}

void* assertMemory(void* p){
  if(p==NULL){
	printf("Erro ao alocar memoria.");
	exit(1);
  }
  return p;
}

char* string_malloc(int size){
  char* result = (char*) assertMemory(malloc(size*sizeof(char)+1));
  return result;
}

Cliente criarCliente(char* nome, float peso, float altura, int id){
  Cliente result = (Cliente) assertMemory(malloc(sizeof(struct cliente)));

  result->id = id;
  result->nome = string_malloc(strlen(nome));
  strcpy(result->nome, nome);
  result->bio.peso = peso;
  result->bio.altura = altura;

  return result;
}

int main(void) {
  char* messages[] = {"abaixo do peso", "acima do peso"};
  int i;
  Cliente cliente; /* Cliente é um ponteiro, definido no typedef */
  int status;
  float imc;
  char nome[81];
  float altura;
  float peso;
  int id;

  for (i = 0; i < 2; i++){

	printf("Digite o nome (limite de 80 letras):\n>>> ");
	scanf(" %80[^\n]s", nome);
	printf("Digite o peso:\n>>> ");
	scanf("%f", &peso);
	printf("Digite a altura:\n>>> ");
	scanf("%f", &altura);
	printf("Digite o id:\n>>> ");
	scanf("%d", &id);

	cliente = criarCliente(nome, peso, altura, id);
	imc = calculaIMC(cliente, &status);
	exibeCliente(cliente);
	printf("Com imc %.2f, está %s.\n\n", imc, messages[status]);
	free(cliente->nome);
	free(cliente);
  }

  return 0;
}