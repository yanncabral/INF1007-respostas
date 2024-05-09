#include <stdio.h>

struct person {
  char name[51];
  float height;
  float weight;
};
typedef struct person Person;

void person_print(Person* p)
{
  printf("%-10s %.2f %.2f\n", p->name, p->height, p->weight);
}

void person_print_all(Person** p, int len)
{
  int i;
  for(i = 0; i < len; i++)
	person_print(p[i]);
}

static int person_height_cmp(float height, Person* b)
{
  if (height==b->height)
	return 0;
  return (height > b->height)*2-1;
}

int person_get_index_of_shortest(int len, Person** v, float height)
{
  int left = 0;
  int right = len - 1;
  int mid, cmp;
  while(left <= right)
  {
	mid = (right+left)/2;
	cmp = person_height_cmp(height, v[mid]);
	if(cmp<0) right = mid - 1;
	else if(cmp>0) left = mid + 1;
	else {
	  while (mid > 0 && person_height_cmp(height, v[mid-1]) == 0) 
		mid--;
	  return mid;
	}
  }
  return -1;
}

int main(void)
{
	float test_values[] = {2.0, 1.2, 1.9, 1.7, 1.8};
  int test_values_len = 5;
  int i;
  int current_index;
	Person d[] = { {"Leo",1.70,70}, {"Eva",1.70,75}, {"Ana",1.80,40}, {"Turing",1.80,50},
	{"Luiza",1.80,75}, {"Lovelace",1.90,60}, {"Sato",2.0,50}, {"Duda",2.0,55} };
	Person * v[] = { d, d + 1, d + 2, d + 3, d + 4, d + 5, d + 6, d + 7 };
	int len = 8;
	person_print_all(v, len);

  /* testing */
  printf("\n");
  for(i = 0; i<test_values_len; i++)
  {
	current_index = person_get_index_of_shortest(len, v, test_values[i]);
	printf("searching for height %.2fm...\n\t>>> ", test_values[i]);
	if(current_index >= 0)
	  person_print(v[current_index]);
	else
	  printf("Person not found...\n");
  }

	return 0;
}