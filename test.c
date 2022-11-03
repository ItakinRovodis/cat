#include <stdio.h>

#define SIZE 4

enum names{
	N,
    A,
	C
};

static const char * const name[4] = { "N", "A", "C" };

int main() {
	printf("%s = %d\n",name[N], N);
	printf("%s = %d\n",name[A], A);
	printf("%s = %d\n",name[C], C);
	printf("%s = %d\n", name[3], 3);
	printf("%s = %d\n", name[4], 4);
	printf("%c\t%c", 160, 161);
	return 0;
}