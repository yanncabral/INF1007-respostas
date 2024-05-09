#include <stdio.h>
#include <string.h>


typedef struct bioData BioData;
typedef struct cliente Cliente;


struct bioData
{
   float peso;
   float altura;
};

struct cliente
{
   char nome[81];
   int id;
   BioData bio;
};


void exibeCliente(Cliente cliente){
  printf("Informações sobre o cliente %d:\n", cliente.id);
  printf("\tNome: %s\n", cliente.nome);
  printf("\tPeso: %.2fkg\n", cliente.bio.peso);
  printf("\tAltura: %.2fm\n", cliente.bio.altura);
}

float calculaIMC(Cliente cliente, int *status){
  float imc = cliente.bio.peso / (cliente.bio.altura*cliente.bio.altura);
  *status = imc >= 25;
  return imc;
}


int main(void) {
  char* messages[] = {"abaixo do peso", "acima do peso"};
  int status;
  float imc;
  Cliente c1 = {"Yann", 1, {61.5f, 1.87f}};
  Cliente c2;
  strcpy(c2.nome, "Hannah");
  c2.id = 2;
  c2.bio.peso = 57.0f;
  c2.bio.altura = 1.61f;

  imc = calculaIMC(c1, &status);
  exibeCliente(c1);
  printf("Com imc %.2f, está %s.\n\n", imc, messages[status]);

  imc = calculaIMC(c2, &status);
  exibeCliente(c2);
  printf("Com imc %.2f, está %s.\n\n", imc, messages[status]);
  return 0;
}