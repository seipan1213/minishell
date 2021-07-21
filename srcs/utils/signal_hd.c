/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 18:43:46 by kotatabe          #+#    #+#             */
/*   Updated: 2021/07/21 21:13:39 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	sigquit_hd_handler(int sig_num)
{
	(void)sig_num;
	ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
}

void	sigint_hd_handler(int sig_num)
{
	ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
	g_data.status = 128 + sig_num;
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
	unlink(HD_TMPFILE);
	kill(0, SIGINT);
}

void	set_heredoc_sig(void)
{
	if (signal(SIGINT, sigint_hd_handler) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
	if (signal(SIGQUIT, sigquit_hd_handler) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
}
