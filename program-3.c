#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

void uppercase_title(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    char buffer[MAX_LINE];
    off_t position = 0;
    ssize_t bytes_read;
    int line_start = 1;
    off_t line_offset = 0;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            if (line_start) {
                line_offset = position + i;
                line_start = 0;
            }

            if (buffer[i] == '\n') {
                size_t line_length = (position + i) - line_offset + 1;
                char line[MAX_LINE];
                lseek(fd, line_offset, SEEK_SET);
                read(fd, line, line_length);
                line[line_length] = '\0';

                if (strncmp(line, "## Program 3", 12) == 0) {
                    to_uppercase(line);
                    lseek(fd, line_offset, SEEK_SET);
                    write(fd, line, line_length);
                    close(fd);
                    printf("Heading replaced\n");
                    return 0;
                }

                line_start = 1;
            }
        }

        position += bytes_read;
    }

    close(fd);
    printf("Target not found\n");
    return 1;
}