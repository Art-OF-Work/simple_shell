# Simple Shall projct





# Made by

[Yassir Boukhima](https://github.com/art-of-work)



[Dinipre Ikpaikpai](https://github.com/Woyengidinipre)

## What I Need





### **skils-1**

    - Basics of programming

    - Basics of C

    - Basics of thinking like an engineer

    - Group work

    - Learning how to learn



### **skils-2**



    - Who designed and implemented the original Unix operating system

    - Who wrote the first version of the UNIX shell

    - Who invented the B programming language (the direct predecessor to the C programming language)

    - Who is Ken Thompson

    - How does a shell work

    - What is a pid and a ppid

    - How to manipulate the environment of the current process

    - What is the difference between a function and a system call

    - How to create processes

    - What are the three prototypes of main

    - How does the shell use the PATH to find the programs

    - How to execute another program with the execve system call

    - How to suspend the execution of a process until one of its children terminates

    - What is EOF / “end-of-file”?



### List of allowed functions and system calls



|Name of the function|Header file|Prototyp|
|---|---|---|
|access, faccessat|<fcntl.h>/<unistd.h>|int faccessat(int dirfd, const char *pathname, int mode, int flags)|
|chdir, fchdir|<unistd.h>| int chdir(const char *path); / int fchdir(int fd);|
| close|<unistd.h>|int close(int fd);||closedir|<sys/types.h> / <dirent.h>|int closedir(DIR *dirp);||execve|<unistd.h>|int execve(const char *pathname, char *const argv[],char *const envp[]);||exit|<stdlib.h>|void exit(int status);|| _Exit, _exit|<stdlib.h>//<unistd.h>|void _Exit(int status);//void _exit(int status);||fflush|<stdio.h>|int fflush(FILE *stream);||fork	|pid_t fork(void)	|unistd.h|
|free	|void free(void *ptr)	|stdlib.h|
|getcwd	|char *getcwd(char *buf, size_t size)	|unistd.h||getline|	ssize_t getline(char **lineptr, size_t *n, FILE *stream)	|stdio.h||getpid	|pid_t getpid(void)	|unistd.h||isatty	|int isatty(int fd)	|unistd.h||kill	|int kill(pid_t pid, int sig)	|signal.h||malloc|	void *malloc(size_t size)	|stdlib.h||open	|int open(const char *pathname, int flags, mode_t mode)	|fcntl.h||opendir	|DIR *opendir(const char *name)	|dirent.h||perror	|void perror(const char *s)	|stdio.h||read	|ssize_t read(int fd, void *buf, size_t count)	|unistd.h||readdir	|struct dirent *readdir(DIR *dirp)	|dirent.h||signal	|sig_t signal(int sig, sig_t handler)	|signal.h||stat	|int stat(const char *pathname, struct stat *buf)|	sys/stat.h||lstat	|int lstat(const char *pathname, struct stat *buf)	|sys/stat.h||fstat	|int fstat(int fd, struct stat *buf)	|sys/stat.h||strtok	|char *strtok(char *s1, const char *s2)	|string.h||wait	|int wait(int *status)	|sys/wait.h||waitpid	|pid_t waitpid(pid_t pid, int *status, int options)	|sys/wait.h||wait3	|int wait3(int *status, int options, struct rusage *rusage)	|sys/wait.h||wait4	|int wait4(pid_t pid, int *status, int options, struct rusage *rusage)	|sys/wait.h||write	|ssize_t write(int fd, const void *buf, size_t count)	|unistd.h|---



### 1-File access

The access() function in C is used to check whether the calling process can access a specific file. Here’s the prototype of the access() function:

```c

#include <unistd.h>

int access(const char *pathname, int mode);

```

`pathname`: This is a pointer to a null-terminated string that specifies the path to the file you want to check.

`mode`: This is an integer that specifies the accessibility checks to be performed. It can be `F_OK`, or a bitwise-inclusive OR of one or more of `R_OK`, `W_OK`, and `X_OK`.

The mode argument can have the following values12:



`F_OK`: Tests for the existence of the file.<br>

`R_OK`: Tests whether the file can be accessed for reading.<br>

`W_OK`: Tests whether the file can be accessed for writing.<br>

`X_OK`: Tests whether the file can be accessed for execution.

<br>

**Return**<br>

The function returns `0` if the directory was successfully changed, and `-1` otherwise <br>



**CODE**

```c

#include <unistd.h>

#include <stdio.h>



int main() {

    char path[] = "/path/to/file";



    if (access(path, F_OK) != 0) {

        printf("'%s' does not exist!\n", path);

    } else {

        if (access(path, R_OK) == 0) {

            printf("You have read access to '%s'\n", path);

        }

        if (access(path, W_OK) == 0) {

            printf("You have write access to '%s'\n", path);

        }

        if (access(path, X_OK) == 0) {

            printf("You have execute access to '%s'\n", path);

        }

    }



    return 0;

}

```



In this example, replace `"/path/to/file"` with the path to the file you want to check. This code checks whether the file exists and whether it can be read, written, or executed. If the file does not exist or cannot be accessed in the specified way, a message is printed to the console



### 2-Change Directory

The `chdir()` function in C is used to change the current working directory of the calling process. Here’s the prototype of the `chdir()` function:

```c

#include <unistd.h>

int chdir(const char *path);

```



`path`: This is a pointer to a null-terminated string that specifies the path to the directory you want to change to.<br>



**Return**<br>

The function returns `0` if the directory was successfully changed, and `-1` otherwise <br>



**CODE**

```c

#include <unistd.h>

#include <stdio.h>



int main() {

    if (chdir("/path/to/directory") != 0) {

        perror("chdir() failed");

        return 1;

    }



    // Now the current working directory has been changed to "/path/to/directory"

    return 0;

}

```



In this example, replace `"/path/to/directory" `with the path to the directory you want to change to. This code changes the current working directory to the specified directory. If the directory cannot be changed (for example, because it does not exist, or the process does not have sufficient permissions), an error message is printed to the console



Please note that the `chdir()` function changes the current working directory of the calling process only. So when you execute a program that uses `chdir()`, it does not change the working directory of the terminal or shell that launched the program. This is because each process in a Unix-like operating system has its own current working directory, and changing it affects only that process



### Close a file descriptor



The `close()` function in C is used to close a file descriptor. Here’s the prototype of the `close()` function:



```c

#include <unistd.h>



int close(int fd);

```

* `fd`: This is the file descriptor that you want to close.



**Return**<br>

The function returns `0` if the directory was successfully changed, and `-1` otherwise <br>



**CODE**



```c

#include <unistd.h>

#include <stdio.h>

#include <fcntl.h>



int main() {

    int fd = open("/path/to/file", O_RDONLY);

    if (fd == -1) {

        perror("open() failed");

        return 1;

    }



    // Now the file is open and fd is the file descriptor



    if (close(fd) != 0) {

        perror("close() failed");

        return 1;

    }



    // Now the file descriptor fd has been closed



    return 0;

}

```



In this example, replace `"/path/to/file"` with the path to the file you want to open. This code opens a file, and then closes the file descriptor. If the file cannot be opened or closed (for example, because it does not exist, or the process does not have sufficient permissions), an error message is printed to the console.



Please note that after a file descriptor has been closed, it no longer refers to any file and may be reused1. Any record locks held on the file it was associated with, and owned by the process, are removed1. If `fd` is the last file descriptor referring to the underlying open file description, the resources associated with the open file description are freed



### Close a directory



The `closedir()` function in C is used to close a directory stream that was opened by `opendir()`. Here’s the prototype of the `closedir()` function:



```c

#include <dirent.h>



int closedir(DIR *dirp);

```

* `dirp`: This is a pointer to a directory stream that you want to close.



**Return**<br>

The function returns `0` if the directory was successfully changed, and `-1` otherwise <br>



**CODE**

```c

#include <dirent.h>

#include <stdio.h>



int main() {

    DIR *dirp = opendir("/path/to/directory");

    if (dirp == NULL) {

        perror("opendir() failed");

        return 1;

    }



    // Now the directory is open and dirp is the directory stream



    if (closedir(dirp) != 0) {

        perror("closedir() failed");

        return 1;

    }



    // Now the directory stream dirp has been closed



    return 0;

}

```



In this example, replace `"/path/to/directory" `with the path to the directory you want to open. This code opens a directory, and then closes the directory stream. If the directory cannot be opened or closed (for example, because it does not exist, or the process does not have sufficient permissions), an error message is printed to the console.



Please note that after a directory stream has been closed, it no longer refers to any directory and may be reused. Any resources associated with the directory stream are freed.



### Execute program



The `execve()` function in C is used to replace the current process image with a new process image. It is part of the `exec` family of functions. Here’s the prototype of the `execve()` function:

```c

#include <unistd.h>



int execve(const char *pathname, char *const argv[], char *const envp[]);

```

`pathname`: This is a pointer to a null-terminated string that specifies the path to the file you want to execute.



`argv`: This is an array of pointers to strings that represent the argument list available to the new program. The first argument, by convention, should point to the filename associated with the file being executed. The array must be terminated by a NULL pointer.



`envp:` This is an array of pointers to strings, which are passed as the environment of the new program. The array must be terminated by a NULL pointer.

The `execve()` function replaces the current process image with a new process image. This means the program that is currently being run by the calling process is replaced with a new program, with newly initialized stack, heap, and data segments.



**CODE**

```c

#include <unistd.h>



int main() {

    char *pathname = "/path/to/program";

    char *argv[] = { "program", "arg1", "arg2", NULL };

    char *envp[] = { "VAR1=value1", "VAR2=value2", NULL };



    if (execve(pathname, argv, envp) == -1) {

        perror("execve() failed");

        return 1;

    }



    // The execve() function does not return on success



    return 0;

}

```



In this example, replace `"/path/to/program" `with the path to the program you want to execute. This code executes a new program, passing it two arguments (“arg1” and “arg2”) and two environment variables (“VAR1=value1” and “VAR2=value2”). If the new program cannot be executed (for example, because it does not exist, or the process does not have sufficient permissions), an error message is printed to the console.



Please note that the `execve()` function does not return on success. If it does return, that means there was an error



### Terminate the process

The `exit()` function in C is used to terminate the calling process. Here’s the prototype of the `exit()` function:

```c

#include <stdlib.h>



void exit(int status);

```

`status`: This is the exit status that is returned to the parent process. Most systems use the status value mod 256 as the exit status.



The `exit()` function does not return. When `exit()` is called, the following steps are performed:



1. All functions registered with `atexit()` and `on_exit()` are called in the reverse order of their registration.



2. All open file descriptors are closed.

3. The process is terminated.



**CODE**

```c

#include <stdlib.h>

#include <stdio.h>



int main() {

    printf("About to exit...\n");

    exit(0);



    // This line will never be printed

    printf("This line will never be printed\n");



    return 0;

}

```

In this example, the program prints “About to exit…”, then calls `exit(0)`. The `exit()` function terminates the program, so the line “This line will never be printed” is never printed.



Please note that the argument to `exit()` is the exit status of the process. By convention, an exit status of 0 indicates success, and non-zero values indicate different kinds of errors. The specific meanings of different non-zero exit statuses are generally program-specific.

### Terminate the process

The `_exit()` function in C is used to terminate the current process immediately. It is part of the POSIX standard and is typically used when you want to end a process immediately without performing any cleanup operations that `exit()` would normally do1. Here’s the prototype of the `_exit()` function:

```c

#include <unistd.h>



void _exit(int status);

```



`status`: This is the exit status that is returned to the parent process. Most systems use the status value mod 256 as the exit status.



The `_exit()` function does not return. When `_exit()` is called, the process is terminated immediately.



```c

#include <unistd.h>

#include <stdio.h>



int main() {

    printf("About to exit...\n");

    _exit(0);



    // This line will never be printed

    printf("This line will never be printed\n");



    return 0;

}

```

In this example, the program prints “About to exit…”, then calls `_exit(0)`. The `_exit()` function terminates the program, so the line “This line will never be printed” is never printed.



Please note that the argument to `_exit()` is the exit status of the process. By convention, an exit status of 0 indicates success, and non-zero values indicate different kinds of errors. The specific meanings of different non-zero exit statuses are generally program-specific

### Flush a stream

The `fflush()` function in C is used to flush the output buffer of a stream. It is typically used for output streams only. Its purpose is to clear (or flush) the output buffer and move the buffered data to console (in case of `stdout`) or disk (in case of file output stream)1. Here’s the prototype of the `fflush()` function:

```C

#include <stdio.h>



int fflush(FILE *stream);

```

* `stream`: This is a pointer to a stream that you want to flush.



**Return**

The function returns zero if the stream was successfully flushed, and `EOF` if there was an error.



**CODE**



```c

#include <stdio.h>



int main() {

    printf("Hello, World!");

    fflush(stdout);



    // Now the output buffer of stdout has been flushed,

    // and "Hello, World!" has been written to the console



    return 0;

}

```

In this example, the program prints “Hello, World!” to the standard output (`stdout`), then calls `fflush(stdout)`. The `fflush()` function flushes the output buffer of `stdout`, so “Hello, World!” is written to the console immediately1.



Please note that the use of `fflush()` with input streams (`stdin`) is undefined by the C standard. Some compilers like Microsoft Visual Studio allow it, but it’s generally not recommended



### Create a child process

The fork() function in C is used to create a new process, which is called the child process, which runs concurrently with the process that called fork() (which is now referred to as the parent process). Here’s the prototype of the fork() function:



```c

#include <unistd.h>



pid_t fork(void);

```

**Description:**



The fork() function creates a new process by duplicating the calling process. The new process, called the child process, is an exact copy of the calling process, called the parent process, except for the returned values. In the parent process, fork() returns the process ID (PID) of the child process, while in the child process, it returns 0.



**Return Value:**



On success, the PID of the child process is returned to the parent process, and 0 is returned to the child process.

On failure, -1 is returned to the parent process, and no child process is created.



**Example:**

```c

#include <stdio.h>

#include <unistd.h>



int main() {

    pid_t pid = fork(); // Create a child process

    if (pid == -1) {

        perror("fork() failed");

        return 1;

    }



    if (pid == 0) {

        // Child process

        printf("Child process with PID: %d\n", getpid());

    } else {

        // Parent process

        printf("Parent process with PID: %d, created child with PID: %d\n", getpid(), pid);

    }



    return 0;

}

```

In this example, `fork()` is called to create a new child process. If `fork()` succeeds, it returns the PID of the child process in the parent process and 0 in the child process. The program then distinguishes between the parent and child processes and prints their respective PIDs.



### Deallocate memory

The free() function in C is used to deallocate memory that was previously allocated dynamically by the malloc(), calloc(), or realloc() functions. Here’s the prototype of the free() function:



```c

#include <stdlib.h>



void free(void *ptr);

```

**Description:**



The free() function deallocates the memory block pointed to by ptr, which must have been previously allocated by malloc(), calloc(), or realloc(). If ptr is NULL, no operation is performed.



Parameters:

ptr: A pointer to the memory block to deallocate.

Example:

```c

#include <stdlib.h>



int main() {

    int *ptr = (int *)malloc(sizeof(int)); // Allocate memory

    if (ptr == NULL) {

        perror("malloc() failed");

        return 1;

    }



    // Use the allocated memory...



    free(ptr); // Deallocate memory



    return 0;

}

```

In this example, malloc() is used to allocate memory for an integer. After using the allocated memory, free() is called to deallocate it.



### Get current working directory

The `getcwd()` function in C is used to get the current working directory of the calling process. Here’s the prototype of the `getcwd()` function:



```c

#include <unistd.h>



char *getcwd(char *buf, size_t size);

```

**Description:**



The `getcwd()` function copies the absolute pathname of the current working directory into the buffer pointed to by buf. The size argument specifies the size of the buffer.



**Parameters:**



* `buf`: A pointer to the buffer where the current working directory pathname will be stored.



* `size`: The size of the buffer.



**Return Value:**



* On success, `getcwd()` returns a pointer to the buffer containing the current working directory pathname.



* On failure, NULL is returned, and `errno` is set appropriately.



**Example:**



```c

#include <unistd.h>

#include <stdio.h>



int main() {

    char cwd[1024]; // Buffer to store the current working directory

    if (getcwd(cwd, sizeof(cwd)) == NULL) {

        perror("getcwd() failed");

        return 1;

    }



    printf("Current working directory: %s\n", cwd);



    return 0;

}

```

In this example, `getcwd()` is called to retrieve the current working directory pathname, which is then printed to the console.



### Read a line

The `getline()` function in C is used to read a line from a file stream, dynamically allocating memory as needed. Here’s the prototype of the `getline()` function:



```c

#include <stdio.h>



ssize_t getline(char **lineptr, size_t *n, FILE *stream);

```

**Description:**



The `getline()` function reads a line from the input stream stream and stores it in the buffer pointed to by lineptr. If lineptr is NULL, `getline()` will allocate a buffer for storing the line. The size of the allocated buffer is stored in the object pointed to by n.



**Parameters:**



* `lineptr`: A pointer to a buffer where the line will be stored, or NULL to let getline() allocate a buffer.

* `n`: A pointer to a variable containing the size of the buffer pointed to by lineptr, or NULL.

* `stream`: The input stream to read from.



**Return Value:**



* On success, `getline()` returns the number of characters read, including the newline character.



* On failure or when the end of the file is **reached, -1 is returned.



**Example:**



```c

#include <stdio.h>



int main() {

    char *line = NULL; // Pointer to the line buffer

    size_t len = 0; // Length of the buffer

    ssize_t bytes_read; // Number of bytes read



    printf("Enter a line of text: ");

    bytes_read = getline(&line, &len, stdin); // Read a line from stdin

    if (bytes_read == -1) {

        perror("getline() failed");

        return 1;

    }



    printf("Line read: %s", line);



    free(line); // Free dynamically allocated memory



    return 0;

}

```



In this example, `getline()` is used to read a line of text from the standard input (`stdin`). The function dynamically allocates memory as needed to store the line. After using the line buffer, `free()` is called to deallocate the memory.



### Get process ID

The `getpid()` function in C is used to get the process ID (`PID`) of the current process. Here’s the prototype of the `getpid()` function:



```c

#include <unistd.h>



pid_t getpid(void);

```

**Description:**



The `getpid()` function returns the process ID of the current process.





**Return Value:**



The PID of the current process.



**Example:**



```c



#include <stdio.h>

#include <unistd.h>



int main() {

    pid_t pid = getpid(); // Get the PID of the current process

    printf("PID: %d\n", pid);

    return 0;

}

```

In this example, `getpid()` is called to retrieve the PID of the current process, which is then printed to the console.



### Test whether a file descriptor refers to a terminal

The `isatty()` function in C is used to determine whether a given file descriptor refers to a terminal. Here’s the prototype of the `isatty()` function:



```c

#include <unistd.h>



int isatty(int fd);

```

**Description:**



The `isatty()` function tests whether the file descriptor fd refers to a terminal device.



**Parameters:**



* `fd`: The file descriptor to be tested.



**Return Value:**

* If fd refers to a terminal, `isatty()` returns `1`.

* If fd does not refer to a terminal, `isatty()` returns `0`.



* On error, `-1` is returned, and errno is set appropriately.



**Example:**



```c

#include <stdio.h>

#include <unistd.h>



int main() {

    if (isatty(STDIN_FILENO)) {

        printf("stdin is a terminal.\n");

    } else {

        printf("stdin is not a terminal.\n");

    }

    return 0;

}

```

In this example, `isatty()` is used to test whether the standard input (`stdin`) refers to a terminal device. The result is then printed to the console.



### Send a signal

The `kill()` function in C is used to send a signal to a process or a group of processes. Here’s the prototype of the `kill()` function:



```c

#include <sys/types.h>

#include <signal.h>



int kill(pid_t pid, int sig);

```

**Description:**



The `kill()` function sends the signal sig to the process specified by pid.



**Parameters:**



* `pid`: The process ID of the target process.



* `sig`: The signal to be sent.



**Return Value:**



* On success, `0` is returned.

* On failure, `-1` is returned, and errno is set appropriately.



**Example:**

```c

#include <stdio.h>

#include <unistd.h>

#include <signal.h>



int main() {

    pid_t pid = getpid(); // Get the PID of the current process

    if (kill(pid, SIGKILL) == -1) { // Send the SIGKILL signal to terminate the process

        perror("kill() failed");

        return 1;

    }

    return 0;

}

```

In this example, `kill()` is called to send the SIGKILL signal to terminate the current process. If `kill()` fails, an error message is printed to the console.



### Allocate memory

The `malloc()` function in C is used to dynamically allocate memory. Here’s the prototype of the `malloc()` function:



```c

#include <stdlib.h>



void *malloc(size_t size);

```

**Description:**



The `malloc()` function allocates a block of memory of size bytes and returns a pointer to the beginning of the block.



**Parameters:**



* `size`: The size of the memory block to 

allocate, in bytes.



**Return Value:**



* On success, a pointer to the allocated memory block is returned.

* On failure, NULL is returned.



**Example:**



```c

#include <stdio.h>

#include <stdlib.h>



int main() {

    int *ptr = (int *)malloc(sizeof(int)); // Allocate memory for an integer

    if (ptr == NULL) {

        perror("malloc() failed");

        return 1;

    }



    // Use the allocated memory...



    free(ptr); // Free dynamically allocated memory



    return 0;

}

```

In this example, malloc() is called to allocate memory for an integer. If malloc() fails to allocate memory, an error message is printed to the console.



### Open a file

The `open()` function in C is used to open or create a file. Here’s the prototype of the `open()` function:



```c

#include <fcntl.h>



int open(const char *pathname, int flags, mode_t mode);

```

**Description:**



The `open()` function opens the file specified by pathname and returns a file descriptor that can be used to perform I/O operations on the file.



**Parameters:**



* `pathname`: The path to the file to open or create.

* `flags`: A bitmask specifying the file access mode and file status flags.

* `mode`: The file permission mode to use when creating a new file.



**Return Value:**

* On success, the file descriptor of the opened file is returned.

* On failure, -1 is returned, and errno is set appropriately.



**Example:**



```c

#include <stdio.h>

#include <fcntl.h>



int main() {

    int fd = open("/path/to/file", O_RDWR | O_CREAT, 0644); // Open or create a file

    if (fd == -1) {

        perror("open() failed");

        return 1;

    }



    // Perform I/O operations on the file...



    close(fd); // Close the file



    return 0;

}

```



In this example, `open()` is called to open or create a file for reading and writing. If `open()` fails to open or create the file, an error message is printed to the console.



### Open a directory

The `opendir()` function in C is used to open a directory stream. Here’s the prototype of the `opendir()` function:



```c

#include <dirent.h>



DIR *opendir(const char *name);

```

**Description:**



The `opendir()` function opens the directory specified by name and returns a pointer to a DIR structure that can be used to read the contents of the directory.



**Parameters:**



* `name`: The path to the directory to open.



**Return Value:**



* On success, a pointer to a DIR structure representing the opened directory stream is returned.



* On failure, NULL is returned, and errno is set appropriately.



**Example:**



```c

#include <stdio.h>

#include <dirent.h>



int main() {

    DIR *dir = opendir("/path/to/directory"); // Open a directory stream

    if (dir == NULL) {

        perror("opendir() failed");

        return 1;

    }



    // Read the contents of the directory...



    closedir(dir); // Close the directory stream



    return 0;

}

```

In this example, `opendir()` is called to open a directory stream for the specified directory. If `opendir()` fails to open the directory, an error message is printed to the console.



### Print an error message

The `perror()` function in C is used to print an error message to the standard error stream (`stderr`) along with the error description corresponding to the current value of `errno`. Here’s the prototype of the `perror()` function:



```c

#include <stdio.h>



void perror(const char *s);

```

**Description:**

The `perror()` function prints the string pointed to by `s`, followed by a colon and a space, followed by the `error` message corresponding to the current value of errno, and a newline character.



**Parameters:**



`s`: The error message prefix string.

**Return Value:**

This function does not return a value.



**Example:**



****

```c

#include <stdio.h>



int main() {

    FILE *file = fopen("nonexistent_file.txt", "r"); // Try to open a nonexistent file

    if (file == NULL) {

        perror("Error opening file");

        return 1;

    }

    return 0;

}

```

In this example, `perror()` is called to print an error message indicating the failure to open a nonexistent file.





### Read from a file descriptor



The `read()` function in C is used to read data from a file descriptor into a buffer. Here’s the prototype of the `read() `function:



```c



#include <unistd.h>



ssize_t read(int fd, void *buf, size_t count);

```

**Description:**



The `read()` function reads up to count bytes of data from the file referred to by the file descriptor fd into the buffer pointed to by buf.



**Parameters:**



* `fd`: The file descriptor from which to read.

* `buf`: A pointer to the buffer into which the data is read.

* `count`: The maximum number of bytes to read.



**Return Value:**



On success, the number of bytes read is returned (0 indicates end-of-file).

On failure, -1 is returned, and errno is set appropriately.



**Example:**

```c

#include <stdio.h>

#include <unistd.h>



int main() {

    char buf[100];

    ssize_t bytes_read = read(STDIN_FILENO, buf, sizeof(buf)); // Read from standard input

    if (bytes_read == -1) {

        perror("read() failed");

        return 1;

    }



    printf("Read %zd bytes: %s\n", bytes_read, buf);



    return 0;

}

```

In this example, `read()` is called to read data from standard input (`stdin`) into a buffer. If `read()` fails to read data, an error message is printed to the console.



### Read a directory



The `readdir()` function in C is used to read the contents of a directory stream. Here’s the prototype of the `readdir()` function:



```c

#include <dirent.h>



struct dirent *readdir(DIR *dirp);

```

**Description:**



The `readdir()` function reads the next directory entry from the directory stream referred to by the DIR pointer dirp.



**Parameters:**



* `dirp`: A pointer to a DIR structure representing the directory stream.



**Return Value:**



On success, a pointer to a dirent structure representing the next directory entry is returned.

When the end of the directory stream is reached or an error occurs, NULL is returned, and errno is set appropriately.



**Example:**



```c



#include <stdio.h>

#include <dirent.h>



int main() {

    DIR *dir = opendir("/path/to/directory"); // Open a directory stream

    if (dir == NULL) {

        perror("opendir() failed");

        return 1;

    }



    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {

        printf("%s\n", entry->d_name); // Print the name of each directory entry

    }



    closedir(dir); // Close the directory stream



    return 0;

}

```

In this example, `readdir()` is called repeatedly to read each directory entry from the opened directory stream. The name of each directory entry is then printed to the console.



### Signal handling

The `signal()` function in C is used to set up signal handling for specific signals. Here’s the prototype of the `signal()` function:



```c



#include <signal.h>



sighandler_t signal(int signum, sighandler_t handler);

```

**Description:**



The `signal()` function sets the disposition of the signal signum to handler, which can be either a function pointer or one of the predefined signal handling behaviors.



**Parameters:**



* `signum`: The signal number for which the disposition is to be set.

* `handler`: The signal handler function pointer or one of the predefined signal handling behaviors (`SIG_DFL`, `SIG_IGN`, or `SIG_ERR`).



**Return Value:**



On success, a function pointer to the previous signal handler is returned.

On failure, `SIG_ERR` is returned, and `errno` is set appropriately.



**Example:**



```c

#include <stdio.h>

#include <signal.h>

#include <unistd.h>



void signal_handler(int signum) {

    printf("Signal %d received.\n", signum);

}



int main() {

    if (signal(SIGINT, signal_handler) == SIG_ERR) { // Set up signal handling for SIGINT (Ctrl+C)

        perror("signal() failed");

        return 1;

    }



    while (1) {

        printf("Waiting for a signal...\n");

        sleep(1);

    }



    return 0;

}

```

In this example, `signal()` is called to set up a signal handler function for the SIGINT signal (`Ctrl+C`). When SIGINT is received, the custom signal handler function `signal_handler()` is called to handle the signal.



### Get file status

The `stat()`, `lstat()`, and `fstat()` functions in C are used to get file status information. Here are the prototypes of these functions:



```c

#include <sys/types.h>

#include <sys/stat.h>



int stat(const char *pathname, struct stat *statbuf);

int lstat(const char *pathname, struct stat *statbuf);

int fstat(int fd, struct stat *statbuf);

```



**Description:**



* `stat()`: The `stat()` function retrieves the file status of the file specified by pathname and stores it in the statbuf structure.

* `lstat()`: The `lstat()` function is similar to `stat()`, but if pathname is a symbolic link, it returns the file status of the symbolic link itself rather than the file it points to.

* `fstat()`: The `fstat()` function retrieves the file status of the open file referred to by the file descriptor fd and stores it in the statbuf structure.



Parameters:

pathname: The path to the file whose status is to be retrieved.

fd: The file descriptor of the open file whose status is to be retrieved.

statbuf: A pointer to a struct stat buffer where the file status information will be stored.



**Return Value:**



On success, `0` is returned.

On failure, `-1` is returned, and `errno` is set appropriately.



**Example:**



```c

#include <stdio.h>

#include <sys/stat.h>

#include <unistd.h>



int main() {

    struct stat statbuf;

    if (stat("/path/to/file", &statbuf) == -1) {

        perror("stat() failed");

        return 1;

    }



    printf("File size: %lld bytes\n", (long long)statbuf.st_size);

    printf("Permissions: %o\n", statbuf.st_mode & 0777);



    return 0;

}

```

In this example, `stat()` is called to retrieve the file status of a specified file. If successful, information such as file size and permissions is printed to the console.



### Extract tokens from strings

The `strtok()` function in C is used to tokenize (`split`) strings into smaller strings (`tokens`). Here’s the prototype of the `strtok()` function:



```c

#include <string.h>



char *strtok(char *str, const char *delim);

```

**Description:**



The `strtok()` function breaks the string str into a series of tokens using the delimiter characters specified by the string delim.





**Parameters:**



* `str`: The string to be tokenized. On the first call, the function expects a string as argument for str. In subsequent calls, str must be NULL, and the function continues from where it left off in the previous call.

* `delim`: A string containing delimiter characters. Each character in this string is considered a potential delimiter.



**Return Value:**



On success, a pointer to the next token found in the string is returned.

When no more tokens are found, `NULL` is returned.



**Example:**



```c

#include <stdio.h>

#include <string.h>



int main() {

    char str[] = "This is a sample string";

    char *token = strtok(str, " "); // Tokenize the string using space as delimiter

    while (token != NULL) {

        printf("%s\n", token); // Print each token

        token = strtok(NULL, " "); // Get the next token

    }

    return 0;

}

```

In this example, `strtok()` is used to tokenize a sample string into individual words separated by spaces. Each token is printed to the console.



### Wait for process to change state

The `wait()`, `waitpid()`, `wait3()`, and `wait4()` functions in C are used to wait for child processes to change state. Here are the prototypes of these functions:



```c

#include <sys/wait.h>



pid_t wait(int *wstatus);

pid_t waitpid(pid_t pid, int *wstatus, int options);

pid_t wait3(int *wstatus, int options, struct rusage *rusage);

pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);

```

**Description:**



`wait()`: The `wait()` function suspends execution of the calling process until one of its child processes terminates.

`waitpid()`: The `waitpid()` function suspends execution of the calling process until a child process specified by pid changes state.

* `wait3()`: The `wait3()` function is similar to `waitpid()`, but it also provides resource usage information in the rusage structure.

* `wait4()`: The `wait4()` function is similar to `wait3()`, but it allows specifying additional options.



**Parameters:**



* `pid`: The process ID of the child process to wait for. Use `-1` to wait for any child process.

* `wstatus`: A pointer to an integer where the exit status or termination signal of the child process will be stored.

* `options`: Additional options for controlling the behavior of the `waitpid()`, `wait3()`, or `wait4() `function.

* `rusage`: A pointer to a struct rusage buffer where resource usage information will be stored (for `wait3()` and `wait4()`).



**Return Value:**



On success, the process ID of the terminated child process is returned by `wait()`, `waitpid()`, `wait3()`, or `wait4()`.

On failure, `-1` is returned, and errno is set appropriately.



**Example:**



```c

#include <stdio.h>

#include <sys/wait.h>

#include <unistd.h>



int main() {

    pid_t pid = fork(); // Create a child process

    if (pid == -1) {

        perror("fork() failed");

        return 1;

    }



    if (pid == 0) {

        // Child process

        printf("Child process is executing.\n");

        sleep(2); // Simulate some work

        printf("Child process is exiting.\n");

        _exit(0); // Exit the child process

    } else {

        // Parent process

        printf("Parent process is waiting for the child.\n");

        int status;

        waitpid(pid, &status, 0); // Wait for the child process to terminate

        printf("Parent process detected child exit with status: %d\n", status);

    }



    return 0;

}

```

In this example, the parent process creates a child process using `fork()`. The parent then waits for the child process to terminate using `waitpid()`. When the child process exits, the parent process detects the child's exit status and continues execution.



### Write to a file descriptor

The `write()` function in C is used to write data from a buffer to a file descriptor. Here’s the prototype of the `write()` function:



```c

#include <unistd.h>



ssize_t write(int fd, const void *buf, size_t count);

```

**Description:**



The `write()` function writes up to count bytes of data from the buffer pointed to by buf to the file referred to by the file descriptor fd.



**Parameters:**

* `fd`: The file descriptor to which data is to be written.

* `buf`: A pointer to the buffer containing the data to be written.

* `count`: The number of bytes to write.



**Return Value:**



On success, the `number of bytes` written is returned.

On failure, `-1` is returned, and errno is set appropriately.

**Example:**

```c



#include <stdio.h>

#include <unistd.h>



int main() {

    const char *str = "Hello, World!\n";

    ssize_t bytes_written = write(STDOUT_FILENO, str, strlen(str)); // Write to standard output

    if (bytes_written == -1) {

        perror("write() failed");

        return 1;

    }



    printf("Wrote %zd bytes to stdout.\n", bytes_written);



    return 0;

}

```

In this example, `write()` is called to write a string to standard output (stdout). The number of bytes written is then printed to the console. If `write()` fails, an error message is printed.�
