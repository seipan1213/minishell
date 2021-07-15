/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:09:56 by kotatabe          #+#    #+#             */
/*   Updated: 2021/07/13 20:44:43 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

t_env	*search_env(char *key, t_env *env)
{
	int	ret;

	ret = 0;
	if (!env)
		return (NULL);
	while (env != NULL)
	{
		ret = ft_strcmp(key, env->name);
		if (ret == 0)
		{
			return (env);
		}
		env = env->next;
	}
	return (NULL);
}

int	update_env(char *key, char *newVal, t_env **envs)
{
	t_env	*newEnv;

	newEnv = search_env(key, *envs);
	if (!newEnv)
	{
		newEnv = create_env(key, newVal);
		if (newEnv)
			addb_env(envs, newEnv);
		else
			return (0);
		return (1);
	}
	if (newVal)
		free(newEnv->value);
	if (newVal)
		newEnv->value = ft_strdup(newVal);
	return (1);
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

int	del_env(char *delKey, t_env **envs)
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
			return (1);
		}
		prev = delEnv;
		delEnv = delEnv->next;
	}
	return (0);
}
