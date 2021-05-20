
#include "../../includes/env.h"

void	env_delone(t_env **envs, t_env *prev, t_env *delEnv)
{
	t_env	*tmp;

	if (!prev)
	{
		tmp = (*envs)->next;
		free_env(*envs);
		*envs = tmp;
		printf("\nenv->name: %s\n", (*envs)->name);
	}
	else
	{
		prev->next = delEnv->next;
		free_env(delEnv);
	}
}

int		del_env(char *delKey, t_env **envs)
{
	t_env	*prev;
	t_env	*delEnv;

	prev = NULL;
	delEnv = *envs;

	while (delEnv)
	{
		if (!(ft_strcmp(delKey, delEnv->name)))
		{
			env_delone(envs, prev, delEnv);
			return(1);
		}
		prev = delEnv;
		delEnv = delEnv->next;
	}
	return(0);
}