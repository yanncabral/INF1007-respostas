#include <stdio.h>
#include <string.h>

struct person {
  char name[51];
  float height;
  float weight;
};
typedef struct person Person;

void person_print(Person** p, int len)
{
  int i;
  for(i = 0; i < len; i++)
	printf("%-10s %.2f %.2f\n", p[i]->name, p[i]->height, p[i]->weight);
}

static int person_match(float target_height, float target_weight, Person * b)
{
  if(target_height == b->height)
	if(target_weight != b->weight)
	  return (target_weight > b->weight)*2-1;

  if(target_height != b->height)
	  return (target_height > b->height)*2-1;

  return 0;
}

char* person_search(int len, Person ** v, float target_height, float target_weight)
{
	char* not_found = "Person not found";
	int left = 0;
	int right = len - 1;
	int mid, cmp;
	while (left <= right)
	{
		mid = (left + right) / 2;
		cmp = person_match(target_height, target_weight, v[mid]);
		if (cmp < 0)
			right = mid - 1;
		else if (cmp > 0)
			left = mid + 1;
		else
			return v[mid]->name;
	}
	return not_found;
}

int main(void)
{
  char* macro = "search(%.2f, %.2f) -> %s\n";
	Person d[] = { {"Leo", 1.70, 70}, {"Eva", 1.70, 75}, {"Ana", 1.80, 40}, {"Turing",1.80,50},
	{"Luiza", 1.80, 75}, {"Lovelace", 1.90, 60}, {"Sato", 2.0, 50}, {"Duda",2.0,55} };
	Person * v[] = { d, d + 1, d + 2, d + 3, d + 4, d + 5, d + 6, d + 7 };
	int len = 8;
	person_print(v, len);

  /* testing */ 
	printf(macro, 1.80, 50.0, person_search(len, v, 1.80, 50.0));
  printf(macro, 2.00, 55.0, person_search(len, v, 2.00, 55.0));
  printf(macro, 1.70, 70.0, person_search(len, v, 1.70, 70.0));
  printf(macro, 1.23, 45.6, person_search(len, v, 1.23, 45.6));

	return 0;
}
