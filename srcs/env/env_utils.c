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

int		update_env(char *key, char *newVal, t_env *env)
{
	t_env *newEnv;

	if (!(newEnv = search_env(key, env)))
		return (0);
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

/* int		main ()//int argc, char **argv)
{
	t_env *envs;
	t_env *val;
	char	**c_envs;
	int		i;

	i = 0;
	envs = envs_init();

	print_envs(envs);
	c_envs = environ_gen(envs);
	while (c_envs[i])
	{
		printf("%s\n", c_envs[i]);
		i++;
	}
	//printf("\n---------------\n");
	//printf("\nenv: %p\n", env);
	//printf("\nenv->name: %p\n", env->name);
	//del_env("TERM", &env);
	//print_envs(env);
	//printf("\n---------------\n");
	free_envs(envs);
	// system("leaks a.out");
	return(0);
} */