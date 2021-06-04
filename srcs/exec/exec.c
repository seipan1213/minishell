
#include "../../includes/exec.h"

void	exec_bin(char **args)
{
	char		*line;
	char		*path;
	extern char	**environ;

	line = args[0];
	path = ft_strjoin("/bin/", line);
	execve(path, args, environ);
	exit(1);
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
	char			**args;
	t_pipe_status	p_stat;

	p_stat = NO_PIPE;
	if (node->type == PIPE)
	{
		exec_pipeline(node);
	}
	else
	{
		exec_cmd(node->cmd, &p_stat, NULL);
		wait_commands(node->cmd);
	}
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