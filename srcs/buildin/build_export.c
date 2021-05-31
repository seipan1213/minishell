#include "../../includes/buildin.h"

static void	print_export(t_env *envs)
{
	sort_envs(envs);
	while (envs)
	{
		ft_putstr_fd("declare -x ", STDERR_FILENO);
		ft_putstr_fd(envs->name, STDERR_FILENO);
		ft_putstr_fd("=", STDERR_FILENO);
		ft_putchar_fd('\"', STDOUT_FILENO);
		ft_putstr_fd(envs->value, STDERR_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
		envs = envs->next;
	}
}

static int	export_env(char *str)
{
	t_env	*env;

	if (!(env = create_env(str)))
		return (0);
	addb_env(&g_data.envs, env);
	return (1);
}

int	build_export(char **argv)
{
	int	i;

	i = 1;
	if (argv[i] != NULL)
	{
		while (argv[i])
		{
			if (!(export_env(argv[i])))
				return (-1);
			i++;
		}
	}
	else
		print_export(g_data.envs);
	return (EXIT_SUCCESS);
}