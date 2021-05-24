

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