#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>

/**
 * Create a shared memory position. This position will be readable and
 * writable to the parent process and its children.
 *
 * @size: size to be allocated.
 */
void *create_shared_memory(size_t size)
{
    // Readable and writable.
    int protection = PROT_READ | PROT_WRITE;

    // The buffer will be shared (meaning other processes can access it), but
    // anonymous (meaning third-party processes cannot obtain an address for it),
    // so only this process and its children will be able to use it:
    int visibility = MAP_SHARED | MAP_ANONYMOUS;

    return mmap(NULL, size, protection, visibility, -1, 0);
}

int main()
{
    const char *parent_message = "Welcome to life my child";
    const char *child_message = "Thank you my father";

    // 1K shared memory.
    void *shared_buffer = create_shared_memory(1024);

    memcpy(shared_buffer, parent_message, strlen(parent_message)+1);

    int pid = fork();

    if (pid == 0) {
        printf("Shared buffer state for the child process: %s\n", shared_buffer);
        memcpy(shared_buffer, child_message, strlen(child_message)+1);
        printf("Shared buffer state for the child process: %s\n", shared_buffer);
    } else {
        printf("Shared buffer state for the parent process: %s\n", shared_buffer);
        sleep(2);
        printf("Shared buffer state for the parent process after sleeping for 2 seconds: %s\n", shared_buffer);
    }

    return 0;
}
