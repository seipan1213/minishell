/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:11:13 by kotatabe          #+#    #+#             */
/*   Updated: 2021/06/30 16:11:13 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	env->name = name;
	env->value = value;
	env->next = NULL;
	return (env);
}

t_env *create_env(char *key, char *newVal)
{
	char	*tmp;
	char	*value;
	t_env	*env;

	tmp = ft_strdup(key);
	if (!newVal)
	{
		value = NULL;
		env = make_env(tmp, value);
		return (env);
	}
	value = ft_strdup(newVal);
	if (!tmp || !value)
	{
		if (tmp)
			free(tmp);
		if (value)
			free(value);
		return (NULL);
	}
	env = make_env(tmp, value);
	return (env);
}