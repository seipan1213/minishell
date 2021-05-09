#ifndef LEXER_H
# define LEXER_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"

typedef enum e_ttype
{
	STR = 0,
	SPACE = 1,
	SQUOTE = 2,
	DQUOTE = 3,
	RDIR = 4,
	RRDIR = 5,
	LDIR = 6,
	LLDIR = 7,
	PIPE = 8,
	DPIPE = 9,
	AND = 10,
	DAND = 11,
	SCOLON = 12,
	DSCOLON = 13,
	ESC = 14,
}				t_ttype;

typedef struct s_tokens
{
	char			*str;
	t_ttype		type;
	struct s_tokens	*next;
}			t_tokens;


#endif