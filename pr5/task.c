```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#ifndef MAX_PATH
#define MAX_PATH 4096 
#endif

#define SIZE_100B   100
#define SIZE_1KB    1024
#define SIZE_100KB  102400

typedef struct {
    long total_dirs;         
    long empty_dirs;         
    long dir_only_dirs;      
    long total_files;        
    long file_small_t;       
    long file_large_P;       
    long file_small_txt;     
} FileStats;

void analyze_directory_recursive(const char *path, FileStats *stats) {
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    
    char full_path[MAX_PATH];
    
    int local_files_count = 0;
    int local_dirs_count = 0;

    dir = opendir(path);
    if (!dir) return;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(full_path, MAX_PATH, "%s/%s", path, entry->d_name);

        if (stat(full_path, &st) == -1) {
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            stats->total_dirs++;
            local_dirs_count++;
            
            analyze_directory_recursive(full_path, stats);

        } else if (S_ISREG(st.st_mode)) {
            stats->total_files++; 
            local_files_count++;
            
            long file_size = (long)st.st_size;
            const char *file_name = entry->d_name;
            size_t name_len = strlen(file_name);

            if (file_size < SIZE_100B && strstr(file_name, "t") != NULL) {
                stats->file_small_t++;
            }

            if (file_size > SIZE_1KB && file_name[0] == 'P') {
                stats->file_large_P++;
            }

            if (file_size < SIZE_100KB) {
                if (name_len > 4 && strcmp(file_name + name_len - 4, ".txt") == 0) {
                    stats->file_small_txt++;
                }
            }
        }
    }

    closedir(dir);

    if (local_files_count == 0 && local_dirs_count == 0) {
        stats->empty_dirs++;
    } else if (local_files_count == 0 && local_dirs_count > 0) {
        stats->dir_only_dirs++;
    }
}

int main() {
    const char *start_dir = "Primates";
    FileStats stats = {0};

    struct stat st;
    
    if (stat(start_dir, &st) == -1 || !S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Ошибка: Стартовый каталог '%s' не найден или недоступен.\n", start_dir);
        return 1;
    }
    
    stats.total_dirs++;

    analyze_directory_recursive(start_dir, &stats);

    printf("1. Общее количество каталогов: %ld\n", stats.total_dirs);
    printf("2. Пустых каталогов: %ld\n", stats.empty_dirs);
    printf("3. Каталогов, содержащих только каталоги: %ld\n", stats.dir_only_dirs);
    printf("4. Общее количество файлов: %ld\n", stats.total_files);
    printf("5. Файлов < 100 b И с 't' в названии: %ld\n", stats.file_small_t);
    printf("6. Файлов > 1 Kb И начинающихся на 'P': %ld\n", stats.file_large_P);
    printf("7. Файлов < 100 Kb И с расширением '.txt': %ld\n", stats.file_small_txt);
    
    return 0;
}
```


