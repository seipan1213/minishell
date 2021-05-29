#include "../../includes/buildin.h"

static void	print_envs(t_env *envs)
{
	while (envs)
	{
		ft_putstr_fd(envs->name, STDERR_FILENO);
		ft_putstr_fd("=", STDERR_FILENO);
		ft_putendl_fd(envs->value, STDERR_FILENO);
		envs = envs->next;
	}
}

int	env(void)
{
	print_envs(g_data.envs);
	return(1);
}