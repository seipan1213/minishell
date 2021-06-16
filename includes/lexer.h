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

#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "minishell.h"
# include "utils.h"

typedef enum e_ttype
{
	STR = 0,
	RDIR = 1,
	RRDIR = 2,
	LDIR = 3,
	LLDIR = 4,
	LLLDIR = 5,
	SP = 6,
	SQUOTE = 7,
	DQUOTE = 8,
	PIPE = 9,
	DPIPE = 10,
	AND = 11,
	DAND = 12,
	SCOLON = 13,
	DSCOLON = 14,
	DOLL = 15,
	ESCAPE = 16,
	SSTR = 17,
	RINT = 18,
}				t_ttype;

typedef struct s_token
{
	char			*str;
	t_ttype			type;
	struct s_token	*next;
}			t_token;

typedef struct s_tdata
{
	char			*line;
	int			i;
	int			j;
	int			status;
}			t_tdata;

t_token	*create_token(t_ttype type, char *str);
void	addb_token(t_token **tokens, t_token *token);
void	set_token(t_token **t, char *line, int len, t_ttype type);
void	token_squote(t_tdata *d, t_token **t);
void	token_dquote(t_tdata *d, t_token **t);
void	token_and(t_tdata *d, t_token **t);
void	token_pipe(t_tdata *d, t_token **t);
void	token_lrdct(t_tdata *d, t_token **t);
void	token_rrdct(t_tdata *d, t_token **t);
void	token_esc(t_tdata *d, t_token **t);
void	token_semi(t_tdata *d, t_token **t);
void	token_meta(t_tdata *d, t_token **t);
int		is_meta(char c);
t_token	*tokens_last(t_token *t);
void	tokenise_init(t_tdata *data, t_token **t, char **line);
t_token	*tokenise(char *line);
void	print_tokens(t_token *t);
int		is_metatype(int i);
int		is_rdcttype(int i);
void	check_qoute(int *flag, int type);
int		check_syntax(t_token *t);
int		check_avoid(t_token *t);
int		check_tokens(t_token *t);
int		lexer_str(t_token *t);
void	lexer_space(t_token *t);
int		lexer_tokens(t_token *t);
t_token	*lexer(char *line);

#endif