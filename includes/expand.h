#ifndef EXPAND_H
# define EXPAND_H

# include "const.h"
# include "../libft/libft.h"
# include "env.h"
# include "minishell.h"

char	*expand_env(char *str);
char	*front_join(char *front, char *str);
char	*sub_join(char *front, char *str, int i, int j);
char	*expand_init(int *i, int *j);
char	*expand_sub(char *front, char *str, int *i, int *j);
char	*expand_null(char *str, char *front);
char	*expand(char *str);
int		add_cnt_stop_env(char *str);
char	*expand_str(char *str);
char	*expand_sub_sp(char *front, char *str, int *i, int *j);

#endif