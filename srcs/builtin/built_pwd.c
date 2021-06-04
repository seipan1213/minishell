#include "../../includes/builtin.h"

int	built_pwd(void)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (!pwd)
		return (-1);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (EXIT_SUCCESS);
}