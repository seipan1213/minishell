#include "../../includes/env.h"

t_env	*search_env(char *key, t_env *env)
{
	int ret;

	ret = 0;
	if (!env)
		return(NULL);
	while (env != NULL)
	{
		if ((ret = ft_strcmp(key, env->name)) == 0)
		{
			return (env);
		}
		env = env->next;
	}
	return (NULL);
}

int		update_env(char *key, char *newVal, t_env *envs)
{
	t_env *newEnv;
	char	*tmp;
	char	*str;

	if (!(newEnv = search_env(key, envs)))
	{
		tmp = ft_strjoin(key, "=");
		str = NULL;
		if (tmp && (str = ft_strjoin(tmp, newVal)))
			if ((newEnv = create_env(str)))
				addb_env(&envs, newEnv);
		if (tmp)
			free(tmp);
		if (str)
			free(str);
		if (newEnv)
			return (1);
		return (0);
	}
	free(newEnv->value);
	newEnv->value = ft_strdup(newVal);
	return(1);
}

t_env	*envlast(t_env *env)
{
	t_env	*last;

	if (!env)
		return (NULL);
	last = env;
	while (last->next != NULL)
	{
		last = last->next;
	}
	return (last);
}

void	env_delone(t_env **envs, t_env *prev, t_env *delEnv)
{
	t_env	*tmp;

	if (!prev)
	{
		tmp = (*envs)->next;
		free_env(*envs);
		*envs = tmp;
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