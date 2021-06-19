#include "../../includes/exec.h"

void	exec_bin(char **args)
{
	char	*path;
	char	**envs;

	if (!(envs = environ_gen(g_data.envs)))
		exit_error(MALLOCERR, 1);
	if (!(path = exec_serach(args[0])))
		exit(1);
	execve(path, args, envs);
	free_split(envs);
	free(path);
	exit(1);
}

int		exec_cmd_node(astNode *node)
{
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
	free_node(node);
	return (TRUE);
}