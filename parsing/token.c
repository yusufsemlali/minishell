/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:19:32 by ysemlali          #+#    #+#             */
/*   Updated: 2024/08/03 14:45:33 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

int new_len(char *s, char c)
{
    int i = 0;
    int new_len = 0;
    while (s[i])
    {
        if (s[i] == c && s[i- 1] != '\\')
            new_len += 2;
        i++;
    }
    return (new_len);
}

char *delimiter(char *s, char c)
{
    int i = 0;
    int j = 0;
    int len = new_len(s, c);
    char *new = malloc(new_len + 1);
    if (!new)
        return (NULL);
    while (s[i])
    {
        new[j] = s[i];
        if (s[i] == c && s[i - 1] != '\\')
        {
            new[j++] = ' ';
            new[j++] =  s[i++];
            new[j] = ' ';
        }
        i++;
        j++;
    }
    new[j] = '\0';
    return (s);
}
void tokenize(t_shell *shell)
{
    shell->line = delimiter(shell->line, '|');    
    shell->av = ft_split(shell->line, ' ');

    
}