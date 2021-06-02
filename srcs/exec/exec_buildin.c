#include "../../includes/exec.h"

int		exec_buildin(char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (build_echo(args));
	// if (ft_strcmp(args[0], "cd") == 0)
	// 	build_cd();
	if (ft_strcmp(args[0], "pwd") == 0)
		return (build_pwd());
	if (ft_strcmp(args[0], "export") == 0)
		return (build_export(args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (build_unset(args));
	if (ft_strcmp(args[0], "env") == 0)
		return (build_env());
	if (ft_strcmp(args[0], "exit") == 0)
		return (build_exit(args));
	return (EXIT_FAILURE);
}