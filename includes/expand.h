#ifndef EXPANSION_H
# define EXPANSION_H

# include "../libft/libft.h"
# include "env.h"
# include "minishell.h"

char	*expand_env(char *str);
char	*front_join(char *front, char *str);
char	*sub_join(char *front, char *str, int i, int j);
char	*expand_init(int *i, int *j);
char	*sub_quote(char *front, char *str, int *i, int *j);
char	*expand_null(char *str, char *front);
char	*expand(char *str);
int		add_cnt_stop_env(char *str);

#endif