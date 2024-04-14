
int main(int argc, char **argv, char **envp)
{
    char *buffer = NULL;
    int buff_size;

    buff_size = 1024;
    while (getline(buffer, buff_size, 0) != 0) // tant qu il y a une ligne saisie par l user dans le prompt
    {
        
        //ft_display_prompt();
        //ft_exec_cmd();
    }
}