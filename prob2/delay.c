#include <time.h>
#include <stdio.h>

void waitFor (unsigned int secs) {
	unsigned int retTime = time(0) + secs;
	while (time(0) < retTime);
}

int main() {
	int i;
	for (i = 0; i < 10; i++) {
		printf("%d\n", i);
		waitFor(1);
	}
	return 0;
}
