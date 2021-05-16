/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 19:55:18 by sehattor          #+#    #+#             */
/*   Updated: 2021/05/14 19:55:18 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int		main()
{
	char *line;
	t_token *t;

	ft_putstr_fd(MINISHELL, STDERR_FILENO);
	get_next_line(0, &line);
	t = tokenise(line);
	print_tokens(t);
	check_tokens(t);
}