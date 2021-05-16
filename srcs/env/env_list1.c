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

void	print_envs(t_env *envs)
{
	int i = 1;
	while (envs)
	{
		ft_putnbr_fd(i, 1);
		write(1, ": ", 2);
		ft_putstr_fd(envs->name, STDERR_FILENO);
		ft_putstr_fd("  =  ", STDERR_FILENO);
		ft_putendl_fd(envs->value, STDERR_FILENO);
		envs = envs->next;
		i++;
	}
}

void	addb_env(t_env **envs, t_env *env)
{
	t_env	*back;

	if (!env || !env)
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

	if (!(env = malloc(sizeof(t_env))))
		return (NULL);
	if (!(tmp = ft_strchr(environ, '=')))
	{
		free(env);
		return (NULL);
	}
	*tmp = '\0';
	env->name = ft_strdup(environ);
	env->value = ft_strdup(tmp + 1);
	*tmp = '=';
	env->next = NULL;
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

void	free_envs(t_env *env)
{
	while (env != NULL)
	{
		free(env->name);
		free(env->value);
		env = env->next;
	}
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