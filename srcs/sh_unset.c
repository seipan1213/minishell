
#include "../includes/env.h"





int		del_env(char *delKey, t_env *env)
{
	t_env *delEnv;
	t_env *tmp;	
	t_env *end;
	t_env *prev;
	t_env *now;

	prev = NULL;
	now = env;

	while (now)
	{
		if (!(ft_strcmp(delKey, now->name)))
		{
			delone;
		}
		prev = now;
		now = now->next;
	}

	return(1);
}