#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {

	int bflag = 0, eflag = 0, nflag = 0, sflag = 0, tflag = 0, vflag = 0;
	int opt;

	while ((opt = getopt(argc, argv, "AbeEnstTuv?")) != -1) {
		switch (opt) {
			case 'A':
				vflag = 1;
				eflag = 1;
				tflag = 1;
				break;
			case 'b':
				bflag = 1;
				break;
			case 'e':
				eflag = 1;
				vflag = 1;
				break;
			case 'E':
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
				vflag = 1;
				break;
			case 'T':
				tflag = 1;
				break;
			case 'u':
				// ignored
				break;
			case 'v': 
				vflag = 1;
				break;
			case '?':
				printf("usage: cat [-AbeEnstTuv] [file ...]\n");
				exit(1);
		}
	}

	FILE *fp;
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
		char ch;
		int line_char_counter = 0;

		while (fscanf(fp == NULL ? stdin : fp, "%c", &ch) != EOF) {
			line_char_counter++;
			if (bflag) {
				if (line_char_counter == 1 && ch !='\n') {
					printf("%6d", lineNumber);
				}
				if (line_char_counter != 1 && ch == '\n') {
					lineNumber++;
					line_char_counter = 0;
				} else if (line_char_counter == 1 && ch == '\n') {
					line_char_counter = 0;
				}
			} else if (nflag) {
				if (line_char_counter == 1) {
					printf("%6d", lineNumber);
				}
				if (ch == '\n') {
					lineNumber++;
					line_char_counter = 0;
				}
			}
			if (vflag) {
					if (ch >= 32) {
						if (ch < 127)
							printf("%c",ch);
						else if (ch == 127) {
							printf("^?");
						} else {
							printf("M-");
							if (ch >= 128 + 32) {
								if (ch < 128 + 127)
									printf("%c",ch - 128);
								else
									printf("^?");
							} else {
							printf("^%c",ch - 128 + 64);
							}
						}
					} else if (ch == '\t'){
						if (!tflag)
							printf("\t");
						else 
							printf("^I");
					} 
					else if (ch == '\n') {
						if (eflag) {
							printf("$");
						}
						printf("\n");
					} else {
						printf("^%c",ch + 64);
                }
			} else if (tflag && ch =='\t') {
				printf("^I");
			} else if (eflag && ch == '\n') {
				printf("$\n");
			} else {
				printf("%c",ch);
			}
		}
		fclose(fp);
		currentFile++;
	}

	return 0;
}
