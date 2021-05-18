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

void	token_join(t_token *t)
{
	t_token	*tmp;
	char	*str;

	str = ft_strjoin(t->str, t->next->str);
	free(t->str);
	t->str = str;
	tmp = t->next;
	t->next = t->next->next;
	free(tmp->str);
	free(tmp);
}

void	lexer_tokens(t_token *t)
{
	while(t && t->next)
	{
		while (t->next && t->type == t->next->type && t->type == STR)
			token_join(t);
		t = t->next;
	}
}

int		main()
{
	char *line;
	t_token *t;

	ft_putstr_fd(MINISHELL, STDERR_FILENO);
	get_next_line(0, &line);
	t = tokenise(line);
	check_tokens(t);
	lexer_tokens(t);
	print_tokens(t);
}