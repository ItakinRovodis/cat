#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {

	int bflag = 0, eflag = 0, nflag = 0, sflag = 0, tflag = 0;
	int opt;

	while ((opt = getopt(argc, argv, "Abenst?")) != -1) {
		switch (opt) {
			case 'A':
				eflag = 1;
				tflag = 1;
				break;
			case 'b':
				bflag = 1;
				break;
			case 'e':
				eflag = 1;
				break;
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
	int currentFile = optind;

	while (currentFile < argc) {
		if (argc > 1) {
			fp = fopen(argv[currentFile], "rb");
			if (fp == NULL) {
				fprintf(stderr, "%s: %s : No such file of directory\n",
					argv[0], argv[currentFile]);
				exit(1);
			}
		}

		int lastLineBlank = 0;
		int lineNumber = 1;

		while (fgets(buffer, bufferSize, (fp == NULL ? stdin : fp))) {
			int length = strlen(buffer);
			buffer[length - 1] =  '\0';
			
			if (sflag) {
				length = strlen(buffer);
				int currentLineBlank = (length <= 1) ? 1 : 0;
				if (lastLineBlank && currentLineBlank) {
					continue;
				}
				lastLineBlank = currentLineBlank;
			}

			if (bflag) {
				length = strlen(buffer);
				if (length >= 1) {
					char * tmp = strdup(buffer);
					buffer[0] = '\0';
					sprintf(buffer, "%*d\t", 6, lineNumber++);
					strcat(buffer, tmp);
				}
			} else if (nflag) {
				char *tmp = strdup(buffer);
				buffer[0] = '\0';
				sprintf(buffer, "%*d\t", 6, lineNumber++);
				strcat(buffer, tmp);
			}

			if (eflag) {
				length = strlen(buffer);
				buffer[length] = '$';
				buffer[length+1] = '\0';
			} 

			fprintf(stdout, "%s\n", buffer);
		}

		fclose(fp);
		currentFile++;
	}

	return 0;
}
