#include "../../includes/exec.h"

void	backup_cur_fd(t_redirect *rd)
{
	t_redirect	*rd_now;

	if (!rd)
		return ;
	rd_now = rd;
	while (rd_now)
	{
		if (rd_now->fd_file != NOT_SPECIFIED)
		{
			rd_now->fd_backup = dup(rd_now->fd_file);
			return ;
		}
		if (rd_now->type == RD_INPUT)
		{
			rd_now->fd_backup = dup(STDIN_FILENO);
		}
		else if (rd_now->type == RD_OUTPUT || rd_now->type == RD_APPEND_OUTPUT)
		{
			if (rd_now->fd_file == STDERR_FILENO)
				rd_now->fd_backup = dup(STDERR_FILENO);
			else
				rd_now->fd_backup = dup(STDOUT_FILENO);
		}
		rd_now = rd_now->next;
	}
}

void	recover_fd(t_redirect *rd)
{
	t_redirect	*rd_now;

	if (!rd)
		return ;
	rd_now = rd;
	while (rd_now)
	{
		if (rd_now->fd_file != NOT_SPECIFIED)
		{
			dup_fd(rd_now->fd_backup, rd_now->fd_file);
			return ;
		}
		if (rd_now->type == RD_INPUT)
		{
			dup_fd(rd_now->fd_backup, STDIN_FILENO);
		}
		else if (rd_now->type == RD_OUTPUT || rd_now->type == RD_APPEND_OUTPUT)
		{
			dup_fd(rd_now->fd_backup, STDOUT_FILENO);
		}
		rd_now = rd_now->next;
	}
}

void	close_rd_fd(t_redirect *rd)
{
	if (!rd)
		return ;
	if (rd->fd_file != NOT_SPECIFIED)
		close(rd->fd_file);
}

	void		print_rd(t_redirect *rd)
	{
		while (rd)
		{
			printf("[%s]\n", rd->filename->str);
			rd = rd->next;
			if (!rd)
				printf("p: %p\n", rd);
		}
	}

int		exec_simple_buildin(t_command *cmd, char **args)
{
	int		ret;

	backup_cur_fd(cmd->rd);
	get_rd_fd(cmd->rd);
	change_rd_fd(cmd->rd);
	ret = exec_builtin(args);
	// if (errno)
	// {
	// 	ft_putstr_fd(args[0], STDERR_FILENO);
	// 	ft_putstr_fd(": ", STDERR_FILENO);
	// 	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	// 	ft_putstr_fd("\n", STDERR_FILENO);
	// }
	// errno = 0;
	recover_fd(cmd->rd);
	close_rd_fd(cmd->rd);
	return (ret);
}