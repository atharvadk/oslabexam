#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <sys/wait.h>
#endif

int main() {

    int fd;
    char buffer[50];

    // ------------------------------
    // FILE SYSTEM CALLS
    // ------------------------------

    // Open a file (create if not exists)
    fd = open("sample.txt", O_CREAT | O_RDWR, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // Write to the file
    char msg[] = "Hello from system call demo!\n";
    write(fd, msg, sizeof(msg));

    // Move file pointer to beginning
    lseek(fd, 0, SEEK_SET);

    // Read from file (check return and avoid buffer overflow)
    ssize_t n = read(fd, buffer, sizeof(buffer));
    if (n < 0) {
        perror("read");
        close(fd);
        return 1;
    }

    if (n >= (ssize_t)sizeof(buffer)) {
        // ensure last byte is NUL if buffer filled completely
        buffer[sizeof(buffer) - 1] = '\0';
    } else {
        buffer[n] = '\0';
    }

    printf("Data read from file: %s", buffer);

    // Close the file
    close(fd);

    // ------------------------------
    // PROCESS SYSTEM CALLS
    // ------------------------------

    pid_t pid = fork();  // create child process

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child Process: PID = %d\n", getpid());
    } 
    else {
        // Parent process
        // wait for child to finish (POSIX). On Windows, `wait`/`fork` are typically unavailable
        // so we fall back to a short Sleep to allow the child to print (if running under a
        // POSIX compatibility layer this block won't be used).
    #if defined(_WIN32) || defined(_WIN64)
        Sleep(100);
        printf("Parent Process: PID = %d, Child PID = %d finished.\n", getpid(), pid);
    #else
        wait(NULL);
        printf("Parent Process: PID = %d, Child PID = %d finished.\n", getpid(), pid);
    #endif
    }

    return 0;
}

/*
Sample Output (no stdin; program demonstrates file and process system calls):

When you run the program it will create (or open) `sample.txt`, write a message,
read it back, then fork a child process. Example output:

Data read from file: Hello from system call demo!
Child Process: PID = 12345
Parent Process: PID = 12344, Child PID = 12345 finished.

Notes:
- The actual PIDs will vary. If you run on Windows without POSIX support, `fork()` and
    `unistd.h` calls may not be available; compile/run on a POSIX environment (WSL, Linux, or
    MSYS2/MinGW with POSIX layer) for correct behaviour.
- The program now performs error checks on `open` and `read`, and avoids buffer overflow
    when the read fills the buffer completely.
*/
