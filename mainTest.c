

#include "./includes/env.h"

int	ft_strcmp(char *s1, char *s2)
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

char *return_env(char *val, t_env *env)
{
	int i;
	int ret;
	i = 0;
	ret = 0;
	if (!env)
		return(NULL);
	while (env != NULL)
	{
		if ((ret = ft_strcmp(val, env->name)) == 0)
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

int main ()
{
	t_env *env;
	char *val;

	env = envs_init();
	val = return_env(" ", env);

	

	if (!val)
	{
		printf("Error: invalid key\n");
		return (0);
	}
	ft_putendl_fd(val, 1);

	return(0);
}