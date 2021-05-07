#ifndef ENV_H
# define ENV_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}			t_env;

void	print_envs(t_env *envs);
void	addb_env(t_env **envs, t_env *env);
t_env	*create_env(char *environ);
t_env *envs_init(void);

#endif