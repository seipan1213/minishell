/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_meta_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 21:18:27 by sehattor          #+#    #+#             */
/*   Updated: 2021/05/15 21:18:27 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	token_meta(t_tdata *d, t_token **t)
{
	if (d->j != d->i)
		set_token(t, d->line + d->j, d->i - d->j, STR);
	if (d->line[d->i] == '\'')
		token_squote(d, t);
	else if (d->line[d->i] == '\"')
		token_dquote(d, t);
	else if (d->line[d->i] == '&')
		token_and(d, t);
	else if (d->line[d->i] == '|')
		token_pipe(d, t);
	else if (d->line[d->i] == '<')
		token_lrdct(d, t);
	else if (d->line[d->i] == '>')
		token_rrdct(d, t);
	else if (d->line[d->i] == '\\')
		token_esc(d, t);
	else if (d->line[d->i] == ';')
		token_semi(d, t);
}

void	token_squote(t_tdata *d, t_token **t)
{
	t_token	*token;
	char		*str;
	char		*tmp;

	d->j = d->i;
	while (d->line[++d->i] != '\'' && d->line[d->i])
		;
	str = ft_substr(d->line, d->j, d->i - d->j);
	if (d->line[d->i] == '\'')
	{
		tmp = ft_strjoin(str, "\'");
		free(str);
	}
	else
	{
		free(str);
		exit_error(SYNTAXERR, 1);
	}
	token = create_token(STR, tmp);
	addb_token(t, token);
	d->j = d->i + 1;
}

void	token_dquote(t_tdata *d, t_token **t)
{
	t_token	*token;
	char		*str;
	char		*tmp;

	d->j = d->i;
	while (d->line[++d->i] != '\"' && d->line[d->i])
		;
	str = ft_substr(d->line, d->j, d->i - d->j);
	if (d->line[d->i] == '\"')
	{
		tmp = ft_strjoin(str, "\"");
		free(str);
	}
	else
	{
		free(str);
		exit_error(SYNTAXERR, 1);
	}
	token = create_token(STR, tmp);
	addb_token(t, token);
	d->j = d->i + 1;
}

void	token_and(t_tdata *d, t_token **t)
{
	t_token	*token;

	if (!ft_strncmp(d->line + d->i, "&&", 2))
	{
		token = create_token(DAND, "&&");
		addb_token(t, token);
		d->i++;
	}
	else
	{
		token = create_token(AND, "&");
		addb_token(t, token);
	}
	d->j = d->i + 1;
}

void	token_pipe(t_tdata *d, t_token **t)
{
	t_token	*token;

	if (!ft_strncmp(d->line + d->i, "||", 2))
	{
		token = create_token(DPIPE, "||");
		addb_token(t, token);
		d->i++;
	}
	else
	{
		token = create_token(PIPE, "|");
		addb_token(t, token);
	}
	d->j = d->i + 1;
}
