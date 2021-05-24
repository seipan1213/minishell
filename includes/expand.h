#ifndef EXPANSION_H
# define EXPANSION_H

# include "../libft/libft.h"
# include "env.h"

char	*expand_env(char *str, t_env *envs);
char	*front_join(char *front, char *str);
char	*sub_join(char *front, char *str, int i, int j);
char	*expand_init(int *i, int *j);
char	*sub_quote(char *front, char *str, int *i, int *j);
char	*expand(char *str, t_env *envs);

#endif