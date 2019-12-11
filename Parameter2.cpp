#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
int main(int argc, char* argv[])
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	int n = atoi(argv[2]);
	int* strn = (int*)malloc(n * sizeof(int));
	FILE* f = fopen(argv[1], "wt");
	for (int i = 0; i < n; i++)
	{
		strn[i] = rand() % 10;
		printf("%d", strn[i]);
		fprintf(f, "%d\n", strn[i]);
	}
	fclose(f);
	getch();
}