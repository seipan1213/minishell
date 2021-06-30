#include "../../includes/exec.h"

void	backup_cur_fd(t_redirect *rd)
{
	t_redirect	*rd_now;

	if (!rd)
		return ;
	rd_now = rd;
	while (rd_now)
	{
		if (rd_now->fd_file >= 0)
		{
			rd_now->fd_backup = dup(rd_now->fd_file);
		}
		rd_now = rd_now->next;
	}
}

void	recover_fd(t_redirect *rd)
{
	if (!rd)
		return ;
	while (rd->next)
		rd = rd->next;
	while (rd)
	{
		if (rd->fd_file >= 0)
		{
			close(rd->fd_file);
			dup_fd(rd->fd_backup, rd->fd_file);
		}
		rd = rd->prev;
	}
}

int	exec_simple_buildin(t_command *cmd, char **args)
{
	int		ret;

	backup_cur_fd(cmd->rd);
	if (!(get_rd_fd(cmd->rd, FALSE)))
		return (EXIT_FAILURE);
	change_rd_fd(cmd->rd);
	ret = exec_builtin(args);
	recover_fd(cmd->rd);
	return (ret);
}
