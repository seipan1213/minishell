#ifndef EXPAND_H
# define EXPAND_H

# include "const.h"
# include "../libft/libft.h"
# include "lexer.h"
# include "env.h"
# include "minishell.h"

char	*expand_env(char *str);
char	*front_join(char *front, char *str);
char	*sub_join(char *front, char *str, int i, int j);
char	*expand_init(t_token **lst, int *i, int *j);
void	expand_sub(t_token **lst, char *str, int *i, int *j);
void	expand_null(char *str, char **front);
void	expand(t_token **lst);
int		add_cnt_stop_env(char *str);
void	expand_str(t_token **lst, char *str, int flag);
void	expand_sub_sp(t_token **lst, char *str, int *i, int *j);
void	expand_div(t_token **lst, char *str, int flag);
void	addnext_token(t_token **lst, t_token *t);
void	token_next_set(t_token **lst);

#endif