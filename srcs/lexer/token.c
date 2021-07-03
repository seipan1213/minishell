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

t_token	*create_token(t_ttype type, char *str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
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
		back = tokens_last(*tokens);
		back->next = token;
	}
}

void	set_token(t_token **t, char *line, int len, t_ttype type)
{
	char	*str;
	t_token	*token;

	if (len <= 0)
		return ;
	str = ft_substr(line, 0, len);
	if (!str)
		exit_error(MALLOCERR, NULL, 1);
	token = create_token(type, str);
	addb_token(t, token);
}

void	tokenise_init(t_tdata *data, t_token **t, char **line)
{
	if (!line)
		exit_error("", NULL, 1);
	*t = NULL;
	data->i = -1;
	data->line = *line;
}

t_token	*tokenise(char *line)
{
	t_token	*tokens;
	t_tdata	d;

	tokenise_init(&d, &tokens, &line);
	while (ft_isspace(line[++d.i]))
		;
	d.i--;
	while (line[++d.i])
	{
		if (ft_isspace(line[d.i]))
			set_token(&tokens, line + d.i, 1, SP);
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
