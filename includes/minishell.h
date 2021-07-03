#ifndef MINISHELL_H
# define MINISHELL_H

# include "const.h"
# include "env.h"

typedef struct s_env t_env;

typedef struct s_minidata
{
	t_env	*envs;
	int		status;
	int		quit;
	char	*pwd;
}	t_minidata;

t_minidata	g_data;
void		minishell(void);

#endif