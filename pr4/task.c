#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    FILE *file = fopen("/dev/full", "w");
    if (file == NULL) {
        perror("Ошибка открытия файла в main");
        fprintf(stderr, "Код ошибки (errno): %d\n", errno);
        return errno;
    }
    
    const char *data = "Test data";
    size_t result = fwrite(data, 1, strlen(data), file);
    
    if (result != strlen(data)) {
        perror("Ошибка записи в файл в main");
        fprintf(stderr, "Код ошибки (errno): %d\n", errno);
        fprintf(stderr, "Записано байт: %zu из %zu\n", result, strlen(data));
    }
    
    fclose(file);
    return 0;
}
