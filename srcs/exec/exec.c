
#include "../../includes/exec.h"

int		exec_bin(char **args)
{
	char		*line;
	char		*path;
	extern char	**environ;

	line = args[0];
	path = ft_strjoin("/bin/", line);
	execve(path, args, environ);
	exit(1);
	return (FALSE);
}

int		exec_bin_cmd(astNode *node)
{
	pid_t	pid;
	int		status;
	char	**args;

	if ((pid = fork()) < 0)
		exit(errno);
	else if (pid == 0)
	{
		errno = 0;
		args = token_to_args(node->cmd->arg);
		exec_bin(args);
		if (errno)
		{
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("...\n", 2);
			exit(errno);
		}
	}
	if (waitpid(pid, &status, 0) < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		exit(errno);
	}
	return (TRUE);
}

int		exec_cmd_node(astNode *node)
{
	if (node->type == PIPE)
	{
		exec_pipeline(node);
	}
	else
		exec_bin_cmd(node);
	return (TRUE);
}

int		exec(astNode *node)
{
	if (!node)
		return (FALSE);
	if (node->type == SCOLON)
	{
		exec(node->left);
		exec(node->right);
	}
	else
	{
		exec_cmd_node(node);
	}
	return (TRUE);
}