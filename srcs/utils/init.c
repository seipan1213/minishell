#include "../../includes/utils.h"

void	init_data(void)
{
	char	*oldpwd;

	g_data.envs = envs_init();
	if (!(update_env("OLDPWD", NULL, g_data.envs)))
		exit_error("init error", NULL, 1);
	if (!(g_data.pwd = getcwd(0, 0)))
		exit_error("init error", NULL, 1);
}