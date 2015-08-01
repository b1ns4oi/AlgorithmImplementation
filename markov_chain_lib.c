
#include <string.h>

int isendword(char *w, char *ENDCHARS, int len) {
	char c = w[strlen(w)-1];
	while (len-- > 0) {
		if (c == ENDCHARS[len])
			return 1;
	}
	return 0;
}