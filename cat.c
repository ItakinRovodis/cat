#include "cat.h"

int main(const int argc, const char **const argv) {

	int bflag = 0, eflag = 0, nflag = 0, sflag = 0, tflag = 0;
	
	int ret = 0;
	if (check_args(argc, argv)) {
		flag f = {0};
		int is_set = parse_flag(&f, argv[1]);
		show_flags(&f);
		for (int i = 1 + is_set; i < argc; ++i) {

		}
	}

	return 0;
}

int check_args(const int count, const char **const strs) {
	int ret = 0;
	if (count == 2 && strs[1][0] != '-') 
		ret = 1;
	if (count > 2 && check_flags(strs[1]))
		ret = 1;
	return ret;
}

int check_flags(const char* const flags) {
	int ret = flags[0] == '-' ? 0 : 1;
	if (flags[0] == '-') {
		for (int i = 0; strcmp("NULL", str_flags[i]); ++i) {
			printf("%s\n",str_flags[i]);
			if (!strcmp(str_flags[i], flags)) {
				ret = 1;
				break;
			}
		}
	}
	return ret;
}

int parse_flag(flag *const f, const char *const str) {
	int ret = *str == '-' ? 1 : 0;
	if (!strcmp(str, str_flags[b]) || strcmp(str, str_flags[gnu_b]))
		f->b = 1;
	if (!strcmp(str, str_flags[e]))
		f->e = 1;
	if (!strcmp(str, str_flags[gnu_e]))
		f->E = 1;
	if (!strcmp(str, str_flags[n]) || !strcmp(str, str_flags[gnu_n]))
		f->n = 1;
	if (!strcmp(str, str_flags[s]))
        f->s = 1;
    if (!strcmp(str, str_flags[t]))
        f->t = 1;
    if (!strcmp(str, str_flags[gnu_t]))
        f->T = 1;
    return ret;

}

void show_flags(flag *f) {
	printf ("b e E n s t T\n");
	printf("%d %d %d %d %d %d %d\n", f->b, f->e, f->E, f->n, f->s, f->t, f->T);
}


