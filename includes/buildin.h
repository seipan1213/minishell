#ifndef BUILDIN_H
# define BUILDIN_H

# include "../libft/libft.h"
# include "minishell.h"
# include <stdio.h>

# define UNSET_ERR "unset: not enough arguments"

typedef enum e_echo_flag
{
	ECHO_OP_N = 1,
}	t_echo_flag;

int		build_echo(char **argv);
int		build_env(void);
int		build_exit(char **argv);
int		build_export(char **argv);
int		build_pwd(void);
int		build_unset(char **argv);

int		check_identifier(char *str);


#endif