#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* f = fopen("file.txt", "r+");
    if (f == NULL) {
        perror("Ошибка при открытии файла");
        return 1;
    }

    // Считаем сколько чисел уже есть
    int count = 0;
    long long num, last;
    while (fscanf(f, "%lld", &num) == 1) {
        count++;
        last = num;
    }

    printf("В файле уже есть %d чисел Фибоначчи.\n", count);
    
    int n;
    printf("Сколько чисел добавить? ");
    scanf_s("%d", &n);

    long long a = 0, b = 1;
    if (count > 0) {
        // Находим последние два числа для продолжения
        if (count == 1) {
            a = 0; b = last;
        } else {
            // Для точности нужно хранить предпоследнее число
            // Упрощенный вариант - продолжаем с последнего
            a = last;
            b = last + (last > 1 ? last - 1 : 1);
        }
    }

    fseek(f, 0, SEEK_END);
    for (int i = 0; i < n; i++) {
        long long next = a + b;
        fprintf(f, " %lld", next);
        a = b;
        b = next;
    }

    fclose(f);
    printf("Числа добавлены.\n");
    return 0;
}
