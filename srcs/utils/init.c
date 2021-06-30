#include "../../includes/utils.h"

void	init_data(void)
{
	g_data.envs = envs_init();
	del_env("OLDPWD", &g_data.envs);
	if (!(update_env("OLDPWD", NULL, g_data.envs)))
		exit_error("init error", NULL, 1);
	if (!(g_data.pwd = getcwd(0, 0)))
		exit_error("init error", NULL, 1);
	shlvl_init();
}

void	shlvl_add(t_env *envs)
{
	char	*name;
	char	*value;
	t_env	*env;

	if (!(name = ft_strdup("SHLVL")))
		exit_error(MALLOCERR, NULL, 1);
	if (!(value = ft_strdup("1")))
	{
		free(name);
		exit_error(MALLOCERR, NULL, 1);
	}
	if (!(env = make_env(name, value)))
	{
		free(name);
		free(value);
		exit_error(MALLOCERR, NULL, 1);
	}
	addb_env(&envs, env);
}

void	shlvl_puterr(int num)
{
	char	*str;
	char	*tmp;

	if (!(str = ft_itoa(num)))
		exit_error(MALLOCERR, NULL, 1);
	tmp = str;
	if (!(str = ft_strjoin("shell level (", str)))
	{
		free(str);
		exit_error(MALLOCERR, NULL, 1);
	}
	free(tmp);
	tmp = str;
	if (!(str = ft_strjoin(str, ") too high, resetting to 1")))
	{
		free(str);
		exit_error(MALLOCERR, NULL, 1);
	}
	free(tmp);
	put_error(str, "warning", STDERR_FILENO);
	free(str);
}

void	shlvl_change(t_env *shlvl)
{
	char	*lv;
	int		lv_num;

	lv = NULL;
	lv_num = 0;
	if (shlvl->value)
		lv_num = ft_atoi(shlvl->value) + 1;
	if (!shlvl->value || !is_strdigit(shlvl->value) || lv_num > 1000)
		lv = ft_strdup("1");
	else if (lv_num < 0)
		lv = ft_strdup("0");
	else if (lv_num == 1000)
		lv = ft_strdup("");
	else
		lv = ft_itoa(lv_num);
	if (shlvl->value)
		free(shlvl->value);
	if (!lv)
		exit_error(MALLOCERR, NULL, 1);
	shlvl->value = lv;
	if (lv_num > 1000)
		shlvl_puterr(lv_num);
}

void	shlvl_init(void)
{
	t_env	*shlvl;

	shlvl = search_env("SHLVL", g_data.envs);
	if (shlvl)
		shlvl_change(shlvl);
	else
		shlvl_add(g_data.envs);
}