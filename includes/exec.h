
#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"

int		exec(astNode *node);
char	**to_wchar(t_token *token);


#endif
