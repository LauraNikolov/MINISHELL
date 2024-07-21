#include "../minishell.h"

t_redir	*ft_redir(char *s, int *i, int len)
{
	t_redir	*redir;
	char	*cmd;
	int		infile;

	infile = 0;
	redir = NULL;
	while (*i < len)
	{
		if (ft_is_str(s[*i], "><"))
		{
			*i += ft_check_double_symbols(&s[*i], &cmd);
			add_to_redir_lst(&redir, create_redir_node(cmd));
			ft_safe_free(&cmd);
		}
		while (*i < len && s[*i] == ' ')
			(*i)++;
		if (!ft_is_str(s[*i], "><"))
		{
			while (s[*i + infile] && !ft_is_str(s[*i + infile], "><") && s[*i
				+ infile] != ' ')
				infile++;
			ft_handle_quote(&s[*i], &cmd, infile, NULL, 0);
			add_to_redir_lst(&redir, create_redir_node(cmd));
			ft_safe_free(&cmd);
			(*i) += infile - 1;
			break ;
		}
	}
	return (redir);
}

t_redir	*create_redir_node(char *s)
{
	t_redir	*new_node;

	if (!s)
		return (NULL);
	new_node = malloc(sizeof(t_redir));
	new_node->redir = ft_strdup(s);
	if (!ft_strcmp(s, "<<"))
		new_node->type = R_HEREDOC;
	else if (!ft_strcmp(s, "<"))
		new_node->type = R_IN;
	else if (!ft_strcmp(s, ">"))
		new_node->type = R_OUT;
	else if (!ft_strcmp(s, ">>"))
		new_node->type = R_APPEND;
	else
		new_node->type = WORD;
	new_node->next = NULL;
	return (new_node);
}
