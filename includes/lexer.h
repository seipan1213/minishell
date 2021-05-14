#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

# define MINISHELL "MINISHELL$ "

typedef enum e_ttype
{
	STR = 0,
	RDIR = 1,
	RRDIR = 2,
	LDIR = 3,
	LLDIR = 4,
	LLLDIR = 5,
	SPACE = 6,
	SQUOTE = 7,
	DQUOTE = 8,
	PIPE = 9,
	DPIPE = 10,
	AND = 11,
	DAND = 12,
	SCOLON = 13,
	DSCOLON = 14,
	DOLL = 15,
	ESC = 16,
	SSTR = 17,
	RINT = 18,
}				t_ttype;

typedef struct s_token
{
	char			*str;
	t_ttype		type;
	struct s_token	*next;
}			t_token;

typedef struct s_tdata
{
	char			*line;
	int			i;
	int			j;
	int			status;
}			t_tdata;


t_token *create_token(t_ttype type, char *str);

void	addb_token(t_token **tokens, t_token *token);

void	token_squote(t_tdata *d, t_token **t);

void	token_meta(t_tdata *d, t_token **t);

void	tokenise_init(t_tdata *data, t_token **t, char **line);

t_token	*tokenise(char *line);

int		is_meta(char c);

#endif