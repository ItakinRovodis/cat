#include <stdio.h>

#define SIZE 256

enum names{
	Nikita,
	Andrew,
	Chendler
};

static const char name[][SIZE] = { "Nikita", "Andrew", "Chendler" };

int main() {
	printf("%s = %d\n",name[Nikita], Nikita);
	printf("%s = %d\n",name[Andrew],Andrew);
	printf("%s = %d\n",name[Chendler],Chendler);
	return 0;
}