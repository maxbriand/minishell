#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// void sigint_handler(int signum) {
//     printf("Signal SIGINT reçu.\n");
//     exit(signum); // Sortir du programme avec le numéro de signal
// }


// int main(void)
// {
// 	struct sigaction sa;


// 	sigemptyset(&sa.sa_mask);
//     sa.sa_flags = 0;
//     sa.sa_handler = sigint_handler;

// 	sigaction(EOF, &sa, NULL);
//     while(1) {}

// 	return(0);
// }

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;
    while (1) {
        // Prompt the user for input
        input = readline("Enter command (type 'exit' to quit): ");

        // Check if the input is NULL, indicating EOF or an error
        if (!input) {
            printf("EOF or read error occurred.\n");
            break;
        }

        // Check if the user typed 'exit' to terminate the loop
        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        // Display the entered command
        printf("You entered: '%s'\n", input);

        // Optional: add the input to the history
        add_history(input);

        // Free the dynamically allocated input memory
        free(input);
    }
    return 0;
}
