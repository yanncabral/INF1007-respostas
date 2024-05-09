#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
	float p[2];
} Ponto;

typedef struct { 
	Ponto centro;
	float raio;
} Circulo;


typedef struct elemento { 
	Circulo *circulo;
	struct elemento *prox;
} Elemento;

Elemento* lst_cria (void){
	return NULL; 
}

static float calcula_distancia(Ponto ponto){
	float x = ponto.p[0];
	float y = ponto.p[1];
	return sqrt(pow(x, 2) + pow(y,2));
}

Elemento* lst_insere(Elemento* lst, Ponto ponto, float raio) {
	Elemento* novo;
	Circulo* novoCirculo;
	if(lst != NULL && calcula_distancia(ponto) <= calcula_distancia(lst->circulo->centro)){
		printf("Circulo de centro P(%.1f, %.1f) rejeitado.\n",
			ponto.p[0], 
			ponto.p[1]
		);
		return lst;
	}

	novo = (Elemento*) malloc(sizeof(Elemento)); 
	novoCirculo = (Circulo*) malloc(sizeof(Circulo)); 
	if (novo==NULL || novoCirculo == NULL){
		return NULL;
	}
	novoCirculo->centro = ponto;
	novoCirculo->raio = raio;
	novo->circulo = novoCirculo;
	novo->prox = lst;
	return novo;
}

void lst_libera (Elemento* lst) {
	if(lst){
		lst_libera(lst->prox);
		free(lst->circulo);
		free(lst);
	}
}

void lst_libera_sem_circulo(Elemento* lst) {
	if(lst){
		lst_libera_sem_circulo(lst->prox);
		free(lst);
	}
}

void array_uniao(int left[], int right[], int left_size, int right_size, int *result, int *count) { 
	int i = 0, j = 0; *count = 0;

	while (i < left_size && j < right_size) { 
		if (left[i] < right[j]){
			*(result++) = left[i++];
			*count += 1;
		}
		else if (right[j] < left[i]){
			*(result++) = right[j++];
			*count += 1;
		} 
		else { 
			*(result++) = right[j++];
			i++; 
			*count += 1;
		} 
	} 

	while (i < left_size){
		*count += 1;
		*(result++) = left[i++];
	} 
	while (j < right_size) {
		*count += 1;
		*(result++) = right[j++];
	}
} 

static void array_imprime(int* arr, int size){
	printf("[");
	for(int i = 0; i < size; i++){
		printf("%d, ", arr[i]);
	}
	printf("\b\b]\n");
}

void lst_imprime(Elemento* lst){
	if(lst){
		printf("Centro(%.2f, %.2f); raio: %.2f\n", 
		lst->circulo->centro.p[0],
		lst->circulo->centro.p[1],
		lst->circulo->raio);
		lst_imprime(lst->prox);
	}
}

Elemento *lst_insere_circulo(Elemento *lst, Circulo *circulo){
	Elemento* novo = (Elemento*) malloc(sizeof(Elemento)); 
	if (novo==NULL){
		return NULL;
	}
	novo->circulo = circulo;
	novo->prox = lst;
	return novo;
}

int checa_primeiro_quadrante(Circulo *circulo){
	float x = circulo->centro.p[0];
	float y = circulo->centro.p[1];
	float raio = circulo->raio;
	return x - raio >= 0 && y - raio >= 0;
}

Elemento *primeiro_quadrante(Elemento *lst, int *n){
	Elemento* result = lst_cria();
	*n = 0;
	float maior_distancia = -1;
	while(lst){
		if(checa_primeiro_quadrante(lst->circulo)) {
			result = lst_insere_circulo(result, lst->circulo);
			*n += 1;
		}
		lst = lst->prox;
	}
	return result;
}

int main(){

	/* questão 1 */
	int left1[] =  {1, 2, 4};
	int right1[] = {1, 3, 5, 6};
	int left2[] =  {2, 6, 12};
	int right2[] = {1, 9, 10, 11, 12};
	int left3[] =  {7, 8, 9};
	int right3[] = {7, 8, 9};
	int result[30];
	int size_of_result;
	array_uniao(left1, right1, 3, 4, result, &size_of_result);
	array_imprime(result, size_of_result);
	array_uniao(left2, right2, 3, 5, result, &size_of_result);
	array_imprime(result, size_of_result);
	array_uniao(left3, right3, 3, 3, result, &size_of_result);
	array_imprime(result, size_of_result);

	/* questão 2 */
	Elemento* lst;
	Elemento* lista_filtrada;
	int n;

	/*
	checar se o retorno eh null, como proposto no enunciado,
	nao funcionaria porque caso um circulo seja recusado e a lista retorne vazia,
	 seria tratado como falha de memoria tambem.
	*/

	lst = lst_cria();
	lst = lst_insere(lst, (Ponto) {1, 1}, 2);
	lst = lst_insere(lst, (Ponto) {6, 2}, 1);
	lst = lst_insere(lst, (Ponto) {9, 5}, 2);
	lst = lst_insere(lst, (Ponto) {14, 2}, 1);
	lst = lst_insere(lst, (Ponto) {12, 1}, 2);
	lst = lst_insere(lst, (Ponto) {17, 1}, 2);
	lista_filtrada = primeiro_quadrante(lst, &n);

	printf("\nLista a ser filtrada: \n\n");
	lst_imprime(lst);
	printf("\nCirculos no primeiro quadrante: \n\n");
	lst_imprime(lista_filtrada);
	printf("(%d circulos no primeiro quadrante)", n);

	printf("\nLimpando memoria e comecando segundo teste. \n\n");
	lst_libera_sem_circulo(lista_filtrada);
	lst_libera(lst);

	lst = lst_cria();
	lst = lst_insere(lst, (Ponto) {7, 3}, 2);
	lst = lst_insere(lst, (Ponto) {4, 0}, 1);
	lst = lst_insere(lst, (Ponto) {15, -1}, 2);
	lst = lst_insere(lst, (Ponto) {-1, -1}, 2);
	lst = lst_insere(lst, (Ponto) {12, 0}, 1);
	lista_filtrada = primeiro_quadrante(lst, &n);

	printf("\nLista a ser filtrada: \n\n");
	lst_imprime(lst);
	printf("\nCirculos no primeiro quadrante: \n\n");
	lst_imprime(lista_filtrada);
	printf("(%d circulos no primeiro quadrante)", n);

	printf("\nLimpando memoria e comecando terceiro teste. \n\n");
	lst_libera_sem_circulo(lista_filtrada);
	lst_libera(lst);

	lst = lst_cria();
	lst = lst_insere(lst, (Ponto) {-1, -1}, 2);
	lst = lst_insere(lst, (Ponto) {-6, -2}, 1);
	lst = lst_insere(lst, (Ponto) {-9, -5}, 2);
	lst = lst_insere(lst, (Ponto) {-14, -2}, 1);
	lst = lst_insere(lst, (Ponto) {-12, -1}, 2);
	lst = lst_insere(lst, (Ponto) {-17, -1}, 2);
	lista_filtrada = primeiro_quadrante(lst, &n);

	printf("\nLista a ser filtrada: \n\n");
	lst_imprime(lst);
	printf("\nCirculos no primeiro quadrante: \n\n");
	lst_imprime(lista_filtrada);
	printf("(%d circulos no primeiro quadrante)", n);

	printf("\nLimpando memoria e finalizando. \n\n");
	lst_libera_sem_circulo(lista_filtrada);
	lst_libera(lst);

	return 0;
}
