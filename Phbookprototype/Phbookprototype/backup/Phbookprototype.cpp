#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <Windows.h> //Закомментить в андроид версии

struct Phbook
{
    char name[30];
    char surname[30];
    char number[15];
};

char path[400] = "\pizdec.txt"; //путь к файлу
int n = 50; //допустимая память
char sortname[30]; //для сортировки обменка имени
char sortsurname[30]; //для сортировки обменка фамилии
char sortnumber[15]; //для сортировки обменка номера
struct Phbook* contact = (struct Phbook*)malloc(n * sizeof(struct Phbook)); //контакт, таких массив из n

int write(int count) //функция записи в файл
{
    FILE* writer = fopen(path, "wt");
    for (int i = 0; i < count; i++)
    {
        fprintf(writer, "%s %s %s\n", contact[i].name, contact[i].surname, contact[i].number);
    }
    fclose(writer);
    return 5;
}

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
}

int sort(int count)
{
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (strcmp(contact[j].name, contact[j + 1].name) > 0)
            {
                strcpy(sortname, contact[j].name);
                strcpy(sortsurname, contact[j].surname);
                strcpy(sortnumber, contact[j].number);
                strcpy(contact[j].name, contact[j + 1].name);
                strcpy(contact[j].surname, contact[j + 1].surname);
                strcpy(contact[j].number, contact[j + 1].number);
                strcpy(contact[j].name, sortname);
                strcpy(contact[j].surname, sortsurname);
                strcpy(contact[j].number, sortnumber);
            }
        }
    }
    return 1;
}

int main()
{
    SetConsoleCP(65001); //Закомментить в андроид версии, фиксит кириллицу в винде
    SetConsoleOutputCP(65001); //Закомментить в андроид версии, фиксит кириллицу в винде
    printf("Телефонная книга\n");
    printf("ver: Не ебу какая уже\n");
    char doing[2]; //Для кейса
    while (1)
    {
        printf("Что вы хотите сделать?\nВарианты:\nДобавить - введите 1\nУдалить - введите 2\nВывести все контакты на экран - введите 3\nВыйти - введите 9\n");
        scanf("%s", &doing);
        int idoing = atoi(doing);//делает число из строки, надо для проверки
        if (!atoi(doing))
            printf("Ошибка, ожидалась числовая команда, попробуйте еще раз\n");//если не число - выводит сообщение и отправляет по кругу
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
                printf("Введите номер (10 знаков)\n");
                scanf("%s", &contact[k].number);

                int index=sort(k);


                int c = write(k + 1);
                if (c == 5)
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
            return 0;
        }
    }
}