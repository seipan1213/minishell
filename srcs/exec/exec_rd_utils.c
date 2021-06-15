
#include "../../includes/exec.h"

void	get_rd_fd(t_redirect *rd)
{
	t_redirect	*rd_now;

	if (!rd)
		return ;
	rd_now = rd;
	while (rd_now)
	{
		if (rd_now->type == RD_INPUT)
		{
			rd_now->fd_io = open(rd_now->filename->str, O_RDONLY);
		}
		else if (rd->type == RD_OUTPUT)
		{
			rd_now->fd_io = open(rd_now->filename->str, O_WRONLY | O_CREAT | O_TRUNC, \
			S_IREAD | S_IWRITE);
		}
		else if (rd_now->type == RD_APPEND_OUTPUT)
		{
			rd_now->fd_io = open(rd_now->filename->str, O_WRONLY | O_CREAT | O_APPEND, \
			S_IREAD | S_IWRITE);
		}
		rd_now = rd_now->next;
	}
}

void	dup_fd(int oldfd, int newfd)
{
	dup2(oldfd, newfd);
	close(oldfd);
}

void	change_rd_fd(t_redirect *rd)
{
	t_redirect	*rd_now;

	if (!rd)
		return ;
	rd_now = rd;
	while (rd_now)
	{
		dup_fd(rd_now->fd_io, rd->fd_file);
		rd_now = rd_now->next;
	}
}
