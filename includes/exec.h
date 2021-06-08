
#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include <signal.h>
# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "builtin.h"
# include "expand.h"

# define NO_PID -1
# define PIPE_OUT 0
# define PIPE_IN 1

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
void	exec_cmd(t_command *cmd, t_pipe_status *p_stat, int pipe_fd[]);
char	**token_to_args(t_token *token);
int		dup_pipe(t_pipe_status *p_stat, int old_pipe_fd[], int new_pipe_fd[]);
int		pass_pipe(t_pipe_status *p_stat, int old_pipe_fd[], int new_pipe_fd[]);
void	get_next_p_stat(t_command *cmd, t_pipe_status *p_stat);
void	wait_commands(t_command *cmd);
int		is_builtin(char **args);
int		exec_builtin(char **args);
void	get_rd_fd(t_command *cmd);
void	change_rd_fd(t_command *cmd);
void	exec_simple_buildin(t_command *cmd, char **args);

#endif
