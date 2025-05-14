#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[]) {
    const char *vars[] = {"SHELL", "PATH", "USERNAME"};
    int num_vars = sizeof(vars) / sizeof(vars[0]);

    for (int i = 0; envp[i] != NULL; i++) {
        for (int j = 0; j < num_vars; j++) {
            size_t len = strlen(vars[j]);
            if (strncmp(envp[i], vars[j], len) == 0 && envp[i][len] == '=') {
                printf("%s\n", envp[i]);
            }
        }
    }

    return 0;
}