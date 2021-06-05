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
			exit_error("unset HOME", 1);
		return (home);
	}
	else if (i == 2)
		return (argv[1]);
	else
		exit_error("too many arguments", 1);
	return (NULL);
}

int	built_cd(char **argv)
{
	char	*dst;
	char	*tmp;
	int		i;

	dst = check_cd(argv);
	if (!(tmp = getcwd(0, 0)))
		exit_error("getcwd error", 1);
	else
		update_env("OLDPWD", tmp, g_data.envs);
	free(tmp);
	if (chdir(dst))
		exit_error("No such file or directory", 1);
	if (!(tmp = getcwd(0, 0)))
		exit_error("getcwd error", 1);
	update_env("PWD", tmp, g_data.envs);
	free(tmp);
	return (EXIT_SUCCESS);
}