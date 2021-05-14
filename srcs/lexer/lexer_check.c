/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 19:55:21 by sehattor          #+#    #+#             */
/*   Updated: 2021/05/14 19:55:21 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	put_error(char *str, int ret)
{
	ft_putstr_fd(MINISHELL, STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (ret);
}

int	is_metatype(int i)
{
	if (i == PIPE || i == DPIPE || i == AND || i == DAND
		|| i == SCOLON || i == DSCOLON)
		return (1);
	return (0);
}

int	is_rdcttype(int i)
{
	if (i == RDIR || i == RRDIR || i == LDIR || i == LLDIR || i == LLLDIR)
		return (1);
	return (0);
}

int	check_tokens(t_token *t)
{
	t_ttype	pre_type;
	int		status;

	status = 0;
	pre_type = -1;
	if (t->type == SPACE)
		t = t->next;
	if (is_metatype(t->type))
		return (put_error(SYNTAXERR, -1));
	while (t->next)
	{
		while (t->type == SPACE && t->next)
			t = t->next;
		if (is_metatype(t->type) && is_rdcttype(pre_type))
			return (put_error(SYNTAXERR, -1));
		if (is_metatype(pre_type) && is_rdcttype(t->type))
			return (put_error(SYNTAXERR, -1));
		if (is_metatype(t->type) && is_metatype(pre_type))
			return (put_error(SYNTAXERR, -1));
		if (is_rdcttype(t->type) && is_rdcttype(pre_type))
			return (put_error(SYNTAXERR, -1));
		if (t->type == DSCOLON)
			return (put_error(SYNTAXERR, -1));
		pre_type = t->type;
		if (t->next)
			t = t->next;
	}
	if (is_rdcttype(t->type))
		return (put_error(SYNTAXERR, -1));
	return (0);
}

int	main()
{
	char *line;
	t_token *t;

	ft_putstr_fd(MINISHELL, STDERR_FILENO);
	get_next_line(0, &line);
	t = tokenise(line);
	print_tokens(t);
	check_tokens(t);
}