#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef enum s_token_type
{
	WORD,
	PIPE,
	AND,
	OR,
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC,
	O_BRACKET,
	C_BRACKET,
	NO_TYPE,
}						t_token_type;

typedef struct s_cmd
{
	char				**cmd;
	char				*path;
	int					prev_fd;
	int					std_out;
	int					std_in;
	int					pipe[2];
	int					return_value;
	char				*redir;
	int					*bool_bracket;
	int					expand_flag;
	t_token_type		type;
	struct s_cmd		*next;
	struct s_cmd		*prev;
	struct s_envp		*env;
}						t_cmd;

typedef struct s_envp
{
	char				*var_name;
	char				*var_value;
	struct s_envp		*next;
	struct s_envp		*prev;
}						t_envp;

typedef struct ope
{
	char				*content;
	int					prior;
}						ope;

typedef struct commands
{
	int					std_in;
	int					std_out;
	char				*infile;
	char				*outfile;
	char				**cmds;
	char				*cmd_path;
}						commands;

typedef struct save_struct
{
	struct s_cmd		*cmd;
	struct t_ast		*ast;
	struct s_all_struct	*all_struct;
	struct s_envp		*envp;
	char				*save_spaces;
	struct s_exec		*exec;

}						save_struct;

typedef struct t_ast
{
	t_cmd				*cmd;
	struct t_ast		*left;
	struct t_ast		*right;
}						t_ast;

typedef struct s_exec
{
	int					std_in;
	int					std_out;
	int					prev;
	int					return_value;
	int					pipe[2];
}						t_exec;

typedef struct s_all_struct
{
	t_token_type		token;
	union				data
	{
		struct ope		ope;
		struct commands	commands;
	} data;
	t_ast				*ast;
	t_ast				*root_ast;
	struct s_all_struct	*prev;
	struct s_all_struct	*next;
}						t_all_struct;

#endif