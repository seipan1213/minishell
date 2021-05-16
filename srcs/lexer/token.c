/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 21:13:20 by sehattor          #+#    #+#             */
/*   Updated: 2021/05/15 21:13:20 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token *create_token(t_ttype type, char *str)
{
	t_token *token;

	if (!(token = malloc(sizeof(token))))
		return (NULL);
	token->type = type;
	token->str = str;
	token->next = NULL;
	return (token);
}

void	addb_token(t_token **tokens, t_token *token)
{
	t_token	*back;
	if (!tokens || !token)
		return ;
	if (!*tokens)
		*tokens = token;
	else
	{
		back = *tokens;
		while (back->next)
			back = back->next;
		back->next = token;
	}
}

void	set_token(t_token **t, char *line, int len, t_ttype type)
{
	char *str;
	t_token *token;

	if (len <= 0)
		return ;
	if (!(str = ft_substr(line, 0, len)))
		exit_error("malloc error", 1);
	token = create_token(type, str);
	addb_token(t, token);
}

void	tokenise_init(t_tdata *data, t_token **t, char **line)
{
	if (!line)
		exit_error("", 1);
	*t = NULL;
	data->i = -1;
	data->line = *line;
}

t_token	*tokenise(char *line)
{
	t_token	*tokens;
	t_tdata	d;
	t_token	*token;
	char		*tmp;

	tokenise_init(&d, &tokens, &line);
	while (line[++d.i])
	{
		if (ft_isspace(line[d.i]))
			set_token(&tokens, line + d.i, 1, SPACE);
		while (ft_isspace(line[d.i]))
			d.i++;
		d.j = d.i;
		d.i--;
		while (!ft_isspace(line[++d.i]) && line[d.i])
			if (is_meta(line[d.i]))
				token_meta(&d, &tokens);
		if (d.j != d.i)
			set_token(&tokens, line + d.j, d.i - d.j, STR);
		d.i--;
	}
	return (tokens);
}