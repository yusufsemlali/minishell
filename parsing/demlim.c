#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to calculate the new length of the string after adding delimiters
int new_len(char *s, char c)
{
    int len = 0;
    int i = 0;

    while (s[i])
    {
        len++;
        if (s[i] == c && (i == 0 || s[i - 1] != '\\'))
        {
            len += 2; // Adding space before and after the delimiter
        }
        i++;
    }
    return len;
}

// Function to add delimiters to the string
char *delimiter(char *s, char c)
{
    int i = 0;
    int j = 0;
    int len = new_len(s, c);
    char *new = malloc(len + 1);
    if (!new)
        return NULL;

    while (s[i])
    {
        if (s[i] == c && (i == 0 || s[i - 1] != '\\'))
        {
            new[j++] = ' ';
            new[j++] = s[i++];
            new[j++] = ' ';
        }
        else
        {
            new[j++] = s[i++];
        }
    }
    new[j] = '\0';
    return new;
}

// Main function to test the delimiter function
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <string> <delimiter>\n", argv[0]);
        return 1;
    }

    char *s = argv[1];
    char c = argv[2][0];
    char *result = delimiter(s, c);

    if (result)
    {
        printf("Original: %s\n", s);
        printf("Modified: %s\n", result);
        free(result);
    }
    else
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    return 0;
}
