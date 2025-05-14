#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

#define MAX_PATH 256
#define MAX_LINE 1024

int is_numeric(const char *str) {
    for (; *str; str++) {
        if (!isdigit(*str)) return 0;
    }
    return 1;
}

int main() {
    DIR *proc_dir = opendir("/proc");
    if (!proc_dir) {
        perror("opendir /proc");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(proc_dir)) != NULL) {
        if (!is_numeric(entry->d_name))
            continue;

        char comm_path[MAX_PATH];
        snprintf(comm_path, sizeof(comm_path), "/proc/%s/comm", entry->d_name);

        FILE *comm_file = fopen(comm_path, "r");
        if (!comm_file)
            continue;

        char process_name[256];
        if (fgets(process_name, sizeof(process_name), comm_file) == NULL) {
            fclose(comm_file);
            continue;
        }
        fclose(comm_file);

        // Remove newline character
        process_name[strcspn(process_name, "\n")] = 0;

        if (strcmp(process_name, "top") == 0) {
            // Now read the stat file to get the PPID
            char stat_path[MAX_PATH];
            snprintf(stat_path, sizeof(stat_path), "/proc/%s/stat", entry->d_name);
            FILE *stat_file = fopen(stat_path, "r");
            if (!stat_file)
                continue;

            int pid, ppid;
            char comm[256], state;
            fscanf(stat_file, "%d %s %c %d", &pid, comm, &state, &ppid);
            fclose(stat_file);

            printf("Found 'top' with PID %d, Parent PID (PPID): %d\n", pid, ppid);
            closedir(proc_dir);
            return 0;
        }
    }

    closedir(proc_dir);
    printf("No running 'top' process found.\n");
    return 1;
}