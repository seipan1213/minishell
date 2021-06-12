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