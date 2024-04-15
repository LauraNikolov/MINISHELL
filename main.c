#include "minishell.h"

int ft_get_path(char *cmd)
{
    char **bin;
    char *path = getenv("PATH");
    int i;

    if (!path)
        path = strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
    bin = ft_split_cmd(path, ":");
    i = 0;
    while(bin[i])
    {
        if (access(ft_strjoin(bin[i++], cmd), F_OK) == 0)
           return (1);
    }
    return (0);
}

void ft_display_prompt(void)
{
    write(0, "~$ ", 3);
}

int main(int ac, char **av, char **envp)
{
    char *buffer;
    //char **cmd;
    size_t buff_size;

    (void)envp;
    (void)ac;
    (void)av;
    buff_size = 2084;
    buffer = calloc(sizeof(char), buff_size);
    if (!buffer)
        return (0);
    ft_display_prompt();
    while (getline(&buffer, &buff_size, stdin) > 0) // tant qu il y a une ligne saisie par l user dans le prompt
    {
        //printf("cmd = %s\n", buffer);
        ft_display_prompt();
        if (ft_get_path(buffer))
            //ft_exec_cmd();
    }
    free(buffer);
}