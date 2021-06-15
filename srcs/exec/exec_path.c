#include "../../includes/exec.h"

static int	is_cmd(char *str)
{
	if (!(ft_strchr(str, '/')))
		return (1);
	return (0);
}

int			is_exec(char *path)
{
	t_stat status;

	if (stat(path, &status) == -1)
		return (0);
	if (!(status.st_mode & S_IRUSR))
		return (0);
	if (!(status.st_mode & S_IXUSR))
		return (0);
	return (1);
}

void		free_split(char **split)
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

char		*exec_serach(char *argv)
{
	char	**path;
	char	*res;
	char	*tmp;
	int		i;

	if (!(is_cmd(argv)))
		return (ft_strdup(argv));
	if (!(path = ft_split(get_env("PATH", g_data.envs), ':')))
		return (NULL);
	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		res = ft_strjoin(tmp, argv);
		free(tmp);
		if (is_exec(res))
			break ;
		free(res);
	}
	if (!path[i])
		res = NULL;
	free_split(path);
	return (res);
}