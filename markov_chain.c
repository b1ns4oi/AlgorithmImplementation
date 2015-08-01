// code implementation from the book <The Practice of Programming> in chapter 3
// with minor modification in generate()

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum {
	NPREF = 2,
	NHASH = 4093,
	MAXGEN = 10000,
	MULTIPLIER = 31
};

typedef struct State State;
typedef struct Suffix Suffix;

struct State {
	char *pref[NPREF];
	Suffix *suf;
	State *next;
};

struct Suffix {
	char *word;
	Suffix *next;
};

State *statetab[NHASH];
char *NONWORD = "\n";
char ENDCHARS[] = { '.', '?', '!', '"' };

int hash(char *prefix[]) {
	int i;
	unsigned int h = 0;
	unsigned char *p;

	for (i = 0; i < NPREF; i++) 
		for (p = (unsigned char *)prefix[i]; *p != '\0'; p++)
			h = MULTIPLIER*h + *p;
	return h % NHASH;
}

State *lookup(char *prefix[], int create) {
	State *state;
	int i, n = hash(prefix);

	for (state = statetab[n]; state != NULL; state = state->next) {
		for (i = 0; i < NPREF; i++)
			if (strcmp(prefix[i], state->pref[i]) != 0)
				break;
		if (i == NPREF)
			return state;
	}
	if (create) {
		state = (State *)malloc(sizeof(State));
		for (i = 0; i < NPREF; i++)
			state->pref[i] = prefix[i];
		state->suf = NULL;
		state->next = statetab[n];
		statetab[n] = state;
	}
	return state;
}

void add(char *prefix[], char *suffix) {
	Suffix *suf_new;
	State *sp;

	sp = lookup(prefix, 1);
	suf_new = (Suffix *)malloc(sizeof(Suffix));
	suf_new->word = suffix;
	suf_new->next = sp->suf;
	sp->suf = suf_new;

	memmove(prefix, prefix+1, (NPREF-1)*sizeof(prefix[0]));
	prefix[NPREF-1] = suffix;
}

void build(char *prefix[], FILE* f) {
	char buf[100], fmt[10];

	sprintf(fmt, "%%%ds", sizeof(buf)-1);
	while (fscanf(f, fmt, buf) != EOF) {
		char *t = (char *)malloc(strlen(buf) + 1);
		strcpy(t, buf);
		add(prefix, t);
	}
}

// generate N sentences
void generate(int N) {
	int i, n, len_ENDCHARS = sizeof(ENDCHARS) / sizeof(ENDCHARS[0]);
	char *prefix[NPREF], *w;
	State *sp;
	Suffix *sf;

	for (i = 0; i < NPREF; i++)
		prefix[i] = NONWORD;
	while (N > 0) {
		sp = lookup(prefix, 0);
		n = 0;
		for (sf = sp->suf; sf != NULL; sf = sf->next) {
			if (rand() % ++n == 0)
				w = sf->word;
		}
		if (strcmp(w, NONWORD) == 0) {
			printf("\n");
			return;
		}
		if (isendword(w, ENDCHARS, len_ENDCHARS))
			N--;
		printf("%s ", w);
		memmove(prefix, prefix+1, (NPREF-1)*sizeof(prefix[0]));
		prefix[NPREF-1] = w;
	}
	printf("\n");
}

int main() {
	int i;
	char *prefix[NPREF];

	for (i = 0; i < NPREF; i++)
		prefix[i] = NONWORD;
	build(prefix, stdin);
	add(prefix, NONWORD);
	srand((int) time(NULL));
	generate(2);
	return 0;
}










