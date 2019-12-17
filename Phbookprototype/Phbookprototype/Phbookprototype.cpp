#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <Windows.h> //Закомментить в НЕ WINDOWS версии
//Вообще для НЕ WINDOWS версии надо перефигачить кодировку всех участвующих файлов в UTF-8 и переписать в main
//SetConsoleCP(1251); на SetConsoleCP(65001);
//SetConsoleOutputCP(1251); на SetConsoleOutputCP(65001);



char path[400] = "\contactdb.txt"; //путь к файлу, тут его легче изменить
int n = 50; //допустимая память
char sortname[30]; //для сортировки буфер имени
char sortsurname[30]; //для сортировки буфер фамилии
char sortnumber[15]; //для сортировки буфер номера

struct Phbook
{
    char name[30];
    char surname[30];
    char number[15];
};
struct Phbook* contact = (struct Phbook*)malloc(n * sizeof(struct Phbook)); //контакт, таких массив из n

int write(int count) //функция записи в файл
{
    FILE* writer = fopen(path, "wt");
    for (int i = 0; i < count; i++)
    {
        fprintf(writer, "%s %s %s\n", contact[i].name, contact[i].surname, contact[i].number);
    }
    fclose(writer);
    return 3;
};

int read() //функция чтения из файла
{
    FILE* reader = fopen(path, "rt");
    int i = 0;
    while (!feof(reader))
    {
        fscanf(reader, "%s %s %s", &contact[i].name, &contact[i].surname, &contact[i].number);
        i++;
        //if (i > n)
        //n = n * 2; //-Творит еррор при остановке, а так умножает память на два если при чтении выяснилось что она заполнена.
        //Вообще очень бредовая вещь.
        //При необходимости раскоментить - надо закоментить проверку превышения памяти в case 1.
    }
    fclose(reader);
    return i - 1;
};

int sort(int start, int count)//сортировка по имени по алфавиту
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

int deleting(int delnumb, int count)//Удаление контакта по порядковому номеру
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
    printf("Телефонная книга\n");
    printf("ver: Release 1.2\n");
    char doing[2]; //Для основного меню считывание действия
    while (1)
    {
        printf("Что вы хотите сделать?\nДобавить контакт - введите 1\nМеню контактов - введите 3\nВыйти - введите 9\n");
        scanf("%s", &doing);
        int idoing = atoi(doing);//делает число из строки, надо для устранения вылета при вводе букв
        switch (idoing)
        {
            case 1:
            {
                int k = read();
                if (k >= n)
                {
                    printf("Ошибка добавления, память заполнена.\n");
                    break;
                }
                printf("Введите имя\n");
                scanf("%s", &contact[k].name);
                printf("Введите фамилию\n");
                scanf("%s", &contact[k].surname);
                printf("Введите номер\n");
                scanf("%s", &contact[k].number);
                int index=sort(0, k + 1);//Сортируем по алфавиту перед записью в файл
                int c = write(k + 1);
                if (c == 3)
                {
                    printf("Контакт добавлен\n");
                    printf("\n");
                    continue;
                }
            }
            case 3:
            {
                int k;
                k = read();
                printf("Список контактов:\n");
                for (int i = 0; i < k; i++)
                {
                    printf("Контакт #%d: %s %s\nНомер: %s\n\n", i + 1, contact[i].name, contact[i].surname, contact[i].number);
                }
                printf("Всего %d контактов\n", k);
                printf("Память занята на %d из %d\n", k, n);
                printf("\n");
                while (1)
                {
                    printf("Что вы хотите сделать?\nУдаление контактов - введите 1\nВозврат в предыдущее меню - введите 9\n");
                    char doing2[2];
                    scanf("%s", &doing2);
                    int idoing2 = atoi(doing2);//делает число из строки, надо для устранения вылета при вводе букв
                    switch (idoing2)
                    {
                        case 1:
                        {
                            printf("Введите порядковый номер удаляемого контакта\n");
                            char deleter[2];//номер удаляемого контакта
                            scanf("%s", &deleter);
                            int ideleter = atoi(deleter);//делает число из строки, надо для проверки на "числовость"
                            if (!atoi(deleter))
                            {
                             printf("Ошибка, ожидался номер контакта, попробуйте еще раз\n");//если не число - выводит сообщение и отправляет по кругу
                            }
                            if (ideleter > k)
                            {
                                printf("Контакта с этим порядковым номером не cуществует.\n");
                            }
                            else
                            {
                                int index1 = deleting(ideleter, k);//удаление контакта номер ideleter
                                int index2 = sort(ideleter - 1, k - 1);//отсортировать обновленный список
                                int index3 = write(k - 1); //запись нового списка в файл
                                if (index1 == 2)
                                {
                                    printf("Контакт удален.\n");
                                }
                            }   
                        }
                        case 9:
                        {
                            break;
                        }
                        default:
                        {
                            printf("Такой команды нет, попробуйте еще раз\n");
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
                printf("Такой команды нет, попробуйте еще раз\n");
            }
        }
        if (atoi(doing) == 9)
        {
            printf("Завершение работы программы...\n");
            break;
            free(contact);
            return 0;
        }
    }
}