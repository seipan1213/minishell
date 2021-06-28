#include "../../includes/utils.h"

void	init_data(void)
{
	g_data.envs = envs_init();
	del_env("OLDPWD", &g_data.envs);
	if (!(update_env("OLDPWD", NULL, g_data.envs)))
		exit_error("init error", NULL, 1);
	if (!(g_data.pwd = getcwd(0, 0)))
		exit_error("init error", NULL, 1);
}

void	shlvl_change(t_env *shlvl)
{
	char	*lv;

	lv = NULL;
	if (!shlvl->value)
		return ;
	if (is_strdigit(shlvl->value))
		lv = ft_strdup("1");
}

void	shlvl_init(void)
{
	t_env	*shlvl;

	shlvl = search_env("SHLVL", g_data.envs);
	if (shlvl)
	{
		shlvl_change(shlvl);
	}
}