#ifndef PARSER_H
# define PARSER_H

# include "const.h"
# include "../libft/libft.h"
# include "lexer.h"

# define NOT_SPECIFIED -1

/**
 *
	<command line>	::=  	<job>
						|	<job> '&'
						| 	<job> '&' <command line>
						|	<job> ';'
						|	<job> ';' <command line>
	<job>			::=		<command>
						|	< job > '|' < command >
	<command>		::=		<simple command>
						|	<simple command> '<' <filename>
						|	<simple command> '>' <filename>
	<simple command>::=		<pathname>
						|	<simple command>  <token>
 *
**/

typedef enum e_rd_type
{
	RD_INPUT,
	RD_OUTPUT,
	RD_APPEND_OUTPUT,
	RD_HERE_DOC
}			t_rd_type;

typedef struct s_redirect{
	int					fd_io;
	int					fd_file;
	int					fd_backup;
	t_rd_type			type;
	t_token				*filename;
	struct s_redirect	*prev;
	struct s_redirect	*next;
}				t_redirect;

typedef struct s_command{
	t_token				*arg;
	t_redirect			*rd;
	pid_t				pid;
	struct s_command	*next;
}				t_command;

typedef struct	s_cmd_link
{
	t_command	*ptr;
}				t_cmd_link;

typedef struct	s_astNode {
	int					type;
	t_command			*cmd;
	struct s_astNode	*left;
	struct s_astNode	*right;
}				t_astNode;

# define TRUE 1
# define FALSE 0
# define COLOR_RESET "\033[0m"
# define COLOR_GREEN "\033[32m"
# define COLOR_RED "\033[31m"

t_token		*gen_token(char *val, int type);
bool		set_cmd_args(t_token **tokens, t_command *cmd);
t_astNode	*new_cmd_node(t_cmd_link *cmd_ptr);
t_astNode	*new_parent_node(int type, t_astNode *left, t_astNode *right);
bool		is_type(t_token **tokens, int type);
bool		is_rd(int type);
void		set_cmd_token(t_token *src, t_token **args);
bool		parse_cmd_rd(t_token **tokens, t_command *cmd);
bool		parser(t_token **tokens, t_astNode **node);
int			launch(char *line, char **envp);
void		minishell(void);
t_redirect	*init_redirect(void);
void		set_rd_type(t_redirect *rd, t_token *token);
void		set_cmd_rd(t_redirect *rd, t_redirect **list);
void		free_node(t_astNode *node);
void		free_tokens(t_token **tokens);
void		free_token(t_token *token);

#endif