#include "../../includes/builtin.h"

int	built_pwd(void)
{
	char	*pwd;

	pwd = get_env("PWD", g_data.envs);
	if (!pwd)
		return (-1);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}