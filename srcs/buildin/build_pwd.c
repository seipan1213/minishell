#include "../../includes/buildin.h"

int	pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = search_env("PWD", g_data.envs)->value;
	if (!pwd)
		return (-1);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	return (1);
}