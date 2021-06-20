#include "../../includes/builtin.h"

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
		if (!home)
			exit_error("HOME", "unset", 1);
		return (home);
	}
	else if (i == 2)
		return (argv[1]);
	else
		exit_error("too many arguments", "unset", 1);
	return (NULL);
}

int	built_cd(char **argv)
{
	char	*dst;
	char	*tmp;
	int		i;

	dst = check_cd(argv);
	tmp = get_env("PWD", g_data.envs);
	if (tmp)
		update_env("OLDPWD", tmp, g_data.envs);
	if (chdir(dst))
		exit_error("No such file or directory", "cd", 1);
	if (!(tmp = getcwd(0, 0)))
		exit_error("getcwd error", "cd", 1);
	update_env("PWD", tmp, g_data.envs);
	free(tmp);
	return (EXIT_SUCCESS);
}