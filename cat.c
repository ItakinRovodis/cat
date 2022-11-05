#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char **argv) {

	int bflag = 0, eflag = 0, nflag = 0, sflag = 0, tflag = 0, vflag = 0;
	int opt;

	static struct option const long_options[] = {
		{"number-nonblank", no_argument, NULL, 'b'},
    	{"number", no_argument, NULL, 'n'},
    	{"squeeze-blank", no_argument, NULL, 's'},
    	{"show-nonprinting", no_argument, NULL, 'v'},
    	{"show-ends", no_argument, NULL, 'E'},
    	{"show-tabs", no_argument, NULL, 'T'},
    	{"show-all", no_argument, NULL, 'A'},
    	{NULL, 0, NULL, 0}
	};

	while ((opt = getopt_long(argc, argv, "AbeEnstTuv?", long_options, NULL)) != -1) {
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
		int empty_line = 0;

		while (fscanf(fp == NULL ? stdin : fp, "%c", &ch) != EOF) {
			line_char_counter++;
			if (bflag) {
				if (line_char_counter == 1 && ch !='\n') {
					printf("%6d\t", lineNumber);
				}
			} else if (nflag) {
				if (line_char_counter == 1) {
					printf("%6d\t", lineNumber);
				}				
			}
			if (ch == '\n') {
				if (line_char_counter == 1) {
					empty_line++;
					if (!bflag) {
						lineNumber++;
					}
				} else {
					lineNumber++;
					empty_line = 0;
				}			
				line_char_counter = 0;
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
						if (sflag) {
							if (empty_line <=1) {
								if (eflag)
									printf("$");
								printf("\n");
							}
						} else {
							if (eflag)
								printf("$");
							printf("\n");
						}						
					} else {
						printf("^%c",ch + 64);
                }
			} else if (tflag && ch =='\t') {
				printf("^I");
			} else if (sflag && ch == '\n') {
				if (empty_line <= 1) {
					if (eflag) {
						printf("$");
					}
					printf("\n");
				}
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
