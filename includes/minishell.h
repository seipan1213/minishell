#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "env.h"

# define MINISHELL "MINISHELL$ "
# define MALLOCERR "malloc error..."
# define SYNTAXERR "syntax error..."
# define QUOTEERR "quote is not close..."
# define NUMERR "numeric argument required"

typedef struct s_minidata
{
	t_env	*envs;
	int		status;
	int		quit;
}	t_minidata;

t_minidata g_data;

#endif