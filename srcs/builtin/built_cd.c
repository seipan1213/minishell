#include "../../includes/builtin.h"

char	*get_home(t_env *envs)
{
	char	*home;

	home = get_env("HOME", g_data.envs);
	if (!home)
	{
		put_error("unset HOME", "cd", 0);
		return (NULL);
	}
	return (home);
}

char	*check_cd(char **argv)
{
	int		i;
	char	*home;

	i = 0;
	while (argv[i])
		i++;
	home = get_home(g_data.envs);
	if (i == 1)
	{
		if (home)
			return (ft_strdup(get_home(g_data.envs)));
	}
	else if (i == 2)
	{
		if (argv[1][0] == '~')
			if (home)
				return (ft_strjoin(home, argv[1] + 1));
			else
				return (NULL);
		return (ft_strdup(argv[1]));
	}
	else
		put_error("too many arguments", "cd", 0);
	return (NULL);
}

int	built_cd(char **argv)
{
	char	*oldpwd;
	char	*dst;
	char	*tmp;
	int		i;

	if (!(dst = check_cd(argv)))
		return (EXIT_FAILURE);
	if (!chdir(dst) && (tmp = getcwd(0, 0)))
	{
		if (oldpwd = get_env("PWD", g_data.envs));
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