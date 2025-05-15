#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char _edata; 
extern char _end;    
extern char __bss_end;

int main() {
    char *buffer = (char *)malloc(1024);
    if (buffer == NULL) {
        return 1;  // Failure
    }

    void *program_break = sbrk(0);

    
    volatile void *end_of_program_text = (void *)program_break;
    volatile void *end_of_initialized_data = (void *)&_edata;
    volatile void *end_of_bss = (void *)&_end;

    (void)end_of_program_text;
    (void)end_of_initialized_data;
    (void)end_of_bss;

    free(buffer);
    return 0;
}