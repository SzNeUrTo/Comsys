#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void printLine(int level) {
	int i;
	for (i = 0; i < level; i++) {
		printf("-");
	}
}

void killProcess(char* pid, int level) {
	FILE *in;
	char buff[512];
	char command[30] = "pgrep -P";
	strcat(command, pid);

	if (!(in = popen(command, "r"))){
		return;
	}

	while (fgets(buff, sizeof(buff), in) != NULL){
		killProcess(buff, level + 1);
	}
	printLine(level);
	printf("%s\n", pid);
	kill(atoi(pid), SIGKILL);
	pclose(in);
}

int main(int argc, char *argv[])
{
	if(argc < 2) {
		printf("forget pid.");
		exit(0);
	}
	char accept[5];
	printf("Are you sure to kill %s and its children? ", argv[1]);
	scanf("%s", accept);
	if(strcmp(accept, "yes") == 0) {
		killProcess(argv[1], 0);
	}
    return 0;
}
