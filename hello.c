#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    char *args[] = {"/nonexistent", NULL};
    if (execve(args[0], args, NULL) == -1) {
        perror("execve failed");
        exit(EXIT_FAILURE);
    }
    return 0;
}
