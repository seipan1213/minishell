/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:10:52 by kotatabe          #+#    #+#             */
/*   Updated: 2021/07/03 18:53:59 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

static t_env	*str_to_env_util(t_env *env, char *environ)
{
	char	*tmp;

	tmp = ft_strchr(environ + 1, '=');
	*tmp = '\0';
	env->name = ft_strdup(environ);
	env->value = ft_strdup(tmp + 1);
	if (env->name && !env->value)
		free(env->name);
	if (!env->name && env->value)
		free(env->value);
	*tmp = '=';
	if (!env->name || !env->value)
		free(env);
	if (!env->name || !env->value)
		return (NULL);
	return (env);
}

t_env	*str_to_env(char *environ)
{
	t_env	*env;
	char	*tmp;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->next = NULL;
	tmp = ft_strchr(environ + 1, '=');
	if (!tmp)
	{
		env->name = ft_strdup(environ);
		if (!env->name)
			free(env);
		if (!env->name)
			return (NULL);
		env->value = NULL;
		return (env);
	}
	env = str_to_env_util(env, environ);
	return (env);
}

int	envs_len(t_env *envs)
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

static char	*environ_gen_util(t_env *env)
{
	char	*tmp;
	char	*value;

	tmp = NULL;
	value = NULL;
	if (!env->value)
	{
		tmp = ft_strdup(env->name);
		if (!tmp)
			exit_error(MALLOCERR, NULL, 0);
		return (tmp);
	}
	tmp = ft_strjoin(env->name, "=");
	if (!tmp)
		exit_error(MALLOCERR, NULL, 0);
	value = ft_strjoin(tmp, env->value);
	free(tmp);
	if (!value)
		exit_error(MALLOCERR, NULL, 0);
	return (value);
}

char	**environ_gen(t_env *envs)
{
	char	**c_envs;
	int		len;
	int		i;

	i = 0;
	len = envs_len(envs);
	c_envs = (char **)malloc(sizeof(char *) * (len + 1));
	if (!c_envs)
		return (NULL);
	c_envs[len] = NULL;
	while (i < len)
	{
		c_envs[i++] = environ_gen_util(envs);
		envs = envs->next;
	}
	return (c_envs);
}
