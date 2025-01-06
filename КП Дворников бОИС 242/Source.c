#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ATHLETES 15
#define RACES 2

void generate_times(float times[ATHLETES][RACES]) {
    for (int i = 0; i < ATHLETES; i++) {
        times[i][0] = ((float)rand() / RAND_MAX) * 30 + 20;
        times[i][1] = ((float)rand() / RAND_MAX) * 60 + 50;
    }
}

void print_table(float times[ATHLETES][RACES], char names[ATHLETES][20]) {
    printf("%-13s | 50m    | 100m\n", "���");
    printf("-----------------------------------\n");
    for (int i = 0; i < ATHLETES; i++) {
        printf("%-15s | %6.2f | %6.2f\n", names[i], times[i][0], times[i][1]);
    }
}

void best_and_worst(float times[ATHLETES][RACES], int* best, int* worst, int race) {
    *best = *worst = 0;
    for (int i = 1; i < ATHLETES; i++) {
        if (times[i][race] < times[*best][race]) {
            *best = i;
        }
        if (times[i][race] > times[*worst][race]) {
            *worst = i;
        }
    }
}

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

void edit_time(float times[ATHLETES][RACES], char names[ATHLETES][20]) {
    int athlete;
    printf("\n������� ����� ���������� ��� �������������� (1-%d): ", ATHLETES);
    scanf("%d", &athlete);
    athlete--;

    if (athlete >= 0 && athlete < ATHLETES) {
        printf("\n������� �������: 50m = %.2f, 100m = %.2f\n", times[athlete][0], times[athlete][1]);
        printf("������� ����� ����� ��� 50m: ");
        scanf("%f", &times[athlete][0]);
        printf("������� ����� ����� ��� 100m: ");
        scanf("%f", &times[athlete][1]);
    }
    else {
        printf("�������� ����� ����������!\n");
    }
}

void save_to_file(float times[ATHLETES][RACES], char names[ATHLETES][20]) {
    FILE* file = fopen("athletes_times.txt", "w");
    fprintf(file, "%-13s | 50m    | 100m\n", "���");
    fprintf(file, "-----------------------------------\n");
    for (int i = 0; i < ATHLETES; i++) {
        fprintf(file, "%-15s %.2f %.2f\n", names[i], times[i][0], times[i][1]);
    }
    fclose(file);
}

void calculate_statistics(float times[ATHLETES][RACES], int race) {
    float sum = 0, min = times[0][race], max = times[0][race];
    for (int i = 0; i < ATHLETES; i++) {
        sum += times[i][race];
        if (times[i][race] < min) min = times[i][race];
        if (times[i][race] > max) max = times[i][race];
    }
    printf("\n������� ����� ��� %d ������: %.2f\n", (race + 1) * 50, sum / ATHLETES);
    printf("����������� �����: %.2f, ������������ �����: %.2f\n", min, max);
}

int main() {
    srand(time(NULL));

    float times[ATHLETES][RACES];
    char names[ATHLETES][20] = { "�����1 ", "�����2 ", "�����3 ", "�����4 ", "�����5 ",
                                "�����6 ", "�����7 ", "�����8 ", "�����9 ", "�����10",
                                "�����11", "�����12", "�����13", "�����14", "�����15" };

    int choice;
    while (1) {
        printf("\n����:\n");
        printf("1. ������������� �������\n");
        printf("2. �������� �������\n");
        printf("3. ������ � ������ �����\n");
        printf("4. ����������� �� �������\n");
        printf("5. ������������� �����\n");
        printf("6. ��������� � ����\n");
        printf("7. ��������� ����������\n");
        printf("0. �����\n");
        printf("������� ��� �����: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            generate_times(times);
            break;
        case 2:
            print_table(times, names);
            break;
        case 3:
        {
            int best, worst;
            best_and_worst(times, &best, &worst, 0);
            printf("\n������ ����� �� 50�: %s %.2f\n", names[best], times[best][0]);
            printf("������ ����� �� 50�: %s %.2f\n", names[worst], times[worst][0]);
            best_and_worst(times, &best, &worst, 1);
            printf("\n������ ����� �� 100�: %s %.2f\n", names[best], times[best][1]);
            printf("������ ����� �� 100�: %s %.2f\n", names[worst], times[worst][1]);
        }
        break;
        case 4:
            sort_by_time(times, names, 0);
            printf("\n������� ����� ���������� �� ������� �� 50�:\n");
            print_table(times, names);
            printf("\n");
            sort_by_time(times, names, 1);
            printf("\n������� ����� ���������� �� ������� �� 100�:\n");
            print_table(times, names);
            break;
        case 5:
            edit_time(times, names);
            break;
        case 6:
            save_to_file(times, names);
            printf("\n������ ��������� � ����.\n");
            break;
        case 7:
            calculate_statistics(times, 0);
            calculate_statistics(times, 1);
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("�������� �����, ���������� ��� ���.\n");
        }
    }

    return 0;
}
