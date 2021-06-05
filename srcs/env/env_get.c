#include "../../includes/env.h"

char	*get_env(char *key, t_env *envs)
{
	t_env	*env;

	env = search_env(key, envs);
	if (env)
		return (env->value);
	return (NULL);
}