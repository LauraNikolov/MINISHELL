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

// typedef struct s_redir
// {
// 	enum				type;
// 	char				*file;
// }						t_redir;

typedef struct s_cmd
{
	char				**cmd;
	char				*path;
	char				*redir;
	int					*bool_bracket;
	int					expand_flag;
	t_token_type		type;
	struct s_cmd		*next;
	struct s_cmd		*prev;
	struct s_envp		*env;
}						t_cmd;

typedef struct s_ast
{
	t_token_type		type;
	char				**args;
	struct s_ast		*right;
	struct s_ast		*left;
	struct s_ast		*prev;
	struct s_ast		*next;
}						t_ast;

typedef struct s_envp
{
	char				*var_name;
	char				*var_value;
	int					add_variables;
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

typedef struct s_all_struct
{
	enum s_token_type	token;
	union				data
	{
		struct ope		ope;
		struct commands	commands;
	} data;
	t_ast				*ast;
	t_ast				*root_ast;
	struct t_all_struct	*prev;
	struct t_all_struct	*next;
}						t_all_struct;

typedef struct save_struct
{
	struct s_cmd		*cmd;
	struct s_ast		*ast;
	struct s_all_struct	*all_struct;
	struct s_envp		*envp;
	char				*save_spaces;

}						save_struct;

#endif
