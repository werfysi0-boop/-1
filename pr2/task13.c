#include <stdio.h>
#include <string.h>

int main() {
    FILE* fin, * fout;
    errno_t err1 = fopen_s(&fin, "file.txt", "r");
    errno_t err2 = fopen_s(&fout, "newfile.txt", "w");

    if (err1 != 0 || err2 != 0) {
        perror("Ошибка при открытии файлов");
        return 1;
    }

    char line[100];
    while (fgets(line, sizeof(line), fin) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // Убираем \n
        fprintf(fout, "%-50s\n", line);   // Дополняем пробелами справа
    }

    fclose(fin);
    fclose(fout);
    printf("Файл создан.\n");
    return 0;
}
