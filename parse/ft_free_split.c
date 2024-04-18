#include "../minishell.h"

void ft_free_split(char **split)
{
    int i;

    i = 0;
    while(split[i])
        free(split[i++]);
}