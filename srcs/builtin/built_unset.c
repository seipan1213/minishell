#include "../../includes/builtin.h"

int	built_unset(char **argv)
{
	int	i;
	int	ret;

	i = 1;
	ret = EXIT_SUCCESS;
	while (argv[i])
	{
		if (!check_identifier(argv[i]))
		{
			ft_putendl_fd("unset: not a valid identifier", STDERR_FILENO);
			ret = EXIT_FAILURE;
		}
		else
			del_env(argv[i], &g_data.envs);
		i++;
	}
	if (i == 1)
	{
		ft_putendl_fd(UNSET_ERR, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (ret);
}