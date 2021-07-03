/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:14:01 by kotatabe          #+#    #+#             */
/*   Updated: 2021/07/03 19:00:16 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void	put_cd_err(char *key)
{
	ft_putstr_fd(ERR_MSH, STDERR_FILENO);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(key, STDERR_FILENO);
	ft_putendl_fd(" not set", STDERR_FILENO);
}

char	*special_cd(char **argv)
{
	char	*env;
	char	*key;
	int		i;

	i = 1;
	key = NULL;
	if (argv[1][0] == '~' || (!ft_strncmp(argv[1], "--", 2) && ++i))
		key = ft_strdup("HOME");
	else if (argv[1][0] == '-')
		key = ft_strdup("OLDPWD");
	else
		return (ft_strdup(argv[1]));
	env = get_env(key, g_data.envs);
	if (!env)
	{
		put_cd_err(key);
		free(key);
		return (NULL);
	}
	if (!ft_strncmp(key, "OLDPWD", 6))
		ft_putendl_fd(env, STDOUT_FILENO);
	free(key);
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
		home = get_env("HOME", g_data.envs);
		if (home)
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
