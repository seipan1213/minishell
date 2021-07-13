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

# include "const.h"
# include "../libft/libft.h"
# include "minishell.h"

typedef struct s_env	t_env;

int		is_strdigit(char *str);
void	set_signal(void (*func)(int));
int		put_error(char *str, char *cmd, int ret);
void	exit_error(char *str, char *cmd, int ex_num);
void	init_data(void);
void	shlvl_add(t_env *envs);
void	shlvl_change(t_env *shlvl);
void	shlvl_init(void);
char	*strjoin_free(char *front, char *back);
void	signal_handler(int i);

#endif