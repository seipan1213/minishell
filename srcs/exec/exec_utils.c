
#include "../../includes/exec.h"

int		is_buildin(char **args)
{
	int			i;
	const char	*buildin[] = {"echo", "cd", "pwd", "export", "unset","env", "exit", NULL};

	i = 0;
	while (buildin[i])
	{
		if (ft_strcmp(args[0], buildin[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int		token_lst_len(t_token *token)
{
	t_token		*list;
	int			token_len = 0;

	list = token;
	while (list)
	{
		list = list->next;
		token_len++;
	}
	return (token_len);
}

char	**token_to_args(t_token *token)
{
	t_token		*list;
	int			token_len = 0;
	int			i;
	char		**args;

	token_len = token_lst_len(token);
	args = (char **)malloc((token_len + 1) * sizeof(char *));
	args[token_len] = NULL;
	list = token;
	i = 0;
	while (i < token_len)
	{
		args[i] = expand(list->str, g_data.envs);
		list = list->next;
		i++;
	}
	return (args);
}

// int main()
// {
// 	char		**wp;
// 	t_token		*tokens;

// 	tokens = NULL;
// 	tokens = token_init();
// 	print_tokens(tokens);
// 	ft_putstr_fd("start\n", 1);
// 	wp = token_to_args(tokens);
// 	printf("%s\n", *wp);
// 	while (*wp)
// 	{
// 		printf("%s\n", *wp);
// 		wp++;
// 	}
// 	return(0);
// }