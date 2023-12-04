#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_SIZE 100

struct university {
    char surname[20];
    char name[20];
    char curse[20];
    char speciality[20];
    double averagePoint;
    int year;
};

void searchBySurname(struct university programs[], int size, char searchNumber[]);
void sortByAveragePoint(struct university programs[], int size);
void writeToFile(struct university programs[], int size);
void openFile(struct university programs[], int size);

int main() {
    setlocale(LC_ALL, "RUS");
    struct university programs[MAX_SIZE];
    int size = 0;
    int choice;
    system("chcp 1251");
    do {
        printf("Меню:\n");
        printf("1) Добавить запись\n");
        printf("2) Поиск по фамилии студента\n");
        printf("3) Сортировка по среднему баллу\n");
        printf("4) Записать в файл\n");
        printf("5) Выход из программы\n");
        printf("Выберите пункт меню: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            if (size < MAX_SIZE) {
                printf("Введите данные для программы:\n");
                printf("Фамилия студента: ");
                scanf(" %s", &programs[size].surname);
                printf("Имя студента: ");
                scanf(" %s", &programs[size].name);
                printf("Курс: ");
                scanf(" %s", &programs[size].curse);
                printf("Специальность: ");
                scanf("%s", &programs[size].speciality);
                printf(" Средний балл: ");
                scanf(" %lf", &programs[size].averagePoint);
                printf("  Год поступления: ");
                scanf(" %d", &programs[size].year);
                size++;
            }
            else {
                printf("База данных полна. Невозможно добавить новую запись.\n");
            }
            break;
        case 2:
            if (size > 0) {
                char searchSurname[20];
                printf("Введите фамилию студента: ");
                scanf("%s", searchSurname);
                searchBySurname(programs, size, searchSurname);
            }
            else {
                printf("База данных пуста.\n");
            }
            break;
        case 3:
            if (size > 0) {
                sortByAveragePoint(programs, size);
                printf("\nОтсортированные данные по среднему баллу:\n");
                for (int i = 0; i < size; ++i) {
                    printf("Фамилия студента: %s, Средний балл: %.2lf\n", programs[i].surname, programs[i].averagePoint);
                }
            }
            else {
                printf("База данных пуста.\n");
            }
            break;
        case 4:
            if (size > 0) {
                writeToFile(programs, size);
            }
            else {
                printf("Нечего записывать в файл.\n");
            }
            break;
        case 5:
            printf("Программа завершена.\n");
            break;
        /*case 6:
            openFile(programs, size);
            break;*/
        default:
            printf("Некорректный ввод. Пожалуйста, выберите существующий пункт меню.\n");
        }

    } while (choice != 5);
}

void searchBySurname(struct university programs[], int size, char searchSurname[]) {
    printf("\nРезультаты поиска по фамилии студента \"%s\":\n", searchSurname);
    printf("------------------------------------------------\n");
    for (int i = 0; i < size; ++i) {
        if (strstr(programs[i].surname, searchSurname) != NULL) {
            printf("Фамилия студента: %s\n", programs[i].surname);
            printf("Имя студента: %s\n", programs[i].name);
            printf("Курс: %s\n", programs[i].curse);
            printf("Специальность: %s\n", programs[i].speciality);
            printf("Средний балл: %.2lf\n", programs[i].averagePoint);
            printf("Год поступления: %d\n", programs[i].year);
            printf("------------------------------------------------\n");
        }
    }
}

void sortByAveragePoint(struct university programs[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (programs[j].averagePoint < programs[j + 1].averagePoint) {
                struct university temp = programs[j];
                programs[j] = programs[j + 1];
                programs[j + 1] = temp;
            }
        }
    }
}

/*void openFile(struct university programs[], int size) {
    char fname[100];
    printf("Введите путь к файлу: ");
    scanf("%s", fname);
    FILE* fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("Не удалось открыть файл.\n");
        return;
    }
    printf(" файл.\n");
    for (int i = 0; i < size; ++i) {
        fscanf(fp, "Фамилия студента: %s", programs[i].surname);
        fscanf(fp, "Имя студента:%s", programs[i].name);
        fscanf(fp, "Курс: %s", programs[i].curse);
        fscanf(fp, "Специальность: %s", programs[i].speciality);
        fscanf(fp, "Средний балл: %.2lf", &programs[i].averagePoint);
        fscanf(fp, "Год поступления: %d", &programs[i].year);
    }
    fclose(fp);
}*/
    

void writeToFile(struct university programs[], int size) {
    FILE* file = fopen("programs.txt", "a");
    if (file == NULL) {
        printf("Не удалось открыть файл.\n");
        return;
    }
    for (int i = 0; i < size; ++i) {
        fprintf(file, "Фамилия студента: %s\n", programs[i].surname);
        fprintf(file, "Имя студента:%s\n", programs[i].name);
        fprintf(file, "Курс: %s\n", programs[i].curse);
        fprintf(file, "Специальность: %s\n", programs[i].speciality);
        fprintf(file, "Средний балл: %.2lf\n", programs[i].averagePoint);
        fprintf(file, "Год поступления: %d\n", programs[i].year);
        fprintf(file, "------------------------------------------------\n");
    }
    fclose(file);
    printf("Данные успешно записаны в файл.\n");
}