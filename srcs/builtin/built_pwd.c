#include "../../includes/builtin.h"

int	built_pwd(void)
{
	if (!g_data.pwd)
		return (EXIT_FAILURE);
	ft_putendl_fd(g_data.pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}