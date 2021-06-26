
#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "builtin.h"
# include "expand.h"

# define NO_PID -1
# define PIPE_OUT 0
# define PIPE_IN 1
# define HD_TMPFILE ".heredoc_tmpfile"
# define SQUOTE '\''
# define DQUOTE '\"'
# define NO_QUOTE 0
# define QUOTE_FALSE -1

typedef struct stat	t_stat;

typedef struct	s_quote
{
	int		start;
	int		end;
	char	quote;
}				t_quote;

typedef enum	e_pipe_status
{
	NO_PIPE,
	PIPE_RD_ONLY,
	PIPE_WR_ONLY,
	PIPE_RD_WR
}				t_pipe_status;

int		exec(astNode *node);
void	exec_pipeline(astNode *node);
void	exec_bin(char **args);
int		exec_cmd(t_command *cmd, t_pipe_status *p_stat, int pipe_fd[]);
char	**token_to_args(t_token *token);
int		dup_pipe(t_pipe_status *p_stat, int old_pipe_fd[], int new_pipe_fd[]);
int		pass_pipe(t_pipe_status *p_stat, int old_pipe_fd[], int new_pipe_fd[]);
void	get_next_p_stat(t_command *cmd, t_pipe_status *p_stat);
void	wait_commands(t_command *cmd);
int		is_builtin(char **args);
int		exec_builtin(char **args);
void	get_rd_fd(t_redirect *rd);
void	change_rd_fd(t_redirect *rd);
int		exec_simple_buildin(t_command *cmd, char **args);
int		is_exec(char *path);
void	free_split(char **split);
char	*exec_serach(char *argv);
void	dup_fd(int oldfd, int newfd);
void	get_heredoc(t_redirect *rd);
int		is_quote(char c);
char	*expand_delimiter(char *deli);

#endif
