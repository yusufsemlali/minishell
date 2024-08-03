#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define a structure for tokens
typedef struct Token {
    char *value;
    struct Token *next;
} Token;

// Function to create a new token
Token *create_token(char *value) {
    Token *new_token = (Token *)malloc(sizeof(Token));
    new_token->value = strdup(value);
    new_token->next = NULL;
    return new_token;
}

// Function to add a token to the list
void add_token(Token **head, char *value) {
    Token *new_token = create_token(value);
    if (*head == NULL) {
        *head = new_token;
    } else {
        Token *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_token;
    }
}

// Function to tokenize the input string
Token *tokenize(char *input) {
    Token *head = NULL;
    char *start = input;
    char *current = input;
    int in_quotes = 0;
    char quote_char = '\0';

    while (*current != '\0') {
        if (*current == '"' || *current == '\'') {
            if (in_quotes && *current == quote_char) {
                in_quotes = 0;
                quote_char = '\0';
            } else if (!in_quotes) {
                in_quotes = 1;
                quote_char = *current;
            }
        } else if (!in_quotes && isspace(*current)) {
            if (start != current) {
                char *token = strndup(start, current - start);
                add_token(&head, token);
                free(token);
            }
            start = current + 1;
        } else if (!in_quotes && (*current == '|' || *current == '>' || *current == '<')) {
            if (start != current) {
                char *token = strndup(start, current - start);
                add_token(&head, token);
                free(token);
            }
            char operator[2] = {*current, '\0'};
            add_token(&head, operator);
            start = current + 1;
        }
        current++;
    }

    if (start != current) {
        char *token = strndup(start, current - start);
        add_token(&head, token);
        free(token);
    }

    return head;
}

// Function to print tokens (for debugging)
void print_tokens(Token *head) {
    Token *current = head;
    while (current != NULL) {
        printf("Token: %s\n", current->value);
        current = current->next;
    }
}

// Main function
int main() {
    char input[1024];
    
    // Get input from the user
    printf("minishell> ");
    fgets(input, sizeof(input), stdin);
    
    // Remove newline character from input
    input[strcspn(input, "\n")] = 0;
    
    // Tokenize the input
    Token *tokens = tokenize(input);
    
    // Print tokens (for debugging)
    print_tokens(tokens);
    
    // Free tokens
    Token *current = tokens;
    while (current != NULL) {
        Token *next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
    
    return 0;
}

