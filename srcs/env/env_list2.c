

#include "../../includes/env.h"

int		ft_strcmp(char *s1, char *s2)
{
	int i;
	int diff;
	i = 0;
	diff = 0;
	
	while (s1[i])
	{
		diff = s1[i] - s2[i];
		if (diff != 0)
			return(diff);
		i++;
	}
	return(0);
}

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

int		main ()//int argc, char **argv)
{
	t_env *env;
	t_env *val;

	env = envs_init();
	// val = search_env(argv[1], env);

	
	print_envs(env);
	printf("\n---------------\n");
	
	del_env("SHLVL", env);



	// print_envs(env);
	printf("\n---------------\n");


	// if (!val)
	// {
	// 	printf("Error: invalid key\n");
	// 	return (0);
	// }
	// ft_putendl_fd(val->value, 1);
	free_envs(env);
	// system("leaks a.out");

	return(0);
}