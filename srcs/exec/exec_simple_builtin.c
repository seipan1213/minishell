#include "../../includes/exec.h"

void	backup_cur_fd(t_redirect *rd)
{
	t_redirect	*rd_tmp;

	if (!rd)
		return ;
	rd_tmp = rd;
	while (rd_tmp)
	{
		if (rd_tmp->fd_file >= 0)
		{
			rd_tmp->fd_backup = dup(rd_tmp->fd_file);
		}
		rd_tmp = rd_tmp->next;
	}
}

void	recover_fd(t_redirect *rd)
{
	t_redirect	*rd_now;

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

	// void		print_rd(t_redirect *rd)
	// {
	// 	while (rd)
	// 	{
	// 		printf("[%s]\n", rd->filename->str);
	// 		rd = rd->next;
	// 		if (!rd)
	// 			printf("p: %p\n", rd);
	// 	}
	// }

int		exec_simple_buildin(t_command *cmd, char **args)
{
	int		ret;

	backup_cur_fd(cmd->rd);
	get_rd_fd(cmd->rd);
	change_rd_fd(cmd->rd);
	ret = exec_builtin(args);
	recover_fd(cmd->rd);
	return (ret);
}