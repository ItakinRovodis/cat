#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	char ch = 0;
	FILE *fp;
	printf("%s\n", argv[1]);
	if (argc > 1)
		fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		printf("ERROR");
	} else {
	while (fscanf(fp == NULL ? stdin : fp, "%c", &ch) != EOF) {
		if (ch == '\0') {
			break;
		}
		if (ch == '\t') {
			printf("TAB");
		} else {
			printf("%c",ch);
		}
	}
}
	return 0;
}