#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h"
# include "lexer.h"
# include "env.h"
# include <stdio.h>

typedef struct s_minidata
{
	t_env	*envs;
	int		states;
	int		quit;
}	t_minidata;

t_minidata g_data;

#endif