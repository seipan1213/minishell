#include "../../includes/builtin.h"

static int	is_numeric_argument(char *str)
{
	int	size;
	int	m;

	m = 1;
	size = 0;
	if (!is_strdigit(str))
		return (1);
	while (ft_isspace(str[size]))
		str++;
	if (str[size] == '-')
		m = -1;
	if (str[size] == '+' || str[size] == '-')
		str++;
	while (ft_isdigit(str[size]))
		size++;
	if ((m == -1 && size > 19))
		return (1);
	if ((m == 1 && size > 19))
		return (1);
	if ((m == -1 && ft_strncmp(str, "9223372036854775808", 19) > 0) && size == 19)
		return (1);
	if ((m == 1 && ft_strncmp(str, "9223372036854775807", 19) > 0) && size == 19)
		return (1);
	return (0);
}

int	built_exit(char **argv)
{
	int	i;
	int	num;

	i = 1;
	if (g_data.quit == 1)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (argv == NULL || argv[i] == NULL)
		exit(g_data.status);
	num = ft_atoi(argv[i]);
	num &= 255;
	if (is_numeric_argument(argv[i]))
		exit_error(NUMERR, "exit", 255);
	if (is_strdigit(argv[i]) && !argv[i + 1])
		exit(num);
	if (argv[i + 1])
		put_error("args err", "exit", -1);
	return (-1);
}