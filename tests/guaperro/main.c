#include "foo.h"
#include <stdio.h>

int main () {
	int val;
	val=bar();
	printf("This is working, %i\n", val);
	return 0;
}