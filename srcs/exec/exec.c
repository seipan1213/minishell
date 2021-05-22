

#include "../../includes/exec.h"

int		exec_bin(astNode *node)
{
	char		*line;
	char		*path;
	char		**args;
	extern char	**environ;

	args = to_wchar(node->cmd->arg);
	line = args[0];
	path = ft_strjoin("/bin/", line);
	execve(path, args, environ);
	return (TRUE);
}

int		exec_bin_cmd(astNode *node)
{
	pid_t	pid;
	int		status;

	if ((pid = fork()) < 0)
		exit(errno);
	else if (pid == 0)
	{
		errno = 0;
		exec_bin(node);
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

int		exec_cmd(astNode *node)
{
	// exec_pipeline
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
		exec_cmd(node);
	}
	return (TRUE);
}