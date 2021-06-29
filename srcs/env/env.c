#include "../../includes/env.h"

t_env	*envs_init(void)
{
    extern char **environ;
		t_env *envs;
		t_env *env;
		int	i;

		i = 0;
		envs = NULL;
		while (environ[i])
		{
			env = create_env(environ[i]);
			addb_env(&envs, env);
			i++;
		}
    return (envs);
}

void	addb_env(t_env **envs, t_env *env)
{
	t_env	*back;

	if (!envs || !env)
		return ;
	if (!*envs)
		*envs = env;
	else
	{
		back = *envs;
		while (back->next)
			back = back->next;
		back->next = env;
	}
}

t_env	*create_env(char *environ)
{
	t_env	*env;
	char	*tmp;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	env->next = NULL;
	if (!(tmp = ft_strchr(environ + 1, '=')))
	{
		if (!(env->name = ft_strdup(environ)))
			free(env);
		if (!env->name)
			return (NULL);
		env->value = NULL;
		return (env);
	}
	*tmp = '\0';
	env->name = ft_strdup(environ);
	if (!(env->value = ft_strdup(tmp + 1)))
		free(env->name);
	*tmp = '=';
	if (!env->name || !env->value)
		free(env);
	if (!env->name || !env->value)
		return (NULL);
	return (env);
}

void	free_env(t_env *env)
{
	free(env->name);
	env->name = NULL;
	free(env->value);
	env->value = NULL;
	free(env);
	env = NULL;
}

void	free_envs(t_env *envs)
{
	while (envs != NULL)
	{
		free_env(envs);
		envs = envs->next;
	}
}