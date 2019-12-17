#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <Windows.h> //������������ � �� WINDOWS ������
//������ ��� �� WINDOWS ������ ���� ������������ ��������� ���� ����������� ������ � UTF-8 � ���������� � main
//SetConsoleCP(1251); �� SetConsoleCP(65001);
//SetConsoleOutputCP(1251); �� SetConsoleOutputCP(65001);



char path[400] = "\contactdb.txt"; //���� � �����, ��� ��� ����� ��������
int n = 50; //���������� ������
char sortname[30]; //��� ���������� ����� �����
char sortsurname[30]; //��� ���������� ����� �������
char sortnumber[15]; //��� ���������� ����� ������

struct Phbook
{
    char name[30];
    char surname[30];
    char number[15];
};
struct Phbook* contact = (struct Phbook*)malloc(n * sizeof(struct Phbook)); //�������, ����� ������ �� n

int write(int count) //������� ������ � ����
{
    FILE* writer = fopen(path, "wt");
    for (int i = 0; i < count; i++)
    {
        fprintf(writer, "%s %s %s\n", contact[i].name, contact[i].surname, contact[i].number);
    }
    fclose(writer);
    return 3;
};

int read() //������� ������ �� �����
{
    FILE* reader = fopen(path, "rt");
    int i = 0;
    while (!feof(reader))
    {
        fscanf(reader, "%s %s %s", &contact[i].name, &contact[i].surname, &contact[i].number);
        i++;
        //if (i > n)
        //n = n * 2; //-������ ����� ��� ���������, � ��� �������� ������ �� ��� ���� ��� ������ ���������� ��� ��� ���������.
        //������ ����� �������� ����.
        //��� ������������� ������������ - ���� ����������� �������� ���������� ������ � case 1.
    }
    fclose(reader);
    return i - 1;
};

int sort(int start, int count)//���������� �� ����� �� ��������
{
    for (int i = start + 1; i < count; i++)
    {
        for (int j = start; j < count - 1; j++)
        {
            if (strcmp(contact[j].name, contact[j + 1].name) > 0)
            {
                strcpy(sortname, contact[j].name);
                strcpy(sortsurname, contact[j].surname);
                strcpy(sortnumber, contact[j].number);
                strcpy(contact[j].name, contact[j + 1].name);
                strcpy(contact[j].surname, contact[j + 1].surname);
                strcpy(contact[j].number, contact[j + 1].number);
                strcpy(contact[j + 1].name, sortname);
                strcpy(contact[j + 1].surname, sortsurname);
                strcpy(contact[j + 1].number, sortnumber);
            }
        }
    }
    return 1;
};

int deleting(int delnumb, int count)//�������� �������� �� ����������� ������
{
    strcpy(contact[delnumb - 1].name, contact[count - 1].name);
    strcpy(contact[delnumb - 1].surname, contact[count - 1].surname);
    strcpy(contact[delnumb - 1].number, contact[count - 1].number);
    strcpy(contact[count - 1].name, "");
    strcpy(contact[count - 1].surname, "");
    strcpy(contact[count - 1].number, "");
    return 2;
};

int main()
{
    system("color 03");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    printf("���������� �����\n");
    printf("ver: Release 1.2\n");
    char doing[2]; //��� ��������� ���� ���������� ��������
    while (1)
    {
        printf("��� �� ������ �������?\n�������� ������� - ������� 1\n���� ��������� - ������� 3\n����� - ������� 9\n");
        scanf("%s", &doing);
        int idoing = atoi(doing);//������ ����� �� ������, ���� ��� ���������� ������ ��� ����� ����
        switch (idoing)
        {
            case 1:
            {
                int k = read();
                if (k >= n)
                {
                    printf("������ ����������, ������ ���������.\n");
                    break;
                }
                printf("������� ���\n");
                scanf("%s", &contact[k].name);
                printf("������� �������\n");
                scanf("%s", &contact[k].surname);
                printf("������� �����\n");
                scanf("%s", &contact[k].number);
                int index=sort(0, k + 1);//��������� �� �������� ����� ������� � ����
                int c = write(k + 1);
                if (c == 3)
                {
                    printf("������� ��������\n");
                    printf("\n");
                    continue;
                }
            }
            case 3:
            {
                int k;
                k = read();
                printf("������ ���������:\n");
                for (int i = 0; i < k; i++)
                {
                    printf("������� #%d: %s %s\n�����: %s\n\n", i + 1, contact[i].name, contact[i].surname, contact[i].number);
                }
                printf("����� %d ���������\n", k);
                printf("������ ������ �� %d �� %d\n", k, n);
                printf("\n");
                while (1)
                {
                    printf("��� �� ������ �������?\n�������� ��������� - ������� 1\n������� � ���������� ���� - ������� 9\n");
                    char doing2[2];
                    scanf("%s", &doing2);
                    int idoing2 = atoi(doing2);//������ ����� �� ������, ���� ��� ���������� ������ ��� ����� ����
                    switch (idoing2)
                    {
                        case 1:
                        {
                            printf("������� ���������� ����� ���������� ��������\n");
                            char deleter[2];//����� ���������� ��������
                            scanf("%s", &deleter);
                            int ideleter = atoi(deleter);//������ ����� �� ������, ���� ��� �������� �� "����������"
                            if (!atoi(deleter))
                            {
                             printf("������, �������� ����� ��������, ���������� ��� ���\n");//���� �� ����� - ������� ��������� � ���������� �� �����
                            }
                            if (ideleter > k)
                            {
                                printf("�������� � ���� ���������� ������� �� c���������.\n");
                            }
                            else
                            {
                                int index1 = deleting(ideleter, k);//�������� �������� ����� ideleter
                                int index2 = sort(ideleter - 1, k - 1);//������������� ����������� ������
                                int index3 = write(k - 1); //������ ������ ������ � ����
                                if (index1 == 2)
                                {
                                    printf("������� ������.\n");
                                }
                            }   
                        }
                        case 9:
                        {
                            break;
                        }
                        default:
                        {
                            printf("����� ������� ���, ���������� ��� ���\n");
                        }
                    }
                    if (atoi(doing2) == 9)
                    {
                        break;
                    }
                }
            }
            case 9:
                break;
            default:
            {
                printf("����� ������� ���, ���������� ��� ���\n");
            }
        }
        if (atoi(doing) == 9)
        {
            printf("���������� ������ ���������...\n");
            break;
            free(contact);
            return 0;
        }
    }
}