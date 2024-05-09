#include <stdio.h>
#include <stdlib.h>

typedef struct ponto Ponto;
struct ponto
{
  float x;
  float y; 
};

FILE* assert_open_file(char* filename){
  FILE* result = fopen(filename, "r");
  if(result == NULL){
	printf("Error na leitura do arquivo. Abortando.");
	exit(2);
  }
  return result;
}

void* assert_memory(void* p){
  if(p == NULL){
	printf("Erro ao alocar memoria. Abortando.");
	exit(1);
  }
  return p;
}

Ponto* get_center_of_polygon(Ponto ** vector_of_points, int vector_length)
{
	Ponto* result = (Ponto*) assert_memory(malloc(sizeof(Ponto)));
	result->x = result->y = 0.0f;
  int i;

	for (i = 0; vector_length > i; i++){
		result->x += vector_of_points[i]->x;
		result->y += vector_of_points[i]->y;
	}

	result->x /= vector_length;
	result->y /= vector_length;

	return result;
}

int main(void)
{
	FILE * file_with_points = assert_open_file("T26-dados.txt");
  Ponto **vector_of_points;
	int vector_length, i;

	fscanf(file_with_points, "%d ", &vector_length);
	vector_of_points = (Ponto**) assert_memory(malloc(vector_length * sizeof(Ponto*)));

  for(i = 0; !feof(file_with_points); i++){
	vector_of_points[i] = (Ponto*) assert_memory(malloc(sizeof(Ponto)));
		fscanf(file_with_points, "%f %f ", &vector_of_points[i]->x, &vector_of_points[i]->y);
		printf("(%.2f,\t%.2f)\n", vector_of_points[i]->x, vector_of_points[i]->y);
  }
  fclose(file_with_points); /* nao precisaremos mais do arquivo */

	Ponto * center_of_polygon = get_center_of_polygon(vector_of_points, vector_length);
	printf("Centro: (%.2f, %.2f)\n",center_of_polygon->x, center_of_polygon->y);
  free(center_of_polygon);

	for (i = 0; i < vector_length; i++){
		free(vector_of_points[i]);
	}
  free(vector_of_points);

	return 0;
}
