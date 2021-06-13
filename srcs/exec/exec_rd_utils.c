
#include "../../includes/exec.h"

void	get_rd_fd(t_command *cmd)
{
	if (!cmd->rd)
		return ;
	if (cmd->rd->type == RD_INPUT)
	{
		cmd->rd->fd_io = open(cmd->rd->filename->str, O_RDONLY);
	}
	else if (cmd->rd->type == RD_OUTPUT)
	{
		cmd->rd->fd_io = open(cmd->rd->filename->str, O_WRONLY | O_CREAT | O_TRUNC, \
		S_IREAD | S_IWRITE);
	}
	else if (cmd->rd->type == RD_APPEND_OUTPUT)
	{
		cmd->rd->fd_io = open(cmd->rd->filename->str, O_WRONLY | O_CREAT | O_APPEND, \
		S_IREAD | S_IWRITE);
	}
}

void	change_rd_fd(t_command *cmd)
{
	if (!cmd->rd)
		return ;
	if (cmd->rd->fd_file != NOT_SPECIFIED)
	{
		dup2(cmd->rd->fd_io, cmd->rd->fd_file);
		close(cmd->rd->fd_io);
		return ;
	}
	if (cmd->rd->type == RD_INPUT)
	{
		dup2(cmd->rd->fd_io, STDIN_FILENO);
		close(cmd->rd->fd_io);
	}
	else if (cmd->rd->type == RD_OUTPUT || cmd->rd->type == RD_APPEND_OUTPUT)
	{
		if (cmd->rd->fd_file == STDERR_FILENO)
			dup2(cmd->rd->fd_io, STDERR_FILENO);
		else
			dup2(cmd->rd->fd_io, STDOUT_FILENO);
		close(cmd->rd->fd_io);
	}
}

