#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for tokens
typedef struct Token
{
	char			*value;
	struct Token	*next;
}					Token;

// Function to create a new token
Token	*create_token(char *value)
{
	Token	*new_token;

	new_token = (Token *)malloc(sizeof(Token));
	new_token->value = strdup(value);
	new_token->next = NULL;
	return (new_token);
}

// Function to add a token to the list
void	add_token(Token **head, char *value)
{
	Token	*new_token;
	Token	*current;

	new_token = create_token(value);
	if (*head == NULL)
	{
		*head = new_token;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_token;
	}
}

// Function to tokenize the input string
Token	*tokenize(char *input)
{
	Token	*head;
	char	*start;
	char	*current;
	int		in_quotes;
	char	quote_char;
	char	*token;
	char	*token;
			char operator[2] = {*current, '\0'};
	char	*token;

	head = NULL;
	start = input;
	current = input;
	in_quotes = 0;
	quote_char = '\0';
	while (*current != '\0')
	{
		if (*current == '"' || *current == '\'')
		{
			if (in_quotes && *current == quote_char)
			{
				in_quotes = 0;
				quote_char = '\0';
			}
			else if (!in_quotes)
			{
				in_quotes = 1;
				quote_char = *current;
			}
		}
		else if (!in_quotes && isspace(*current))
		{
			if (start != current)
			{
				token = strndup(start, current - start);
				add_token(&head, token);
				free(token);
			}
			start = current + 1;
		}
		else if (!in_quotes && (*current == '|' || *current == '>'
				|| *current == '<'))
		{
			if (start != current)
			{
				token = strndup(start, current - start);
				add_token(&head, token);
				free(token);
			}
			add_token(&head, operator);
			start = current + 1;
		}
		current++;
	}
	if (start != current)
	{
		token = strndup(start, current - start);
		add_token(&head, token);
		free(token);
	}
	return (head);
}

// Function to print tokens (for debugging)
void	print_tokens(Token *head)
{
	Token	*current;

	current = head;
	while (current != NULL)
	{
		printf("Token: %s\n", current->value);
		current = current->next;
	}
}

// Main function
int	main(void)
{
	char	input[1024];
	Token	*tokens;
	Token	*current;
	Token	*next;

	// Get input from the user
	printf("minishell> ");
	fgets(input, sizeof(input), stdin);
	// Remove newline character from input
	input[strcspn(input, "\n")] = 0;
	// Tokenize the input
	tokens = tokenize(input);
	// Print tokens (for debugging)
	print_tokens(tokens);
	// Free tokens
	current = tokens;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	return (0);
}
