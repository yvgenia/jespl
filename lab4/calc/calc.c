#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, char **argv) {
	int a, op, b, c;

	if(argc!=4) {
		fprintf(stderr, "usage: calc <number> [+|-|*|/] <number>\n");
		exit(1);
	}

printf("before fun %d\n",argv[1][0]);
	a = atod(argv[1]);
printf("the fun returned with %c\n",a);
	op = argv[2][0];
	b = atod(argv[3]);
	switch(op) {
	case '+': c = a + b; break;
	case '-': c = a - b; break;
	case '*': c = a * b; break;
	case '/': c = a / b; break;
	default: assert(0);
	}

	printf("%d %c %d = %d\n", a, op, b, c);
	return 0;
}
