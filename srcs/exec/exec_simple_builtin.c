#include "../../includes/exec.h"

void	backup_fd(t_command *cmd)
{
	if (!cmd->rd)
		return ;
	if (cmd->rd->type == RD_INPUT)
	{
		cmd->rd->fd_backup = dup(STDIN_FILENO);
	}
	else if (cmd->rd->type == RD_OUTPUT || cmd->rd->type == RD_APPEND_OUTPUT)
	{
		cmd->rd->fd_backup = dup(STDOUT_FILENO);
	}
}

void	recover_fd(t_command *cmd)
{
	if (!cmd->rd)
		return ;
	if (cmd->rd->type == RD_INPUT)
	{
		dup2(cmd->rd->fd_backup, STDIN_FILENO);
		close(cmd->rd->fd_backup);
	}
	else if (cmd->rd->type == RD_OUTPUT || cmd->rd->type == RD_APPEND_OUTPUT)
	{
		dup2(cmd->rd->fd_backup, STDOUT_FILENO);
		close(cmd->rd->fd_backup);
	}
}

void	exec_simple_buildin(t_command *cmd, char **args)
{
	backup_fd(cmd);
	get_rd_fd(cmd);
	change_rd_fd(cmd);
	exec_builtin(args);
	recover_fd(cmd);
}