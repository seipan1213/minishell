#ifndef EXPANSION_H
# define EXPANSION_H

# include "../libft/libft.h"
# include "env.h"

char	*expand(char *str, t_env *envs);
char	*front_join(char *front, char *str);
char	*expand_str(char *str, t_env *envs);

#endif