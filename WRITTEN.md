# Spring 2025 System Programming — Final Project

## Written Portion

### 1. Describe what happens to memory released by the OS with regard to virtual memory

Regarding virtual memory, memory released by the OS is freed for other processes using locality of reference.

---

### 2. In a C program, why does `argv[argv]` return `NULL`?

I assume this is a typo. The phrase "argv[argv]" is invalid due to it being a pointer and pointing to itself. If you meant "argv[argc]", this returns "NULL" because argc is out of the argv[] array's bounds.

---

### 3. When a system call is made the CPU changes from user mode to kernel mode. Why?

Switching from user mode to kernel mode allows the CPU to access protected kernel memory.

---

### 4. Explain the relationship between the return value of a system call and the global variable `errno`

If the return value of the system call service routine indicated an error, the wrapper function sets the global variable errno using this value. The wrapper function then returns to the caller, providing an integer return value indicating the success or failure of the system call.

---

### 5. Consider the following C program. The variables and functions get allocated to which memory segments? Write your answers in comments to the right of each item

```c
#include <stdio.h>
#include <stdlib.h>

#define MAX 128

char my_string[MAX];  /* Uninitialized data segment */
char class_name[] = "System Programming";  /* Initialized data segment */
int global_integer = 3;  /* Initialized data segment */

void print_global() {   /* Allocated in frame for print_global() */
  printf("%d\n", global_integer); /* Allocated in frame for print_global() */
}

int square(int x) {  /* Uninitialized data segment */
  int result = x * x;   /* Allocated in frame for square() */

  return result;    /* Return value passed via register */
}

int main (int argc, char *argv[]) {   /* Allocated in frame for main() */
  char *dynamic_memory;   /* Uninitialized data segment */
  dynamic_memory = malloc(MAX);  /* Initialized data segment */
  free(dynamic_memory);    /* Allocated in frame for main() */
  dynamic_memory = NULL;    /* Allocated in frame for main() */

  return 0;   /* Return value passed via register */
}
```

---

### 6. Explain the difference between `malloc`, `calloc`, `realloc`

malloc- allocates a single continuous memory block onto the heap at runtime
calloc- initializes allocated memory to 0
realloc- resizes previously allocated memory block

---

### 7. Explain the difference between `brk` and `sbrk`. Why is `malloc` a better option of `brk`, and `sbrk`?

brk() system call sets the program break to the location specified by end_data_segment. A call to sbrk() adjusts the program break by adding increment to it. 

malloc is a better option due to being standardized as part of the C language, easier to use in threaded programs having a simpler interface that allows memory to be allocated in small units and allowing us to arbitrarily deallocate blocks of memory.

---

### 8. Explain why a shadow password file is needed

Shadow password files are a method for UNIX systems to protect against hackers by encrypting passwords.

---

### 9. What is the numeric equivalent of the `README.md` file’s permission bits below, and what is the command to give the file full access, across the board?

```sh
-rw-r--r-- 1  johnnythunders  staff  3476 May  1 11:57 README.md
```
numeric (octal): 644

command: chmod 777 README.md

---

### 10. What does `kill -9 1` do? Explain in detail

Kill -9 -1 is used to terminate process ID 1, crashing the system.
