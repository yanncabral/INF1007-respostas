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

typedef struct stack
{
  Node top;
}
* Stack;

Stack stack_create(void);
int stack_is_empty(Stack stack);
Node stack_push(Stack stack, node_type data);
node_type stack_pop(Stack stack);
void stack_print(Stack stack);
void stack_free(Stack stack);
char* reverse_string(char* head);

/* implementation */

Stack stack_create(void)
{
  Stack result = (Stack) malloc(sizeof(struct stack));
  assert(result);
  result->top = NULL;
  return result;
}

int stack_is_empty(Stack stack)
{
  return (stack->top == NULL);
}

Node stack_push(Stack stack, node_type data)
{
  Node node = (Node) malloc(sizeof(node_type));
  assert(node);
  node->data = data;
  node->next = stack->top;
  stack->top = node;
  return node;
}

node_type stack_pop(Stack stack)
{
  Node top;
  node_type result;
  if(stack_is_empty(stack))
  {
	printf("Stack is empty!\n");
	exit(1);
  }
  top = stack->top;
  result = top->data;
  stack->top = top->next;
  free(top);
  return result;
}

void stack_free(Stack stack)
{
  while(!stack_is_empty(stack))
  {
	stack_pop(stack);
  }
  free(stack);
}

void stack_print(Stack stack)
{
  node_type data;
  if(!stack_is_empty(stack))
  {
	data = stack_pop(stack);
	printf("|%c|\n", data);
	stack_print(stack);
	stack_push(stack, data);
  }
}

char* reverse_string(char* head)
{
  Stack stack = stack_create();
  char* s;

  for(s = head; *s != '\0'; s++)
	stack_push(stack, *s);

  s = head;
  while(!stack_is_empty(stack))
	*(s++) = stack_pop(stack);

  *s = '\0'; /* desnecessário  */
  stack_free(stack);

  return head;
}

int main() 
{
  char name[] = "Yann Cabral Dias";
  char empty[] = "";

  printf("Meu nome: %s\n", name);
  reverse_string(name);
  printf("Meu nome invertido: %s\n", name);
  reverse_string(name);
  printf("Meu nome invertido 2x: %s\n", name);
  reverse_string(reverse_string(name));
  printf("Meu nome invertido 4x: %s\n", name);
  reverse_string(empty);
  printf("String vazia: \"%s\"\n", empty);
  return 0;
}