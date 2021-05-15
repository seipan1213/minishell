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

#include "../../includes/lexer.h"

int	put_error(char *str, int ret)
{
	ft_putstr_fd(MINISHELL, STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (ret);
}

void	exit_error(char *str, int ex_num)
{
	ft_putstr_fd(MINISHELL, STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	exit(ex_num);
}