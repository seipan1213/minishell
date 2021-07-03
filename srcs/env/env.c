/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:09:53 by kotatabe          #+#    #+#             */
/*   Updated: 2021/06/30 16:09:53 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

t_env	*envs_init(void)
{
	extern char	**environ;
	t_env		*envs;
	t_env		*env;
	int			i;

	i = 0;
	envs = NULL;
	while (environ[i])
	{
		env = str_to_env(environ[i]);
		addb_env(&envs, env);
		i++;
	}
	return (envs);
}

void	addb_env(t_env **envs, t_env *env)
{
	t_env	*back;

	if (!envs || !env)
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

void	free_env(t_env *env)
{
	free(env->name);
	env->name = NULL;
	free(env->value);
	env->value = NULL;
	free(env);
	env = NULL;
}

void	free_envs(t_env *envs)
{
	while (envs != NULL)
	{
		free_env(envs);
		envs = envs->next;
	}
}
