#include "../minishell.h"

int ft_return_code(char *code, t_envp **env)
{
    if (!env)
        return (0);
    t_envp *curr;

    curr = *env;
    //  printf("return code %s\n", code);
    while(curr)
    {
        if (!ft_strcmp(curr->var_name, "?"))
            curr->var_value = code;
        curr = curr->next;
    }
    return (ft_atoi(code));
}