#include "minishell.h"

int ft_get_path(char *buffer)
{
    char *path = getenv("PATH");
    char **bin;
    char **cmd;
    char **split_cmd;
    t_token *lst = NULL;
    t_token *token = NULL;
    int i;
    int j;

    if (!path)
        path = strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
    bin = ft_split_cmd(path, ":"); // split les paths
    cmd = ft_split_cmd(buffer, ";"); // split les commandes
    // le but est de split la ou les commandes en plusieurs niveaux :
    // 1. les differentes commandes entres elles dans cmd. 
    // 2. la ou les comnmandes avec leur(s) option(s) dans split_cmd.
    j = 0;
    printf ("commande de base %s", cmd[0]);
    while(cmd[j])
    {   
        // TODO si cmd[j] n est pas une commande, return;
        i = 0;
        split_cmd = ft_split_cmd(cmd[j], " /n"); // pour sep commandes et options
        printf ("commande apres split %s", split_cmd[0]);
        while(bin[i])
        {
            if (access(ft_strjoin(bin[i], split_cmd[0]), F_OK) == 0)
            {
                token = create_node(cmd[j], ft_strjoin(bin[i], split_cmd[0]));// creer le nouveau noeud avec le envp_path
                break ;
            }
            i++;
        }
        if (!token)
            token = create_node(cmd[j], NULL); // si y a pas de path dans envp alors je set le chemin de la commande a NULL -> utiliser un built in + tard      
        if (lst == NULL)
            lst = token;
        else
            add_to_lst(&lst, token); 
        printf ("token->cmd = %s, token->path %s", token->cmd, token->envp_path);
        ft_free_split(split_cmd);
        token = NULL;
        j++;
        
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
        ft_get_path(buffer);
            //ft_exec_cmd();
    }
    free(buffer);
}