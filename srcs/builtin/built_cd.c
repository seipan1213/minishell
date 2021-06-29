#include "../../includes/builtin.h"

char	*get_home(void)
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
	home = get_home();
	if (i == 1)
	{
		if (home)
			return (ft_strdup(get_home()));
	}
	else if (i == 2)
	{
		if (argv[1][0] == '~')
		{
			if (home)
				return (ft_strjoin(home, argv[1] + 1));
			else
				return (NULL);
		}
		return (ft_strdup(argv[1]));
	}
	else
		put_error("too many arguments", "cd", 0);
	return (NULL);
}

int	built_cd(char **argv)
{
	char	*dst;
	char	*tmp;

	if (!(dst = check_cd(argv)))
		return (EXIT_FAILURE);
	tmp = get_env("PWD", g_data.envs);
	if (tmp)
		update_env("OLDPWD", tmp, g_data.envs);
	if (chdir(dst))
		put_error(strerror(errno), "cd", 1);
	if (!(tmp = getcwd(0, 0)))
		put_error(strerror(errno), "cd", 1);
	if (tmp)
		update_env("PWD", tmp, g_data.envs);
	free(tmp);
	free(dst);
	return (EXIT_SUCCESS);
}