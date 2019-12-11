#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
int main (int argc, char* argv[1])
{
	setlocale(LC_ALL, "Russian");
int n=100;
char* strn=(char*)malloc(n*sizeof(char));
FILE* f=fopen(argv[1],"rt");
while (1)
  { 
    strn= fgets(strn,n*sizeof(char),f);
    printf("%s",strn);
	if (feof(f))
		break;
  }
fclose(f);
return 0;
getch();
}