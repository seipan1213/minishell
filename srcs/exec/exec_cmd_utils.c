#include "../../includes/exec.h"

int	dup_pipe(t_pipe_status *p_stat, int old_pipe_fd[], int new_pipe_fd[])
{
	if (*p_stat == PIPE_RD_ONLY || *p_stat == PIPE_RD_WR)
	{
		if (close(old_pipe_fd[PIPE_IN]) < 0 ||\
				dup2(old_pipe_fd[PIPE_OUT], STDIN_FILENO) < 0 ||\
				close(old_pipe_fd[PIPE_OUT]) < 0)
			return (FALSE);
	}
	if (*p_stat == PIPE_WR_ONLY || *p_stat == PIPE_RD_WR)
	{
		if (close(new_pipe_fd[PIPE_OUT]) < 0 ||\
				dup2(new_pipe_fd[PIPE_IN], STDOUT_FILENO) < 0 ||\
				close(new_pipe_fd[PIPE_IN]) < 0)
			return (FALSE);
	}
	return (TRUE);
}

int	pass_pipe(t_pipe_status *p_stat, \
					int old_pipe_fd[], int new_pipe_fd[])
{
	if (*p_stat == PIPE_RD_ONLY || *p_stat == PIPE_RD_WR)
	{
		if (close(old_pipe_fd[PIPE_IN]) < 0 ||\
				 close(old_pipe_fd[PIPE_OUT]) < 0)
			return (FALSE);
	}
	if (*p_stat == PIPE_WR_ONLY || *p_stat == PIPE_RD_WR)
	{
		old_pipe_fd[PIPE_IN] = new_pipe_fd[PIPE_IN];
		old_pipe_fd[PIPE_OUT] = new_pipe_fd[PIPE_OUT];
	}
	return (TRUE);
}

void	get_next_p_stat(t_command *cmd, t_pipe_status *p_stat)
{
	t_command	*now;

	now = cmd;
	if (*p_stat == NO_PIPE)
		return ;
	if (!now->next)
		return ;
	*p_stat = PIPE_RD_ONLY;
	if (now->next->next)
	{
		*p_stat = PIPE_RD_WR;
	}
}

static void	handler_singal(int status, int is_sig)
{
	if (WIFEXITED(status))
			g_data.status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_data.status = WTERMSIG(status);
		if (g_data.status == SIGQUIT)
			ft_putendl_fd("Quit: 3", STDERR_FILENO);
		g_data.status += 128;
	}
	if (is_sig)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	wait_commands(t_command *cmd)
{
	int	status;
	int	is_sig;
	int	is_cmd;

	is_sig = 0;
	is_cmd = 0;
	while (cmd)
	{
		if (cmd->pid != NO_PID)
		{
			is_cmd = 1;
			if (waitpid(cmd->pid, &status, 0) < 0)
			{
				ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd("\n", 2);
				exit(errno);
			}
			if (WIFSIGNALED(status))
				is_sig = 1;
		}
		cmd = cmd->next;
	}
	if (is_cmd)
		handler_singal(status, is_sig);
}
