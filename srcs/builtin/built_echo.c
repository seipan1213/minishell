#include "../../includes/builtin.h"

int	built_echo(char **argv)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	flag = 0;
	while (argv[i] && argv[i][0] == '-')
	{
		j = 1;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] == ' ' && ++i)
			flag |= ECHO_OP_N;
		else
			break ;
	}
	while (argv[i] != NULL)
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i++] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!(flag & ECHO_OP_N))
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}