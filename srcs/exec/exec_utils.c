#include "../../includes/exec.h"

int	is_builtin(char **args)
{
	int			i;
	const char	*builtin[] = {"echo", "cd", "pwd", \
								"export", "unset", \
									"env", "exit", NULL};

	i = 0;
	while (builtin[i])
	{
		if (ft_strcmp(args[0], builtin[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	token_lst_len(t_token *token)
{
	t_token		*list;
	char 		*tmp;
	int			token_len;

	token_len = 0;
	list = token;
	while (list)
	{
		if ((tmp = expand(list->str)))
		{
			free(tmp);
			token_len++;
		}
		list = list->next;
	}
	return (token_len);
}

char	**token_to_args(t_token *token)
{
	t_token		*list;
	int			token_len;
	int			i;
	char		*arg_tmp;
	char		**args;

	token_len = token_lst_len(token);
	args = (char **)malloc((token_len + 1) * sizeof(char *));
	args[token_len] = NULL;
	list = token;
	i = 0;
	while (i < token_len)
	{
		if ((arg_tmp = expand(list->str)))
		{
			args[i] = arg_tmp;
			i++;
		}
		list = list->next;
	}
	return (args);
}
