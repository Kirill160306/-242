/*
* Программа: Работа с матрицей значений заплыва спортсменов на 50 и 100 м.
* Автор кода:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "interface.h"

#define ATHLETES 15
#define RACES 2

/*
* генерирует значения в матрице times.
* times - матрица значений заплывов.
* возвращает void, сразу присваивает значения в матрице.
* rand() / RAND_MAX * 30 + 20 - для генерации в диапазоне от 20 до 50.
* rand() / RAND_MAX * 60 + 50 - для генерации в диапазоне от 50 до 110.
*/
void generate_times(float times[ATHLETES][RACES]) {
    for (int i = 0; i < ATHLETES; i++) {
        times[i][0] = ((float)rand() / RAND_MAX) * 30 + 20;
        times[i][1] = ((float)rand() / RAND_MAX) * 60 + 50;
    }
}

/*
* выводит таблицу с именами и значениями заплывов.
* times - матрица значений заплывов, names - имена спортсменов.
* возвращает void, выводит таблицу при вызове функции.
*/
void print_table(float times[ATHLETES][RACES], char names[ATHLETES][20]) {
    printf("%-13s | 50m    | 100m\n", "Имя");
    printf("-----------------------------------\n");
    for (int i = 0; i < ATHLETES; i++) {
        printf("%-15s | %6.2f | %6.2f\n", names[i], times[i][0], times[i][1]);
    }
}

/*
* находит худшее и лучшее значение.
* times - матрица значений заплывов.
* best - значение лучшего спортсмена.
* worst - значение худшего спортсмена.
* race - индекс столбца (50 м и 100 м).
* возвращает void, присваивает значение для лучшего и худшего спортсмена.
*/
void best_and_worst(float times[ATHLETES][RACES], int* best, int* worst, int race) {
    *best = *worst = 0; // переменная, где хранится значения для лучшего и худшего спортсмена
    for (int i = 1; i < ATHLETES; i++) {
        if (times[i][race] < times[*best][race]) {
            *best = i;
        }
        if (times[i][race] > times[*worst][race]) {
            *worst = i;
        }
    }
}

/*
* сортирует указанный столбец по возрастанию.
* times - матрица значений заплывов.
* names - массив строк имен.
* race - индекс столбца (50 м и 100 м)
* возвращает void, меняет местами, используя сортировку пузырьком.
* memcpy - копирует указанное кол-во символом в первый аргумент из второго.
* strcpy - копирует в первый аргумент из второго аргумента.
*/
void sort_by_time(float times[ATHLETES][RACES], char names[ATHLETES][20], int race) {
    for (int i = 0; i < ATHLETES - 1; i++) {
        for (int j = i + 1; j < ATHLETES; j++) {
            if (times[i][race] > times[j][race]) {
                float temp_time[RACES];
                memcpy(temp_time, times[i], RACES * sizeof(float));
                memcpy(times[i], times[j], RACES * sizeof(float));
                memcpy(times[j], temp_time, RACES * sizeof(float));

                char temp_name[20];
                strcpy(temp_name, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], temp_name);
            }
        }
    }
}

/*
* редактирует значение заплыва указанного спортсмена.
* times - матрица значений заплывов.
* names - массив строк имен.
* возвращает void, выводит и меняет значение в матрице times.
*/
void edit_time(float times[ATHLETES][RACES], char names[ATHLETES][20]) {
    int athlete;
    printf("\nВведите номер спортсмена для редактирования (1-%d): ", ATHLETES);
    scanf("%d", &athlete);
    athlete--;

    if (athlete >= 0 && athlete < ATHLETES) {
        printf("\nТекущие времена: 50m = %.2f, 100m = %.2f\n", times[athlete][0], times[athlete][1]);
        printf("Введите новое время для 50m: ");
        scanf("%f", &times[athlete][0]);
        printf("Введите новое время для 100m: ");
        scanf("%f", &times[athlete][1]);
    } else {
        printf("Неверный номер спортсмена!\n");
    }
}

/*
* сохраняет в файл текущую таблицу.
* times - матрица значений заплывов.
* names - массив строк имен.
* возвращает void, при вызове функции, все сохраняется в файл.
* используются функции fprintf для записи и fopen/fclose для открытия и закрытия файла.
*/
void save_to_file(float times[ATHLETES][RACES], char names[ATHLETES][20]) {
    FILE* file = fopen("athletes_times.txt", "w");
    fprintf(file, "%-13s | 50m    | 100m\n", "Имя");
    fprintf(file, "-----------------------------------\n");
    for (int i = 0; i < ATHLETES; i++) {
        fprintf(file, "%-15s %.2f %.2f\n", names[i], times[i][0], times[i][1]);
    }
    fclose(file);
}

/*
* подсчитывает среднее, максимальное и минимальное значение.
* times - матрица значений заплывов, race - индекс столбца.
* возвращает void, подсчитывает и выводит в консоль.
*/
void calculate_statistics(float times[ATHLETES][RACES], int race) {
    float sum = 0, min = times[0][race], max = times[0][race];
    for (int i = 0; i < ATHLETES; i++) {
        sum += times[i][race];
        if (times[i][race] < min) min = times[i][race];
        if (times[i][race] > max) max = times[i][race];
    }
    printf("\nСреднее время для %d метров: %.2f\n", (race + 1) * 50, sum / ATHLETES);
    printf("Минимальное время: %.2f, Максимальное время: %.2f\n", min, max);
}

int main() {
    srand(time(NULL));

    float times[ATHLETES][RACES];
    char names[ATHLETES][20] = {"Атлет1 ", "Атлет2 ", "Атлет3 ", "Атлет4 ", "Атлет5 ",
                                "Атлет6 ", "Атлет7 ", "Атлет8 ", "Атлет9 ", "Атлет10",
                                "Атлет11", "Атлет12", "Атлет13", "Атлет14", "Атлет15"};
    printf("Привет! Данная программа предзначена для работы с матрицей значений заплывов спортсменов. \n");
    printf("Используйте пункты в меню для расчетов или вывода таблицы.\n");
    int choice; // переменная для выбора пользователя
    while (1) {
        interface();
        scanf("%d", &choice);

        switch (choice) {
            case 1: // при вводе 1 - вызов функции для генерации
                generate_times(times);
                break;
            case 2: // при вводе 2 - вызов функции для вывода таблицы
                print_table(times, names);
                break;
            case 3: // при вводе 3 - вызов функии для нахождения лучшего и худшего спортсмена
                {
                    int best, worst;
                    best_and_worst(times, &best, &worst, 0); // подсчет для 1 столбца
                    printf("\nЛучшее время на 50м: %s %.2f\n", names[best], times[best][0]);
                    printf("Худшее время на 50м: %s %.2f\n", names[worst], times[worst][0]);
                    best_and_worst(times, &best, &worst, 1); // подсчет для 2 столбца
                    printf("\nЛучшее время на 100м: %s %.2f\n", names[best], times[best][1]);
                    printf("Худшее время на 100м: %s %.2f\n", names[worst], times[worst][1]);
                }
                break;
            case 4: // при вводе 4 - вызов функции для сортировки
                sort_by_time(times, names, 0); // сортировка первого столбца
                printf("\nТаблица после сортировки по времени на 50м:\n");
                print_table(times, names);
                printf("\n");
                sort_by_time(times, names, 1); // сортировка второго столбца
                printf("\nТаблица после сортировки по времени на 100м:\n");
                print_table(times, names);
                break;
            case 5: // при вводе 5 - вызов функции для редактирования
                edit_time(times, names);
                break;
            case 6: // при вводе 6 - вызов функции для сохранения таблицы в файл
                save_to_file(times, names);
                printf("\nДанные сохранены в файл.\n");
                break;
            case 7: // при вводе 7 - вызывается функции для подсчета статистических значений
                calculate_statistics(times, 0); // подсчет для 1 столбца
                calculate_statistics(times, 1); // подсчет для 2 столбца
                break;
            case 0: // при вводе 0 - выход из программы
                exit(0);
                break;
            default: // в остальных случаях - вывод текста "неверный выбор"
                printf("Неверный выбор, попробуйте еще раз.\n");
        }
    }

    return 0;
}
