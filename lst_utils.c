#include "minishell.h"

t_token *lst_last(t_token *node)
{
    t_token *curr;

    curr = node;
    while(curr->next)
        curr = curr->next;
    return (curr);
}

void add_to_lst(t_token **head, t_token *new_node)
{
    t_token *last;

    last = lst_last(*head);
    last->next = new_node;
}

t_token *create_node(char *cmd, char *envp_path)
{
    t_token *new_node;
    new_node = malloc(sizeof(t_token));
    if (!new_node)
        return(NULL);
    new_node->next = NULL;
    new_node->options = NULL;
    new_node->cmd = cmd;
    new_node->envp_path = envp_path;
    return(new_node);
}