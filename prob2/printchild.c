#include <stdio.h>
#include <string.h>

void printLine(int level) {
	int i;
	for (i = 0; i < level; i++) {
		printf("-");
	}
}

void printProcess(char* pid, int level) {
	FILE *in;
	char buff[512];
	char command[30] = "pgrep -P";
	strcat(command, pid);

	if (!(in = popen(command, "r"))){
		return;
	}

	while (fgets(buff, sizeof(buff), in) != NULL){
		//printf("%s", atoi(buff));
		printProcess(buff, level + 1);
	}
	printLine(level);
	printf("%s\n", pid);
	pclose(in);
}

int main() {
	printProcess("3309", 0);
	return 0;
}
