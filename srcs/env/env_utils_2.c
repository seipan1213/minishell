#include "../../includes/env.h"

char	*get_env(char *key, t_env *envs)
{
	t_env	*env;

	env = search_env(key, envs);
	if (env)
		return (env->value);
	return (NULL);
}

t_env	*make_env(char *name, char *value)
{
	t_env	*env;

	if (!(env = malloc(sizeof(t_env))))
		return (NULL);
	env->name = name;
	env->value = value;
	env->next = NULL;
	return (env);
}