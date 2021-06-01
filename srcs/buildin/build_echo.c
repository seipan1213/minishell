#include "../../includes/buildin.h"

int	build_echo(char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (argv[i] && !ft_strncmp(argv[i], "-n", 3) && ++i)
		flag |= ECHO_OP_N;
	while (argv[i] != NULL)
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i++;
		if (argv[i] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!(flag & ECHO_OP_N))
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}