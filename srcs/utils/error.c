/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 21:16:48 by sehattor          #+#    #+#             */
/*   Updated: 2021/05/15 21:16:48 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	put_error(char *str, char *cmd, int ret)
{
	ft_putstr_fd(ERR_MSH, STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(str, STDERR_FILENO);
	return (ret);
}

void	exit_error(char *str, char *cmd, int ex_num)
{
	ft_putstr_fd(ERR_MSH, STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(str, STDERR_FILENO);
	exit(ex_num);
}
