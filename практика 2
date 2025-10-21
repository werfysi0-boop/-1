#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(char*)a - *(char*)b);
}

int main() {
    FILE* f;
    errno_t err = fopen_s(&f, "file.txt", "r");
    if (err != 0) {
        perror("Ошибка при открытии файла");
        return 1;
    }

    char str[100];
    char result[1024] = "";

    while (fgets(str, sizeof(str), f) != NULL) {
        str[strcspn(str, "\n")] = '\0'; // Убираем символ новой строки
        qsort(str, strlen(str), sizeof(char), compare);
        strcat_s(result, sizeof(result), str);
        strcat_s(result, sizeof(result), "\n");
    }

    fclose(f);

    err = fopen_s(&f, "file.txt", "w");
    if (err != 0) {
        perror("Ошибка при открытии файла");
        return 1;
    }

    fputs(result, f);
    fclose(f);
    return 0;
}
