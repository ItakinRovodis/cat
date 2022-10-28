#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {

	int bflag = 0, eflag = 0, nflag = 0, sflag = 0, tflag = 0;
	int opt;

	while ((opt = getopt(argc, argv, "benst?")) != -1) {
		switch (opt) {
			case 'b':
				bflag = 1;
				break;
			case 'e':
				eflag = 1;
				break
			case 'n':
				nflag = 1;
				break;
			case 's':
				sflag = 1;
				break;
			case 't':
				tflag = 1;
				break;
			case '?':
				printf("usage: cat [-benst] [file ...]\n");
				exit(1);
		}
	}

	FILE *fp;
	const int bufferSize = 4096;
	char buffer[bufferSize];
	int currentFile = (argc > 1 ? 1 : 0);
	while (currentFile < argc) {
		if (argc > 1) {
			fp = fopen(argv[currentFile], "rb");
			if (fp == NULL) {
				fprintf(stderr, "%s: %s : No such file of directory\n",
					argv[0], argv[currentFile]);
				exit(1);
			}
		}
		while (fgets(buffer, bufferSize, (fp == NULL ? stdin : fp))) {
			int length = strlen(buffer);
			buffer[length - 1] =  '\0';
			fprintf(stdout, "%s\n", buffer);
		}

		fclose(fp);
		currentFile++;
	}

	return 0;
}
