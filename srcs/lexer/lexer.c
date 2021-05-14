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

void	exit_error(char *str, int ex_num)
{
	ft_putstr_fd(MINISHELL, STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	exit(ex_num);
}

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

void	token_squote(t_tdata *d, t_token **t)
{
	t_token	*token;

	token = create_token(SQUOTE, "\'");
	addb_token(t, token);
	d->j = d->i + 1;
	while (d->line[++d->i] != '\'' && d->line[d->i])
		;
	set_token(t, d->line + d->j, d->i - d->j, STR);
	if (d->line[d->i] == '\'')
	{
		token = create_token(SQUOTE, "\'");
		addb_token(t, token);
	}
	d->j = d->i + 1;
}

void	token_dquote(t_tdata *d, t_token **t)
{
	t_token	*token;

	token = create_token(DQUOTE, "\"");
	addb_token(t, token);
	d->j = d->i + 1;
	while (d->line[++d->i] != '\"' && d->line[d->i])
		;
	set_token(t, d->line + d->j, d->i - d->j, STR);
	if (d->line[d->i] == '\"')
	{
		token = create_token(DQUOTE, "\"");
		addb_token(t, token);
	}
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

void	token_lrdct(t_tdata *d, t_token **t)
{
	t_token	*token;

	if (!ft_strncmp(d->line + d->i, "<<<", 3))
	{
		token = create_token(LLLDIR, "<<<");
		addb_token(t, token);
		d->i+=2;
	}
	else if (!ft_strncmp(d->line + d->i, "<<", 2))
	{
		token = create_token(LLDIR, "<<");
		addb_token(t, token);
		d->i++;
	}
	else
	{
		token = create_token(LDIR, "<");
		addb_token(t, token);
	}
	d->j = d->i + 1;
}

void	token_rrdct(t_tdata *d, t_token **t)
{
	t_token	*token;

	if (!ft_strncmp(d->line + d->i, ">>", 2))
	{
		token = create_token(RRDIR, ">>");
		addb_token(t, token);
		d->i++;
	}
	else
	{
		token = create_token(RDIR, ">");
		addb_token(t, token);
	}
	d->j = d->i + 1;
}

void	token_esc(t_tdata *d, t_token **t)
{
	t_token	*token;


	token = create_token(ESC, "\\");
	addb_token(t, token);
	d->j = d->i + 1;
}

void	token_semi(t_tdata *d, t_token **t)
{
	t_token	*token;

	if (!ft_strncmp(d->line + d->i, ";;", 2))
	{
		token = create_token(DSCOLON, ";;");
		addb_token(t, token);
		d->i++;
	}
	else
	{
		token = create_token(SCOLON, ";");
		addb_token(t, token);
	}
	d->j = d->i + 1;
}

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

int		is_meta(char c)
{
	if (c == '\'' || c == '\"' || c == '<' || c == '>' ||
		c == '&' || c == '|' || c == '\\' || c == ';')
		return (1);
	return (0);
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

void	print_tokens(t_token *t)
{
	while (t)
	{
		printf("%s %d\n", t->str, t->type);
		t = t->next;
	}
}