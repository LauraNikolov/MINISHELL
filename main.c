#include "minishell.h"

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
    buff_size = 1084;
    buffer = malloc(sizeof(char) * buff_size * 1);
    while (getline(&buffer, &buff_size, 0) != 0) // tant qu il y a une ligne saisie par l user dans le prompt
    {
    buffer = malloc(sizeof(char) * buff_size * 1);

        ft_display_prompt();
        //ft_exec_cmd();
        free(buffer);
    }
}