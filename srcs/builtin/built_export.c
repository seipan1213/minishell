/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:15:20 by kotatabe          #+#    #+#             */
/*   Updated: 2021/07/03 20:12:36 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static void	print_export(t_env *envs)
{
	int		i;
	char	*tmp;
	char	**str_envs;

	i = -1;
	str_envs = environ_gen(envs);
	sort_str(str_envs);
	while (str_envs[++i])
	{
		tmp = ft_strchr(str_envs[i], '=');
		if (tmp)
			*tmp = '\0';
		printf("declare -x %s", str_envs[i]);
		if (tmp)
		{
			printf("=\"%s\"", tmp + 1);
			*tmp = '=';
		}
		printf("\n");
	}
	i = -1;
	while (str_envs[++i])
		free(str_envs[i]);
	free(str_envs);
}

int	check_identifier(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_env(char *str)
{
	t_env	*env;

	env = str_to_env(str);
	if (!env)
		return (0);
	if (!check_identifier(env->name))
	{
		free_env(env);
		return (0);
	}
	if (!(update_env(env->name, env->value, g_data.envs)))
	{
		free_env(env);
		return (0);
	}
	free_env(env);
	return (1);
}

int	built_export(char **argv)
{
	int	i;
	int	ret;

	i = 1;
	ret = EXIT_SUCCESS;
	if (argv[i] != NULL)
	{
		while (argv[i])
		{
			if (!export_env(argv[i]))
				ret = put_error("not a valid identifier", \
									"export", EXIT_FAILURE);
			i++;
		}
	}
	else
		print_export(g_data.envs);
	return (ret);
}
