/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_meta_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 21:10:47 by sehattor          #+#    #+#             */
/*   Updated: 2021/05/15 21:10:47 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	token_lrdct(t_tdata *d, t_token **t)
{
	t_token	*token;
	t_token	*back;

	back = tokens_last(*t);
	if (back && is_strdigit(back->str) && ft_isdigit(*(back->str)))
		back->type = RINT;
	if (!ft_strncmp(d->line + d->i, "<<<", 3))
	{
		token = create_token(LLLDIR, ft_strdup("<<<"));
		addb_token(t, token);
		d->i += 2;
	}
	else if (!ft_strncmp(d->line + d->i, "<<", 2))
	{
		token = create_token(LLDIR, ft_strdup("<<"));
		addb_token(t, token);
		d->i++;
	}
	else
	{
		token = create_token(LDIR, ft_strdup("<"));
		addb_token(t, token);
	}
	d->j = d->i + 1;
}

void	token_rrdct(t_tdata *d, t_token **t)
{
	t_token	*token;
	t_token	*back;

	back = tokens_last(*t);
	if (back && is_strdigit(back->str) && ft_isdigit(*(back->str)))
		back->type = RINT;
	if (!ft_strncmp(d->line + d->i, ">>", 2))
	{
		token = create_token(RRDIR, ft_strdup(">>"));
		addb_token(t, token);
		d->i++;
	}
	else
	{
		token = create_token(RDIR, ft_strdup(">"));
		addb_token(t, token);
	}
	d->j = d->i + 1;
}

void	token_esc(t_tdata *d, t_token **t)
{
	t_token	*token;

	token = create_token(ESCAPE, ft_strdup("\\"));
	addb_token(t, token);
	d->j = d->i + 1;
}

void	token_semi(t_tdata *d, t_token **t)
{
	t_token	*token;

	if (!ft_strncmp(d->line + d->i, ";;", 2))
	{
		token = create_token(DSCOLON, ft_strdup(";;"));
		addb_token(t, token);
		d->i++;
	}
	else
	{
		token = create_token(SCOLON, ft_strdup(";"));
		addb_token(t, token);
	}
	d->j = d->i + 1;
}
