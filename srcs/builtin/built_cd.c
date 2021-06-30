/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:14:01 by kotatabe          #+#    #+#             */
/*   Updated: 2021/06/30 16:14:01 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

char	*special_cd(char **argv)
{
	char	*env;
	int		i;

	i = 1;
	if (argv[1][0] == '~' || (!ft_strncmp(argv[1], "--", 2) && ++i))
	{
		if (!(env = get_env("HOME", g_data.envs)))
		{
			put_error("HOME not set", "cd", 0);
			return (NULL);
		}
	}
	else if (argv[1][0] == '-')
	{
		if (!(env = get_env("OLDPWD", g_data.envs)))
		{
			put_error("OLDPWD not set", "cd", 0);
			return (NULL);
		}
		ft_putendl_fd(env, STDOUT_FILENO);
	}
	else
		return (ft_strdup(argv[1]));
	return (ft_strjoin(env, argv[1] + i));
}

char	*check_cd(char **argv)
{
	int		i;
	char	*home;

	i = 0;
	while (argv[i])
		i++;
	if (i == 1)
	{
		if ((home = get_env("HOME", g_data.envs)))
			return (ft_strdup(home));
		else
			put_error("HOME not set", "cd", 0);
	}
	else if (i == 2)
		return (special_cd(argv));
	else
		put_error("too many arguments", "cd", 0);
	return (NULL);
}

int	built_cd(char **argv)
{
	char	*oldpwd;
	char	*dst;
	char	*tmp;

	if (!(dst = check_cd(argv)))
		return (EXIT_FAILURE);
	if (!chdir(dst) && (tmp = getcwd(0, 0)))
	{
		if ((oldpwd = get_env("PWD", g_data.envs)))
			update_env("OLDPWD", oldpwd, g_data.envs);
		update_env("PWD", tmp, g_data.envs);
		free(g_data.pwd);
		g_data.pwd = tmp;
	}
	else
		put_error(strerror(errno), "cd", 1);
	free(dst);
	return (EXIT_SUCCESS);
}
