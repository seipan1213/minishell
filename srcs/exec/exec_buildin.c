#include "../../includes/exec.h"

void	exec_buildin(char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		build_echo(args);
	// if (ft_strcmp(args[0], "cd") == 0)
	// 	build_cd();
	if (ft_strcmp(args[0], "pwd") == 0)
		build_pwd();
	if (ft_strcmp(args[0], "export") == 0)
		build_export(args);
	if (ft_strcmp(args[0], "unset") == 0)
		build_unset(args);
	if (ft_strcmp(args[0], "env") == 0)
		build_env();
	if (ft_strcmp(args[0], "exit") == 0)
		build_exit(args);
}