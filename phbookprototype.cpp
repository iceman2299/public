#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <time.h>

struct Phbook
{
    char name[30];
    char surname[30];
    int code[5];
    int number[10];
};

int n=25;
struct Phbook* list=(struct Phbook*)malloc(n*sizeof(struct Phbook));

int add(char name[30], char surname[30], int code[5], int number[10])
{
    
}

int main()
{
}