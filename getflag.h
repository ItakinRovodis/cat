#ifndef CAT_GETFLAG_H_
#define CAT_GETFLAG_H_

#define SIZE 256

enum flags {
	b,
	gnu_b,
	e,
	gnu_e,
	n,
	gnu_n,
	s,
	gnu_s,
	t,
	gnu_t
};

typedef struct flag {
	int b;
	int e;
	int E;
	int n;
	int s;
	int t;
	int T;
	int count;
} flag;

static const char str_flags[][SIZE] = {
	"-b", "--number-nonblank", "-e", "-E", "--number",
	"-s", "--squeeze-blank", "-t", "-T", "NULL"
};
