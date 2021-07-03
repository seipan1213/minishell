/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:12:32 by kotatabe          #+#    #+#             */
/*   Updated: 2021/07/03 18:17:40 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static int	is_cmd(char *str)
{
	if (!(ft_strchr(str, '/')))
		return (1);
	return (0);
}

int	is_exec(char *path)
{
	t_stat	status;

	if (stat(path, &status) == -1)
		return (0);
	if (!(status.st_mode & S_IRUSR))
		return (0);
	if (!(status.st_mode & S_IXUSR))
		return (0);
	if (lstat(path, &status) == -1)
		return (0);
	if (S_ISDIR(status.st_mode))
		exit_error("is a directory", path, 126);
	return (1);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static char	*exec_serach_util(char *path, char *argv)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
	{
		put_error(MALLOCERR, NULL, 1);
		return (NULL);
	}
	res = ft_strjoin(tmp, argv);
	free(tmp);
	if (!res)
	{
		put_error(MALLOCERR, NULL, 1);
		return (NULL);
	}
	return (res);
}

char	*exec_serach(char *argv)
{
	char	**path;
	char	*res;
	int		i;

	if (!(is_cmd(argv)) && is_exec(argv))
		return (ft_strdup(argv));
	else if ((!(is_cmd(argv)) && !is_exec(argv)))
		return (NULL);
	if (!get_env("PATH", g_data.envs))
		return (NULL);
	path = ft_split(get_env("PATH", g_data.envs), ':');
	if (!path && put_error(MALLOCERR, NULL, 1))
		return (NULL);
	i = -1;
	while (path[++i])
	{
		res = exec_serach_util(path[i], argv);
		if (!res || is_exec(res))
			break ;
		free(res);
	}
	if (!path[i])
		res = NULL;
	free_split(path);
	return (res);
}