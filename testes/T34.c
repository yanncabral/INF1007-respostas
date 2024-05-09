#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/* interface */

typedef int node_type;

typedef struct node
{
	node_type data;
	struct node * next;
}
* Node;

typedef struct queue
{
	Node front;
	Node rear;
}
* Queue;

Queue queue_create(void);
int queue_is_empty(Queue self);
Queue queue_insert(Queue self, node_type data);
node_type queue_remove(Queue self);
void queue_free(Queue self);
Queue queue_reverse(Queue self);
void queue_print(Queue self);

/* implementation */

Queue
queue_create(void)
{
	Queue result = (Queue) malloc(sizeof(struct queue));
	assert(result);
	result->rear = result->front = NULL;
	return result;
}

int
queue_is_empty(Queue self)
{
	return (self->front == NULL);
}

Queue
queue_insert(Queue self, node_type data)
{
	Node node = (Node) malloc(sizeof(struct node));
	assert(node);
	node->data = data;
	node->next = NULL;
	if (queue_is_empty(self))
		self->front = node;
	else
		self->rear->next = node;
	self->rear = node;
	return self;
}

node_type
queue_remove(Queue self)
{
	assert(!queue_is_empty(self));
	Node front = self->front;
	node_type result = front->data;

	self->front = front->next;
	free(front);
	return result;
}

void
queue_free(Queue self)
{
	while(!queue_is_empty(self))
	{
		queue_remove(self);
	}
	free(self);
}

Queue
queue_reverse(Queue self)
{
	node_type temp;
	if (!queue_is_empty(self))
	{
		temp = queue_remove(self);
		return queue_insert(queue_reverse(self), temp);
	}
	return queue_create();
}

void 
queue_print(Queue self)
{
	/* queue_print esvaziando */
	putchar('[');
	if(queue_is_empty(self))
	{
		printf("]\n");
	} 
	else
	{
		do
		{
			printf("%i, ", queue_remove(self));
		} while(!queue_is_empty(self));
		printf("\b\b]\n");
	}
}

int
main()
{
	Queue teste = queue_create();

	/* teste com 3 elementos */
	queue_insert(teste, 19);
	queue_insert(teste, 130);
	queue_insert(teste, 89);

	teste = queue_reverse(teste);
	queue_print(teste);

	/* teste com 1 elemento */
	queue_insert(teste, 1913089);   

	teste = queue_reverse(teste);
	queue_print(teste);

	/* teste com fila vazia */
	teste = queue_reverse(teste);
	queue_print(teste);

	queue_free(teste);

	return 0;
}