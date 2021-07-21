/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 18:43:46 by kotatabe          #+#    #+#             */
/*   Updated: 2021/07/21 18:45:32 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	sig_hd_handler(int sig_num)
{
	ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
	g_data.status = 128 + sig_num;
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
	unlink(HD_TMPFILE); // tmpfile in child ps // cat << eof + ctrlC
	kill(0, SIGINT);
}

void	set_heredoc_sig(void)
{
	if (signal(SIGINT, sig_hd_handler) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
}
