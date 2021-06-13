
#include "../../includes/exec.h"

int		is_file_error(int fd_file, int rd_type)
{
	if (fd_file == 0 && rd_type == RD_OUTPUT)
		return (1);
	if (fd_file == 1 && rd_type == RD_INPUT)
		return (1);
	if (fd_file == 2 && rd_type == RD_INPUT)
		return (1);
	return (0);
}

void	get_rd_fd(t_command *cmd)
{
	if (!cmd->rd)// || is_file_error(cmd->rd->fd_file, cmd->rd->type))
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
	if (cmd->rd->fd_file >= 3)
	{
		dup2(cmd->rd->fd_io, cmd->rd->fd_file);
		close(cmd->rd->fd_io);
	}
}

void	change_rd_fd(t_command *cmd)
{
	if (!cmd->rd || is_file_error(cmd->rd->fd_file, cmd->rd->type))
		return ;
	if (cmd->rd->fd_file >= 3)
		cmd->rd->fd_io = cmd->rd->fd_file;
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

