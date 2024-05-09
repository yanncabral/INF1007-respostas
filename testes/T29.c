#include <stdio.h>
#include <stdlib.h>

typedef int node_type;

typedef struct node
{
	node_type data;
	struct node *next;
}
*Node;

static Node node_create()
{
	Node result = (Node) malloc(sizeof(struct node));
	if(!result)
	{
		printf("Houve um erro ao alocar memoria. Abortando...");
		exit(2);
	}
	return result;
}

Node node_append(Node next, node_type data)
{
	Node result = node_create();
	result->data = data;
	result->next = next;
	return result;
}

Node node_from_array(node_type* data_array, unsigned int len)
{
	Node result = NULL;
	if(len)
	{
		result = node_from_array(data_array+1, len-1);
		result = node_append(result, *data_array);
	}
	return result;
}

void node_print_int(Node node)
{
	printf("[");
	if(!node)
	{
		printf("]");
	} else {
		while(node)
		{
			printf("%i, ", node->data);
			node = node->next;
		}
		printf("\b\b]");
	}
}

void node_println_int(Node node)
{
	node_print_int(node);
	printf("\n");
}

Node node_filter(Node head, node_type match, int* len)
{
	Node temp = NULL;
	if(head)
	{
		temp = node_filter(head->next, match, len);
		if(head->data == match)
		{
			*len += 1;
			free(head);
			return temp;
		}
		head->next = temp;
		return head;
	}
	return NULL;
}

void node_free(Node head)
{
	if(head)
	{
		node_free(head->next);
		free(head);
	}
}

int main()
{
	int len;
	Node tree;
	int i;
	int test_lists[5][64] = {
			{4, 4, 2, 3, 4, 2, 4, 4, 7},    /* size:  9 */
			{14, 15, 16, 17},               /* size:  4 */
			{4, 4, 4, 4},                   /* size:  4 */
			{},                             /* size:  0 */
			{9, 9, 4, 6, 1, 2, 6, 1, 4, 4}  /* size: 10 */
	};
	int test_sizes[] = {9, 4, 4, 0, 10};

	for(i = 0; i < 5; i++)
	{
		len = 0;
		tree = node_from_array(test_lists[i], test_sizes[i]);
		node_print_int(tree);
		printf(" -> ");
		tree = node_filter(tree, 4, &len);
		node_println_int(tree);
		printf("Foram removidos %i elementos [4].\n\n", len);
		node_free(tree);
	}

	return 0;
}
