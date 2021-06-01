#include "../../includes/buildin.h"

static void	print_export(t_env *envs)
{
	int		i;
	int		j;
	char	**str_envs;

	i = 0;
	str_envs = environ_gen(envs);
	sort_str(str_envs);
	while (str_envs[i])
	{
		j = 0;
		while (str_envs[i][j] != '=')
			j++;
		str_envs[i][j] = '\0';
		ft_putstr_fd(str_envs[i], STDERR_FILENO);
		ft_putstr_fd("=", STDERR_FILENO);
		ft_putchar_fd('\"', STDOUT_FILENO);
		ft_putstr_fd(str_envs[i] + j + 1, STDERR_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
		str_envs[i][j] = '=';
		i++;
	}
	i = -1;
	while (str_envs[++i])
		free(str_envs[i]);
	free(str_envs);
}

int	check_identifier(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_env(char *str)
{
	t_env	*env;

	if (!(env = create_env(str)))
		return (0);
	if (!check_identifier(env->name))
		return (0);
	addb_env(&g_data.envs, env);
	return (1);
}

int	export(char **argv)
{
	int	i;
	int	ret;

	i = 1;
	ret = EXIT_SUCCESS;
	if (argv[i] != NULL)
	{
		while (argv[i])
		{
			if (!export_env(argv[i]))
			{
				ft_putendl_fd("export: not a valid identifier", STDERR_FILENO);
				ret = -1;
			}
			i++;
		}
	}
	else
		print_export(g_data.envs);
	return (ret);
}