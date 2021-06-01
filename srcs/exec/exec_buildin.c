#include "../../includes/exec.h"

void	exec_buildin(char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		echo(args);
	// if (ft_strcmp(args[0], "cd") == 0)
		// echo();
	// if (ft_strcmp(args[0], "pwd") == 0)
	// 	echo();
	// if (ft_strcmp(args[0], "export") == 0)
	// 	echo();
	// if (ft_strcmp(args[0], "unset") == 0)
	// 	echo();
	if (ft_strcmp(args[0], "env") == 0)
		env();
	// if (ft_strcmp(args[0], "exit") == 0)
	// 	echo();
	exit(0);
}