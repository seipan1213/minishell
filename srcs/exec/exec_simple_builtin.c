#include "../../includes/exec.h"

void	backup_cur_fd(t_command *cmd)
{
	if (!cmd->rd)
		return ;
	if (cmd->rd->fd_file != NOT_SPECIFIED)
	{
		cmd->rd->fd_backup = dup(cmd->rd->fd_file);
		return ;
	}
	if (cmd->rd->type == RD_INPUT)
	{
		cmd->rd->fd_backup = dup(STDIN_FILENO);
	}
	else if (cmd->rd->type == RD_OUTPUT || cmd->rd->type == RD_APPEND_OUTPUT)
	{
		if (cmd->rd->fd_file == STDERR_FILENO)
			cmd->rd->fd_backup = dup(STDERR_FILENO);
		else
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

void	close_rd_fd(t_command *cmd)
{
	if (!cmd->rd)
		return ;
	if (cmd->rd->fd_file != NOT_SPECIFIED)
		close(cmd->rd->fd_file);
}

int		exec_simple_buildin(t_command *cmd, char **args)
{
	int	ret;

	backup_cur_fd(cmd);
	get_rd_fd(cmd);
	change_rd_fd(cmd);
	ret = exec_builtin(args);
	close_rd_fd(cmd);
	// if (errno)
	// {
	// 	ft_putstr_fd(args[0], STDERR_FILENO);
	// 	ft_putstr_fd(": ", STDERR_FILENO);
	// 	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	// 	ft_putstr_fd("\n", STDERR_FILENO);
	// }
	// errno = 0;
	recover_fd(cmd);
	return (ret);
}