/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 21:08:09 by sehattor          #+#    #+#             */
/*   Updated: 2021/05/15 21:08:09 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include "../libft/libft.h"
# include "minishell.h"

int		is_strdigit(char *str);
void	set_signal(void (*func)(int));
int		put_error(char *str, char *cmd, int ret);
void	exit_error(char *str, char *cmd, int ex_num);
int		init_data(void);
#endif