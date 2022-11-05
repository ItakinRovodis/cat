#include <stdio.h>
#include <string.h>

int getflag (int argc, char** argv, char* flags) {
	if (argc > 1) {
		for (int i = 0; i < argc; ++i) {
			if (argv[i][0] == '-') {
				int length = strlen(argv[i]);
				for (int i = 1; i < length; ++i) {
					
				}
			}
		}
	}
	return 0;
}