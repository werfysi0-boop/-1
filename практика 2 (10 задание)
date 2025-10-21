#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* f = fopen("file.txt", "r");
    FILE* newf = fopen("newfile.txt", "w");

    if (f == NULL || newf == NULL) {
        perror("Ошибка при открытии файла");
        return 1;
    }

    char line[100];
    while (fgets(line, sizeof(line), f) != NULL) {
        char* token = strtok(line, " ");
        while (token != NULL) {
            int num = atoi(token);
            if (num < 0) {
                fprintf(newf, "0 ");
            } else {
                fprintf(newf, "%d ", num);
            }
            token = strtok(NULL, " ");
        }
        fprintf(newf, "\n");
    }

    fclose(f);
    fclose(newf);
    return 0;
}
