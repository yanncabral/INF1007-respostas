#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/* interface */
#define N 100
typedef int node_type;

typedef struct node
{
	node_type data;
	struct node * next;
}
* Node;

typedef struct queue
{
	int front;
	int len;
	int data[N];
}
* Queue;

typedef struct stack
{
	Node top;
}
* Stack;

Stack stack_create(void);
int stack_is_empty(Stack stack);
Stack stack_push(Stack stack, node_type data);
node_type stack_pop(Stack stack);
void stack_free(Stack stack);

Queue queue_create(void);
int queue_is_empty(Queue self);
Queue queue_insert(Queue self, node_type data);
node_type queue_remove(Queue self);
void queue_free(Queue self);
void queue_print(Queue self);
int queue_len(Queue self);
void queue_mirror(Queue self);

/* implementation */

/* stack */


Stack
stack_create(void)
{
	Stack result = (Stack) malloc(sizeof(struct stack));
	assert(result);
	result->top = NULL;
	return result;
}

int
stack_is_empty(Stack stack)
{
	return (stack->top == NULL);
}

Stack
stack_push(Stack stack, node_type data)
{
	/* cria a pilha automaticamente se for NULL */
	if(stack == NULL) stack = stack_create();
	Node node = (Node) malloc(sizeof(struct node));
	assert(node);
	node->data = data;
	node->next = stack->top;
	stack->top = node;
	return stack;
}

node_type
stack_pop(Stack stack)
{
	Node top;
	node_type result;
	assert(!stack_is_empty(stack));

	top = stack->top;
	result = top->data;
	stack->top = top->next;

	free(top);
	return result;
}

void
stack_free(Stack stack)
{
	free(stack);
}

/* queue */

Queue
queue_create(void)
{
	Queue result = (Queue) malloc(sizeof(struct queue));
	assert(result);
	result->len = result->front = 0;
	return result;
}

int
queue_is_empty(Queue self)
{
	return (self->len == 0);
}

Queue
queue_insert(Queue self, node_type data)
{
	int index;
	if(self == NULL) self = queue_create();
	assert(self->len < N);
	index = (self->len + self->front) % N;
	self->data[index] = data;
	self->len += 1;
	return self;
}

node_type
queue_remove(Queue self)
{
	node_type result;
	assert(!queue_is_empty(self));
	result = self->data[self->front];
	self->front = (self->front + 1) % N;
	self->len -= 1;
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

int
queue_len(Queue self)
{
	return self->len;
}

void
queue_mirror(Queue self)
{
	int i;
	node_type temp;
	Stack stack_aux = stack_create();

	for(i = queue_len(self); i > 0; i--)
	{
		temp = queue_remove(self);
		stack_aux = stack_push(stack_aux, temp);
		self = queue_insert(self, temp);
	}

	while(!stack_is_empty(stack_aux))
	{
		queue_insert(self, stack_pop(stack_aux));
	}

	stack_free(stack_aux);
}

int
main()
{
	Queue queue = queue_create();

	queue_insert(queue, 19);
	queue_insert(queue, 13);
	queue_insert(queue,  0);
	queue_insert(queue, 89);
	queue_mirror(queue);

	/* queue_print esvaziando a lista */
	printf("A lista espelhada: [");
	while(!queue_is_empty(queue))
	{
		printf("%i, ", queue_remove(queue));
	}
	printf("\b\b]\n");

	queue_free(queue);
	return 0;
}