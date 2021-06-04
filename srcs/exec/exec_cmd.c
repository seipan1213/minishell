#include "../../includes/exec.h"

int		exec_cmdline(t_command *cmd, char **args, t_pipe_status *p_stat, int pipe_fd[])
{
	pid_t	pid;
	int		new_pipe_fd[2];

	if (*p_stat == PIPE_WRITE_ONLY || *p_stat == PIPE_READ_WRITE)
	{
		if (pipe(new_pipe_fd) < 0)
			return (FALSE);
	}
	if ((pid = fork()) < 0)
		return (FALSE);
	if (pid == 0)
	{
		dup_pipe(p_stat, pipe_fd, new_pipe_fd);
		if (is_builtin(args))
			exit(exec_builtin(args));
		else
			exec_bin(args);
	}
	pass_pipe(p_stat, pipe_fd, new_pipe_fd);
	cmd->pid = pid;
	return (TRUE);
}

void	exec_cmd(t_command *cmd, t_pipe_status *p_stat, int pipe_fd[])
{
	char	**args;

	args = token_to_args(cmd->arg);
	if (*p_stat == NO_PIPE && is_builtin(args))
		exec_builtin(args);
	else
		exec_cmdline(cmd, args, p_stat, pipe_fd);
	get_next_p_stat(cmd, p_stat);
	// free args
}

void	exec_pipeline(astNode *node)
{
	t_pipe_status	p_stat;
	t_command		*cmd;
	int				pipe_fd[2];

	p_stat = PIPE_WRITE_ONLY;
	while (node->type == PIPE)
		node = node->left;
	cmd = node->cmd;
	while (cmd)
	{
		exec_cmd(cmd, &p_stat, pipe_fd);
		cmd = cmd->next; 
	}
	wait_commands(node->cmd);
}