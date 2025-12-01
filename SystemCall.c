#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

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

    // Read from file
    int n = read(fd, buffer, sizeof(buffer));
    buffer[n] = '\0';  // null terminate

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
        wait(NULL);  // wait for child to finish
        printf("Parent Process: PID = %d, Child PID = %d finished.\n", getpid(), pid);
    }

    return 0;
}
