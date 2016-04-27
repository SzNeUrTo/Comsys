
#include <stdio.h> 
#include <time.h>
#include <stdlib.h>

int main() {
	srand(time(NULL)); 
	int N=100, i=0, j=0, k=0;
	int A[N][N], B[N][N], C[N][N];

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) { 
			A[i][j] = rand() % 100; 
			B[i][j] = rand() % 100; 
			C[i][j] = 0; 
		}
	}

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			for (k = 0; k < N; k++) {
				C[i][j] += A[i][k] * B[k][j]; 
			}
		}
	}
	return 0;
}
