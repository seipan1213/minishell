/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:05:22 by kotatabe          #+#    #+#             */
/*   Updated: 2021/07/14 21:18:02 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	sigint_handler(int i)
{
\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	i = 0;
}

void	set_signal(void (*func)(int))
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
	if (signal(SIGQUIT, func) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
}
