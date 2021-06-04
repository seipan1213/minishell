#ifndef BUILTIN_H
# define BUILTIN_H

# include "../libft/libft.h"
# include "minishell.h"
# include <stdio.h>

# define UNSET_ERR "unset: not enough arguments"

typedef enum e_echo_flag
{
	ECHO_OP_N = 1,
}	t_echo_flag;

int		built_echo(char **argv);
int		built_env(void);
int		built_exit(char **argv);
int		built_export(char **argv);
int		built_pwd(void);
int		built_unset(char **argv);

int		check_identifier(char *str);


#endif