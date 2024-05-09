/***********************************************************************
NOME COMPLETO: YANN CABRAL DIAS
MATRICULA PUC-Rio: 1913089
DATA: 18/06/2020
DISCIPLINA: INF1007 TURMA (33A, 33B): 33B
DECLARACAO DE AUTORIA:
Declaro que este documento foi produzido em sua totalidade por mim,
sem consultas a outros alunos, professores ou qualquer outra pessoa. ************************************************************************/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/* interface */
typedef struct node
{
  float noise;
  struct node *next;
}
* Node;
Node list_append(Node head, float noise);
void list_print(Node head);
float list_sum(Node head);
int list_count(Node head);
void list_free(Node head);
int node_search(int len, Node* items, int key);
void rooms_print(Node* rooms, int len);
void rooms_free(Node* rooms, int len);

/* implementation */

Node list_append(Node head, float noise)
{
  Node result = (Node) malloc(sizeof(struct node));
  assert(result);
  result->next = head;
  result->noise = noise;
  return result;
}

void list_print(Node head)
{
  if(head)
  {
	printf("[%.2fdB]->", head->noise);
	list_print(head->next);
  } else{
	printf("NULL\n");
  }
}

float list_sum(Node head)
{
  if(head)
	return head->noise + list_sum(head->next);
  return 0;
}

int list_count(Node head)
{
  if(head)
	return 1 + list_count(head->next);
  return 0;
}

void list_free(Node head)
{
  if(head)
  {
	list_free(head->next);
	free(head);
  }
}

static int node_cmp(int size, Node b)
{
  int count = list_count(b);
  if (size==count)
	return 0;
  return (size > count)*2-1;
}

int node_search(int len, Node* items, int key)
{
  int low, high, mid, cmp;
  low = 0; high = len-1;
  while (low <= high) {
	mid = (low+high)/2;
	cmp = node_cmp(key, items[mid]);
	if(cmp<0) high = mid-1;
	else if (cmp>0) low = mid + 1;
	else {
	  while (mid<len-1 && !node_cmp(key, items[mid + 1])) mid++;
	  return mid;
	}
  }
  return -1;
}

void rooms_print(Node* rooms, int len)
{
  int i;
  for(i=0; i<len; i++)
  {
	printf("Exibindo informacoes da sala %d:\n", i);
	printf("* Numero de quipamentos: %d:\n", list_count(rooms[i]));
	printf("* Ruido total: %.2fdB:\n", list_sum(rooms[i]));
	printf("* Ruidos de cada equipamento:\n");
	list_print(rooms[i]);
	printf("\n");
  }
}

void rooms_free(Node* rooms, int len)
{
  int i;
  for(i=0; i<len; i++)
  {
	list_free(rooms[i]);
  }
  free(rooms);
}

int main()
{
  int len = 8, i, search;
  Node *rooms = (Node*) malloc(len*sizeof(Node));
  assert(rooms);

  /* criando vetores */
  for(i = 0; i < len; i++)
	rooms[i] = NULL;

  rooms[0] = list_append(rooms[0], 21.0f);
  /* letra a */
  rooms[1] = list_append(list_append(rooms[1],    0.0f), 19.0f);
  rooms[2] = list_append(list_append(rooms[2],  100.0f), 30.0f);
  rooms[3] = list_append(list_append(rooms[3],  800.0f), 90.0f);
  /* letra b */
  for(i = 4; i < len; i++)
  {
	rooms[i] = list_append(rooms[i],  (float) i*i);
	rooms[i] = list_append(rooms[i],  (float) i*i*i);
	rooms[i] = list_append(rooms[i],  (float) i*i*i*i);
  }
  rooms_print(rooms, len);
  /* testando a busca */

  search = node_search(len, rooms, 2);
  if(search>0)
  {
	printf("Indice da sala com 2 equipamentos: %i.\n", search);
  } else {
	printf("Nenhuma sala foi encontrada com 2 equipamentos.\n");
  }
  search = node_search(len, rooms, 3);
  if(search>0)
  {
	printf("Indice da sala com 3 equipamentos: %i.\n", search);
  } else {
	printf("Nenhuma sala foi encontrada com 3 equipamentos.\n");
  }
  search = node_search(len, rooms, 4);
  if(search>0)
  {
	printf("Indice da sala com 4 equipamentos: %i.\n", search);
  } else {
	printf("Nenhuma sala foi encontrada com 4 equipamentos.\n");
  }

  /* liberando memoria */
  rooms_free(rooms, len);
  return 0;
}
