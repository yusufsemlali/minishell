#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>



int main() {
    // Parent allocates two strings
    char *str1 = (char *)malloc(20 * sizeof(char));
    char *str2 = (char *)malloc(20 * sizeof(char));

    if (str1 == NULL || str2 == NULL) {
        perror("malloc failed");
        exit(1);
    }

    strcpy(str1, "Hello from str1!");
    strcpy(str2, "Hello from str2!");

    printf("Parent: Allocated str1: %s\n", str1);
    printf("Parent: Allocated str2: %s\n", str2);

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {  // Child process
        printf("Child: I'm the child process.\n");
        
        // Free only the first string in the child
        printf("Child: Freeing str1.\n");
        char *str3 = (char *)malloc(20 * sizeof(char));
        strcpy(str3, "Hello from str2!");

        /*free(str1);*/
        /*free(str2);*/
        
        // Intentionally not freeing str2
        printf("Child: Not freeing str2.\n");
        
        // Exit the child process
        exit(0);
    } else {  // Parent process
        // Wait for child to finish
        wait(NULL);
        
        printf("Parent: Child has exited.\n");
        
        // Parent still has its copy of both strings
        printf("Parent: str1 is %s (should still be valid)\n", str1);  // May cause issues if accessed after child freed it
        printf("Parent: str2 is %s (should still be valid)\n", str2);
        
        // Free memory in the parent
        free(str1);
        free(str2);
        
        printf("Parent: Freed str1 and str2.\n");
    }

    return 0;
}

