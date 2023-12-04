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
        printf("����:\n");
        printf("1) �������� ������\n");
        printf("2) ����� �� ������� ��������\n");
        printf("3) ���������� �� �������� �����\n");
        printf("4) �������� � ����\n");
        printf("5) ����� �� ���������\n");
        printf("�������� ����� ����: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            if (size < MAX_SIZE) {
                printf("������� ������ ��� ���������:\n");
                printf("������� ��������: ");
                scanf(" %s", &programs[size].surname);
                printf("��� ��������: ");
                scanf(" %s", &programs[size].name);
                printf("����: ");
                scanf(" %s", &programs[size].curse);
                printf("�������������: ");
                scanf("%s", &programs[size].speciality);
                printf(" ������� ����: ");
                scanf(" %lf", &programs[size].averagePoint);
                printf("  ��� �����������: ");
                scanf(" %d", &programs[size].year);
                size++;
            }
            else {
                printf("���� ������ �����. ���������� �������� ����� ������.\n");
            }
            break;
        case 2:
            if (size > 0) {
                char searchSurname[20];
                printf("������� ������� ��������: ");
                scanf("%s", searchSurname);
                searchBySurname(programs, size, searchSurname);
            }
            else {
                printf("���� ������ �����.\n");
            }
            break;
        case 3:
            if (size > 0) {
                sortByAveragePoint(programs, size);
                printf("\n��������������� ������ �� �������� �����:\n");
                for (int i = 0; i < size; ++i) {
                    printf("������� ��������: %s, ������� ����: %.2lf\n", programs[i].surname, programs[i].averagePoint);
                }
            }
            else {
                printf("���� ������ �����.\n");
            }
            break;
        case 4:
            if (size > 0) {
                writeToFile(programs, size);
            }
            else {
                printf("������ ���������� � ����.\n");
            }
            break;
        case 5:
            printf("��������� ���������.\n");
            break;
        /*case 6:
            openFile(programs, size);
            break;*/
        default:
            printf("������������ ����. ����������, �������� ������������ ����� ����.\n");
        }

    } while (choice != 5);
}

void searchBySurname(struct university programs[], int size, char searchSurname[]) {
    printf("\n���������� ������ �� ������� �������� \"%s\":\n", searchSurname);
    printf("------------------------------------------------\n");
    for (int i = 0; i < size; ++i) {
        if (strstr(programs[i].surname, searchSurname) != NULL) {
            printf("������� ��������: %s\n", programs[i].surname);
            printf("��� ��������: %s\n", programs[i].name);
            printf("����: %s\n", programs[i].curse);
            printf("�������������: %s\n", programs[i].speciality);
            printf("������� ����: %.2lf\n", programs[i].averagePoint);
            printf("��� �����������: %d\n", programs[i].year);
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
    printf("������� ���� � �����: ");
    scanf("%s", fname);
    FILE* fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("�� ������� ������� ����.\n");
        return;
    }
    printf(" ����.\n");
    for (int i = 0; i < size; ++i) {
        fscanf(fp, "������� ��������: %s", programs[i].surname);
        fscanf(fp, "��� ��������:%s", programs[i].name);
        fscanf(fp, "����: %s", programs[i].curse);
        fscanf(fp, "�������������: %s", programs[i].speciality);
        fscanf(fp, "������� ����: %.2lf", &programs[i].averagePoint);
        fscanf(fp, "��� �����������: %d", &programs[i].year);
    }
    fclose(fp);
}*/
    

void writeToFile(struct university programs[], int size) {
    FILE* file = fopen("programs.txt", "a");
    if (file == NULL) {
        printf("�� ������� ������� ����.\n");
        return;
    }
    for (int i = 0; i < size; ++i) {
        fprintf(file, "������� ��������: %s\n", programs[i].surname);
        fprintf(file, "��� ��������:%s\n", programs[i].name);
        fprintf(file, "����: %s\n", programs[i].curse);
        fprintf(file, "�������������: %s\n", programs[i].speciality);
        fprintf(file, "������� ����: %.2lf\n", programs[i].averagePoint);
        fprintf(file, "��� �����������: %d\n", programs[i].year);
        fprintf(file, "------------------------------------------------\n");
    }
    fclose(file);
    printf("������ ������� �������� � ����.\n");
}