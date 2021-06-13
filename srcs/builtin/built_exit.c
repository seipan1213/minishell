#include "../../includes/builtin.h"

int	built_exit(char **argv)
{
	int	i;
	int	num;

	i = 1;
	if (g_data.quit == 1)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (argv == NULL || argv[i] == NULL)
		exit(g_data.states);
	num = ft_atoi(argv[i]);
	if (is_strdigit(argv[i]) && !argv[i + 1])
		exit(num);
	ft_putendl_fd("args err", STDERR_FILENO);
	return (-1);
}