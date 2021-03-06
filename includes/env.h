#ifndef ENV_H
# define ENV_H

# include "const.h"
# include "../libft/libft.h"
# include "minishell.h"
# include "utils.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}			t_env;

void	addb_env(t_env **envs, t_env *env);
t_env	*str_to_env(char *environ);
t_env	*envs_init(void);
void	free_env(t_env *env);
void	free_envs(t_env *env);
t_env	*envlast(t_env *env);
t_env	*search_env(char *key, t_env *env);
int		update_env(char *key, char *newVal, t_env **envs);
int		ft_strcmp(const char *s1, const char *s2);
int		del_env(char *delKey, t_env **env);
int		envs_len(t_env *envs);
char	**environ_gen(t_env *envs);
void	sort_envs(t_env *envs);
void	sort_str(char **envs);
char	*get_env(char *key, t_env *envs);
t_env	*make_env(char *name, char *value);
t_env	*create_env(char *key, char *newVal);

#endif