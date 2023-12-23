#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_SIZE 100
//Объявление структуры
struct software {
    int number;
    int year;
    int month;
    int day;
    char client[20];
    double sum;
    char status[20];
};
// Прототипы функций
void searchByNumber(struct software programs[], int size);
void sortByDate(struct software programs[], int size);
void writeToFile(struct software programs[], int size);
void openFile(struct software programs[], int* size);
void menuPrint();
void newRecord(struct software* programs, int* size);
void record(struct software programs[], int i);
void table();
int main() {
    setlocale(LC_ALL, "RUS");
    //Создание рамки
    printf("+----------------------------------------------+\n");
    printf("| Выполнил: Семенютин Илья Игоревич            |\n");
    printf("| Группа: бИСТ-232                             |\n");
    printf("| Программа: работа с файловой БД «Заказ ПО»   |\n");
    printf("+----------------------------------------------+\n");
    struct software programs[MAX_SIZE];
    int size = 0;
    int choice;
    system("chcp 1251");
    do {
        //Создание меню
        printf("Меню:\n");
        printf("1) Добавить запись\n");
        printf("2) Поиск по номеру заказа\n");
        printf("3) Сортировка по дате заказа\n");
        printf("4) Записать в файл\n");
        printf("5) Загрузить из файла\n");
        printf("6) Выход из программы\n");
        printf("Выберите пункт меню: ");
        scanf("%d", &choice);
        //Реализация меню
        switch (choice) {
        case 1:
            newRecord(programs, &size);
            break;
        case 2:
            searchByNumber(programs, size);
            break;
        case 3:
            sortByDate(programs, size);
            break;
        case 4:
            writeToFile(programs, size);
            break;
        case 5:
            openFile(programs, &size);
            break;
        case 6:
            printf("Программа завершена.\n");
            break;
        default:
            printf("Некорректный ввод. Пожалуйста, выберите существующий пункт меню.\n");
        }

    } while (choice != 6);
}
//Функция для добавления новой записи
void newRecord(struct software* programs, int* size) {
    if (*size < MAX_SIZE) {
        printf("Введите данные для программы:\n");
        printf("Номер заказа: ");
        scanf(" %d", &programs[*size].number);
        printf("Дата заказа(Формат ввода:День.Месяц.Год): ");
        scanf(" %d.%d.%d", &programs[*size].day, &programs[*size].month, &programs[*size].year);
        printf("Клиент(Например:И.И.Иванов): ");
        scanf(" %s", programs[*size].client);
        printf("Сумма заказа: ");
        scanf("%lf", &programs[*size].sum);
        printf("Статус заказа: ");
        scanf(" %s", programs[*size].status);
        (*size)++;
    }
    else {
        printf("База данных полна.\n");
    }
}
//Функция табулирования
void table() {
    printf("|  Номер заказа |  Дата заказа  |    Клиент     |  Сумма заказа | Статус заказа |\n");
}
//Функция вывода элемента БД
void record(struct software programs[], int i) {
    printf("|%15d|  %2d.%2d.%4d   |%15s|%13.2lf|%15s|\n", programs[i].number, programs[i].day, programs[i].month, programs[i].year, programs[i].client, programs[i].sum, programs[i].status);
}
//Функция поиска элемента БД по номеру заказа
void searchByNumber(struct software programs[], int size) {
    if (size > 0) {
    int searchNumber;
    printf("Введите номер заказа: ");
    scanf("%d", &searchNumber);
    printf("\nРезультаты поиска по номеру заказа \"%d\":\n", searchNumber);
    table();
    for (int i = 0; i < size; ++i) {
        if (programs[i].number == searchNumber) {
            record(programs, i);
            }
        }
    }
    else {
        printf("База данных пуста.\n");
    }
}
//Функция для сортировки БД по дате
void sortByDate(struct software programs[], int size) {
    if (size > 0) {
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - i - 1; ++j) {
                if ((programs[j].year > programs[j + 1].year) ||
                    (programs[j].year == programs[j + 1].year && programs[j].month > programs[j + 1].month) ||
                    (programs[j].year == programs[j + 1].year && programs[j].month == programs[j + 1].month && programs[j].day > programs[j + 1].day)) {

                    struct software temp = programs[j];
                    programs[j] = programs[j + 1];
                    programs[j + 1] = temp;
                }
            }
        }
        printf("\nОтсортированные данные по дате:\n");
        table();
        for (int i = 0; i < size; ++i) {
            record(programs, i);
        }
    }
    else {
        printf("База данных пуста.\n");
    }
}
//Функция для записи БД в файл
void writeToFile(struct software programs[], int size) {
    if (size > 0) {
        FILE* file;
        file = fopen("data.txt", "a");
        if (file == NULL) {
            printf("Ошибка открытия файла.\n");
            return;
        }
        for (int i = 0; i < size; ++i) {
            fprintf(file, "%d %d %d %d %s %lf %s\n", programs[i].number, programs[i].day, programs[i].month, programs[i].year, programs[i].client, programs[i].sum, programs[i].status);
        }
        printf("\nБаза данных успешно записана в файл.\n");
        fclose(file);
    }
    else {
        printf("Нечего записывать в файл.\n");
    }
}
//Функция для загрузки БД из файла
void openFile(struct software programs[], int* size) {
    if (*size < MAX_SIZE) {
        FILE* file;
        file = fopen("data.txt", "r");
        if (file == NULL) {
            printf("Ошибка открытия файла.\n");
            return;
        }
        while (fscanf(file, "%d %d %d %d %s %lf %s", &programs[*size].number, &programs[*size].day,
            &programs[*size].month, &programs[*size].year, programs[*size].client, &programs[*size].sum,
            programs[*size].status) == 7) {
            (*size)++;
        }
        printf("\nБаза данных успешно загружена из файла.\n");
        fclose(file);
    }
    else {
        printf("База данных полна.\n");
    }
}