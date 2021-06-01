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

int	check_identifier(char *str);


#endif