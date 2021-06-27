#include "../../includes/env.h"

int		envs_len(t_env *envs)
{
	int	len;

	len = 0;
	while (envs)
	{
		envs = envs->next;
		len++;
	}
	return (len);
}

char	**environ_gen(t_env *envs)
{
	char	**c_envs;
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	len = envs_len(envs);
	if (!(c_envs = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	c_envs[len] = NULL;
	while(i < len)
	{
		if (!envs->value)
			c_envs[i++] = ft_strdup(envs->name);
		else
		{
			if (!(tmp = ft_strjoin(envs->name, "=")))
				exit_error(MALLOCERR, NULL, 0);
			if (!(c_envs[i++] = ft_strjoin(tmp, envs->value)))
				exit_error(MALLOCERR, NULL, 0);
			free(tmp);
		}
		printf("%s\n",c_envs[i-1]);
		envs = envs->next;
	}
	return (c_envs);
}