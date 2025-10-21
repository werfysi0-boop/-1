#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    FILE* f;
    errno_t err = fopen_s(&f, "file.txt", "r");
    if (err != 0) {
        perror("Ошибка при открытии файла");
        return 1;
    }

    char line[1000];
    int count = 0;

    while (fgets(line, sizeof(line), f) != NULL) {
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }
        if (len > 0 && line[0] == line[len - 1]) {
            count++;
        }
    }

    fclose(f);
    printf("Количество строк: %d\n", count);
    return 0;
}
