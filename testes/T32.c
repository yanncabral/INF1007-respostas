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
Stack stack_push(Stack stack, node_type data);
node_type stack_pop(Stack stack);
void stack_print(Stack stack);
void stack_free(Stack stack);
void int_to_hex(int number, char* head);
void int_to_hex_print(int number);

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

Stack stack_push(Stack stack, node_type data)
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

node_type stack_pop(Stack stack)
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

void int_to_hex(int number, char* head)
{
  Stack stack = stack_push(NULL, '\0');
  char map[] = "0123456789ABCDEF";
  char* s = head;

  /* do-while pra dar push no 0 tambem */ 
  do
  {
	stack_push(stack, map[(number % 16)]);
	number /= 16;
  } while(number); 

  do
  {
	*(s++) = stack_pop(stack);
  } while(!stack_is_empty(stack));

  stack_free(stack);
}

void int_to_hex_print(int number)
{
  char result[32];
  int_to_hex(number, result);
  printf("int_to_hex(%d): 0x%s\n", number, result);
}

int main() 
{

  int_to_hex_print(2300);
  int_to_hex_print(1913089);
  int_to_hex_print(0);

  return 0;
}