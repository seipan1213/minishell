#include "../../includes/buildin.h"

int	build_unset(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		del_env(argv[i], &g_data.envs);
		i++;
	}
	if (i == 1)
	{
		ft_putendl_fd(UNSET_ERR, STDERR_FILENO);
		return (-1);
	}
	return (EXIT_SUCCESS);
}