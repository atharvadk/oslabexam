#include <stdio.h>
#include <unistd.h>     // fork, getpid, lseek, read, write, close
#include <fcntl.h>      // open
#include <string.h>     // strlen
#include <sys/types.h>  // pid_t
#include <sys/stat.h>   // file permission flags
#include <sys/wait.h>   // wait

int main(void) {
    int fd;
    char buffer[64];

    // ------------------------------
    // FILE SYSTEM CALLS
    // ------------------------------

    // Open a file (create if not exists, read/write, truncate old contents)
    fd = open("sample.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // Write to the file
    const char msg[] = "Hello from system call demo!\n";
    ssize_t written = write(fd, msg, strlen(msg));
    if (written < 0) {
        perror("write");
        close(fd);
        return 1;
    }

    // Move file pointer to beginning
    if (lseek(fd, 0, SEEK_SET) == (off_t)-1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    // Read from file (limit size to buffer-1 for '\0')
    ssize_t n = read(fd, buffer, sizeof(buffer) - 1);
    if (n < 0) {
        perror("read");
        close(fd);
        return 1;
    }

    buffer[n] = '\0';   // null-terminate the string
    printf("Data read from file: %s", buffer);

    // Close the file
    close(fd);

    // Flush stdout before fork so output is not duplicated
    fflush(stdout);

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
        printf("Child Process: PID = %d\n", (int)getpid());
    } else {
        // Parent process
        wait(NULL);  // wait for child to finish
        printf("Parent Process: PID = %d, Child PID = %d finished.\n",
               (int)getpid(), (int)pid);
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
