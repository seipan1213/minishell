#ifndef ENV_H
# define ENV_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}			t_env;

void	print_envs(t_env *envs);
void	addb_env(t_env **envs, t_env *env);
t_env	*create_env(char *environ);
t_env	*envs_init(void);
void 	free_env(t_env *env);
void 	free_envs(t_env *env);
t_env	*envlast(t_env *env);
t_env	*search_env(char *key, t_env *env);
int		ft_strcmp(char *s1, char *s2);
int		del_env(char *delKey, t_env **env);
int		envs_len(t_env *envs);
char	**environ_gen(t_env *envs);

#endif